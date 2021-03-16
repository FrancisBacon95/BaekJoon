#include <iostream>
using namespace std;
int N, M, ret= 11;
int H_row, H_col;
int d_row[4] = {0,  0, 1, -1};
int d_col[4] = {1, -1, 0,  0};

struct GLOBE{
    int row, col;
};

struct BOARD{
    char board[10][10];
};

void debug(BOARD board){
    cout <<endl;
    for (int r=0; r<N; r++){
        for (int c=0; c<M; c++){
            cout << board.board[r][c] << " ";
        }
        cout << endl;
    }
    cout << endl << endl;
}

int B_move(GLOBE& _blue, int d, BOARD& _board){
    while(true){
        int n_row = _blue.row + d_row[d];
        int n_col = _blue.col + d_col[d];
        char spot = _board.board[n_row][n_col];
        if      (spot == '#') return 0;
        else if (spot == 'O') return 1;
        else if (spot == 'R') return 2;
        else if (spot == '.') {
            _board.board[_blue.row][_blue.col] = '.';
            _blue.row = n_row;
            _blue.col = n_col;
            _board.board[_blue.row][_blue.col] = 'B';
        }
    }
}

int R_move(GLOBE& _red, int d, BOARD& _board, int len){
    while(true){
        int n_row = _red.row + d_row[d];
        int n_col = _red.col + d_col[d];
        char spot = _board.board[n_row][n_col];
        if      (spot == 'r') break;
        else if (spot == '#') break;
        else if (spot == 'B') break;
        else if (spot == 'O') {
            _board.board[_red.row][_red.col] = '.';
            _red.row = n_row;
            _red.col = n_col;
            len = 100;
            break;
        }
        else if (spot == '.') {
            _board.board[_red.row][_red.col] = '.';
            _red.row = n_row;
            _red.col = n_col;
            _board.board[_red.row][_red.col] = 'R';

            len++;
        }
    }
    return len;
}

void BFS(GLOBE _red, GLOBE _blue, BOARD _board, int cnt){
    if ((_blue.row == H_row && _blue.col == H_col) || cnt >= ret) return;
    if (_red.row == H_row && _red.col == H_col){
        ret = cnt;
        return;
    }

    for (int d=0; d<4; d++){
        BOARD n_board = _board;
        GLOBE n_blue  = _blue ;
        GLOBE n_red   = _red  ;

        int B_chck = B_move(n_blue, d, n_board);
        if (B_chck == 1) continue;

        int R_chck = R_move(n_red , d, n_board, 0);
        if (B_chck == 2) B_chck = B_move(n_blue, d, n_board);
        if (B_chck == 1) continue;

        BFS(n_red, n_blue, n_board, cnt+1);
    }
}

int main()
{
    GLOBE red;
    GLOBE blue;
    BOARD board;

    cin >> N >> M;
    for (int r=0; r<N; r++){
        for (int c=0; c<M; c++){
            cin >> board.board[r][c];
            if (board.board[r][c] == 'R'){
                red.row = r;
                red.col = c;
            }
            if (board.board[r][c] == 'B'){
                blue.row = r;
                blue.col = c;
            }
            if (board.board[r][c] == 'O'){
                H_row = r;
                H_col = c;
            }
        }
    }

    BFS(red, blue, board, 0);

    if (ret > 10) ret = -1;
    cout << ret;
    return 0;
}
