#include <iostream>
#include <vector>
#define MAXN 20
using namespace std;

vector<long long> A(MAXN);
int N;
long long K;

bool recurse(int i, long long sum) {
    if (i == N) 
        return sum == K;
    return recurse(i + 1, sum) || recurse(i + 1, sum + A[i]);
}

int main() {
    cin >> N >> K;
    for (int i = 0; i < N; ++i)
        cin >> A[i];
    cout << (recurse(0, 0) ? "YES" : "NO") << endl;
}