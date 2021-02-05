#include <iostream>
using namespace std;
int N;
int num[11] = {0, };
int tool[4] = {0, };

int MAX = -1000000001;
int MIN = +1000000001;

const int PLUS     = 0;
const int MINUS    = 1;
const int PRODUCT  = 2;
const int DIVISION = 3;

void input(){
    cin >> N;
    for (int i=0; i<N; i++){
        cin >> num[i] ;
    }
    for (int i=0; i<4; i++){
        cin >> tool[i];
    }
}

int solve(int c_num, int target, int idx){
    if      (idx == PLUS    ) c_num += target;
    else if (idx == MINUS   ) c_num -= target;
    else if (idx == PRODUCT ) c_num *= target;
    else if (idx == DIVISION) c_num /= target;

    return c_num;
}

void DFS(int idx, int c_num){
    if (idx == N){
        if (c_num > MAX) MAX = c_num;
        if (c_num < MIN) MIN = c_num;
        return;
    }

    for (int i=0; i<4; i++){
        if (tool[i] == 0) continue;
        tool[i]--;
        int n_num = solve(c_num, num[idx], i);
        DFS(idx+1, n_num);
        tool[i]++;
    }
}

int main()
{
    input();
    DFS(1, num[0]);
    cout << MAX << endl << MIN;
    return 0;
}
