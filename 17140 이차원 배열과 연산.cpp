#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;
int ROW = 3;
int COL = 3;
int t   = 0;

int r, c, k;

int board[100][100] = {0, };

void input(){
    cin >> r >> c >> k;
    r--, c--;
    for (int i=0; i<3; i++){
        for (int j=0; j<3; j++){
            cin >> board[i][j];
        }
    }
}

bool cmp(const pair<int,int> a, const pair<int,int> b){
    if (a.second == b.second) return a.first < b.first;
    return a.second < b.second;
}

void R_func(){
    int tmp_max = COL;
    for (int i=0; i<ROW; i++){
        //INPUT VISIT
        map<int, int> visit;
        for (int j=0; j<COL; j++){
            if (board[i][j] == 0) continue;
            map<int,int>::iterator iter = visit.find(board[i][j]);
            if (iter != visit.end()) visit[board[i][j]]++  ;
            else                     visit[board[i][j]] = 1;
        }

        //SORTING
        vector<pair<int,int>> vec(visit.begin(), visit.end());
        sort(vec.begin(),vec.end(),cmp);
        int idx = 0;
        for(int j=0; j < vec.size(); j++){
            if (idx == 100) break;
            board[i][idx  ] = vec[j].first ;
            board[i][idx+1] = vec[j].second;
            idx += 2;
        }
        for(int j=idx; j<100; j++) board[i][j] = 0;
        if (idx > tmp_max) tmp_max = idx;
    }
    if (tmp_max > COL) COL = tmp_max;
}

void C_func(){
    int tmp_max = ROW;
    for (int j=0; j<COL; j++){
        map<int, int> visit;
        for(int i=0; i<ROW; i++){
            if (board[i][j] == 0) continue;
            map<int,int>::iterator iter = visit.find(board[i][j]);
            if (iter != visit.end()) visit[board[i][j]]++  ;
            else                     visit[board[i][j]] = 1;
        }
        //SORTING
        vector<pair<int,int>> vec(visit.begin(), visit.end());
        sort(vec.begin(),vec.end(),cmp);
        int idx = 0;
        for(int i=0; i < vec.size(); i++){
            if (idx == 100) break;
            board[idx  ][j] = vec[i].first ;
            board[idx+1][j] = vec[i].second;
            idx += 2;
        }
        for(int i=idx; i<100; i++) board[i][j] = 0;
        if (idx > tmp_max) tmp_max = idx;
    }
    if (tmp_max > ROW) ROW = tmp_max;
}

int main()
{
    int ret = -1;
    input();//ok
    while (true){
        if (t > 100) break;

        if (board[r][c] == k) {
            ret = t;
            break;
        }

        if (ROW >= COL) R_func();
        else            C_func();
        t++;
    }
    cout << ret;
    return 0;
}
