#include <iostream>
#include <deque>
using namespace std;
/*
1. 큰 물고기 지나갈 수 X
2. 같은 크기 물고기 지나갈 수 O

3. 같은 크기 물고기 먹을 수 X

4. 먹을 수 있는 물고기 중 가장 가까운 것 선택

5. 거리 같은 것 여러개면 ROW 가장 작은 것, 그것도 여러개면 COL 가장 작은 것

6. 같은 크기만큼 물고기 먹으면 크기 +1
*/
const int d_row[4] = {-1,  0, 0, 1};
const int d_col[4] = { 0, -1, 1, 0};
int board[20][20] = {0, };
int N;
struct SHARK{
    int row, col;
    int eat = 0;
    int lev = 2;
    int dist = 0;
    int time = 0;
};
SHARK shark;

void init(){
    cin >> N;
    for (int r = 0; r < N; r++){
        for (int c = 0; c < N; c++){
            cin >> board[r][c];
            if (board[r][c] == 9){
                shark.row = r;
                shark.col = c;
            }
        }
    }
}
void detect(){
    deque<SHARK> que;
    que.push_back(shark);

    bool visit[20][20] = {false, };
    visit[shark.row][shark.col] = true;
    int short_fish = 400;//첫 사냥 가능한 물고기까지의 거리
    ///1. 후보 먹이 탐색
    while(!que.empty()){
        SHARK c_shark = que.front(); que.pop_front();
        int c_row  = c_shark.row;
        int c_col  = c_shark.col;
        int c_lev  = c_shark.lev;
        int c_eat  = c_shark.eat;
        int c_dist = c_shark.dist;
        int c_time = c_shark.time;
        //(2) 다음 진행이 최소거리 물고기보다 더 먼 경우 break
        if (c_dist == short_fish) {
            que.push_back(c_shark);
            break;
        }
        for (int d = 0; d < 4; d++){
            int n_row  = c_row  + d_row[d];
            int n_col  = c_col  + d_col[d];
            int n_dist = c_dist + 1;
            int n_time = c_time + 1;
            //(1) 범위 밖 OR 이미 방문 OR 큰 물고기 : CONTINUE
            if (n_row < 0 || n_row >= N || n_col < 0 || n_col >= N || visit[n_row][n_col] == true || board[n_row][n_col] > c_lev) continue;

            //(3) 자기보다 작은 물고기
            if (board[n_row][n_col] > 0 && board[n_row][n_col] < c_lev) short_fish  = n_dist;
            //(4) 다음 shark 초기화
            visit[n_row][n_col] = true;
            SHARK n_shark = c_shark;
            n_shark.row   = n_row;
            n_shark.col   = n_col;
            n_shark.dist  = n_dist;
            n_shark.time  = n_time;
            que.push_back(n_shark);
        }
    }
    ///2. 최종 먹이 선정
    int target = 2121;
    int time   = shark.time;
    int eat    = shark.eat ;
    while(!que.empty()){
        SHARK c_shark = que.front(); que.pop_front();
        int c_point = c_shark.row*100 + c_shark.col;
        int c_time  = c_shark.time;
        int c_eat   = c_shark.eat ;
        if (board[c_point / 100][c_point % 100] > 0 && board[c_point / 100][c_point % 100] < c_shark.lev){
            if (c_point < target) {
                target = c_point;
                time   = c_time ;
                eat    = c_eat  ;
            }
        }
    }

    ///3. 먹이 먹고 성장
    //(1) board 최신화
    board[target / 100][target % 100] = 9;
    board[   shark.row][   shark.col] = 0;
    //(2) shark 최신화
    shark.row  = target / 100;
    shark.col  = target % 100;
    shark.time = time;
    if (target != 2121){
        shark.eat += 1;
        if (shark.eat == shark.lev){
            shark.eat  = 0;
            shark.lev += 1;
        }
    }
}

int main()
{
    init();
    while(shark.row != 21 && shark.col != 21) detect();//BFS
    cout << shark.time;
    return 0;
}
