#include <iostream>
#include <vector>
#include <algorithm>
#define MAXN 1000000
#define MAXM 1000000
using namespace std;

vector<int> A(MAXN);
vector<int> B(MAXM);
int N;
int M;
int L;
int R;

int main() {
    cin >> N >> M >> L >> R;
    for (int i = 0; i < N; ++i)
        cin >> A[i];
    for (int i = 0; i < M; ++i)
        cin >> B[i];
    sort(A.begin(), A.begin() + N);
    sort(B.begin(), B.begin() + M);
}