#include <iostream>
using namespace std;
int N, M, T;
int board[50][50]={0, };
int d_row[4] = {0, 1,  0, -1};
int d_col[4] = {1, 0, -1,  0};
bool change = false;

void debug(){
    cout << endl;
    for (int r = 0; r < N; r++){
        for (int c = 0; c < M; c++){
            cout << board[r][c] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void init(){
    cin >> N >> M >> T;
    for (int r = 0; r < N; r++){
        for (int c = 0; c < M; c++){
            cin >> board[r][c];
        }
    }
}

int answer(){
    int ret = 0;
    for (int r = 0; r < N; r++){
        for (int c = 0; c < M; c++){
            ret += board[r][c];
        }
    }
    return ret;
}

void rotate(int _floor, int _d, int _k){
    //반시계 방향의 경우, k를 시계방향으로 조정
    if (_d == 1) _k =  M - _k;
    //board[floor][...] -> tmp_floor[...]
    int tmp_floor[50] ={0, };
    for (int idx = 0; idx < M; idx++) tmp_floor[(idx + _k) % M] = board[_floor][idx];

    //tmp_floor[...] -> board[floor][...]
    for (int idx = 0; idx < M; idx++) board[_floor][idx] = tmp_floor[idx];
}

void detect(int _floor, int _idx, int _tar){
    board[_floor][_idx] = 0;

    //(1) RIGHT
    int R_idx = (_idx+  1  ) % M;
    if (_tar == board[_floor][R_idx]) detect(_floor, R_idx, _tar);
    //(2) LEFT
    int L_idx = (_idx+(M-1)) % M;
    if (_tar == board[_floor][L_idx]) detect(_floor, L_idx, _tar);
    //(3) UPPER
    int U_floor = _floor + 1;
    if (U_floor <  N && _tar == board[U_floor][_idx]) detect(U_floor, _idx, _tar);
    //(4) UNDER
    int D_floor = _floor - 1;
    if (D_floor >= 0 && _tar == board[D_floor][_idx]) detect(D_floor, _idx, _tar);
}
void solution(){
    int x, d, k; cin >> x >> d >> k;
    ///1. 회전
    for (int floor = x-1; floor < N; floor = floor + x) rotate(floor, d, k);
    ///2. 제거 목록 추가
    change = false;
    for (int floor = 0; floor < N; floor++){
        for (int idx = 0; idx < M; idx++){
            //(1) 이미 방문한 곳은 통과
            if (board[floor][idx] == 0) continue;
            int cur = board[floor][idx];
            //(2) 주변에 갈 곳 있는지 확인(상, 하, 좌, 우)
            for (int d = 0; d < 4; d++){
                int n_floor = floor + d_row[d];
                int n_idx = idx;
                if      (d_col[d] > 0) n_idx = (idx +    d_col[d]   ) % M;
                else if (d_col[d] < 0) n_idx = (idx + (M - d_col[d])) % M;
                if (n_floor < 0 || n_floor >= N) continue;
                if (cur == board[n_floor][n_idx]) {
                    change = true;
                    detect(floor, idx, cur);
                    break;
                }
            }
        }
    }
    if (!change){
        ///3. 삭제 안 된 곳 합계
        float total = 0, cnt = 0;
        for (int floor = 0; floor < N; floor++){
            for (int idx = 0; idx < M; idx++){
                //중복 체크 안 된 곳
                if (board[floor][idx] != 0){
                    total += board[floor][idx];
                    cnt++;
                }
            }
        }
        ///4. 평균 비교 후 처리
        float mean = total / cnt;
        for (int floor = 0; floor < N; floor++){
            for (int idx = 0; idx < M; idx++){
                if (board[floor][idx] == 0) continue;
                if      (board[floor][idx] > mean) board[floor][idx]--;
                else if (board[floor][idx] < mean) board[floor][idx]++;
            }
        }
    }
}

int main()
{
    init();
    for (int t = 0; t < T; t++) solution();
    cout << answer();
    return 0;
}
