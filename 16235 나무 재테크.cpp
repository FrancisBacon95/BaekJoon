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
        //���� ����� �纸�� ���̰� ���ų� ������ : old+1 ó�� ��, que�� ������.
        if (c_old <= food_board[r][c]){
            food_board[r][c] -= c_old;
            c_old++;
            que.push_back(c_old);
        }
        //���� ����� �纸�� ���̰� ������ : die_sum�� �ջ��Ѵ�.
        else {
            die_sum += c_old / 2; // 1/2�� �縸ŭ�� �߰�
        }
    }
    //���� ������ ����ְ�, ���Ӱ� ������Ʈ �� ������(in que)�� �߰������ش�.
    tree_board[r][c].clear();

    //que�� �ִ� ������ �ٽ� food_tree�� ������.
    while(!que.empty()){
        tree_board[r][c].push_back(que.front());
        que.pop_front();
    }
    //�ջ�� die_sum�� SUMMER �� ������� �ش�.
    food_board[r][c] += die_sum;
}
void fallin(int r, int c){
    //tree_board[r][c]���� �ϳ��� �̾Ƴ��鼭 ���� ���� ���� Ȯ��
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
