#include <iostream>
#define max_int 501
using namespace std;
int N, M, board[max_int][max_int], result;
bool check[max_int][max_int];

int d_row[4] = { 0, 0, 1, -1};
int d_col[4] = {-1, 1, 0,  0};

int e_row[4][4] = {{0, 0, 0, 1}, {0, 1, 2, 1}, {0, 0, 0, -1}, {0, -1, 0, 1}};
int e_col[4][4] = {{0, 1, 2, 1}, {0, 0, 0, 1}, {0, 1, 2,  1}, {0,  1, 1, 1}};

void init(){
    cin >> N >> M;
    for(int row=0; row<N; row++){
        for (int col=0; col<M; col++){
            cin  >> board[row][col];
        }
    }
}

int max(int a, int b){
    return a > b ? a : b;
}

void dfs(int c_row, int c_col, int sum_value, int length){
    if (length == 4){
        result = max(result, sum_value);
        return;
    }

    for (int i=0; i<4; i++){
        int n_row = c_row + d_row[i];
        int n_col = c_col + d_col[i];

        if (n_row < 0 || n_row >= N || n_col < 0 || n_col >= M) continue;

        if (!check[n_row][n_col]){
            check[n_row][n_col] = true;

            dfs(n_row, n_col, sum_value + board[n_row][n_col], length+1);
            check[n_row][n_col] = false;
        }
    }
}

void fuck_shape(int row, int col){
    for (int i=0; i<4; i++){
        bool isOut = false;
        int sum_value = 0;

        for (int j=0; j<4; j++){
            int n_row = row + e_row[i][j];
            int n_col = col + e_col[i][j];

            if (n_row < 0 || n_row >= N || n_col < 0 || n_col >= M){
                isOut = true;
                break;
            }

            sum_value += board[n_row][n_col];
        }

        if (!isOut) result = max(result, sum_value);
    }
}

int main()
{
    init();
    for(int i=0; i<N; i++){
        for (int j=0; j<M; j++){
            check[i][j] = true;
            dfs(i, j, board[i][j], 1);
            check[i][j] = false;

            fuck_shape(i, j);
        }
    }
    cout << result;
    return 0;
}
