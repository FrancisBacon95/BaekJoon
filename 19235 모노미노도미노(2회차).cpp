#include <iostream>
#define GREEN 0
#define BLUE  1
using namespace std;
int N, ret = 0;
int board[2][6][4] = {0, };

void debug(int _color){
    if (_color == GREEN){
        cout << endl << "GREEN BOARD" <<endl;
        for (int r = 0; r < 6; r++){
            for (int c = 0; c < 4; c++){
                cout <<  board[GREEN][r][c] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
    else {
        cout << endl << "BLUE BOARD"<< endl;
        for (int r = 0; r < 6; r++){
            for (int c = 0; c < 4; c++){
                cout <<  board[BLUE ][r][c] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
}

int answer(){
    int local_ret = 0;
    for(int color=0; color<2; color++){
      for(int row=0; row<6; row++){
         for(int col=0; col<4; col++){
            if (board[color][row][col]!=0) local_ret++;
         }
      }
    }
    return local_ret;
}

bool detect(int _color, int _row, int _cnt){
    int cnt_chck = 0;
    for (int col = 0; col < 4; col++){
        if (board[_color][_row][col] != 0) cnt_chck++;
    }

    if (cnt_chck >= _cnt) return false;
    else                  return true ;
}

void del_row(int _color, int _row){
    for (int col = 0; col < 4; col++){
        board[_color][_row][col] = 0;
    }
}

void top_del(int _color){
    //(1) 0~1행 원소 존재 여부 확인
    int top_cnt = 0;
    for (int r = 0; r < 2; r++){
        if (!detect(_color, r, 1)) top_cnt++;
    }
    for (int r = 6 - top_cnt; r < 6; r++){
        del_row(_color, r);
    }

    //(2) 제거된 행 수만큼 아래로 내림
    for (int r = 5 - top_cnt; r > -1; r--){
        for (int c = 0; c < 4; c++){
            board[_color][r + top_cnt][c] = board[_color][r][c];
        }
    }
    //(3) 이동시 마지막에 남은 0~1행 원상복구
    for (int c = 0; c < 4; c++){
        board[_color][0][c] = 0;
        board[_color][1][c] = 0;
    }
}

void move(int _color, int _row, int _col, int _type, int _idx){
    // TYPE 1. c_col만 만족하는지 여부 확인
    if (_type == 1){
        int n_row;
        for(int c_row = _row; c_row < 6; c_row++){
            n_row = c_row;
            if (c_row != 5 && board[_color][c_row][_col] == 0 && board[_color][c_row+1][_col] != 0) break;
        }
        //이동 후 기존 자리는 원상복구
        board[_color][ _row][_col] =   0;
        board[_color][n_row][_col] = _idx;
    }
    // TYPE 2. c_col, c_col+1 모두 만족하는지 여부 확인
    if (_type == 2){
        int n_row;
        for(int c_row = _row; c_row < 6; c_row++){
            n_row = c_row;
            if (c_row != 5 &&  board[_color][c_row  ][_col] == 0 && board[_color][c_row  ][_col+1] == 0
                           && (board[_color][c_row+1][_col] != 0 || board[_color][c_row+1][_col+1] != 0))
                break;
        }
        //이동 후 기존 자리는 원상복구
        board[_color][ _row][_col  ] =    0;
        board[_color][ _row][_col+1] =    0;
        board[_color][n_row][_col  ] = _idx;
        board[_color][n_row][_col+1] = _idx;
    }
    // TYPE 3. row + 1 행에서 만족하는지 여부 확인
    if (_type == 3){
        int n_row;
        for(int c_row = _row+1; c_row < 6; c_row++){
            n_row = c_row;
            if (c_row != 5 && board[_color][c_row][_col] == 0 && board[_color][c_row+1][_col] != 0) break;
        }
        //이동 후 기존 자리는 원상복구
        board[_color][ _row  ][_col] =    0;
        board[_color][ _row+1][_col] =    0;
        board[_color][n_row-1][_col] = _idx;
        board[_color][n_row  ][_col] = _idx;
    }
}

int type_detect(int _color, int _row, int _col){
    int c_idx = board[_color][_row][_col];

    //오른쪽, 위쪽만 확인
    int d_row[4] = {0, 0, 0, -1};
    int d_col[4] = {0, 0, 1,  0};
    for (int type = 2; type < 4; type++){
        int n_row = _row + d_row[type];
        int n_col = _col + d_col[type];
        int n_idx = board[_color][n_row][n_col];
        if (n_row < 0 || n_col >=4) continue;
        if (c_idx == n_idx) return type;
    }
    return 1;
}

void post_bingo(int _color, int _row){
    for (int c_row = _row; c_row > -1; c_row--){
        for (int c_col = 0; c_col < 4; c_col++){
            if (board[_color][c_row][c_col] == 0) continue;
            int type = type_detect(_color, c_row, c_col);
            int idx = board[_color][c_row][c_col];
            if (type == 3) move(_color, c_row-1, c_col, type, idx);
            else           move(_color, c_row  , c_col, type, idx);
        }
    }
}

void bingo(int _color){
    bool is_removed = false;
    for (int row = 0; row < 6; row++){
        if (!detect(_color, row, 4)){
            is_removed = true;
            del_row(_color, row);
            ret++;
            if (row > 0) post_bingo(_color, row-1);
        }
    }

    if (is_removed) bingo(_color);
}

void solution(int _color, int _col, int _type, int _idx){
    /// 1. 블럭 진입
    move(_color, 0, _col, _type, _idx);

    /// 2. 빙고 탐색 및 처리
    bingo(_color);

    /// 3. 최상단 2개 열 처리
    top_del(_color);
}

void init(){
    cin >> N;
    for (int i = 1; i <= N; i++){
        int type, row, col; cin >> type >> row >> col;
        if      (type == 2){
            solution(GREEN, col, 2, i);
            solution( BLUE, row, 3, i);
        }
        else if (type == 3){
            solution(GREEN, col, 3, i);
            solution( BLUE, row, 2, i);
        }
        else if (type == 1){
            solution(GREEN, col, 1, i);
            solution( BLUE, row, 1, i);
        }
    }
}

int main()
{
    init();
    cout << ret << endl << answer() << endl;
    return 0;
}
