#include <iostream>
using namespace std;
const int d_row[4] = {0,  0, 1, -1};
const int d_col[4] = {1, -1, 0,  0};
const int PEOPLE = 0;
const int UNITED = 1;
const int SUM = 0;
const int CNT = 1;
int N, L, R, ret = 0;
int board[50][50][2] = {0, };

int united_num = 1;

void debug(int i){
    cout << endl;
    if (i == PEOPLE){
        for (int r = 0; r < N; r++){
            for (int c = 0; c < N; c++){
                cout << board[r][c][PEOPLE] << " ";
            }
            cout << endl;
        }
    }
    else if (i == UNITED){
        for (int r = 0; r < N; r++){
            for (int c = 0; c < N; c++){
                cout << board[r][c][UNITED] << " ";
            }
            cout << endl;
        }
    }
    cout << endl;
}

void init(){
    cin >> N >> L >> R;
    for (int r = 0; r < N; r++){
        for (int c = 0; c < N; c++){
            cin >> board[r][c][PEOPLE];
        }
    }
}

void detect(int c_row, int c_col, int c_united){
    int c_num = board[c_row][c_col][PEOPLE];
    board[c_row][c_col][UNITED] = c_united;


    for(int d = 0; d < 4; d++){
        int n_row = c_row + d_row[d];
        int n_col = c_col + d_col[d];
        int n_num = board[n_row][n_col][PEOPLE];
        int diff  = abs(n_num - c_num);
        if (n_row < 0 || n_row >= N || n_col < 0 || n_col >= N || board[n_row][n_col][UNITED] != 0) continue;
        if (diff < L || diff > R) continue;
        board[n_row][n_col][UNITED] = c_united;
        detect(n_row, n_col, c_united);
    }
}

void solution(){
    while(true){
        ///1, nation Å½»ö
        united_num = 1;
        for (int r = 0; r < N; r++){
            for (int c = 0; c < N; c++){
                if (board[r][c][UNITED] == 0) detect(r, c, united_num++);
            }
        }
        int united_list[2501][2] = {0, };
        ///2. Æò±Õ°ª °è»ê
        for (int r = 0; r < N; r++){
            for (int c = 0; c < N; c++){
                int tmp_united = board[r][c][UNITED];
                united_list[tmp_united][SUM] += board[r][c][PEOPLE];
                united_list[tmp_united][CNT]++;
            }
        }
        ///3. Æò±Õ°ª »ðÀÔ
        for (int r = 0; r < N; r++){
            for (int c = 0; c < N; c++){
                int tmp_untied = board[r][c][UNITED];
                board[r][c][PEOPLE] = united_list[tmp_untied][SUM] / united_list[tmp_untied][CNT];
                board[r][c][UNITED] = 0;
            }
        }

        if (united_num == (N*N)+1) return;
        ret += 1;
    }
}

int main()
{
    init();
    solution();
    cout << ret;
    return 0;
}
