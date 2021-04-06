#include <iostream>
using namespace std;
const int d_row[4] = {-1, 0, 1,  0};
const int d_col[4] = { 0, 1, 0, -1};
int N, M, ret = 0;
int board[50][50] = {0, };
bool visit[50][50] = {false, };
struct ROBOT{
    int row, col;
    int dir;
};

ROBOT robot;

void debug(){
    cout << endl;
    for (int r = 0; r < N; r++){
        for (int c =0; c < M; c++){
            cout << board[r][c] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void init(){
    cin >> N >> M;

    cin >> robot.row >> robot.col >> robot.dir;

    for (int r = 0; r < N; r++){
        for (int c =0; c < M; c++){
            cin >> board[r][c];
        }
    }
}

void clean(){
    int c_row = robot.row;
    int c_col = robot.col;
    if (visit[c_row][c_col] == true) return;
    visit[c_row][c_col] = true;
    ret += 1;
}

bool detect_left(){
    int c_dir = robot.dir;
    int left_r = robot.row;
    int left_c = robot.col;
    if      (c_dir == 0) left_c--;
    else if (c_dir == 1) left_r--;
    else if (c_dir == 2) left_c++;
    else if (c_dir == 3) left_r++;

    //왼쪽 방향: (벽 OR 청소된 구역) -> FALSE
    if (board[left_r][left_c] == 1 || visit[left_r][left_c] == true) return false;

    //왼쪽 방향: 청소 요망 구역 -> 좌측회전 -> 한 칸 전진
    robot.dir = (c_dir + 3) % 4;
    robot.row += d_row[robot.dir];
    robot.col += d_col[robot.dir];
    return true;
}

void rotate_left(){
    int c_dir = robot.dir;
    robot.dir = (c_dir + 3) % 4;
}

bool move_back(){
    int c_dir = robot.dir;
    int c_row = robot.row;
    int c_col = robot.col;
    //(1)뒤쪽이 벽인지 확인
    bool wall = false;
    if      (robot.dir == 0 && board[c_row+1][c_col  ] == 1) wall = true;
    else if (robot.dir == 1 && board[c_row  ][c_col-1] == 1) wall = true;
    else if (robot.dir == 2 && board[c_row-1][c_col  ] == 1) wall = true;
    else if (robot.dir == 3 && board[c_row  ][c_col+1] == 1) wall = true;
    //(2-1) 뒤쪽 벽 O -> return;
    if (wall) return false;
    //(2-2) 뒤쪽 벽 X -> 후진;
    if      (robot.dir == 0) robot.row += 1;
    else if (robot.dir == 1) robot.col -= 1;
    else if (robot.dir == 2) robot.row -= 1;
    else if (robot.dir == 3) robot.col += 1;
    return true;
}

int main()
{
    init();
    while (true){
        /// 1. 청소 여부 확인 후 청소
        clean();
        int chck = 0;
        /// 2. 좌측 WATCH -> 갈 곳 X -> 좌측 ROTATE
        while(!detect_left() && chck < 4){
            rotate_left();
            chck++;
        }
        /// 3. 4방향 모두 돌았는데, 갈 곳 없는 경우
        if (chck == 4){
            if (!move_back()){
                cout << ret;
                return 0;
            }
        }
    }
    return 0;
}
