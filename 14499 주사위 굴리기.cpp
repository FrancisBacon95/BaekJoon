#include <iostream>
int N, M, K, row, col;
int board[20][20];
int dice[6] = {0, };
using namespace std;
bool move(int dir){
    if      (dir == 1){
        col++;
        if (col >= M) {
            col--;
            return false;
        }
        int tmp_dice[6] = {dice[4], dice[5], dice[2], dice[3], dice[1], dice[0]};
        for (int i=0; i<6; i++) dice[i] = tmp_dice[i];
        return true;
    }
    else if (dir == 2){
        col--;
        if (col < 0) {
            col++;
            return false;
        }

        int tmp_dice[6] = {dice[5], dice[4], dice[2], dice[3], dice[0], dice[1]};
        for (int i=0; i<6; i++) dice[i] = tmp_dice[i];
        return true;
    }
    else if (dir == 3){
        row--;
        if (row < 0) {
            row++;
            return false;
        }

        int tmp_dice[6] = {dice[0], dice[1], dice[5], dice[4], dice[2], dice[3]};
        for (int i=0; i<6; i++) dice[i] = tmp_dice[i];
        return true;
    }
    else if (dir == 4){
        row++;
        if (row >= N) {
            row--;
            return false;
        }
        int tmp_dice[6] = {dice[0], dice[1], dice[4], dice[5], dice[3], dice[2]};
        for (int i=0; i<6; i++) dice[i] = tmp_dice[i];
        return true;
    }
}

int main()
{
    cin >> N >> M >> row >> col >> K;
    for (int r=0; r<N; r++){
        for (int c=0; c<M; c++){
            cin  >> board[r][c];
        }
    }

    for (int k=0; k<K; k++){
        int dir; cin >> dir;
        if (!move(dir)) continue;
        if (board[row][col] == 0) board[row][col] = dice[5];
        else {
            dice [5]        = board[row][col];
            board[row][col] = 0              ;
        }
        cout << dice[4] << endl;

    }
    return 0;
}
