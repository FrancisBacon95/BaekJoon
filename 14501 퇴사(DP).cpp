#include <iostream>
using namespace std;

int N;
int T[15], P[15];
int cache[15]; //채워졌는지 확인, 채워졌으면 그 값 반환용

int solve(int day){
    if (day >  N) return -1000*15;
    if (day == N) return        0;

    int& ret = cache[day];
    if (ret != -1) return ret;

    // max( 해당 날짜 수행 X, 해당 날짜 수행 O)
    ret = max(solve(day+1), solve(day+T[day])+P[day]);
    return ret;
}

int main(){
    cin >> N;
    for (int i=0; i<N; i++){
        cin >> T[i] >> P[i];
        cache[i] = -1;
    }

    int ret = solve(0);
    cout << ret;

    return 0;
}
