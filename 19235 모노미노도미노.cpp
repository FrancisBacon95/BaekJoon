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
   board[color][row-1][col]=0; //�Ʒ���(idxū ��)�� �����̱� ����.
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
   board[color][row][col+1]=0;//����(idx���� ��)�� �����̱� ����.
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
   //dx[0],dy[0]: ���κ�, dx[1],dy[1]: ���κ�
   const int dy[2] = {-1, 0};
   const int dx[2] = { 0,+1};
   //������ ���� ���ʿ� �ִ� �͵��� �Ʒ��� �̵����� �ش�.
   for(int row=from_y; row>=4; row--){
      for(int col=0; col<4; col++){
         if (board[color][row][col]==0) continue;

         int type=1;//�ش� ������ 0�� �ƴ϶�� �ּ� 1��¥�� ��
         for(int d=0; d<2; d++){
            int ny=row+dy[d];
            int nx=col+dx[d];
            if (ny<4 || nx>=4) continue; //���� �ʰ�

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
      int cnt_remove=0;//4�� ä��� �� ����
      for (int col=0; col<4; col++){
         if (board[color][row][col]!=0) cnt_remove++;
      }
      if (cnt_remove==4){
         is_removed=true;
         score++;
         remove_row(row  , color);//���� ���� �����Ѵ�. �� ���Ҹ� ��� 0���� �ٲ۴�.
         after_move(row-1, color);//����(row idx ���� ��) ��ϵ��� �̵���Ų��.
      }
   }

   //�ѹ��� ������ �� �߻��ϴ� ���Ŵ����� ��͸� ���� �����Ѵ�.
   if(is_removed) delete_filled_block(color);
}

void delete_overflow_block(int color){
   int cnt_remove=0; //�ʰ��� ���� ��
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
      move_h_block(1, space, color);//���� ���� �Ʒ��� �ִ� ���� �������� �����δ�.
   }
   else if((type==3 && color==BLUE ) || (type==2 && color==GREEN)){
      board[color][0][space]  = id;
      board[color][0][space+1]= id;
      move_w_block(0, space, color);//���� ���� ���ʿ� �ִ� ���� �������� �����δ�.
   }

   delete_filled_block(color  );//�� �������� ���� ���� ���� ���� �����Ѵ�.
   delete_overflow_block(color);//�� �������� ���� ���� ���� ���� �����Ѵ�.
}

void input(){
   cin >> N;
   for(int idx=0; idx<N; idx++){
      int t, x, y;//x: row, y: col
      cin >> t >> x >> y;
      put(t, x, BLUE , idx+1);// green������ "��"���� �̵����� �߿��ϴ�.
      put(t, y, GREEN, idx+1);// blue������  "��"���� �̵����� �߿��ϴ�.
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
