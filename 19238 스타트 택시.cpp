#include <stdio.h>
#include <queue>
using namespace std;

struct CUSTOMER {
   int start;
   int end;
};

struct TAXI {
   int pos;
   int distance;
};

const int WALL = -1;
const int EMPTY = -2;
const int dy[4] = { -1, 0, +1, 0 };
const int dx[4] = { 0, -1, 0, +1 };

int N, M, fuel;
int taxi_y, taxi_x;
int board[20][20];
CUSTOMER customer[400];

int find_customer() {
   queue<TAXI> q;
   bool visited[20][20] = { false, };
   TAXI cur = { taxi_y * 100 + taxi_x, 0 };
   visited[taxi_y][taxi_x] = true;
   q.push(cur);

   int candi_size = 0;
   int candi[400] = { 0, };
   int candi_distance = -1;

   while (!q.empty()) {
      cur = q.front();
      q.pop();

      if (candi_distance != -1 && cur.distance > candi_distance) break;

      int y = cur.pos / 100;
      int x = cur.pos % 100;
      if (board[y][x] >= 0) {
         candi[candi_size++] = board[y][x];
         candi_distance = cur.distance;
      }

      for (int d = 0; d < 4; ++d) {
         int ny = y + dy[d];
         int nx = x + dx[d];
         if (ny < 0 || ny >= N || nx < 0 || nx >= N || board[ny][nx] == WALL || visited[ny][nx] == true) continue;
         visited[ny][nx] = true;
         TAXI next = { ny * 100 + nx, cur.distance + 1 };
         q.push(next);
      }
   }
   if (candi_distance > fuel) return -1;

   int ret = -1;
   int candi_val = 10000;
   for (int i = 0; i < candi_size; ++i) {
      if (candi_val > customer[candi[i]].start) {
         candi_val = customer[candi[i]].start;
         ret = candi[i];
      }
   }

   taxi_y = customer[ret].start / 100;
   taxi_x = customer[ret].start % 100;
   board[taxi_y][taxi_x] = EMPTY;
   fuel -= candi_distance;
   return ret;
}

bool move_customer(int target) {
   queue<TAXI> q;
   bool visited[20][20] = { false, };
   TAXI cur = { taxi_y * 100 + taxi_x, 0 };
   visited[taxi_y][taxi_x] = true;
   q.push(cur);

   while (!q.empty()) {
      cur = q.front();
      q.pop();
      if (cur.distance > fuel) return false;

      if (cur.pos == customer[target].end) {
         taxi_y = customer[target].end / 100;
         taxi_x = customer[target].end % 100;
         fuel += cur.distance;
         return true;
      }

      int y = cur.pos / 100;
      int x = cur.pos % 100;
      for (int d = 0; d < 4; ++d) {
         int ny = y + dy[d];
         int nx = x + dx[d];
         if (ny < 0 || ny >= N || nx < 0 || nx >= N || board[ny][nx] == WALL || visited[ny][nx] == true) continue;
         TAXI next = { ny * 100 + nx, cur.distance + 1 };
         q.push(next);
         visited[ny][nx] = true;
      }
   }
   return false;
}

int solve() {
   int ret = -1;
   for (int i = 0; i < M; ++i) {
      int target = find_customer();

      if (target == -1) return ret;

      bool success = move_customer(target);

      if (success == false) return ret;
   }
   ret = fuel;
   return ret;
}

int main() {
   scanf("%d %d %d", &N, &M, &fuel);
   for (int y = 0; y < N; ++y) {
      for (int x = 0; x < N; ++x) {
         scanf("%d", &board[y][x]);
         board[y][x] -= 2;
      }
   }

   scanf("%d %d", &taxi_y, &taxi_x);
   --taxi_y, --taxi_x;

   for (int i = 0; i < M; ++i) {
      int sy, sx, ey, ex;
      scanf("%d %d %d %d", &sy, &sx, &ey, &ex);
      --sy, --sx, --ey, --ex;
      customer[i].start = (sy * 100 + sx);
      customer[i].end = (ey * 100 + ex);
      board[sy][sx] = i;
   }
   int ret = solve();
   printf("%d\n", ret);
   return 0;
}
