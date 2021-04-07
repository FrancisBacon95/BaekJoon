#include <iostream>
using namespace std;
const int T = 0;
const int P = 1;
int N, ret = 0;
int board[15][2] = {0, };
bool visit[15] = {false, };

void init(){
    cin >> N;
    for(int i = 0; i < N; i++){
        cin >> board[i][T] >> board[i][P];
    }
}

void DFS(int _idx, int _sum){
    if (_idx > N-1){
        /*
        ////////////////////////////////////////////
        cout << "DEBUG"<<endl << "NOW IDX:"<<_idx << "  SUM:"<<_sum<<endl;
        for (int i = 0; i < N; i++){
            if (visit[i] == true) cout << i << " ";
        }
        cout << endl;
        /////////////////////////////////////////////
        */
        if (_sum > ret) ret = _sum;
        return;
    }

    for (int n_idx = _idx; n_idx < N; n_idx++){
        if (visit[n_idx] == true) continue;
        visit[n_idx] = true;
        if (n_idx + board[n_idx][T] > N) DFS(n_idx + board[n_idx][T], _sum);
        else DFS(n_idx + board[n_idx][T], _sum + board[n_idx][P]);
        visit[n_idx] = false;
    }
}

int main()
{
    init();
    DFS(0, 0);
    cout << ret;
    return 0;
}
