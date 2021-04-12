/*
1 type: 한칸
2 type: 가로
3 type: 세로

빙고: 한 줄 꽉 찬 거

블록이 빨간 줄로 가는 경우 없음

1) 빙고처리
2) 탑라인 처리
*/
#include <iostream>
using namespace std;
const int GREEN = 0;
const int BLUE  = 1;
int N, ret = 0;
int board[2][6][4] = {0, };

void debug(int _color){
    cout << endl << "DEBUG: "<<_color<<endl;
    for (int row = 0; row < 6; row++){
        for (int col = 0; col < 4; col++){
            cout << board[_color][row][col] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int cnt_block(){
    int local_ret = 0;
    for (int color = GREEN; color <= BLUE; color++){
        for (int row = 0; row < 6; row++){
            for (int col = 0; col < 4; col++){
                if (board[color][row][col] > 0) local_ret++;
            }
        }
    }
    return local_ret;
}

void move(int _type, int _row, int _col, int _color){
    int n_row = _row;
    int   idx = board[_color][_row][_col];
    board[_color][_row][_col] = 0;

    if      (_type == 1){

        while(n_row < 6){
            if (board[_color][n_row][_col] != 0) break;
            n_row++;
        }
        n_row--;
        board[_color][n_row][_col] = idx;
    }
    else if (_type == 2){
        board[_color][_row    ][_col + 1] = 0;
        while(n_row < 6){
            if (board[_color][n_row][_col] != 0 || board[_color][n_row][_col + 1] != 0) break;
            n_row++;
        }
        n_row--;
        board[_color][n_row    ][_col    ] = idx;
        board[_color][n_row    ][_col + 1] = idx;
    }
    else if (_type == 3){
        board[_color][_row + 1][_col    ] = 0;
        while(n_row < 5){
            if (board[_color][n_row + 1][_col] != 0) break;
            n_row++;
        }
        n_row--;
        board[_color][n_row    ][_col    ] = idx;
        board[_color][n_row + 1][_col    ] = idx;
    }
}

void input(int _type, int _idx, int _row, int _col, int _color){
    board[_color][_row][_col] = _idx;

    if      (_type == 2) board[_color][_row    ][_col + 1] = _idx;
    else if (_type == 3) board[_color][_row + 1][_col    ] = _idx;

    move(_type, _row, _col, _color);
}

int line_cnt(int _row, int _color){
    int cnt = 0;

    for (int i = 0; i < 4; i++){
        if (board[_color][_row][i] != 0) cnt++;
    }

    return cnt;
}

int bingo_detect(int _color){
    for (int r = 0; r < 6; r++){
        int cnt = line_cnt(r, _color);
        if (cnt == 4) return r;
    }
    return -1;
}

void delete_line(int _row, int _color){
    for (int c = 0; c < 4; c++) board[_color][_row][c] = 0;

    const int d_row[4] = {1, -1, 0,  0};
    const int d_col[4] = {0,  0, 1, -1};
    //한칸씩 돌면서 타입 탐색
    for (int c_row = _row-1; c_row > -1; c_row--){
        for (int c_col = 0; c_col < 4; c_col++){
            int c_idx = board[_color][c_row][c_col];
            if (c_idx == 0) continue;

            //타입 선정
            int type  = -1;
            for (int d = 0; d <= 3; d++){
                int n_row = c_row + d_row[d];
                int n_col = c_col + d_col[d];
                int n_idx = board[_color][n_row][n_col];
                if (n_idx == c_idx) {
                    type = d;
                    break;
                }
            }

            //각 블록 이동
            if      (type == -1) move(1, c_row    , c_col    , _color);
            else if (type ==  0) move(3, c_row    , c_col    , _color);
            else if (type ==  1) move(3, c_row - 1, c_col    , _color);
            else if (type ==  2) move(2, c_row    , c_col    , _color);
            else if (type ==  3) move(2, c_row    , c_col - 1, _color);
        }
    }
}

int main()
{
    cin >> N;
    for (int i = 1; i <= N; i++){
        int t, x, y;
        cin >> t >> x >> y;
        ///1. TOP LINE 제거 및 INPUT
        if      (t == 1){
            input(1, i, 0, y, GREEN);
            input(1, i, 0, x, BLUE );
        }
        else if (t == 2){
            input(2, i, 0, y, GREEN);
            input(3, i, 0, x, BLUE );
        }
        else if (t == 3){
            input(3, i, 0, y, GREEN);
            input(2, i, 0, x, BLUE );
        }
        ///2. BINGO 처리
        for (int color = 0; color < 2; color++) {

            ///1) bingo 안 생길 때까지 bingo 제거
            while (true){
                int bingo_line = bingo_detect(color);
                if (bingo_line == -1) break;
                ret++;
                delete_line(bingo_line, color);
            }

            ///2) top_line 제거
            while(true){
                //2-1) top_line 개수 집계
                int top_line = 0;
                for (int row = 0; row <= 1; row++){
                    if (line_cnt(row, color) > 0) top_line++;
                }

                if (top_line == 0) break;

                //2-2) top_line 개수만큼 마지막 라인 제거 반복
                for (int i = 0; i < top_line; i++) delete_line(5, color);
            }
        }
    }
    //debug(GREEN);
    //debug(BLUE );
    cout << ret << endl <<cnt_block();
    return 0;
}
