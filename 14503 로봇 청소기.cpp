#include <iostream>
using namespace std;

int N, M, row, col, dir, ret;
int board[50][50] = {0, };
int d_row[4] = {-1, 0, 1,  0};
int d_col[4] = { 0, 1, 0, -1};

void init(){
    cin >> N >> M;
    cin >> row >> col >> dir;
    for (int i=0; i<N; i++){
        for (int j=0; j<M; j++){
            cin >> board[i][j];
        }
    }
}

void clean(){
    if (board[row][col] != 0) return;
    board[row][col] = 2;
    ret++;
}

void rotate_left(){
    if (dir == 0) dir = 3;
    else          dir--;
}

bool detect(){
    int n_row = row + d_row[dir];
    int n_col = col + d_col[dir];
    if (board[n_row][n_col] == 0) return true;
    return false;
}

void move(int i){
    row += d_row[dir]*i;
    col += d_col[dir]*i;
}

bool back(){
    int n_row = row + d_row[dir]*(-1);
    int n_col = col + d_col[dir]*(-1);

    if (board[n_row][n_col] == 1) return false;
    return true;
}

int main()
{
    init();
    while (true){
        clean();
        bool target = false;
        for (int d=0; d <4; d++){
            rotate_left();
            if (detect()){
                move(1);
                target = true;
                break;
            }
        }
        if (!target){
            if (!back()) break;
            move(-1);
        }
    }
    cout << ret;
    return 0;
}
