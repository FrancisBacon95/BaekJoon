#include <iostream>
#include <stack>
#include <vector>
using namespace std;

struct CCTV{
    int row, col;
    int type;
};

int N, M, ret;
int EMPTY = 0;
int board[8][8]={0, };
int cctv_size;
CCTV cctv[8];

const int rot_size[] = {4, 2, 4, 4, 1};

void input(){
    cin >> N >> M;
    for (int i=0; i<N; i++){
        for (int j=0; j<M; j++){
            cin >> board[i][j];

            if (board[i][j] != 0 && board[i][j] != 6){
                cctv[cctv_size].row  = i;
                cctv[cctv_size].col  = j;
                cctv[cctv_size].type = board[i][j] -1;
                cctv_size++;
            }
        }
    }
}

void board_copy(int desc[8][8], int src[8][8]){
    for (int i=0; i<N; i++){
        for (int j=0; j<M; j++){
            desc[i][j] = src[i][j];
        }
    }
}

void update(int dir, CCTV cctv){
    dir  = (dir % 4);

    if      (dir == 0){
        for (int col = cctv.col+1; col <  M; col++){
            if (board[cctv.row][col] == 6) break;
            board[cctv.row][col] = -1;
        }
    }
    else if (dir == 1){
        for (int row = cctv.row-1; row >= 0; row--){
            if (board[row][cctv.col] == 6) break;
            board[row][cctv.col] = -1;
        }
    }
    else if (dir == 2){
        for (int col = cctv.col-1; col >= 0; col--){
            if (board[cctv.row][col] == 6) break;
            board[cctv.row][col] = -1;
        }
    }
    else if (dir == 3){
        for (int row = cctv.row+1; row <  N; row++){
            if (board[row][cctv.col] == 6) break;
            board[row][cctv.col] = -1;
        }
    }
}

void dfs(int cctv_idx){
    if (cctv_idx == cctv_size){
        int candi = 0;
        for (int i=0; i<N; i++){
            for (int j=0; j<M; j++){
                if (board[i][j] == 0) candi++;
            }
        }
        if (ret > candi) ret = candi;
        return;
    }

    int backup[8][8];
    int type = cctv[cctv_idx].type;
    //각 CCTV의 종류에 따라 나올 수 있는 형태를 모두 점검
    for (int d = 0; d <rot_size[type]; d++){
        //기존의 board를 백업한다.
        board_copy(backup, board);
        if (type == 0){
            update(d, cctv[cctv_idx]); //해당 cctv를 d 형태로 두고 실시한다.
        }
        else if (type == 1){
            update(d  , cctv[cctv_idx]);
            update(d+2, cctv[cctv_idx]);
        }
        else if (type == 2){
            update(d  , cctv[cctv_idx]);
            update(d+1, cctv[cctv_idx]);
        }
        else if (type == 3){
            update(d,   cctv[cctv_idx]);
            update(d+1, cctv[cctv_idx]);
            update(d+2, cctv[cctv_idx]);
        }
        else if (type == 4){
            update(d  , cctv[cctv_idx]);
            update(d+1, cctv[cctv_idx]);
            update(d+2, cctv[cctv_idx]);
            update(d+3, cctv[cctv_idx]);
        }
        dfs(cctv_idx+1);
        board_copy(board, backup);
    }
}

int main()
{
    ret = 100;
    input();
    dfs(0);
    cout << ret;
    return 0;
}
