#include <iostream>
#include <deque>
using namespace std;
struct DUST{
    int row  = -1   ;
    int col  = -1   ;
    int dens = -1   ;
};

int R, C, T;
const int d_row[] = {-1, +1,  0,  0};
const int d_col[] = { 0,  0, -1, +1};
int robot_row = -1;
int board[50][50]={0, };
int dust_idx = 0;

void input(){
    cin >> R >> C >> T;

    for (int r=0; r<R; r++) {
        for (int c=0; c<C; c++) {
            cin >> board[r][c];
            if (board[r][c] == -1 && robot_row == -1) robot_row = r;
        }
    }
}

void dust_diffusion() {

    //INITIALIZE QUEUE
    deque<DUST> que;
    for(int r=0; r<R; r++){
        for(int c=0; c<C; c++){
            if (board[r][c] > 0) {
                DUST tmp;
                tmp.row  = r;
                tmp.col  = c;
                tmp.dens = board[r][c];
                que.push_back(tmp);
            }
        }
    }//ok

    //UPDATE QUEUE
    int q_size = que.size(); //ok
    for (int i=0; i<q_size; i++){
        DUST c_dust = que.front();
        que.pop_front();

        //check division size
        int division = 0;

        for (int d=0; d<4; d++){
            int n_row = c_dust.row + d_row[d];
            int n_col = c_dust.col + d_col[d];
            if (n_row < 0 || n_row >= R || n_col < 0 || n_col >= C || board[n_row][n_col] == -1) continue;
            division++;
        }

        if (division == 0) {
            que.push_back(c_dust);
            continue;
        }

        int diffusion_size = int(c_dust.dens / 5);
        c_dust.dens = c_dust.dens - (diffusion_size * division);
        if (c_dust.dens > 0) que.push_back(c_dust);

        //create new dust
        for (int d=0; d<4; d++){
            int n_row  = c_dust.row + d_row[d];
            int n_col  = c_dust.col + d_col[d];

            if (diffusion_size == 0) break;
            if (n_row < 0 || n_row >= R || n_col < 0 || n_col >= C || board[n_row][n_col] == -1) continue;

            DUST n_dust;
            n_dust.row  = n_row         ;
            n_dust.col  = n_col         ;
            n_dust.dens = diffusion_size;
            que.push_back(n_dust);
        }
    }

    //CREATE NEW BOARD
    int n_board[50][50] = {0, };
    n_board[robot_row  ][0] = -1;
    n_board[robot_row+1][0] = -1;

    while (!que.empty()){
        DUST c_dust = que.front();
        que.pop_front();
        n_board[c_dust.row][c_dust.col] += c_dust.dens;
    }

    //UPDATE BOARD
    for(int r=0; r<50; r++){
        for(int c=0; c<50; c++){
            board[r][c] = n_board[r][c];
        }
    }
}

void purifier_work(){
    //INITIALIZE QUEUE
    deque<DUST> que;
    for(int r=0; r<R; r++){
        for(int c=0; c<C; c++){
            if (board[r][c] != 0) {
                DUST tmp;
                tmp.row  = r;
                tmp.col  = c;
                tmp.dens = board[r][c];
                que.push_back(tmp);
            }
        }
    }

    //UPDATE QUEUE
    int q_size = que.size();
    for (int i=0; i<q_size; i++){
        DUST x = que.front();
        que.pop_front();

        //UPDATE CURRENT DUST
        if      ((x.row >= 0             && x.row < robot_row && x.col == 0  ) ||
                 (x.row >= robot_row + 1 && x.row < R - 1     && x.col == C-1)  )
            x.row += 1;
        else if ((x.row >  0             && x.row <= robot_row && x.col == C-1) ||
                 (x.row >  robot_row + 1 && x.row <= R - 1     && x.col == 0  )  )
            x.row -= 1;
        else if ((x.row == robot_row     && x.col >= 1 && x.col <  C - 1) ||
                 (x.row == robot_row + 1 && x.col >= 1 && x.col <  C - 1)  )
            x.col += 1;
        else if ((x.row == 0             && x.col >= 1 && x.col <= C - 1) ||
                 (x.row == R - 1         && x.col >= 1 && x.col <= C - 1)  )
            x.col -= 1;

        if (board[x.row][x.col] == -1) continue;

        que.push_back(x);
    }

    //CREATE NEW BOARD
    int n_board[50][50] = {0, };
    n_board[robot_row  ][0] = -1;
    n_board[robot_row+1][0] = -1;

    while (!que.empty()){
        DUST c_dust = que.front();
        que.pop_front();
        n_board[c_dust.row][c_dust.col] += c_dust.dens;
    }

    //UPDATE BOARD
    for(int r=0; r<50; r++){
        for(int c=0; c<50; c++){
            board[r][c] = n_board[r][c];
        }
    }
}

int main()
{
    input();//ok

    for (int t=0; t<T; t++){
        dust_diffusion();
        purifier_work();
    }

    int ret = 0;
    for (int r=0; r<R; r++){
        for(int c=0; c<C; c++){
            if (board[r][c] > 0) ret +=board[r][c];
        }
    }
    cout << ret;
    return 0;
}

