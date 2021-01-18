#include <iostream>
#include <deque>
#include <algorithm>
using namespace std;
int N, L, R;

int board  [50][50] = {0, };
int visited[50][50] = {0, };
int united_idx = 1;
bool  check = true;
const int d_row[] = {-1, +1,  0,  0};
const int d_col[] = { 0,  0, -1, +1};
int ans=0;
void input(){
    cin >> N >> L >> R;
    for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            cin >> board[i][j];
        }
    }
}

void detect_united(int i, int j){
    if (visited[i][j] == united_idx) return;
    int sum = board[i][j];
    deque<pair<int, int>> que;
    deque<pair<int, int>> pos;
    que.push_back(pair<int, int> (i, j));
    pos.push_back(pair<int, int> (i, j));
    visited[i][j] = united_idx;

    while(!que.empty()){
        int c_row = que.front().first ;
        int c_col = que.front().second;
        int c_num = board[c_row][c_col];
        que.pop_front();

        for (int d=0; d<4; d++){
            int n_row = c_row + d_row[d];
            int n_col = c_col + d_col[d];
            int n_num = board[n_row][n_col];

            if (n_row < 0 || n_row >= N || n_col < 0 || n_col >= N || visited[n_row][n_col] == united_idx || (int)abs(n_num - c_num) < L || (int)abs(n_num - c_num) > R) continue;
            check = true;
            que.push_back(pair<int, int> (n_row, n_col));
            pos.push_back(pair<int, int> (n_row, n_col));
            sum += board[n_row][n_col];
            visited[n_row][n_col] = united_idx;
        }

    }
    int avr = sum / pos.size();
    while(!pos.empty()){
        int c_row = pos.front().first ;
        int c_col = pos.front().second;
        board[c_row][c_col] = avr;
        pos.pop_front();
    }
}


int main()
{
    input();

    while (check){
        check = false;
        for (int i=0; i<N; i++){
            for (int j=0; j<N; j++){
                detect_united(i,j);
            }
        }
        united_idx++;
        ans++;
    }
    cout << ans-1;
    return 0;
}

