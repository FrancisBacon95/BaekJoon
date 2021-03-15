#include <iostream>
using namespace std;
int N;
int A[1000000];
int B, C;
long long ret = 0;
void init(){
    cin >> N;
    for(int i=0; i<N; i++) cin >> A[i];
    cin >> B >> C;
}

void solution(){
    for(int i=0; i<N; i++){
        A[i] -= B;
        if (A[i] < 0) A[i] = 0;
        ret++;
        ret += A[i] / C;
        if (A[i] % C > 0) ret++;
    }
}

int main()
{
    init();
    solution();
    cout << ret;
    return 0;
}
