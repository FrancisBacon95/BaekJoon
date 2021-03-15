#include <iostream>
using namespace std;
int N, answer;

struct BOARD{
    int map[20][20];

    void rotate(){
        int tmp_map[20][20];
        //90µµ È¸Àü
        for (int r=0; r<N; r++){
            for (int c=0; c<N; c++){
                tmp_map[r][c] = map[N - c -1][r];
            }
        }

        for (int r=0; r<N; r++){
            for (int c=0; c<N; c++){
                map[r][c] = tmp_map[r][c];
            }
        }
    }

    int get_Max(){
        int ret;
        for (int r=0; r<N; r++){
            for (int c=0; c<N; c++){
                if (ret < map[r][c]) ret = map[r][c];
            }
        }
        return ret;
    }

    void up(){
        int tmp_map[20][20];
        for (int c=0; c<N; c++){
            int flag = 0, target = -1;
            for (int r=0; r<N; r++){
                if (map[r][c] == 0) continue;
                if (flag == 1 && map[r][c] == tmp_map[target][c]) tmp_map[target][c] *=2, flag = 0;
                else tmp_map[++target][c]  = map[r][c], flag = 1;
            }
            target++;
            for (target; target<N; target++) tmp_map[target][c] = 0;
        }

        for (int c=0; c < N; c++){
            for (int r=0; r < N; r++){
                map[r][c] = tmp_map[r][c];
            }
        }
    }
};


void dfs(BOARD cur, int cnt){
    if (cnt == 5){
        int candi = cur.get_Max();
        if (answer < candi) answer = candi;
        return;
    }

    for (int dir = 0; dir < 4; dir++){
        BOARD next = cur;
        next.up();
        dfs(next, cnt+1);
        cur.rotate();
    }
}

int main()
{
    BOARD board;
    cin >> N;
    for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            cin >> board.map[i][j];
        }
    }
    answer = 0;
    dfs(board, 0);
    cout << answer;

    return 0;
}
