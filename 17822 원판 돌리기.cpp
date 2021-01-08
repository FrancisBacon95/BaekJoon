#include <iostream>
using namespace std;
const int DEL = 0;
int N, M, T;
int board[50][50];
int trans[50][3];

void input() {
   cin >> N >> M >> T;
   for (int i=0; i<N; i++){
      for (int j=0; j<M; j++){
         cin >> board[i][j];
      }
   }
   for (int t=0; t<T; t++) cin >> trans[t][0] >> trans[t][1] >> trans[t][2];
}

void solve(int t) {
   /// 1) rotate
   int x = trans[t][0];
   int d = trans[t][1];
   int k = trans[t][2];

   int pick = x - 1;
   if(d==1) k = -k;

   while (pick < N) {
      int tmp[50] = {0,};
      for (int i = 0; i < M; i++) tmp[(i + k + M) % M] = board[pick][i];
      for (int i = 0; i < M; i++) board[pick][i]       = tmp[i];

      pick += x; // up row(pick) as x;
   }

   bool is_update       = false;
   bool visited[50][50] = {false, };
   const int d_row[4]   = {-1, +1,  0,  0};
   const int d_col[4]   = { 0,  0, -1, +1};
   //Enable to check if there is a deletion by check[][]
   for (int row = 0; row < N; row++) {
      for (int col = 0; col < M; col++){
         for (int d =0; d < 4; d++){
            int n_row = row + d_row[d];
            int n_col = (col + d_col[d] + M) % M;
            if (n_row < 0 || n_row >= N) continue; //col has circular feature, then no codition.
            if (board[row][col] != DEL && board[n_row][n_col] != DEL && board[row][col] == board[n_row][n_col]) {
               is_update = true;
               visited[row  ][col  ] = true;
               visited[n_row][n_col] = true;
            }
         }
      }
   }
   if (is_update) { /// 2-1) remove
      for (int row = 0; row < N; row++) {
         for (int col = 0; col < M; col++){
            if (visited[row][col]) board[row][col] = DEL;
         }
      }
   }
   else { /// 2-2) (+/-) processing
      int sum = 0, num = 0;
      //caculate mean
      for (int row = 0; row < N; row++) {
         for (int col = 0; col < M; col++) {
            if (board[row][col] != DEL) {
               sum += board[row][col];
               num++;
            }
         }
      }
      float mean = ((float)sum / (float)num);
      for (int row = 0; row < N; row++) {
         for (int col = 0; col < M; col++) {
            if (board[row][col] != DEL) {
               if (board[row][col] > mean) board[row][col]--;
               else if (board[row][col] < mean) board[row][col]++;
            }
         }
      }
   }
}

int main() {
   //input
   input();
   //solve
   for(int t=0; t<T; t++) solve(t);

   //Calculate result
   int ret = 0;
   for (int i=0; i<N; i++) {
      for (int j=0; j<M; j++) {
         ret += board[i][j];
      }
   }
   cout << ret;

   return 0;
}

