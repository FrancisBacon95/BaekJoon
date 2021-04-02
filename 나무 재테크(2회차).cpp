#include <iostream>
#include <deque>
using namespace std;
/*
1. 1부터 시작, 최초에 모든 칸 양분: 5

2. 1칸에 여러개 나무 가능

3.
    봄: 나이만큼 양분 먹기, 나이 +1
        어린 놈부터 먹음
        나이만큼 못 먹은 나무 죽음

    여름: 죽은 나무 나이 / 2 -> 양분
    가을: 나이가 5의 배수 -> 8방에 1레벨 나무 생성
    겨울: 양분 추가

4. 보드 N*N, 최초 심는 나무: M, K년 후 나무 수
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
            //겨울에 뿌릴 양분 초기화
            cin >> const_board[r][c];
            //최초 양분 무조건 5 지급
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
            int n_fuel = 0;//성장 끝난 후 board에 추가시킬 양분
            //어린놈부터 하나씩 추출하여 잔여 양분과 비교
            while(!tree[r][c].empty()){
                int c_old = tree[r][c].back();tree[r][c].pop_back();
                //(1) 현재 나이 >  잔여 양분: 양분으로의 전환 준비
                if (c_old > board[r][c]) {
                    n_fuel += c_old / 2;
                }
                //(2) 현재 나이 <= 잔여 양분: 나이만큼 양분 차감 AND 나이+1
                else {
                    board[r][c] -= c_old;
                    n_que.push_front(c_old+1);
                    //각 위치에서 주변에 생성할 수 있는 나무 개수 증가
                    if ( (c_old+1) % 5 == 0) kids[r][c]+=1;
                }
            }
            tree [r][c] = n_que;
            ///여름
            board[r][c] += n_fuel;
        }
    }
}

void fall(){
    for (int r = 1; r <= N; r++){
        for (int c = 1; c <= N; c++){
            //(1)주변에 퍼뜨릴 새끼 수
            int kid_num = kids[r][c];
            for (int d = 0; d < 8; d++){
                int n_row = r + d_row[d];
                int n_col = c + d_col[d];
                if (n_row < 1 || n_row > N || n_col < 1 || n_col > N) continue;
                //(2) kid num만큼 8방에 Lv.1짜리 나무 추가
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
