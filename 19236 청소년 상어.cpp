#include <iostream>
using namespace std;

struct SHARK{
   int dir, row, col, score=0;
};

struct FISH{
   int dir, row, col;
};

int max_score=0;
int d_row[8] = {-1, -1,  0,  1, 1, 1, 0, -1};
int d_col[8] = { 0, -1, -1, -1, 0, 1, 1,  1};

int board[4][4];
FISH fish[16];
SHARK shark;

void input(){
   for(int i=0; i<4; i++){
      for(int j=0; j<4; j++){
         int tmp_idx, tmp_dir;
         cin >> tmp_idx >> tmp_dir;
         tmp_idx--; tmp_dir--;

         fish[tmp_idx].dir = tmp_dir;
         fish[tmp_idx].row = i;
         fish[tmp_idx].col = j;

         board[i][j] = tmp_idx;
      }
   }
}

void shark_eat(int n_row, int n_col, SHARK &_shark, FISH _fish[16], int _board[][4]){
   int c_row = _shark.row;
   int c_col = _shark.col;

   //Change fish info
   int fish_idx = _board[n_row][n_col];
   _fish[fish_idx].row = -1;

   //Change shark info
   _shark.dir = _fish[fish_idx].dir;
   _shark.row = n_row;
   _shark.col = n_col;
   _shark.score += fish_idx+1;


   //Change board info
   _board[n_row][n_col] = 99;
   _board[c_row][c_col] = -1;
}

void fish_move(FISH _fish[16], int _board[4][4]){
   for(int i=0; i<16; i++){
      if (_fish[i].row == -1) continue;

      int c_row = _fish[i].row;
      int c_col = _fish[i].col;
      int c_dir = _fish[i].dir;

      int n_dir = c_dir;
      int n_row = c_row + d_row[n_dir];
      int n_col = c_col + d_col[n_dir];

      while (n_row < 0 || n_row >= 4 || n_col < 0 || n_col >= 4 || _board[n_row][n_col]== 99){
         n_dir = (n_dir + 1) % 8;
         n_row = c_row + d_row[n_dir];
         n_col = c_col + d_col[n_dir];
      }

      //Change the fish's loca
      ///if next loca. is empty space
      if (_board[n_row][n_col] == -1){
         _board[c_row][c_col] = -1;
      }
      ///if next loca. is other fish space
      else{
         int target = _board[n_row][n_col];
         _fish[target].row = c_row;
         _fish[target].col = c_col;

         _board[c_row][c_col] = target;
      }
      _fish[i].row = n_row;
      _fish[i].col = n_col;
      _fish[i].dir = n_dir;

      _board[n_row][n_col] = i;
   }
}

void solve(SHARK _shark, FISH _fish[16], int _board[4][4]){
   if (_shark.score > max_score) max_score = _shark.score;

   //Detect next location of shark
   for(int len=1; len<4; len++){
      int n_row = _shark.row + len*d_row[_shark.dir];
      int n_col = _shark.col + len*d_col[_shark.dir];

      //if candidate location is empty, it's -1.
      if (n_row < 0 || n_row >= 4 || n_col < 0 || n_col >= 4) break;

      if (_board[n_row][n_col]!= -1){
         ///Copy all that shark, fish, board
         SHARK n_shark;
         FISH n_fish[16];
         int n_board[4][4];

         //Copy shark
         n_shark.dir   = _shark.dir;
         n_shark.row   = _shark.row;
         n_shark.col   = _shark.col;
         n_shark.score = _shark.score;

         //Copy fish
         for(int i=0; i<16; i++){
            n_fish[i] = _fish[i];
         }
         //Copy board
         for(int i=0; i<4; i++){
            for(int j=0; j<4; j++){
               n_board[i][j] = _board[i][j];
            }
         }

         //Eat and change shark's location
         shark_eat(n_row, n_col, n_shark, n_fish, n_board);

         //Move fish
         fish_move(n_fish, n_board);

         solve(n_shark, n_fish, n_board);
      }
   }
}

int main(){
   input();

   //Initialize Shark
   shark.row = 0;
   shark.col = 0;
   shark.dir = fish[board[0][0]].dir;
   shark.score = board[0][0]+1;

   //Kill fish on (0,0)
   fish[board[0][0]].row = -1;
   board[0][0] = 99;
   fish_move(fish, board);
   solve(shark, fish, board);
   cout<<max_score;
   return 0;
}

