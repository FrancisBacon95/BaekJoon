#include <iostream>
#define _SHARK 0
#define _SMELL 1
#define EMPTY 0
using namespace std;

int N, M, k, num, ret;
int board    [2][20][20];
int tmp_board[2][20][20];
int d_row[5] = {0, -1, 1,  0, 0};
int d_col[5] = {0,  0, 0, -1, 1};

struct SHARK{
    int  row, col, dir;
    int  prior[5][4] = {0, };
    bool death       = false;
};
SHARK shark[401];

void init(){
    cin >> N >> M >> k;
    num = M;
    for (int r=0; r < N; r++){
        for (int c=0; c < N; c++){
            cin >> board[_SHARK][r][c];
            if (board[_SHARK][r][c] > 0){
                //shark row, col 초기화
                int idx = board[_SHARK][r][c];
                shark[idx].row = r;
                shark[idx].col = c;
                //smell 뿌리기
                board[_SMELL][r][c] = k;
            }
        }
    }
    //shark dir 초기화
    for (int idx = 1; idx <= M; idx++) cin >> shark[idx].dir;

    //shark pior 초기화
    for (int idx = 1; idx <= M; idx++){
        //각각의 바라보는 방향(1~4)
        for (int d = 1; d <= 4; d++){
            //바라보는 방향에 따른 다음 방향 우선순위
            for (int p = 0; p < 4; p++){
                cin >> shark[idx].prior[d][p];
            }
        }
    }
}

void smell_dec(){
    for (int r=0; r<N; r++){
        for (int c=0; c<N; c++){
            //board에서 shark였으면, smell-1과 idx를 tmp_board로 복사
            if (board    [_SHARK][r][c] != EMPTY) {
                tmp_board[_SHARK][r][c] = board[_SHARK][r][c]  ;
                tmp_board[_SMELL][r][c] = board[_SMELL][r][c]-1;
            }
            //복사 후, smell이 없으면 자리 제거
            if (tmp_board[_SMELL][r][c] == 0) tmp_board[_SHARK][r][c] = EMPTY;
        }
    }
}

void shark_move(int idx){
    // 죽은 상어 건너뛰기
    if (shark[idx].death == true) return;
    int c_dir = shark[idx].dir;
    int c_row = shark[idx].row;
    int c_col = shark[idx].col;

    int noWHERE = 0;

    for (int d = 0; d < 4; d++){
        int n_dir = shark[idx].prior[c_dir][d];
        int n_row = c_row + d_row[n_dir];
        int n_col = c_col + d_col[n_dir];

        //(1) 범위를 벗어난 경우
        if (n_row < 0 || n_row >= N || n_col < 0 || n_col >= N) {
            noWHERE++;
            continue;
        }
        //(2) [이전 상태 바라보기] 뭔가 있는 경우
        if (board[_SHARK][n_row][n_col] != EMPTY){
                noWHERE++;
                continue;
        }
        shark[idx].row = n_row;
        shark[idx].col = n_col;
        shark[idx].dir = n_dir;
        // [이전 상태] 뭔가 없어서 이동 but [이후 상태] 쎈 놈이 동시에 옴
        if (board[_SHARK][n_row][n_col] == EMPTY && tmp_board[_SHARK][n_row][n_col] != EMPTY) {
            shark[idx].death = true;
            num--;
            return;
        }
        tmp_board[_SHARK][n_row][n_col] = idx;
        tmp_board[_SMELL][n_row][n_col] = k  ;
        return;
    }

    if (noWHERE == 4){
        for (int d = 0; d < 4; d++){
            int n_dir = shark[idx].prior[c_dir][d];
            int n_row = c_row + d_row[n_dir];
            int n_col = c_col + d_col[n_dir];

            if (n_row < 0 || n_row >= N || n_col < 0 || n_col >= N || board[_SHARK][n_row][n_col] != idx) continue;
            shark[idx].row = n_row;
            shark[idx].col = n_col;
            shark[idx].dir = n_dir;
            tmp_board[_SHARK][n_row][n_col] = idx;
            tmp_board[_SMELL][n_row][n_col] = k  ;
            return;
        }
    }
}

int main()
{
    init();

    while(num > 1){
        if (ret >= 1000){
            ret = -1;
            break;
        }
        smell_dec();
        for (int idx = 1; idx <= M; idx++){
            //smell_dec(idx);
            shark_move(idx);
        }

        ///COPY: n_board -> board
        for (int r=0; r<N; r++){
            for (int c=0; c<N; c++){
                board    [_SHARK][r][c] = tmp_board[_SHARK][r][c];
                board    [_SMELL][r][c] = tmp_board[_SMELL][r][c];
                tmp_board[_SHARK][r][c] = 0                      ;
                tmp_board[_SMELL][r][c] = 0                      ;
            }
        }
        ret++;
    }
    cout << ret;
    return 0;
}
