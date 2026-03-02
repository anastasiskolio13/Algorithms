#include <bits/stdc++.h>
#define MAXN 100000
using namespace std;

vector<long long> A(MAXN + 1);
vector<long long> PS(MAXN + 2);
int N;
int Q;

long long findKthNumber(long long K) {
    long long lo = 1;
    long long hi = N + 1;
    while (lo < hi) {
        long long mid = (lo + hi) / 2;
        if (K >= PS[mid])
            hi = mid;
        else
            lo = mid + 1;
    }
}

int main() {
    cin >> N >> Q;
    for (int i = 1; i <= N; ++i)
        cin >> A[i];
    PS[1] = A[1] - 1;
    for (int i = 2; i <= N; ++i)
        PS[i] = PS[i - 1] + A[i] - A[i - 1] - 1;
    PS[N + 1] = PS[N] + 1e18 - A[N] - 1;
    while (Q--) {
        long long K;
        cin >> K;
        cout << findKthNumber(K) << endl;
    }
}
