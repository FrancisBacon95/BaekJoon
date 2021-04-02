#include <iostream>
#include <deque>
using namespace std;
const int EMPTY = -1;
const int VIRUS = -2;
const int WALL  = -3;

const int CHECK =  1;
const int SPACE =  0;

const int d_row[4] = {0,  0, 1, -1};
const int d_col[4] = {1, -1, 0,  0};

int N, M, ret = 1000;
int board[50][50] = {0, };
int virus[10][ 2] = {0, };
int virus_size    = 0    ;
void init(){
    cin >> N >> M;
    for (int r = 0; r < N; r++){
        for (int c = 0; c < N; c++){
            int type; cin >> type;
            if      (type == 0) board[r][c] = EMPTY;
            else if (type == 1) board[r][c] = WALL ;
            else if (type == 2) {
                board[r][c] = VIRUS;
                virus[virus_size++][SPACE] = r*100 + c;
            }
        }
    }
}

void diffuse(){
    int n_board[50][50];
    int cnt_EMPTY = 0;
    ///1. board -> n_board
    for (int r = 0; r < N; r++){
        for (int c = 0; c < N; c++){
            n_board[r][c] = board[r][c];
            if (n_board[r][c] == EMPTY) cnt_EMPTY++;
        }
    }

    ///2. Ȱ�� virus ó�� �� QUE ����
    deque<int> que;
    for (int i = 0; i < virus_size; i++){
        if (virus[i][CHECK] == 1){
            //(1) QUE ����
            que.push_back(virus[i][SPACE])   ;
            //(2) n_board�� ���ʽð� 0���� �ʱ�ȭ
            int tmp_r = virus[i][SPACE] / 100;
            int tmp_c = virus[i][SPACE] % 100;
            n_board[tmp_r][tmp_c] = 0;
        }
    }
    ///3. BFS
    while(!que.empty()){
        if (cnt_EMPTY == 0) break;
        int c_vir  = que.front(); que.pop_front();
        int c_row  = c_vir / 100;
        int c_col  = c_vir % 100;
        int c_time = n_board[c_row][c_col];

        //(1) ���� �ܰ� ����
        for (int d = 0; d < 4; d++){
            int n_row  = c_row  + d_row[d];
            int n_col  = c_col  + d_col[d];
            int n_time = c_time + 1       ;

            //(1-1) ���� ��� OR ��  : CONTINUE
            if (n_row < 0 || n_row >= N || n_col < 0 || n_col >= N || n_board[n_row][n_col] == WALL || n_board[n_row][n_col] >= 0) continue;
            //(1-2) EMPTY, ��Ȱ��VIRUS : ����
            else if (n_board[n_row][n_col] == EMPTY || n_board[n_row][n_col] == VIRUS){
                if (n_board[n_row][n_col] == EMPTY) cnt_EMPTY--;
                n_board[n_row][n_col] = n_time;
                que.push_back(n_row*100 + n_col);
            }
        }
    }
    ///4. Ȯ�� �Ϸ� Ȯ��(EMPTY ������ Ȯ��)
    if (cnt_EMPTY <= 0) {
        int tmp_max = 0;
        for (int r = 0; r < N; r++){
            for (int c = 0; c < N; c++){
                if (tmp_max < n_board[r][c]) tmp_max = n_board[r][c];
            }
        }
        if (ret > tmp_max) ret = tmp_max;
    }
}

//SELECT ����  ����
void select(int _cnt, int _start){
    if (_cnt == M){
        diffuse();
        return;
    }

    for (int i = _start; i < virus_size; i++){
        if (virus[i][CHECK] == 1) continue;
        virus[i][CHECK] = 1;
        select(_cnt + 1, i + 1);
        virus[i][CHECK] = 0;
    }
}

int main()
{
    init();
    select(0, 0);
    if (ret == 1000) cout << -1 ;
    else             cout << ret;
    return 0;
}
