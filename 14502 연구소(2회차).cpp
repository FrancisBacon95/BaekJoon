#include <iostream>
#include <deque>
using namespace std;
const int d_row[4] = {0,  0, 1, -1};
const int d_col[4] = {1, -1, 0,  0};
int N, M, ret = 0;
int board[8][8];
int virus[64] = {0, };
int virus_size = 0;
void init(){
    cin >> N >> M;
    for (int r = 0; r < N; r++){
        for (int c =0; c < M; c++){
            cin >> board[r][c];
            if (board[r][c] == 2) virus[virus_size++] = r*100 + c;
        }
    }
}

void diffuse(){
    bool visit[8][8] = {false, };
    deque<int> que;
    for (int i = 0; i < virus_size; i++) {
        int tmp_v = virus[i];
        visit[tmp_v / 100][tmp_v % 100] = true;
        que.push_back(tmp_v);
    }

    while(!que.empty()){
        int c_vir = que.front(); que.pop_front();
        int c_row = c_vir / 100;
        int c_col = c_vir % 100;

        visit[c_row][c_col] = true;
        for (int d = 0; d < 4; d++){
            int n_row = c_row + d_row[d];
            int n_col = c_col + d_col[d];
            if (n_row < 0 || n_row >= N || n_col < 0 || n_col >= M || visit[n_row][n_col] == true || board[n_row][n_col] != 0) continue;
            que.push_back(n_row*100 + n_col);
        }
    }

    int sum = 0;
    for (int r = 0; r < N; r++){
        for (int c = 0; c < M; c++){
            //ºóÄ­ -> °¨¿° OR
            if (visit[r][c] == true || board[r][c] != 0) continue;
            sum++;
        }
    }
    if (sum > ret) ret = sum;
}

void select(int _cnt, int _row, int _col){
    if (_cnt == 3){
        //BFS
        diffuse();
        return;
    }

    for (int r = _row; r < N; r++){
        for (int c = _col; c < M; c++){
            if (board[r][c] != 0) continue;
            board[r][c] = 1;
            select(_cnt + 1, r, c);
            board[r][c] = 0;
        }
        _col = 0;
    }
}

int main()
{
    init();
    select(0, 0, 0);
    cout << ret;
    return 0;
}
