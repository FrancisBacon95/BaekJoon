#include <iostream>
using namespace std;
const int ROW = 0;
const int COL = 1;
int N, L, ret = 0;
int board[100][100] = {0, };
int target[100] = {0, };
void init(){
    cin >>  N >> L;
    for (int r = 0; r < N; r++){
        for (int c = 0; c < N; c++){
            cin >> board[r][c];
        }
    }
}

struct SLIDE{
    bool visit[100] = {false, };
};

bool put_slide(int _idx, int _DIR, SLIDE& _slide){
    //(1) 정방향 SLIDE
    if (_DIR ==  1){
        int height = target[_idx+1];
        for (int cur = _idx+1; cur <= _idx+L; cur++){
            if (_slide.visit[cur] == true || target[cur] != height) return false;
            _slide.visit[cur] = true;
        }
    }
    //(2) 역방향 SLIDE
    if (_DIR == -1){
        int height = target[_idx];
        for (int cur = _idx; cur > _idx-L; cur--){
            if (_slide.visit[cur] == true || target[cur] != height) return false;
            _slide.visit[cur] = true;
        }
    }
    return true;
}

void inspection(){
    int cur = 0;
    SLIDE slide;
    while(cur < N-1){
        int next = cur+1;
        int diff = target[cur] - target[next];
        //(1) 차이 1 이상 -> FALSE
        if (diff  >  1 || diff < -1) return;
        //(2) 차이 +1     -> 정방향 SLIDE
        else if (diff ==  1) {
            //(2-1) 정방향 SLIDE 설치 불가 -> FALSE
            if (!put_slide(cur,  1, slide)) return;
            cur += L;
            continue;
        }
        //(3) 차이 -1     -> 역방향 SLIDE
        else if (diff == -1){
            //(3-1) 역방향 SLIDE 설치 불가 -> FALSE
            if (!put_slide(cur, -1, slide)) return;
        }
        cur++;
    }
    ret++;
}

int main()
{
    init();
    ///가로 탐색
    for (int r = 0; r < N; r++){
        //(1) board -> target
        for (int i = 0; i < N; i++) target[i] = board[r][i];
        //(2) target inspection
        inspection();
    }
    ///세로 탐색
    for (int  c = 0; c < N; c++){
        //(1) board -> target
        for (int i = 0; i < N; i++) target[i] = board[i][c];
        //(2) target inspection
        inspection();
    }

    cout << ret;
    return 0;
}
