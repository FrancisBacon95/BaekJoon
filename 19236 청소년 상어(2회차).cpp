#include <iostream>
#include <stack>
using namespace std;

const int d_row[9] = {-1, -1, -1,  0, 1, 1, 1, 0, -1};
const int d_col[9] = { 1,  0, -1, -1, -1, 0, 1, 1, 1};
const int shark_idx = 99;

const int ROW = 0;
const int COL = 1;
const int DIR = 2;
struct SHARK{
    int row = 0, col = 0, dir;
    int sum = 0;
};

struct FISH{
    int fish[17][3] = {0, };
};

SHARK init_shark;
FISH  init_fish ;

stack<SHARK> shark_stack;
stack<FISH > fish_stack ;


void init(){
    for (int r = 0; r < 4; r++){
        for (int c =0; c < 4; c++){
            int i, d; cin >> i >> d;
            init_fish.fish[i][ROW] = r;
            init_fish.fish[i][COL] = c;
            init_fish.fish[i][DIR] = d;
        }
    }
}

int main()
{
    init();
    int ret = 0;
    ///1. 초기화
    int tmp_board[4][4] = {0, };
    for (int i = 1; i <= 16; i++){
        if (init_fish.fish[i][ROW] == 0 && init_fish.fish[i][COL] == 0){
            init_shark.dir = init_fish.fish[i][DIR];
            init_fish.fish[i][DIR] = -1;
            init_shark.sum += i;
        }
        tmp_board[init_fish.fish[i][ROW]][init_fish.fish[i][COL]] = i;
    }
    tmp_board[0][0] = shark_idx;


    ///2. fish move
    for (int i = 1; i <= 16; i++){
        if (init_fish.fish[i][DIR] == -1) continue;
        int c_row_f = init_fish.fish[i][ROW];
        int c_col_f = init_fish.fish[i][COL];
        int c_dir_f = init_fish.fish[i][DIR];

        ///3. fish rotate
        for (int d = 0; d < 8; d++){
            int n_dir_f = (c_dir_f + d) % 8;
            if (n_dir_f == 0) n_dir_f = 8;
            int n_row_f = c_row_f + d_row[n_dir_f];
            int n_col_f = c_col_f + d_col[n_dir_f];
            if (n_row_f < 0 || n_row_f >= 4 || n_col_f < 0 || n_col_f >= 4 || tmp_board[n_row_f][n_col_f] == shark_idx) continue;

            ///4. fish change
            int tmp_idx = tmp_board[n_row_f][n_col_f];
            tmp_board[n_row_f][n_col_f] = i;
            tmp_board[c_row_f][c_col_f] = tmp_idx;

            //(2) 물고기 정보 수정
            init_fish.fish[i      ][ROW] = n_row_f;
            init_fish.fish[i      ][COL] = n_col_f;
            init_fish.fish[i      ][DIR] = n_dir_f;

            init_fish.fish[tmp_idx][ROW] = c_row_f;
            init_fish.fish[tmp_idx][COL] = c_col_f;
            break;
        }
    }
    shark_stack.push(init_shark);
    fish_stack .push(init_fish );


    ///2. SOLUTION
    while(!shark_stack.empty()){
        SHARK c_shark = shark_stack.top(); shark_stack.pop();
        FISH  c_fish  = fish_stack .top(); fish_stack .pop();

        for (int len = 1; len <= 3; len++){
            SHARK n_shark = c_shark;
            FISH  n_fish  = c_fish ;
            int n_board[15][15] = {0, };
            //(1) shark -> board
            int c_row = n_shark.row;
            int c_col = n_shark.col;
            int c_dir = n_shark.dir;
            n_board[c_row][c_col] = shark_idx;

            //(2)fish -> board
            for (int i = 1; i <= 16; i++){
                if (n_fish.fish[i][DIR] == -1) continue;
                int tmp_r = n_fish.fish[i][ROW];
                int tmp_c = n_fish.fish[i][COL];
                n_board[tmp_r][tmp_c] = i;
            }

            ///1. shark move
            int n_row = c_row + d_row[c_dir]*len;
            int n_col = c_col + d_col[c_dir]*len;

            //(1) 범위 벗어나면 그냥 break
            if (n_row < 0 || n_row >= 4 || n_col < 0 || n_col >= 4) {
                if (n_shark.sum > ret) ret = n_shark.sum;
                break;
            }
            //(2) 물고기가 없으면 continue
            if (n_board[n_row][n_col] == 0) {
                if (n_shark.sum > ret) ret = n_shark.sum;
                continue;
            }
            //(3) 상어/물고기 정보 수정
            int n_fish_num = n_board[n_row][n_col];
            n_shark.row = n_row;
            n_shark.col = n_col;
            n_shark.dir = n_fish.fish[n_fish_num][DIR];
            n_shark.sum += n_fish_num;
            n_fish.fish[n_fish_num][DIR] = -1;

            //(4) 보드 정보 수정
            n_board[n_row][n_col] = shark_idx;
            n_board[c_row][c_col] = 0;

            ///2. fish move
            for (int i = 1; i <= 16; i++){
                if (n_fish.fish[i][DIR] == -1) continue;
                int c_row_f = n_fish.fish[i][ROW];
                int c_col_f = n_fish.fish[i][COL];
                int c_dir_f = n_fish.fish[i][DIR];

                ///3. fish rotate
                for (int d = 0; d < 8; d++){
                    int n_dir_f = (c_dir_f + d) % 8;
                    if (n_dir_f == 0) n_dir_f = 8;
                    int n_row_f = c_row_f + d_row[n_dir_f];
                    int n_col_f = c_col_f + d_col[n_dir_f];
                    if (n_row_f < 0 || n_row_f >= 4 || n_col_f < 0 || n_col_f >= 4 || n_board[n_row_f][n_col_f] == shark_idx) continue;

                    ///4. fish change
                    int tmp_idx = n_board[n_row_f][n_col_f];
                    n_board[n_row_f][n_col_f] = i;
                    n_board[c_row_f][c_col_f] = tmp_idx;

                    //(2) 물고기 정보 수정
                    n_fish.fish[i      ][ROW] = n_row_f;
                    n_fish.fish[i      ][COL] = n_col_f;
                    n_fish.fish[i      ][DIR] = n_dir_f;

                    n_fish.fish[tmp_idx][ROW] = c_row_f;
                    n_fish.fish[tmp_idx][COL] = c_col_f;
                    break;
                }
            }
            shark_stack.push(n_shark);
            fish_stack .push(n_fish );
        }
    }
    cout << ret;
    return 0;
}
