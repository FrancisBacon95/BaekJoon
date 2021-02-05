#include <iostream>
using namespace std;
int N, M;

int ret = 100*100;
int board[50][50] = {0, };

struct CHICK{
    int row, col;
    bool check = false;
};

struct HOUSE{
    int row, col;
};

CHICK chick[13 ];
HOUSE house[100];

int house_size = 0;
int chick_size = 0;

void input(){
    cin >> N >> M;
    for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            cin >> board[i][j];
            if (board[i][j] == 1) {
                house[house_size].row = i;
                house[house_size].col = j;
                house_size++;
            }
            if (board[i][j] == 2) {
                chick[chick_size].row = i;
                chick[chick_size].col = j;
                chick_size++;
            }
        }
    }
}

void solve(){
    int sum = 0;
    for (int i=0; i<house_size; i++){
        int min_dist = 101;

        for (int j=0; j<chick_size; j++){
            if (!chick[j].check) continue;
            int dist = (int)abs(house[i].row - chick[j].row) + (int)abs(house[i].col - chick[j].col);
            if (dist < min_dist) min_dist = dist;
        }
        sum += min_dist;
    }

    if (ret > sum) ret = sum;
}

void DFS(int idx, int cnt){
    if (cnt == M){
        solve();
        return;
    }

    for (int i=idx; i<chick_size; i++){
        if (chick[i].check) continue;

        chick[i].check = true ;
        DFS(i, cnt+1);
        chick[i].check = false;
    }
}

int main()
{
    input();
    DFS(0,0);

    cout << ret;
    return 0;
}
