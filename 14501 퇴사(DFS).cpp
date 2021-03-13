#include <iostream>
using namespace std;
int  N;
int  result = 0;
int  board[16][2];

void init(){
    cin >> N;
    for (int i=1; i<=N; i++){
        cin >> board[i][0] >> board[i][1];
    }
}

int max(int a, int b){return (a > b) ? a : b;}

void dfs(int c_day,int c_sum){
    if (c_day == N+1){
        result = max(result, c_sum);
        return;
    }

    if (c_day + board[c_day][0] > N+1){
        dfs(N+1, c_sum);
        return;
    }
    int n_day = c_day + board[c_day][0];
    int n_sum = c_sum + board[c_day][1];

    for (n_day; n_day<=N+1; n_day++){
        dfs(n_day, n_sum);
    }
}

int main()
{
    init();

    for(int i=1; i<=N; i++){
        dfs(i, 0);
    }

    cout << result;
    return 0;
}
