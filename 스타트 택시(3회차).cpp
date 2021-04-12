#include <iostream>
#include <deque>
using namespace std;
const int d_row[4] = {0,  0, 1, -1};
const int d_col[4] = {1, -1, 0,  0};
const int WALL = -1;
int board [ 20][20] = {0, };
int person[401][ 2] = {0, };
int N, M, fuel;

struct TAXI{
    int row, col, dist;
};

TAXI taxi;

void init(){
    cin >> N >> M >> fuel;
    for (int r = 0; r < N; r++){
        for (int c = 0; c < N; c++){
            cin >> board[r][c];
            if (board[r][c] == 1) board[r][c] = WALL;
        }
    }

    cin >> taxi.row >> taxi.col;
    taxi.row--, taxi.col--;

    for (int i = 1; i <= M; i++){
        int strt_r, strt_c, dest_r, dest_c;
        cin >> strt_r >> strt_c >> dest_r >> dest_c; strt_r--, strt_c--, dest_r--, dest_c--;
        person[i][0] = strt_r*100 + strt_c;
        person[i][1] = dest_r*100 + dest_c;
    }
}

int detect_person(){
    ///1. visit 생성
    for (int i = 1; i <= M; i++){
        if (person[i][0] == -1) continue;
        board[ person[i][0]/100 ][ person[i][0]%100 ] = i;
    }

    bool visit[20][20] = {false, };
    visit[taxi.row][taxi.col] = true;
    bool is_target = false;
    int  min_dist =  401, min_idx = 401, min_row = 21, min_col = 21;

    ///2. que 초기화, while문
    deque<TAXI> que;
    que.push_back(taxi);

    while(!que.empty()){
        TAXI cur = que.front(); que.pop_front();
        int c_dist = cur.dist;
        int c_row  = cur.row;
        int c_col  = cur.col;

        //1) fuel을 초과한 경우
        if (c_dist > fuel) break;
        //2) 이미 쌓인 경우
        if (c_dist > min_dist) break;

        //3) 현재 거리 = MIN_DIST:
        if (c_dist == min_dist){
            //1-1) 현재 위치 > 0: PUSH_BACK
            if (board[c_row][c_col] > 0){
                if (c_row >  min_row) continue;
                if (c_row == min_row && c_col > min_col) continue;
                min_row = c_row;
                min_col = c_col;
                min_idx = board[c_row][c_col];
                continue;
                }
        }
        //4) (사실상 최초에만 있는 경우) 현재 거리 < MIN_DIST && 현재 위치 > 0: MIN_DIST = 현재 거리 && CAND 추가 && CONTINUE
        if (c_dist < min_dist && board[c_row][c_col] > 0){
            is_target = true;
            min_dist = c_dist;
            min_row  = c_row;
            min_col  = c_col;
            min_idx  = board[c_row][c_col];
            continue;
        }

        //5) 탐색 알고리즘
        for (int d = 0; d < 4; d++){
            int n_row  = c_row  + d_row[d];
            int n_col  = c_col  + d_col[d];
            int n_dist = c_dist + 1;
            if (n_row < 0 || n_row >= N || n_col < 0 || n_col >= N || visit[n_row][n_col] == true || board[n_row][n_col] == WALL) continue;
            TAXI n_taxi;
            n_taxi.row  = n_row;
            n_taxi.col  = n_col;
            n_taxi.dist = n_dist;
            visit[n_row][n_col] = true;
            que.push_back(n_taxi);
        }
    }

    ///3. BOARD 원상복구
    for (int i = 1; i <= M; i++){
        if (person[i][0] == -1) continue;
        board[ person[i][0]/100 ][ person[i][0]%100 ] = 0;
    }

    ///4. TARGET 하나도 못 찾은 경우
    if (!is_target) return -1;

    ///6. TAXI 정보 수정
    taxi.row  = min_row;
    taxi.col  = min_col;
    fuel     -= min_dist;

    return min_idx;
}


void detect_desti(int _idx){
    int tar_r = person[_idx][1] / 100;
    int tar_c = person[_idx][1] % 100;

    ///1. visit 생성
    bool visit[20][20] = {false, };
    visit[taxi.row][taxi.col] = true;
    ///2. que 초기화 및 while문
    deque<TAXI> que;
    bool is_dest = false;
    que.push_back(taxi);
    while(!que.empty()){
        TAXI c_taxi = que.front(); que.pop_front();
        int c_dist = c_taxi.dist;
        int c_row  = c_taxi.row;
        int c_col  = c_taxi.col;
        //c_dist > fuel -> break
        if (c_dist > fuel) break;
        //cur = target -> taxi = c_taxi && break
        if (c_row == tar_r && c_col == tar_c){
            taxi = c_taxi;
            is_dest = true;
            break;
        }

        for (int d = 0; d < 4; d++){
            int n_row  = c_row  + d_row[d];
            int n_col  = c_col  + d_col[d];
            int n_dist = c_dist + 1;
            if (n_row < 0 || n_row >= N || n_col < 0 || n_col >= N || visit[n_row][n_col] == true || board[n_row][n_col] == WALL) continue;
            TAXI n_taxi;
            n_taxi.row  = n_row;
            n_taxi.col  = n_col;
            n_taxi.dist = n_dist;
            visit[n_row][n_col] = true;
            que.push_back(n_taxi);
        }
    }

    ///3. FUEL 수정
    fuel -= taxi.dist;
    if (!is_dest) fuel = -1;
}

int main()
{
    init();

    int num = M;
    while (num > 0){
        ///1. target 찾기
        int target = detect_person();
        if (fuel < 0 || target == -1){
            cout << -1;
            return 0;
        }

        ///2. target의 destination으로 이동
        detect_desti(target);
        if (fuel < 0){
            cout << -1;
            return 0;
        }
        fuel += 2*taxi.dist;

        ///3. 완료한 target의 정보 수정
        person[target][0] = -1;
        person[target][1] = -1;

        ///4. taxi의 dist 수정
        taxi.dist = 0;
        num--;
    };
    cout << fuel;
    return 0;
}
