#include <iostream>
#include <string.h>
#include <deque>
using namespace std;

#define RIGHT 0
#define LEFT  1
#define APPLE 1
#define SNAKE 9

int N, K, L, ret=1;

int board[100][100];
int trans[100][2];
int trans_idx = 0;

deque<int> DQ;
int dir;

// E S W N
int d_row[4] = {0, 1,  0, -1};
int d_col[4] = {1, 0, -1,  0};

void debug(){
    for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            cout << board[i][j] << " ";
        }
        cout<<endl;
    }
    cout<<endl<<endl;
}

void init(){
    cin >> N >> K;
    for (int i=0; i<K; i++){
        int r, c; cin >> r >> c; r--, c--;
        board[r][c] = 1;
    }
    cin >> L;
    for (int i=0; i<L; i++){
        int X; char C;
        cin >> X >> C;

        trans[i][0] = X;
        if (C == 'D')  trans[i][1] = RIGHT;
        if (C == 'L')  trans[i][1] = LEFT ;
    }
}

void grow(){
    int head     = DQ.front();
    int head_row = head / 100;
    int head_col = head % 100;

    int n_head_row = head_row + d_row[dir];
    int n_head_col = head_col + d_col[dir];

    board[n_head_row][n_head_col] = SNAKE;
    DQ.push_front(n_head_row*100 + n_head_col);
}

void movi(){
    grow();

    int tail     = DQ.back();
    int tail_row = tail / 100;
    int tail_col = tail % 100;

    DQ.pop_back();
    board[tail_row][tail_col] = 0;
}

int main()
{
    init();
    DQ.push_front(0);
    board[0][0] = SNAKE;

    while(true){
        int n_pnt = DQ.front();
        int n_row = n_pnt / 100 + d_row[dir];
        int n_col = n_pnt % 100 + d_col[dir];

        if (n_row < 0 || n_row >= N || n_col < 0 || n_col >= N) break;
        if (board[n_row][n_col] == SNAKE) break;

        if (board[n_row][n_col] == APPLE) grow();
        else                              movi();

        if (trans[trans_idx][0] == ret){
            if (trans[trans_idx][1] == RIGHT) dir = (dir + 1) % 4;
            else                              dir = (dir + 3) % 4;
            trans_idx++;
        }
        ret++;
    }

    cout << ret;
    return 0;
}
