#include <iostream>
using namespace std;
const int BLUE=0;
const int GREEN=1;
int N, score=0, cnt=0;
int board[2][10][4];

void move_point(int row, int col, int color){
   int id = board[color][row][col];
   board[color][row][col]=0;

   while(row<10){
      if (board[color][row][col]!=0) break;
      row++;
   }
   row--;
   board[color][row][col]=id;
}

void move_h_block(int row, int col, int color){
   int id = board[color][row][col];
   board[color][ row ][col]=0;
   board[color][row-1][col]=0; //아래쪽(idx큰 쪽)이 기준이기 때문.
   while(row<10){
      if (board[color][row][col]!=0) break;
      row++;
   }
   row--;
   board[color][ row ][col]=id;
   board[color][row-1][col]=id;
}

void move_w_block(int row, int col, int color){
   int id = board[color][row][col];
   board[color][row][ col ]=0;
   board[color][row][col+1]=0;//왼쪽(idx작은 쪽)이 기준이기 때문.
   while(row<10){
      if (board[color][row][col]!=0 || board[color][row][col+1]!=0) break;
      row++;
   }
   row--;
   board[color][row][ col ]=id;
   board[color][row][col+1]=id;
}

void remove_row(int row, int color){
   for (int col=0; col<4; col++) board[color][row][col]=0;
}

void after_move(int from_y, int color){
   //dx[0],dy[0]: 세로블럭, dx[1],dy[1]: 가로블럭
   const int dy[2] = {-1, 0};
   const int dx[2] = { 0,+1};
   //제거한 행의 위쪽에 있던 것들을 아래로 이동시켜 준다.
   for(int row=from_y; row>=4; row--){
      for(int col=0; col<4; col++){
         if (board[color][row][col]==0) continue;

         int type=1;//해당 지점이 0이 아니라면 최소 1개짜리 블럭
         for(int d=0; d<2; d++){
            int ny=row+dy[d];
            int nx=col+dx[d];
            if (ny<4 || nx>=4) continue; //범위 초과

            if(board[color][row][col]==board[color][ny][nx]){
               if (d==0) type=2;
               else type=3;
            }
         }//for(d)
         switch(type){
            case 1:
               move_point(  row, col, color);
               break;
            case 2:
               move_h_block(row, col, color);
               break;
            case 3:
               move_w_block(row, col, color);
               break;
         }
      }//for(col)
   }//for(row)
}

void delete_filled_block(int color){
   bool is_removed = false;
   for (int row=4; row<10; row++){
      int cnt_remove=0;//4개 채우면 행 삭제
      for (int col=0; col<4; col++){
         if (board[color][row][col]!=0) cnt_remove++;
      }
      if (cnt_remove==4){
         is_removed=true;
         score++;
         remove_row(row  , color);//빙고 행을 제거한다. 행 원소를 모두 0으로 바꾼다.
         after_move(row-1, color);//위쪽(row idx 낮은 쪽) 블록들을 이동시킨다.
      }
   }

   //한바퀴 제거한 후 발생하는 제거대상들을 재귀를 통해 제거한다.
   if(is_removed) delete_filled_block(color);
}

void delete_overflow_block(int color){
   int cnt_remove=0; //초과한 행의 수
   for (int row=4; row<=5; row++){
      for(int col=0; col<4; col++){
         if (board[color][row][col]!=0){
            cnt_remove++;
            break;
         }
      }
   }

   if (cnt_remove > 0){
      for(int row=9; row>=6;row--){
         for(int col=0; col<4; col++) board[color][row][col]=board[color][row-cnt_remove][col];
      }
      for (int row=4; row<=5; row++){
         for(int col=0; col<4; col++) board[color][row][col]=0;
      }
   }
}

void put(int type, int space, int color, int id){
   if(type==1){
      board[color][0][space] = id;
      move_point(0, space, color);
   }
   else if((type==2 && color==BLUE ) || (type==3 && color==GREEN)){
      board[color][0][space]  = id;
      board[color][1][space]  = id;
      move_h_block(1, space, color);//세로 블럭은 아래의 있는 블럭을 기준으로 움직인다.
   }
   else if((type==3 && color==BLUE ) || (type==2 && color==GREEN)){
      board[color][0][space]  = id;
      board[color][0][space+1]= id;
      move_w_block(0, space, color);//가로 블럭은 왼쪽에 있는 블럭을 기준으로 움직인다.
   }

   delete_filled_block(color  );//블럭 삽입으로 인해 생긴 빙고 행을 제거한다.
   delete_overflow_block(color);//블럭 축적으로 인해 생긴 빙고 행을 제거한다.
}

void input(){
   cin >> N;
   for(int idx=0; idx<N; idx++){
      int t, x, y;//x: row, y: col
      cin >> t >> x >> y;
      put(t, x, BLUE , idx+1);// green에서는 "열"간의 이동만이 중요하다.
      put(t, y, GREEN, idx+1);// blue에서는  "행"간의 이동만이 중요하다.
   }
}

void count_block(){
   for(int color=0; color<2; color++){
      for(int row=4; row<10; row++){
         for(int col=0; col<4; col++){
            if (board[color][row][col]!=0) cnt++;
         }
      }
   }
}

int main(){
   input();
   count_block();
   cout<<score<<endl<<cnt<<endl;
   return 0;
}
