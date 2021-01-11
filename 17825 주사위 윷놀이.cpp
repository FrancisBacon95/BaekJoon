#include <iostream>
using namespace std;

int dice [10];
int horse[ 4];
int board[35]; //board["FROM"] = "TO"
int turn [35]={0,}; //change course (blue point)
int score[35]; //score of location in board
bool check[35];

int ans = 0;

void init(){
   //initialize board board["FROM"] = "TO"
   for(int i=0; i<21; i++) board[i] = i+1;
   board[21] = 21;
   for(int i=22; i<27; i++) board[i] = i+1;
   board[28] = 29; board[29] = 30; board[30] = 25;
   board[31] = 32; board[32] = 25; board[27] = 20;

   //initialize turn (blue point)
   turn[5] = 22; turn[10] = 31; turn[15] = 28; turn[25] = 26;

   //initialize score
   for (int i = 0; i < 21; i++) score[i] = i * 2;
   score[22] = 13; score[23] = 16; score[24] = 19;
   score[31] = 22; score[32] = 24; score[28] = 28;
   score[29] = 27; score[30] = 26; score[25] = 25;
   score[26] = 30; score[27] = 35;

   //initialize dice score
   for (int i = 0; i < 10; i++) cin >> dice[i];
}

void dfs(int cnt, int sum) {
   if (cnt == 10) {
      if (sum > ans) ans = sum;
      return;
   }

   for (int i=0; i<4; i++) {
      int prev   = horse[i];
      int now    = prev;
      int moving = dice[cnt];

      if (turn[now] > 0) {
         now = turn[now];
         moving--; //cuz horse[i] already move one by turn[now]
      }

      //move horse as dice score
      while (moving--) now = board[now];

      if (now != 21 && check[now] == true) continue;

      check[prev] = false;
      check[now ] = true;
      horse[i   ] = now;

      dfs(cnt+1, sum+score[now]);

      check[prev] = true;
      check[now ] = false;
      horse[i]    = prev;
   }
}

int main()
{
   init();
   dfs (0, 0);

   cout<< ans <<endl;

   return 0;
}
