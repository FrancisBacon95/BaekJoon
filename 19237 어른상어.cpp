#include <iostream>
#include <vector>
using namespace std;

int N, M, k, time, kill_shark, ret;

const int d_row[4] = { -1, +1, 0, 0 };
const int d_col[4] = { 0, 0, -1, +1 };

struct SHARK{
   int row, col, dir;
   int prior[4][4];
};

vector<vector<vector<int>>> board;
vector<SHARK> shark;

void input(){
   cin  >> N >> M >> k;

   for(int i=0; i<M; i++){
      SHARK tmp_shark;
      shark.push_back(tmp_shark);
   }

   for(int i=0; i<N; i++){
      vector<vector<int>> in_row;
      for(int j=0; j<N; j++){
         vector<int> in_elem;
         int tmp; cin >> tmp;

         if (tmp!=0) {
            in_elem={tmp, tmp, k};
            shark[tmp-1].row=i;
            shark[tmp-1].col=j;
         }else {
            in_elem={0, 0, 0};
         }
         in_row.push_back(in_elem);
      }
      board.push_back(in_row);
   }

   for(int i=0; i<M; i++){
      int tmp; cin >> tmp;
      shark[i].dir=tmp-1;
   }

   for(int i=0; i<M;i++){
      for(int d=0; d<4; d++){
         int tmp0, tmp1, tmp2, tmp3;
         cin >> tmp0 >> tmp1 >> tmp2 >> tmp3;
         shark[i].prior[d][0] = tmp0-1; shark[i].prior[d][1] = tmp1-1;
         shark[i].prior[d][2] = tmp2-1; shark[i].prior[d][3] = tmp3-1;
      }
   }
}

void smell_down(vector<vector<vector<int>>> &_new_board){
   for(int i=0; i<N; i++){
      for(int j=0; j<N; j++){
         if (_new_board[i][j][2] >  0) _new_board[i][j][2]--;
         if (_new_board[i][j][2] >  0) _new_board[i][j][1]=board[i][j][1];
         else _new_board[i][j][1]=0;
      }
   }
}

void moving(int i, int n_dir, int n_row, int n_col, vector<vector<vector<int>>> &_new_board){
   //Check smell in "board", Move and kill/death in "new board".
   if (_new_board[n_row][n_col][0]==0){
      _new_board[n_row][n_col][0] = i+1;
      _new_board[n_row][n_col][1] = i+1;
      _new_board[n_row][n_col][2] = k;

      shark[i].dir = n_dir;
      shark[i].row = n_row;
      shark[i].col = n_col;
   }else{
      ++kill_shark;
      shark[i].row=-1;
   }
}

void shark_move(int i, vector<vector<vector<int>>> &_new_board){
   int c_row = shark[i].row;
   int c_col = shark[i].col;
   int c_dir = shark[i].dir;

   if (c_row==-1) {
         return;
   }
   bool is_move = false;

   //int n_row, n_col, n_dir;
   for(int d=0; d<4; d++){
      int n_dir = shark[i].prior[c_dir][d];
      int n_row = c_row + d_row[n_dir];
      int n_col = c_col + d_col[n_dir];

      if (n_row < 0 || n_row >= N || n_col < 0 || n_col >= N || board[n_row][n_col][2]!=0) continue;

      is_move = true;
      _new_board[c_row][c_col][0]= 0;
      moving(i, n_dir, n_row, n_col, _new_board);
      break;
   }

   if (is_move==false){
      for(int d=0; d<4; d++){
         int n_dir = shark[i].prior[c_dir][d];
         int n_row = c_row + d_row[n_dir];
         int n_col = c_col + d_col[n_dir];

         if (n_row < 0 || n_row >= N || n_col < 0 || n_col >= N) continue;
         if (board[n_row][n_col][2] != 0 && board[n_row][n_col][1] != i+1) continue;

         _new_board[c_row][c_col][0]= 0;
         moving(i, n_dir, n_row, n_col, _new_board);
         break;
      }
   }
}

int main(){
   input();
   time=0; kill_shark=0; ret=-1;

   while(time<=1000){
      ++time;
      vector<vector<vector<int>>> new_board(board);
      smell_down(new_board);
      for(int i=0; i<M; i++) shark_move(i, new_board);

      if(kill_shark==M-1) break;

      for(int i=0; i<N; i++){
         for(int j=0; j<N; j++){
            board[i][j][0]=new_board[i][j][0];
            board[i][j][1]=new_board[i][j][1];
            board[i][j][2]=new_board[i][j][2];
         }
      }
   }
   if(time<=1000) ret=time;
   cout<< ret;
   return 0;
}

