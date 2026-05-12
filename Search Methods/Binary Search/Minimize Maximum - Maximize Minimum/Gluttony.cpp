#include <bits/stdc++.h>
#define MAXN 200000
using namespace std;

vector<int> A(MAXN);
vector<int> F(MAXN);
int N;
long long K;

bool canAchieveMaximumScore(long long S) {
    long long trainingSets = 0;
    for (int i = 0; i < N; ++i)
        trainingSets += max(ceil(((double)A[i] * F[i] - S) / F[i]), 0.0);
    return trainingSets <= K;
}

int main() {
    // Input.
    cin >> N >> K;
    for (int i = 0; i < N; ++i)
        cin >> A[i];
    for (int i = 0; i < N; ++i)
        cin >> F[i];

    // Sort.
    sort(A.begin(), A.begin() + N);
    sort(F.begin(), F.begin() + N, greater<int>());

    // Binary search.
    long long lo = 0;
    long long hi = (long long)A[N - 1] * F[0];
    while (lo < hi) {
        long long mid = (lo + hi) / 2;
        if (canAchieveMaximumScore(mid))
            hi = mid;
        else
            lo = mid + 1;
    }
    cout << lo << endl;
}
