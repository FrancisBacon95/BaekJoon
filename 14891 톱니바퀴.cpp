#include <iostream>
using namespace std;
int K, ret = 0;
int  dirs[4] = {0, };
char gear[4][9];

void init(){
    for (int i=0; i<4; i++){
        cin >> gear[i];
    }
    cin  >> K;
}

void rotate(int target, int dir){
    if (dir > 0){ //clockwise
        char tmp = gear[target][7];
        for(int i= 7; i>0; i--) gear[target][i] = gear[target][i-1];
        gear[target][0] = tmp;
    }

    else {
        char tmp = gear[target][0];
        for (int i=0; i<7; i++) gear[target][i] = gear[target][i+1];
        gear[target][7] = tmp;
    }
}

int main()
{
    init();

    for(int k=0; k<K; k++){
        int target;
        cin >> target        ;
        cin >> dirs[--target];

        //LEFT
        for(int i = target-1; i>-1; i--){
            if (gear[i][2] == gear[i+1][6]) break;
            dirs[i] = dirs[i+1] * (-1);
        }
        //RIGHT
        for(int i = target+1; i< 4; i++){
            if (gear[i][6] == gear[i-1][2]) break;
            dirs[i] = dirs[i-1] * (-1);
        }
        for (int i=0; i<4; i++) {
            if (dirs[i] != 0) rotate(i, dirs[i]);
            dirs[i] = 0;
        }
    }

    if (gear[0][0] == '1') ret += 1;
    if (gear[1][0] == '1') ret += 2;
    if (gear[2][0] == '1') ret += 4;
    if (gear[3][0] == '1') ret += 8;
    cout << ret;
    return 0;
}
