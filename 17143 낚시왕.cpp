#include <iostream>
using namespace std;
int R, C, M, kill = 0;
struct SHARK{
    int row, col, speed, dir, size;
    bool death = false;
};
int board[100][100] = {0, };
SHARK shark[10001];

const int d_row[4] = {-1, +1,  0,  0};
const int d_col[4] = { 0,  0, +1, -1};

void input(){
    cin >> R >> C >> M;
    for (int i=1; i<=M; i++){
        //INITIALIZE shark
        cin >> shark[i].row >> shark[i].col >> shark[i].speed >> shark[i].dir >> shark[i].size;
        shark[i].row--, shark[i].col--, shark[i].dir--;

        //INITIALIZE board
        board[shark[i].row][shark[i].col] = i;
    }
}

void shark_move(int idx){
    if (shark[idx].death) return;

    int speed = shark[idx].speed;
    int turn;
    if (shark[idx].dir < 2) turn = speed % (2*R - 2);
    else                    turn = speed % (2*C - 2);

    for(int t=0;t<turn; t++){
        int dir   = shark[idx].dir;
        int n_row = shark[idx].row + d_row[dir];
        int n_col = shark[idx].col + d_col[dir];

        if (n_row < 0 || n_row >= R || n_col < 0 || n_col >= C) {
            if (dir % 2 == 0) dir++;
            else              dir--;
            n_row = shark[idx].row + d_row[dir];
            n_col = shark[idx].col + d_col[dir];
        }

        shark[idx].row = n_row;
        shark[idx].col = n_col;
        shark[idx].dir = dir  ;
    }

    return;
}

void change_board(){
    int new_board[100][100] = {0, };
    for (int i=1; i<=M; i++){
        if (shark[i].death) continue;

        int row = shark[i].row;
        int col = shark[i].col;

        if (new_board[row][col] == 0){
            new_board[row][col] = i;
            continue;
        }

        if (shark[new_board[row][col]].size > shark[i].size){
            shark[i].death = true;
        }
        else{
            shark[new_board[row][col]].death = true;
            new_board[row][col] = i;
        }
    }

    //COPY NEW_BOARD
    for(int r=0; r<R; r++){
        for (int c=0; c<C; c++){
            board[r][c] = new_board[r][c];
        }
    }
}

int main()
{
    input();
    //total turn =  COL
    for (int t = 0; t< C; t++){
        //detect shark to kill
        for (int i = 0; i < R; i++){
            if (board[i][t] != 0){
                kill += shark[board[i][t]].size;
                shark[board[i][t]].death = true;
                board[i][t] = -1;
                break;
            }
        }

        for (int idx = 1; idx <= M; idx++) shark_move(idx);

        change_board();
    }
    cout<<kill;
    return 0;
}
