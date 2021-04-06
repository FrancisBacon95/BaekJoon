#include <iostream>
#include <deque>
using namespace std;
const int PLUS  = 1;
const int MINUS = 2;
const int MULTIPLY = 3;
const int DIVISION = 4;

long long MIN =  1000000000;
long long MAX = -1000000000;

int N;
int num [11] = {0, };
int func[ 5] = {0, };

void init(){
    cin >> N;
    for (int i = 0; i <  N; i++) cin >> num [i];
    for (int i = 1; i <= 4; i++) cin >> func[i];
}

void DFS(int _idx, long long c_sum){
    if (_idx == N-1) {
        if (c_sum > MAX) MAX = c_sum;
        if (c_sum < MIN) MIN = c_sum;
        return;
    }

    for (int i = 1; i <= 4; i++){
        if (func[i] == 0) continue;
        int       n_num = num[_idx+1];
        long long n_sum = c_sum;
        if      (i == MINUS   ) n_sum -= n_num;
        else if (i == PLUS    ) n_sum += n_num;
        else if (i == MULTIPLY) n_sum *= n_num;
        else if (i == DIVISION){
            if (c_sum < 0) n_sum *= -1;
            n_sum /= n_num;
            if (c_sum < 0) n_sum *= -1;
        }
        func[i]--;
        DFS(_idx + 1, n_sum);
        func[i]++;
    }
}

int main()
{
    init( );
    DFS (0, num[0]);
    cout << MAX << endl << MIN << endl;
    return 0;
}
