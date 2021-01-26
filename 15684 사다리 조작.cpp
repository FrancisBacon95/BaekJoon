#include <iostream>
using namespace std;
int N, M, H, ret = 4;
int board[31][11];

void input(){
    cin >> N >> M >> H;
    int row, col;
    for (int i=0; i<M; i++){
        cin >> row >> col;
        board[row][col] = 1;
    }
}

bool check(){
    bool ret = true;
    for (int i=1; i<=N; i++){
        int pos = i;
        for (int j=0; j<=H; j++){
            if      (board[j][pos  ] == 1) pos++;
            else if (board[j][pos-1] == 1) pos--;
        }
        if (pos != i) return ret = false;
    }
    return ret;
}

void dfs(int count, int row, int col){
    if (count >= ret) return;
    if (check()){
        ret = count;
        return;
    }
    if (count == 3) return;
    for (int i=row; i<=H; i++){
        for (int j=col; j<N; j++){
            if (board[i][j] == 0 && board[i][j-1] == 0 && board[i][j+1] == 0){
                board[i][j] = 1;
                dfs(count+1, i, j);
                board[i][j] = 0;
            }
        }
        col = 1;
    }
}

int main()
{
    input();
    dfs(0, 1, 1);
    if (ret > 3) ret = -1;
    cout << ret;
    return 0;
}
