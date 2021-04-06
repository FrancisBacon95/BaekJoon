#include <iostream>
#include<cmath>
using namespace std;
int K;
int gear  [4][8] = {0, };
int n_gear[4][8] = {0, };
const int RIGHT = 2;
const int LEFT  = 6;
const int N = 0;
const int S = 1;
bool visit[4] = {false, };

void debug(){
    for (int r = 0; r < 4; r++){
        for (int c = 0; c < 8; c++){
            cout << gear[r][c]<<" ";
        }
        cout <<endl;
    }
}
void rotate(int _idx, int _dir){
    //(1) gear[idx] -> c_gear
    int c_RIGHT = gear[_idx][2];
    int c_LEFT  = gear[_idx][6];

    if      (_dir ==  1){
        for (int i = 0; i < 8; i++) n_gear[_idx][i] = gear[_idx][(i+7) % 8];
    }
    else if (_dir == -1){
        for (int i = 0; i < 8; i++) n_gear[_idx][i] = gear[_idx][(i+1) % 8];
    }
    visit[_idx] = true;
    if (_idx < 3 && c_RIGHT != gear[_idx+1][LEFT ] && visit[_idx+1] == false){
        rotate(_idx+1, _dir*(-1));
    }
    if (_idx > 0 && c_LEFT  != gear[_idx-1][RIGHT] && visit[_idx-1] == false){
        rotate(_idx-1, _dir*(-1));
    }
}

void copy_gear(int i){
    if (i == 0){
        for (int r = 0; r < 4; r++){
            for (int c = 0; c < 8; c++){
                n_gear[r][c] = gear[r][c];
            }
        }
    }

    if (i == 1){
        for (int r = 0; r < 4; r++){
            for (int c = 0; c < 8; c++){
                gear  [r][c] = n_gear[r][c];
                n_gear[r][c] = 0;
            }
        }
    }
}

void init(){
    for (int r = 0; r < 4; r++){
        for (int c = 0; c < 8; c++){
            char tmp; cin >> tmp;
            gear[r][c] = tmp - '0';
        }
    }

    cin >> K;
    for (int i = 0; i < K; i++){
        int idx, dir;
        cin >> idx >> dir; idx--;
        copy_gear(0);
        rotate(idx, dir);
        copy_gear(1);
        for (int i = 0; i < 4; i++) visit[i] = false;
    }
}

int answer(){
    int ret = 0;
    for (int i = 0; i < 4; i++){
        if (gear[i][0] == S) ret += pow(2, i);
    }
    return ret;
}

int main()
{
    init();
    cout << answer();
    return 0;
}
