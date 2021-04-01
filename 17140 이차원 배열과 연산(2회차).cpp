#include <iostream>
using namespace std;
const int NUM = 0;
const int CNT = 1;
int max_R = 3, max_C = 3;
int R, C, K, t = 0;
int board[100][100] = {0, };

void debug(){
    if (max_R >= max_C) cout <<"R FUNC"<<endl;
    else cout <<"C FUNC"<<endl;
    for (int i = 0; i < max_R; i++){
        for (int j = 0; j < max_C; j++){
            cout << board[i][j] <<" ";
        }
        cout << endl;
    }
    cout << endl;
}

void init(){
    cin >> R >> C >> K; R--, C--;
    for (int r = 0; r < 3; r++){
        for (int c = 0; c < 3; c++){
            cin >> board[r][c];
        }
    }
}

void R_func(){
    ///1. �� �ึ�� ���鼭 �ǽ�
    for (int r = 0; r < max_R; r++){
        //(0)�� COL���鼭 CAND�� �����Ͽ� ����
        int cand[100][2] = {0, };
        int cand_size = 0;
        for (int c = 0; c < max_C; c++){
            int tmp_num = board[r][c];
            if (tmp_num == 0) continue;
            //(2) CAND Ž���ϸ� ������ +1
            bool in_cand = false;
            for (int i = 0; i < cand_size; i++){
                if (cand[i][NUM] == tmp_num) {
                    cand[i][CNT]++;
                    in_cand = true;
                    break;
                }
            }
            //(3) ������ CAND�� �߰�
            if (!in_cand){
                cand[cand_size  ][NUM] = tmp_num;
                cand[cand_size++][CNT] = 1      ;
            }
        }

        //(4) CAND ����
        for (int i = 0; i < cand_size-1; i++){
            for (int j = i +1; j < cand_size; j++){
                int tmp_num = cand[j][NUM];
                int tmp_cnt = cand[j][CNT];
                //   (1) before CNT > after CNT      (2) before CNT == after CNT   AND   before NUM > after NUM
                if ( (cand[i][CNT] > cand[j][CNT]) || (cand[i][CNT] == cand[j][CNT] && cand[i][NUM] > cand[j][NUM]) ){
                    cand[j][NUM] = cand[i][NUM];
                    cand[j][CNT] = cand[i][CNT];

                    cand[i][NUM] = tmp_num;
                    cand[i][CNT] = tmp_cnt;
                }
            }
        }

        //(5) CAND -> BOARD
        int new_max_C = cand_size*2;
        for (int i = 0; i < new_max_C; i = i+2){
            board[r][i  ] = cand[i / 2][0];
            board[r][i+1] = cand[i / 2][1];
        }
        //(6) max_C ����
        if (max_C < new_max_C) max_C = new_max_C;
        //(7) max_C�� �� ��ġ�� �κ� 0 ó��
        else{
            for (int c = new_max_C; c < max_C; c++) board[r][c] = 0;
        }
    }
}

void C_func(){
    ///2. �� ������ ���鼭 ����
    for (int c = 0; c < max_C; c++){
        //(0)�� COL���鼭 CAND�� �����Ͽ� ����
        int cand[100][2] = {0, };
        int cand_size = 0;
        for (int r = 0; r < max_R; r++){
            int tmp_num = board[r][c];
            if (tmp_num == 0) continue;
            //(2) CAND Ž���ϸ� ������ +1
            bool in_cand = false;
            for (int i = 0; i < cand_size; i++){
                if (cand[i][NUM] == tmp_num) {
                    cand[i][CNT]++;
                    in_cand = true;
                    break;
                }
            }
            //(3) ������ CAND�� �߰�
            if (!in_cand){
                cand[cand_size  ][NUM] = tmp_num;
                cand[cand_size++][CNT] = 1      ;
            }
        }

        //(4) CAND ����
        for (int i = 0; i < cand_size-1; i++){
            for (int j = i +1; j < cand_size; j++){
                int tmp_num = cand[j][NUM];
                int tmp_cnt = cand[j][CNT];
                //   (1) before CNT > after CNT      (2) before CNT == after CNT   AND   before NUM > after NUM
                if ( (cand[i][CNT] > cand[j][CNT]) || (cand[i][CNT] == cand[j][CNT] && cand[i][NUM] > cand[j][NUM]) ){
                    cand[j][NUM] = cand[i][NUM];
                    cand[j][CNT] = cand[i][CNT];

                    cand[i][NUM] = tmp_num;
                    cand[i][CNT] = tmp_cnt;
                }
            }
        }
        //(5) CAND -> BOARD
        int new_max_R = cand_size*2;
        for (int i = 0; i < new_max_R; i = i+2){
            board[i  ][c] = cand[i / 2][0];
            board[i+1][c] = cand[i / 2][1];
        }
        //(6) max_R ����
        if (max_R < new_max_R) max_R = new_max_R;
        //(7) max_R�� �� ��ġ�� �κ� 0 ó��
        else{
            for (int r = new_max_R; r < max_R; r++) board[r][c] = 0;
        }
    }
}

void solution(int _t){
    if (_t > 100) {
        cout << -1;
        return;
    }
    if (board[R][C] == K) {
        cout << _t;
        return;
    }
    if (max_R >= max_C) R_func();
    else                C_func();

    solution(_t + 1);
}

int main()
{
    init();
    solution(0);
    return 0;
}
