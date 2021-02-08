#include <iostream>
using namespace std;
int N, L;
int ret = 0;
int board[100][100] = {0, };

void input(){
    cin >> N >> L;
    for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            cin >> board[i][j];
        }
    }
}

int search(int pick, int dir){
    float target[100][2] = {0, };
    if (dir == 0) {
        for (int i=0  ; i <  N; i++) target[i][0] = board[pick][i];
    }
    if (dir == 1) {
        for (int i=0  ; i <  N; i++) target[i][0] = board[i][pick];
    }

    for (int i=0; i<N-1; i++){
        float depth = target[i][0] - target[i+1][0];
        if ((target[i][1] == target[i+1][1] && depth ==  0  ) ||
            (target[i][1] >  target[i+1][1] && depth ==  0.5) ) continue;

        if ((target[i][1] == target[i+1][1] && depth <  -1) ||
            (target[i][1] == target[i+1][1] && depth >   1) ||
            (target[i][1] >  target[i+1][1] && depth <   0) ) return 0;

        if (depth < 0){
            if (i-L+1 <  0) return 0;
            for (int l = 0; l < L; l++){
                if (target[i-l][0] - target[i+1][0] != depth) return 0;
                if (target[i-l][1] == 1) return 0;
                target[i-l][0] += 0.5;
                target[i-l][1] =  1  ;
            }
        }
        if (depth > 0){
            if (i+L   >= N) return 0;
            for (int l = 1; l <= L; l++){
                if (target[i  ][0] - target[i+l][0] != depth) return 0;
                target[i+l][0] += 0.5;
                target[i+l][1] =  1  ;
            }
        }
    }
    return 1;
}

int main()
{
    input();
    for (int i=0; i<N; i++){
        ret+= search(i, 0);
        ret+= search(i, 1);
    }
    cout << ret;
    return 0;
}
