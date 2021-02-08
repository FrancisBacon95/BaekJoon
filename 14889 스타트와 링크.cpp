#include <iostream>
using namespace std;

int N;

int res = (((20*20)-20)/2)*100 + 1;

int  board    [20][20] = {0, };
int  true_team [20][2]  = {0, };
int  false_team[20][2]  = {0, };

bool all_team [20]     = {false, };

void input(){
    cin >> N;
    for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            cin >> board[i][j];
        }
    }
}

void t_score(int idx, int cnt, int &c_score){
    if (cnt == 2){
        int point[2] = {0, };
        int pt_idx   = 0;
        for (int i=0; i < N/2; i++){
            if (pt_idx          == 2) break;
            if (true_team[i][1] == 1) point[pt_idx++] = true_team[i][0];
        }
        c_score += board[point[0]][point[1]];
        c_score += board[point[1]][point[0]];
        return;
    }

    for (int i = idx; i < N/2; i++){
        if (true_team[i][1] == 1) continue;
        true_team[i][1] = 1;
        t_score(i, cnt+1, c_score);
        true_team[i][1] = 0;
    }
}

void f_score(int idx, int cnt, int &c_score){
    if (cnt == 2){
        int point[2] = {0, };
        int pt_idx   = 0;
        for (int i=0; i < N/2; i++){
            if (pt_idx          == 2) break;
            if (false_team[i][1] == 1) point[pt_idx++] = false_team[i][0];
        }
        c_score += board[point[0]][point[1]];
        c_score += board[point[1]][point[0]];
        return;
    }

    for (int i = idx; i < N/2; i++){
        if (false_team[i][1] == 1) continue;
        false_team[i][1] = 1;
        f_score(i, cnt+1, c_score);
        false_team[i][1] = 0;
    }
}

void team_select(int idx, int cnt){
    if (cnt == N/2){
        int true_idx  = 0;
        int false_idx = 0;
        for (int i = 0; i < N; i++){
            if (all_team[i]) true_team [true_idx++ ][0] = i;
            else             false_team[false_idx++][0] = i;
        }
        int true_score = 0, false_score = 0;
        t_score(0, 0, true_score );
        f_score(0, 0, false_score);
        if (abs(true_score - false_score) < res) res = abs(true_score - false_score);
        return;
    }

    for (int i = idx; i < N; i++){
        if (all_team[i]) continue;
        all_team[i] = true;
        true_team[cnt][0] = i;
        team_select(i, cnt+1);
        all_team[i] = false;
        true_team[cnt][0] = 0;
    }
}

int main()
{
    input();
    team_select(0, 0);
    cout<< res;
    return 0;
}
