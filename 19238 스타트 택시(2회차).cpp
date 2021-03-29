#include <iostream>
#include <deque>
using namespace std;
int N, M, FUEL;
int board[21][21] = {0, };

struct TAXI{
    int row, col;
    int dist;
};

struct CUSTOMER{
    int start_row, start_col;
    int desti_row, desti_col;
};

CUSTOMER customer[401];
TAXI taxi;

void debug(){
    cout << "_________________DEBUG"<<endl;
    for (int r = 1; r <= N; r++){
        for (int c = 1; c <= N; c++){
            if (board[r][c] == -1) cout << 9 << "  ";
            else cout << board[r][c] << "  ";
        }
        cout << endl;
    }
    cout << endl;
}

void init(){
    //(1) 보드 정보:  1 ~ N이므로 1부터
    cin >> N >> M >> FUEL;
    for (int r = 1; r <= N; r++){
        for (int c = 1; c <= N; c++){
            cin >> board[r][c];
            if (board[r][c] == 1) board[r][c] = -1;
        }
    }
    //(2) 택시 정보
    cin >> taxi.row >> taxi.col;

    //(3) 승객정보: idx가 필요하므로 1부터
    for (int i = 1; i <= M; i++){
        cin >> customer[i].start_row >> customer[i].start_col >> customer[i].desti_row >> customer[i].desti_col;
        board[customer[i].start_row][customer[i].start_col] = i;
    }
}

int detect_person(TAXI _taxi){
    deque<TAXI> que;
    que.push_back(_taxi);
    bool visit[21][21] = {false, };
    visit[_taxi.row][_taxi.col] = true;

    int candi_size = 0;
    int candi[400] = {0, };
    int candi_distance = -1;

    while(!que.empty()){
        TAXI c_taxi = que.front(); que.pop_front();

        // (1) candi_distance가 변경된 이력이 있는데, 현재 taxi의 이동거리가 candi_distance보다 큰 경우
        if (candi_distance != -1 && c_taxi.dist > candi_distance) break;

        // (2) 현재 위치한 고객까지의 거리가 기존의 거리보다 같을 수 밖에 없다.
        //      -> BFS 특성상 한 턴이 지날 때마다 dist는 기존 것보다 짧을 수는 없고,
        //      -> 위의 (1) 조건에 의해, 기존 것보다 길 수 없다.
        //      -> 고로 현재 만난 고객은 기존의 고객까지의 거리와 동일할 수 밖에 없다.
        if (board[c_taxi.row][c_taxi.col] > 0){
            candi[candi_size++] = board[c_taxi.row][c_taxi.col];
            candi_distance      = c_taxi.dist                  ;
        }

        const int d_row[4] = {-1,  0, 0, 1};
        const int d_col[4] = { 0, -1, 1, 0};
        for (int d = 0; d < 4; d++){
            int n_row = c_taxi.row + d_row[d];
            int n_col = c_taxi.col + d_col[d];
            if (n_row < 1 || n_row > N || n_col < 1 || n_col > N || board[n_row][n_col] == -1 || visit[n_row][n_col] == true) continue;
            visit[n_row][n_col] = true;
            TAXI n_taxi;
            n_taxi.row = n_row, n_taxi.col = n_col, n_taxi.dist = c_taxi.dist + 1;
            que.push_back(n_taxi);
        }
    }

    if (candi_distance > FUEL) return -1;

    int local_ret = -1;
    int candi_value = 10000;
    for (int i=0; i < candi_size; i++){
        int row = customer[candi[i]].start_row;
        int col = customer[candi[i]].start_col;
        if (candi_value > row*100 + col){
            candi_value = row*100 + col;
            local_ret = candi[i];
        }
    }

    taxi.row = candi_value / 100;
    taxi.col = candi_value % 100;
    board[taxi.row][taxi.col] = 0;
    FUEL -= candi_distance;
    return local_ret;
}

bool detect_destin(int _tar, TAXI _taxi){
    int desti_row = customer[_tar].desti_row;
    int desti_col = customer[_tar].desti_col;
    /// 1. BFS 준비태세
    deque<TAXI> que;
    que.push_back(_taxi);
    bool visit[21][21] = {false, };
    visit[_taxi.row][_taxi.col] = true;
    /// 2. BFS 활동개시
    while(!que.empty()){
        TAXI c_taxi = que.front(); que.pop_front();

        // (1) 이동거리가 FUEL을 초과하면 그 즉시 끝낸다.
        if (c_taxi.dist > FUEL) return false;


        // (2) 목적지에 도착할 경우, 이동거리만큼 먹고 끝낸다.
        if (c_taxi.row == desti_row && c_taxi.col == desti_col){
            taxi.row = desti_row  ;
            taxi.col = desti_col  ;
            FUEL    += c_taxi.dist;
            return true;
        }

        // (3) 다음 지점 탐색
        const int d_row[4] = {0,  0, 1, -1};
        const int d_col[4] = {1, -1, 0,  0};
        for (int d = 0; d < 4; d++){
            int n_row  = c_taxi.row  + d_row[d];
            int n_col  = c_taxi.col  + d_col[d];
            int n_dist = c_taxi.dist + 1       ;
            if (n_row < 1 || n_row > N || n_col < 1 || n_col > N || board[n_row][n_col] == -1 || visit[n_row][n_col] == true) continue;
            TAXI n_taxi;
            n_taxi.row  = n_row ;
            n_taxi.col  = n_col ;
            n_taxi.dist = n_dist;
            visit[n_taxi.row][n_taxi.col] = true;
            que.push_back( n_taxi );
        }
    }
    // (4) 할 수 있는 만큼 재귀로 다 돌았는데 결국 도달하지 못하고 여기까지 왔으면 절대 도달할 수 없는 목적지
    return false;
}

int solve(){
    int ret = -1;
    for (int m = 0; m < M; m++){
        // 1. 손님 탐색
        int target = detect_person(taxi);
        if (target == -1) return ret;
        // 2. 목적지 탐색
        bool destin = detect_destin(target, taxi);
        if (!destin     ) return ret;
    }
    ret = FUEL;
    return ret;
}

int main(){
    init();
    cout << solve();

    return 0;
};
/*
6 3 2
0 0 1 0 0 0
0 0 1 0 0 0
0 0 0 1 0 0
0 0 0 1 0 0
0 0 0 0 1 0
0 0 0 1 0 0
6 5
2 2 5 6
5 4 1 6
4 2 3 5

6 3 15
0 0 1 0 0 0
0 0 1 0 0 0
0 0 0 0 0 0
0 0 0 0 0 0
0 0 0 0 1 0
0 0 0 1 0 0
6 5
1 6 5 6
5 4 1 6
4 2 3 5

6 3 12
0 0 1 0 0 0
0 0 1 0 0 0
0 0 0 0 0 0
0 0 0 0 0 0
0 0 0 0 1 0
0 0 0 1 0 0
6 5
2 2 5 6
5 4 1 6
4 2 3 5
*/
