#include <iostream>
using namespace std;
int N, total = 0, ret = 100 * 20 * 20;
int board[20][20] = {0, };
int player[20] = {0, };

void init(){
    cin >> N;
    for (int r = 0; r < N; r++){
        for (int c = 0; c < N; c++){
            cin >> board[r][c];
            total += board[r][c];
        }
    }
}

void score(){
    int A_score = 0;
    int B_score = 0;
    for (int i = 0; i < N-1; i++){
        for (int j = i+1; j < N; j++){
            if (player[i] == false && player[j] == false) {
                B_score += board[i][j];
                B_score += board[j][i];
            }
            if (player[i] == true && player[j] == true) {
                A_score += board[i][j];
                A_score += board[j][i];
            }

        }
    }

    if (abs(A_score - B_score) < ret) ret = abs(A_score - B_score);
}

void DFS(int _cnt, int _start){
    if (_cnt == N / 2){
        score();
    }

    for (int idx = _start; idx < N; idx++){
        if (player[idx] == true) continue;
        player[idx] = true;
        DFS(_cnt + 1, idx);
        player[idx] = false;
    }
}

int main()
{
    init();
    DFS(0, 0);
    cout << ret;
    return 0;
}
