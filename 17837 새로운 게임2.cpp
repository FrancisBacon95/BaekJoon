#include <iostream>
#include <stack>
using namespace std;

int d_row[4] = { 0,  0, -1, +1};
int d_col[4] = {+1, -1,  0,  0};
const int COLOR_FLOOR = 0;
const int WHITE = 0;
const int RED   = 1;
const int BLUE  = 2;
struct HORSE {
   int row, col, dir;
   int floor = 1;
};

int N, K, t = 1;
int board[10][12][12] = {0, }; // { color, 1st, 2nd, 3rd, 4th, ...}
HORSE horse[11];

void init() {
    cin >> N >> K;

    //Initialize board
    for (int i=0; i<N; i++) {
        for(int j=0; j<N; j++) {
            cin >> board[COLOR_FLOOR][i][j];
        }
    }

    //Initialize horses
    for (int i=1;i<=K; i++) {
        cin >> horse[i].row >> horse[i].col >> horse[i].dir;
        horse[i].row--, horse[i].col--, horse[i].dir--;
        board[1][horse[i].row][horse[i].col] = i;
    }//ok
}

bool check_four(int i){
    //Check every horse
    if (board[4][horse[i].row][horse[i].col] != 0) return true;
    return false;
}

void default_move(int c_row, int c_col, int c_floor, int n_row, int n_col, int &n_floor){
    ///DEFAULT MOVE
    //detect floor of next location
    for (int i=1; i<5; i++){
        if (board[i][n_row][n_col] == 0) {
            n_floor = i;
            break;
        }
    }
    //move from current location to next location
    for (int f=c_floor; f<10; f++){
        if (board[f][c_row][c_col] == 0) {
            n_floor--;
            break;
        }
        int c_horse = board[f][c_row][c_col];
        //Change horse info
        horse[c_horse].row   = n_row;
        horse[c_horse].col   = n_col;
        horse[c_horse].floor = n_floor;
        //Change board info
        board[n_floor][n_row][n_col] = c_horse;
        board[f      ][c_row][c_col] = 0;
        //Up floor
        n_floor++;
    }
}

void move(int idx){
    int c_row   = horse[idx].row;
    int c_col   = horse[idx].col;
    int c_dir   = horse[idx].dir;
    int c_floor = horse[idx].floor;

    int n_row   = c_row + d_row[c_dir];
    int n_col   = c_col + d_col[c_dir];
    int n_color;
    if (n_row < 0 || n_row >= N || n_col < 0 || n_col >= N) n_color = BLUE;
    else n_color = board[COLOR_FLOOR][n_row][n_col];

    if      (n_color == WHITE) {
        ///DEFAULT MOVE
        //detect floor of next location
        int n_floor = 1;
        default_move(c_row, c_col, c_floor, n_row, n_col, n_floor);
    }
    else if (n_color == RED  ) {
        ///DEFAULT MOVE
        //detect floor of next location
        int n_floor = 1;
        default_move(c_row, c_col, c_floor, n_row, n_col, n_floor);

        //Reverse floor for changed horses
        stack<int> STACK;
        for (int i = n_floor; i > 0; i--) {
            STACK.push(board[i][n_row][n_col]);
            if (board[i][n_row][n_col] == idx) break;
        }
        while (!STACK.empty()) {
            int c_horse = STACK.top();
            STACK.pop();
            board[n_floor][n_row][n_col] = c_horse;
            horse[c_horse].floor = n_floor;
            n_floor--;
        }
    }
    else if (n_color == BLUE ) {
        //reverse direction
        int n_dir = -1;
        if      (c_dir == 0) n_dir = 1;
        else if (c_dir == 1) n_dir = 0;
        else if (c_dir == 2) n_dir = 3;
        else if (c_dir == 3) n_dir = 2;
        n_row   = c_row + d_row[n_dir];
        n_col   = c_col + d_col[n_dir];
        //if next location is also out range or blue, return
        if (n_row < 0 || n_row >= N || n_col < 0 || n_col >= N) {
            horse[idx].dir = n_dir;
            return;
        }
        else{
            n_color = board[COLOR_FLOOR][n_row][n_col];
            horse[idx].dir = n_dir;
            if (n_color == BLUE) return;
            ///DEFAULT MOVE
            //detect floor of next location
            move(idx);
        }
    }
}

int main()
{
   init();
    while(true) {
        if (t >= 1000){
            cout << -1;
            return 0;
        }
        for(int i=1; i <= K; i++) {
            move(i);
            if (check_four(i)) {
                cout<<t;
                return 0;
            }
        }
        t++;
    }
    return 0;
}
