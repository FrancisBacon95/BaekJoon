#include <iostream>
#include <deque>
#include <vector>
#include <algorithm>
using namespace std;
int N, M, K;
int food_board [10][10];
int add        [10][10];
vector<int> tree_board[10][10];

void input(){
    cin >> N >> M >> K;
    //INITIALIZE FOOD BOARD
    for (int r=0; r<N; r++){
        for(int c=0; c<N; c++){
            cin >> add[r][c];
            food_board[r][c] = 5;
        }
    }

    //INTITIALIZE TREE BORAD
    for (int m=0; m<M; m++){
        int tmp_row, tmp_col, tmp_old;
        cin >> tmp_row >> tmp_col >> tmp_old;
        tmp_row--, tmp_col--;
        tree_board[tmp_row][tmp_col].push_back(tmp_old);
    }
}

void spring_summer(int r, int c){
    int die_sum = 0;
    deque<int>que;
    sort(tree_board[r][c].begin(), tree_board[r][c].end());
    for (int i=0; i < tree_board[r][c].size(); i++){
        int c_old = tree_board[r][c][i];
        //남은 양분의 양보다 나이가 적거나 같으면 : old+1 처리 후, que로 보낸다.
        if (c_old <= food_board[r][c]){
            food_board[r][c] -= c_old;
            c_old++;
            que.push_back(c_old);
        }
        //남은 양분의 양보다 나이가 많으면 : die_sum에 합산한다.
        else {
            die_sum += c_old / 2; // 1/2의 양만큼만 추가
        }
    }
    //죽은 나무를 비워주고, 새롭게 업데이트 된 나무들(in que)을 추가시켜준다.
    tree_board[r][c].clear();

    //que에 있는 나무를 다시 food_tree로 보낸다.
    while(!que.empty()){
        tree_board[r][c].push_back(que.front());
        que.pop_front();
    }
    //합산된 die_sum을 SUMMER 때 양분으로 준다.
    food_board[r][c] += die_sum;
}
void fallin(int r, int c){
    //tree_board[r][c]에서 하나씩 뽑아내면서 번식 가능 여부 확인
    for(int i=0; i < tree_board[r][c].size(); i++){
        int c_old = tree_board[r][c][i];
        if (c_old % 5 == 0){
            for (int d=0; d<8; d++){
                const int d_row[8] = {-1, -1, -1,  0,  0, +1, +1, +1};
                const int d_col[8] = {-1,  0, +1, -1, +1, -1,  0, +1};

                int n_row = r + d_row[d];
                int n_col = c + d_col[d];

                if (n_row < 0 || n_row >= N || n_col < 0 || n_col >= N) continue;
                tree_board[n_row][n_col].push_back(1);
            }
        }
    }
}

void winter(){
    for (int r=0; r<N; r++){
        for(int c=0; c<N; c++){
            food_board[r][c] += add[r][c];
        }
    }
}

int main()
{
    input();
    for (int k=0; k<K; k++){
        ///SPRING & SUMMER
        for (int r=0; r<N; r++){
            for (int c=0; c<N; c++){
                if (tree_board[r][c].empty()) continue;
                spring_summer(r, c);
            }
        }
        ///FALLIN
        for (int r=0; r<N; r++){
            for (int c=0; c<N; c++){
                if (tree_board[r][c].empty()) continue;
                fallin(r, c);
            }
        }
        ///WINTER
        winter();
    }

    int ret=0;
    for (int r=0; r<N; r++){
        for (int c=0; c<N; c++){
            ret += tree_board[r][c].size();
        }
    }
    cout << ret;
    return 0;
}
