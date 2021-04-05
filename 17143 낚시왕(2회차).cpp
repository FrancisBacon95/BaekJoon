#include <iostream>
using namespace std;
const int d_row[5] = {0, -1, 1, 0,  0};
const int d_col[5] = {0,  0, 0, 1, -1};
int R, C, M, ret = 0;
int first[101] = {0, };
struct FISH{
    int row, col, spe, dir, siz;
    bool live = true;
};

FISH fish[10001];

void init(){
    cin >> R >> C >> M;
    for (int i = 1; i <= M; i++){
        cin >> fish[i].row >> fish[i].col >> fish[i].spe >> fish[i].dir >> fish[i].siz;
    }

    //size 기준으로 fish 정렬(내림차순:Big -> Small)
    for (int i = 1; i <= M-1; i++){
        for (int j = i; j <= M; j++){
            FISH tmp = fish[j];
            if (fish[i].siz < fish[j].siz){
                fish[j] = fish[i];
                fish[i] = tmp    ;
            }
        }
    }

    //해당 COL의 ROW가 FIRST[COL]보다 작으면 ROW와 교환
    for (int i = 1; i <= M; i++){
        int first_idx = first[ fish[i].col ];
        if (first_idx == 0 || fish[first_idx].row > fish[i].row) first[ fish[i].col ] = i;
    }
}

void hunt_fish(int _col){
    int tar_idx = first[_col];
    if (tar_idx == 0)
        return;

    fish[tar_idx].live = false;
    first[_col]        = 0;
    ret += fish[tar_idx].siz;
}

void all_move(){
    ///0. FIRST 배열 초기화
    for(int c = 1; c <= C; c++) first[c] = 0;

    ///1. 각 FISH 움직임을 n_board에 기록
    for (int idx = 1; idx <= M; idx++){
        FISH c_fish = fish[idx];
        //(1) 죽은 놈은 넘어가기
        if (c_fish.live == false) continue;
        int len   = c_fish.spe;
        int n_row = c_fish.row;
        int n_col = c_fish.col;
        int n_dir = c_fish.dir;
        ///2. 다음 좌표 탐색
        for (int i = 1; i <= len; i++){
            int tmp_row = n_row + d_row[n_dir];
            int tmp_col = n_col + d_col[n_dir];
            //(1) board 경계 넘는 경우 -> 방향 반대로
            if (tmp_row < 1 || tmp_row > R || tmp_col < 1 || tmp_col > C){
                if      (n_dir % 2 == 1) n_dir++;
                else if (n_dir % 2 == 0) n_dir--;
                tmp_row = n_row + d_row[n_dir];
                tmp_col = n_col + d_col[n_dir];
            }
            n_row = tmp_row;
            n_col = tmp_col;

        }
        ///3. 더 큰 놈 있으면 제거
        for (int big = 1; big < idx; big++){
            if (fish[big].row == n_row && fish[big].col == n_col){
                fish[idx].live = false;
                continue;
            }
        }

        ///4. 더 큰 놈 없으면 정보 수정
        //(1) fish 수정
        fish[idx].row = n_row;
        fish[idx].col = n_col;
        fish[idx].dir = n_dir;
        //(2) first 수정
        int first_idx = first[n_col];
        if (first_idx == 0 || fish[first_idx].row > n_row) first[n_col] = idx;
    }
}

int main()
{
    init();
    for (int col = 1; col <= C; col++){
        hunt_fish(col);
        all_move();
    }
    cout << ret;
    return 0;
}
