#include <iostream>
#include <queue>
using namespace std;

int N, M, ret = 0;
int board[8][8] = {0, };

int  d_row[4] = {0,  0, 1, -1};
int  d_col[4] = {1, -1, 0,  0};

int  virus  [10][2] = {0, };

int virus_cnt = 0;


void init(){
    cin >> N >> M;
    for (int row = 0; row < N; row++){
        for (int col = 0; col < M; col++){
            cin >> board[row][col];
            if (board[row][col] == 2){
                virus[virus_cnt][0] = row;
                virus[virus_cnt][1] = col;
                virus_cnt++;
            }
        }
    }
}

int max(int a, int b){return (a > b) ? a : b;}

void virus_DFS(int row, int col){
    queue<int> que;
    que.push(row*100 + col);

    while(!que.empty()){
        int c_pnt = que.front(); que.pop();
        int c_row = c_pnt / 100;
        int c_col = c_pnt % 100;
        board[c_row][c_col] = 2;

        for (int d=0; d<4; d++){
            int n_row = c_row + d_row[d];
            int n_col = c_col + d_col[d];
            if (n_row < 0 || n_row >= N || n_col < 0 || n_col >= M || board[n_row][n_col] != 0) continue;
            que.push(n_row*100 + n_col);
        }
    }
}

void wall_DFS(int row, int col, int cnt){
    if (cnt == 3){
        //COPY: board -> tmp_board
        int tmp_board[8][8] = {0, };
        for (int i=0; i<N; i++){
            for (int j=0; j<M; j++){
                tmp_board[i][j] = board[i][j];
            }
        }

        //Diffusion of virus
        for (int v=0; v<virus_cnt; v++) virus_DFS(virus[v][0], virus[v][1]);

        //Check result
        int sum = 0;
        for (int i=0; i<N; i++){
            for (int j=0; j<M; j++){
                if (board[i][j] == 0) sum++;
            }
        }

        ret = max(ret, sum);

        //COPY: tmp_board -> board
        for (int i=0; i<N; i++){
            for (int j=0; j<M; j++){
                board[i][j] = tmp_board[i][j];
            }
        }

        return;
    }

    for (int n_row = row; n_row < N; n_row++){
        for (int n_col = col; n_col < M; n_col++){
            if (board[n_row][n_col] == 0){
                board[n_row][n_col] = 1;
                wall_DFS(n_row, n_col, cnt+1);
                board[n_row][n_col] = 0;
            }
            col = 0;
        }

    }
}

int main()
{
    init();
    wall_DFS(0, 0, 0);
    cout << ret;
    return 0;
}
