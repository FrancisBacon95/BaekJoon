#include <iostream>
using namespace std;
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))


int N, total_sum=0;
int board[21][21]={0,};
int global_min;

int solve(int x, int y, int d1, int d2){
   int tmp[21][21] = {0, };
   int score[6] ={0, };
   score[5] = total_sum;

   //manage line
   tmp[x][y] = 5;
   for (int i=1; i<=d1; i++) {
      tmp[x+i   ][y-i   ] = 5;
      tmp[x+d2+i][y+d2-i] = 5;
   }
   for (int i=1; i<=d2; i++) {
      tmp[x+i   ][y+i   ] = 5;
      tmp[x+d1+i][y-d1+i] = 5;
   }
   //manage 1~4 sector
   // 1
   for (int r=1; r < x+d1; r++) {
      for (int c=1; c <= y; c++) {
         if (tmp[r][c] == 5) break;
         score[1] += board[r][c];
      }
   }
   // 2
   for (int r=1; r <= x+d2; r++) {
      for(int c=N; c > y; c--){
         if (tmp[r][c] == 5) break;
         score[2] += board[r][c];
      }
   }
   // 3
   for (int r=x+d1; r <= N; r++) {
      for(int c=1; c < y-d1+d2; c++){
         if (tmp[r][c] == 5) break;
         score[3] += board[r][c];
      }
   }
   // 4
   for (int r=x+d2+1; r <= N; r++) {
      for(int c=N; c >= y-d1+d2; c--){
         if (tmp[r][c] == 5) break;
         score[4] += board[r][c];
      }
   }

   for (int i=1; i<=4;i++) score[5] -= score[i];

   int min_score = 100*21*21;
   int max_score = -1;

   for(int i=1; i<=5; i++){
      if (score[i] < min_score) min_score = score[i];
      if (score[i] > max_score) max_score = score[i];
   }

   return max_score - min_score;
}

int main(){
   ///INPUT
   cin >> N;
   global_min = 100*N*N;
   for(int x=1; x<=N; x++){
      for(int y=1; y<=N; y++){
         cin >> board[x][y];
         total_sum+=board[x][y];
      }
   }//OK

   //( x+d1+d2 ¡Â N, 1 ¡Â y-d1 , y+d2 ¡Â N)
   for (int x=1; x<N; x++) {
      for (int y=1; y<N; y++) {
         for (int d1=1; d1<=N; d1++){
            for (int d2=1; d2<=N; d2++){
               if (x+d1+d2 > N) continue;
               if (y-d1 < 1)    continue;
               if (y+d2 > N)    continue;

               int local_min = solve(x, y, d1, d2);
               if (local_min < global_min) global_min = local_min;
            }
         }
      }
   }
   cout << global_min;
   return 0;
}
