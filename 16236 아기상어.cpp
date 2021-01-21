#include <iostream>
#include <deque>
using namespace std;

struct SHARK{
    int row, col, time;
};

int N;
int board[20][20];

int lev = 2;
int eat = 0;
SHARK shark;

const int d_row[] = {-1, +1,  0,  0};
const int d_col[] = { 0,  0, -1, +1};

void input(){
    cin >> N;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            cin >> board[i][j];
            if (board[i][j] == 9){
                shark.row = i; shark.col = j; shark.time = 0;
                board[i][j] = 0;
            }
        }
    }
}

int main(){
    input();
    bool is_update = true;
    while (is_update){
        is_update = false;

        bool visited[20][20] = {false, };
        deque<SHARK> dq;
        visited[shark.row][shark.col] = true;
        dq.push_back(shark);

        SHARK candi;
        candi.row = 20; candi.time = -1;
        while(!dq.empty()){
            SHARK cur = dq.front(); dq.pop_front();

            //candi.time�� -1�̸�, ���� ó�� �����Ѵٴ� ���̴�.
            if (candi.time != -1 && candi.time < cur.time) break;

            if (board[cur.row][cur.col] < lev && board[cur.row][cur.col] != 0){
                is_update = true;
                //������ queue���� ���� c_shark�� �̵��Ÿ��� candi�� ����.
                //���� candi�� �� ª�Ҵٸ� �̹� ���� ���ǹ����� ����������.
                if (candi.row > cur.row || (candi.row == cur.row && candi.col > cur.col)) candi = cur;
            }

            for (int d=0; d < 4; d++){
                SHARK next;
                next.row  = cur.row  + d_row[d];
                next.col  = cur.col  + d_col[d];
                next.time = cur.time + 1;

                if (next.row < 0 || next.row >= N || next.col < 0 || next.col >= N) continue;
                //���ʿ� shark�� lev���� ū ���� �湮�� ���� �������ν� �̸� ���� �ٸ� �������� ���ư��� ���� �����Ѵ�.
                //�̷��� �ϸ� shark�� lev�� ���� ũ�� ������ ������ �ʾƵ� �湮�ϴ� ���� ����������
                //            shark�� lev���� ū ������ ����ġ�� �͵� ���� ���� �� �ִ�.
                if (visited[next.row][next.col] == false && lev >= board[next.row][next.col]){
                    visited[next.row][next.col] = true;
                    dq.push_back(next);
                }
            }
        }
        if (is_update){
            shark = candi;
            eat++;
            if (eat == lev){
                lev++  ;
                eat = 0;
            }
            board[shark.row][shark.col] = 0;
        }
    }

    cout << shark.time;

    return 0;
};


