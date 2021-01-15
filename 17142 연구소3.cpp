#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;
struct POS {
    int row, col, time;
};

int N, M, ret;
int board[50][50];

int pos_size = 0;
POS pos[10];

void input(){
    cin >> N >> M;
    for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            cin >> board[i][j];
            if (board[i][j]==2){
                pos[pos_size].row  = i;
                pos[pos_size].col  = j;
                pos[pos_size].time = 0;
                pos_size++;
            }
        }
    }
}

int bfs(int pick[]){
    int empty_count = 0;
    for (int row = 0; row < N; row++){
        for(int col = 0; col < N; col++){
            if (board[row][col] == 0) empty_count++;
        }
    }

    queue<POS> q;
    int visited[50][50] = {0, };
    for (int i =0; i < M; i++){
        q.push(pos[pick[i]]);
        visited[pos[pick[i]].row][pos[pick[i]].col] = 1;
    }

    const int d_row[] = {+1, -1,  0,  0};
    const int d_col[] = { 0,  0, -1, +1};

    while (!q.empty()){
        POS cur = q.front();
        q.pop();

        if (board[cur.row][cur.row] == 0) empty_count--  ;
        if (empty_count == 0)             return cur.time;

        POS next;
        next.time = cur.time +1;
        for (int d=0; d<4; d++){
            next.row = cur.row + d_row[d];
            next.col = cur.col + d_col[d];
            if (next.row < 0 || next.row >= N || next.col < 0 || next.col >= N) continue;

            if (visited[next.row][next.col] == 0 && map[next.row][next.col] != 1){
                q.push(next);
                visited[next.row][next.col] = 1;
            }
        }
    }
    return 9999;
}

void dfs(int last_pick, int pick_count, int pick[]){
    if (pick_count == M){
        int candi = bfs(pick);
        if (ret > candi) ret = candi;
        return;
    }

    for (int i = last_pick+1; i< pos_size; i++){
        pick[pick_count] = i;
        dfs(i, pick_count + 1, pick);
    }
}

int main()
{
    ret = 9999;
    input();

    int pick[10] = {0, };
    dfs(-1, 0, pick);

    if (ret == 9999) cout << -1 ;
    else             cout << ret;

    return 0;
}
