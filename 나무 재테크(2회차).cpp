#include <iostream>
#include <deque>
using namespace std;
/*
1. 1���� ����, ���ʿ� ��� ĭ ���: 5

2. 1ĭ�� ������ ���� ����

3.
    ��: ���̸�ŭ ��� �Ա�, ���� +1
        � ����� ����
        ���̸�ŭ �� ���� ���� ����

    ����: ���� ���� ���� / 2 -> ���
    ����: ���̰� 5�� ��� -> 8�濡 1���� ���� ����
    �ܿ�: ��� �߰�

4. ���� N*N, ���� �ɴ� ����: M, K�� �� ���� ��
*/
const int d_row[8] = {-1, -1, -1,  0, 0,  1, 1, 1};
const int d_col[8] = {-1,  0,  1, -1, 1, -1, 0, 1};
int N, M, K;
int const_board[11][11] = {0, };
int board[11][11] = {0, };
int kids [11][11] = {0, };

deque<int> tree[11][11];

int answer(){
    int ret = 0;
    for (int r = 1; r <= N; r++){
        for (int c = 1; c <= N; c++){
            ret += tree[r][c].size();
        }
    }
    return ret;
}
void init(){
    cin >> N >> M >> K;
    for (int r = 1; r <= N; r++){
        for (int c = 1; c <= N; c++){
            //�ܿ￡ �Ѹ� ��� �ʱ�ȭ
            cin >> const_board[r][c];
            //���� ��� ������ 5 ����
            board[r][c] = 5;
        }
    }

    for (int i = 1; i <= M; i++){
        int r, c, old;
        cin >> r >> c >> old;
        tree[r][c].push_back(old);
    }
}

void spring_summer(){
    for (int r = 1; r <= N; r++){
        for (int c = 1; c <= N; c++){
            deque<int> n_que;
            int n_fuel = 0;//���� ���� �� board�� �߰���ų ���
            //������ �ϳ��� �����Ͽ� �ܿ� ��а� ��
            while(!tree[r][c].empty()){
                int c_old = tree[r][c].back();tree[r][c].pop_back();
                //(1) ���� ���� >  �ܿ� ���: ��������� ��ȯ �غ�
                if (c_old > board[r][c]) {
                    n_fuel += c_old / 2;
                }
                //(2) ���� ���� <= �ܿ� ���: ���̸�ŭ ��� ���� AND ����+1
                else {
                    board[r][c] -= c_old;
                    n_que.push_front(c_old+1);
                    //�� ��ġ���� �ֺ��� ������ �� �ִ� ���� ���� ����
                    if ( (c_old+1) % 5 == 0) kids[r][c]+=1;
                }
            }
            tree [r][c] = n_que;
            ///����
            board[r][c] += n_fuel;
        }
    }
}

void fall(){
    for (int r = 1; r <= N; r++){
        for (int c = 1; c <= N; c++){
            //(1)�ֺ��� �۶߸� ���� ��
            int kid_num = kids[r][c];
            for (int d = 0; d < 8; d++){
                int n_row = r + d_row[d];
                int n_col = c + d_col[d];
                if (n_row < 1 || n_row > N || n_col < 1 || n_col > N) continue;
                //(2) kid num��ŭ 8�濡 Lv.1¥�� ���� �߰�
                for (int i = 0; i < kid_num; i++) tree[n_row][n_col].push_back(1);
            }
            kids[r][c] = 0;
        }
    }
}

void winter(){
    for (int r = 1; r <= N; r++){
        for (int c = 1; c <= N; c++){
            board[r][c] += const_board[r][c];
        }
    }
}

int main()
{
    init();
    for (int k = 0; k < K; k++){
        spring_summer();
        fall  ();
        winter();
    }
    cout << answer();
    return 0;
}
