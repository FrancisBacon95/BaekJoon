#include <iostream>
using namespace std;
const int d_row[4] = {0,  0, 1, -1};
const int d_col[4] = {1, -1, 0,  0};
const int POS = 0;
const int NUM = 1;
const int DIR = 2;
int  N, M, ret = 65;
int board[8][8] = {0, };
int cctv [8][3] = {0, };
int cctv_size = 0;
void init(){
    cin  >> N >> M;
    for (int r = 0; r < N; r++){
        for (int c = 0; c < M; c++){
            cin >> board[r][c];
            if (board[r][c] > 0 && board[r][c] < 6){
                cctv[cctv_size  ][POS] = r*100 + c  ;
                cctv[cctv_size++][NUM] = board[r][c];
            }
        }
    }
}

void debug(){
    cout << endl << "DEBUG"<< endl;
    for (int r = 0; r < N; r++){
        for (int c = 0; c < M; c++){
            cout << board[r][c] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void lazor(int _row, int _col, int _dir){
    int c_row = _row + d_row[_dir];
    int c_col = _col + d_col[_dir];
    while(true){
        if (c_row < 0 || c_row >= N || c_col < 0 || c_col >= M || board[c_row][c_col] == 6) break;
        if (board[c_row][c_col] == 0) board[c_row][c_col] = 9;
        c_row += d_row[_dir];
        c_col += d_col[_dir];
    }
}

void set_cctv(int _idx){
    int row = cctv[_idx][POS] / 100;
    int col = cctv[_idx][POS] % 100;
    int dir = cctv[_idx][DIR]      ;
    int num = cctv[_idx][NUM]      ;
    if      (num == 1) lazor(row, col, dir);
    else if (num == 2){
        if (dir % 2 == 0){
            lazor(row, col, 0);
            lazor(row, col, 1);
        }
        else {
            lazor(row, col, 2);
            lazor(row, col, 3);
        }
    }
    else if (num == 3){
        if      (dir == 0){
            lazor(row, col, 0);
            lazor(row, col, 2);
        }
        else if (dir == 1){
            lazor(row, col, 0);
            lazor(row, col, 3);
        }
        else if (dir == 2){
            lazor(row, col, 1);
            lazor(row, col, 2);
        }
        else if (dir == 3){
            lazor(row, col, 1);
            lazor(row, col, 3);
        }
    }
    else if (num == 4){
        if      (dir == 0){
            lazor(row, col, 0);
            lazor(row, col, 2);
            lazor(row, col, 3);
        }
        else if (dir == 1){
            lazor(row, col, 1);
            lazor(row, col, 2);
            lazor(row, col, 3);
        }
        else if (dir == 2){
            lazor(row, col, 2);
            lazor(row, col, 0);
            lazor(row, col, 1);
        }
        else if (dir == 3){
            lazor(row, col, 3);
            lazor(row, col, 0);
            lazor(row, col, 1);
        }
    }
    else if (num == 5){
        lazor(row, col, 0);
        lazor(row, col, 1);
        lazor(row, col, 2);
        lazor(row, col, 3);
    }
}

void calculate_reset(){
    int local_ret = 0;
    //debug();
    for (int r = 0; r < N; r++){
        for (int c = 0; c < M; c++){
            if (board[r][c] == 0) local_ret++;
            else if (board[r][c] == 9) board[r][c] = 0;
        }
    }
    if (local_ret < ret) ret = local_ret;
}

void DFS(int _idx){
    if (_idx == cctv_size){
        for (int i = 0; i < cctv_size; i++) set_cctv(i);
        calculate_reset();
        return;
    }

    for (int d = 0; d < 4; d++){
        cctv[_idx][DIR] = d;
        DFS(_idx + 1);
        cctv[_idx][DIR] = 0;
    }
}

int main()
{
    init();
    DFS(0);
    cout << ret;
    return 0;
}
