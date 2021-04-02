#include <iostream>
using namespace std;
const int UPPER = 0;
const int UNDER = 1;
const int d_row[4] = {0,  0, 1, -1};
const int d_col[4] = {1, -1, 0,  0};
int R, C, T;
int board  [50][50] = {0, };
int n_board[50][50] = {0, };
int robot_row[2] = {0,};

void debug(int i){
    if (i == 0){
        cout<<endl;
        for (int r = 0; r < R; r++){
            for (int c = 0; c < C; c++){
                cout << board[r][c] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
    else{
        cout << endl;
        for (int r = 0; r < R; r++){
            for (int c = 0; c < C; c++){
                cout << n_board[r][c] << " ";
            }
            cout << endl;
        }
        cout << endl;

    }
}
void init(){
    cin >> R >> C >> T;
    int robot_idx = 0;
    for (int r = 0; r < R; r++){
        for (int c = 0; c < C; c++){
            cin >> board[r][c];
            if (board[r][c] == -1) robot_row[robot_idx++] = r;
        }
    }
}
void n_board_init(){
    for (int r = 0; r < R; r++){
        for (int c = 0; c < C; c++){
            n_board[r][c] = 0;
        }
    }
}

void to_board(){
    for (int r = 0; r < R; r++){
        for (int c = 0; c < C; c++){
            board  [r][c] = n_board[r][c];
            n_board[r][c] =   board[r][c];
        }
    }
}
int answer(){
    int ret = 0;
    for (int r = 0; r < R; r++){
        for (int c = 0; c < C; c++){
            if (board[r][c] < 0) continue;
            ret += board[r][c];
        }
    }
    return ret;
}

void diffuse(){
    for (int r = 0; r < R; r++){
        for(int c = 0; c < C; c++){
            //(1)미세먼지 없거나 공기청정기: CONTINUE
            if (board[r][c] <= 0) continue;

            //(2) 미세먼지 확산 범위 확인: board(확인)
            int c_dust = board[r][c];
            int diffuse_cnt = 0;
            for (int d = 0; d < 4; d++){
                int n_row = r + d_row[d];
                int n_col = c + d_col[d];
                //공기청정기인지 확인
                if (board[n_row][n_col] == -1) continue;
                //범위 벗어났는지 확인
                if (n_row < 0 || n_row >= R || n_col < 0 || n_col >= C) continue;
                diffuse_cnt++;
            }
            //(3) 미세먼지 확산 처리: board -> n_board
            int diffuse_dust = c_dust / 5;
            int remain_dust  = c_dust - (diffuse_dust)*(diffuse_cnt);
            for (int d = 0; d < 4; d++){
                int n_row = r + d_row[d];
                int n_col = c + d_col[d];
                //공기청정기인지 확인
                if (board[n_row][n_col] == -1) continue;
                //범위 벗어났는지 확인
                if (n_row < 0 || n_row >= R || n_col < 0 || n_col >= C) continue;
                //n_board에 확산되는 곳 처리
                n_board[n_row][n_col] += diffuse_dust;
            }
            //n_board에 확산하는 곳 처리
            n_board[    r][    c] += remain_dust ;
        }
    }
}

void go_R(int _row, int start_c, int final_c, int _UD){
    if      (_UD == UPPER) n_board[_row-1][final_c] = board[_row][final_c];
    else if (_UD == UNDER) n_board[_row+1][final_c] = board[_row][final_c];

    n_board[_row][start_c] = 0;
    for (int c = start_c; c < final_c; c++) n_board[_row][c+1] = board[_row][c];
}

void go_L(int _row, int start_c, int final_c, int _UD){
    if      (_UD == UPPER) n_board[_row+1][final_c] = board[_row][final_c];
    else if (_UD == UNDER) n_board[_row-1][final_c] = board[_row][final_c];

    for (int c = start_c; c > final_c; c--) n_board[_row][c-1] = board[_row][c];
}
//go_U(        C-1, robot_row[UPPER], 0, UPPER);
void go_U(int _col, int start_r, int final_r, int _UD){
    for (int r = start_r; r > final_r; r--) n_board[r-1][_col] = board[r][_col];
    if      (_UD == UPPER) n_board[final_r][_col-1] = board[final_r][_col];
    else if (_UD == UNDER) n_board[final_r][_col]   = -1;
}
//   go_D(     C-1, robot_row[UNDER], R-1, UNDER);
void go_D(int _col, int start_r, int final_r, int _UD){
    for (int r = start_r; r < final_r; r++) n_board[r+1][_col] = board[r][_col];
    if      (_UD == UPPER) n_board[final_r][_col]   = -1;
    else if (_UD == UNDER) n_board[final_r][_col-1] = board[final_r][_col];
}

void cleaner(){
    ///1. 위의 공기청정기
    go_R(robot_row[UPPER], 1, C-1, UPPER);
    go_U(C-1, robot_row[UPPER], 0, UPPER);
    go_L(0, C-1, 0, UPPER);
    go_D(0, 0, robot_row[UPPER], UPPER);
    ///2. 아래 공기청정기
    go_R(robot_row[UNDER], 1, C-1, UNDER);
    go_D(C-1, robot_row[UNDER], R-1, UNDER);
    go_L(R-1, C-1, 0, UNDER);
    go_U(0, R-1, robot_row[UNDER], UNDER);
}

int main()
{
    init();
    for (int t = 0; t < T; t++){
        n_board_init();
        diffuse     ();
        to_board    ();
        cleaner     ();
        to_board    ();
    }
    cout << answer();
    return 0;
}
