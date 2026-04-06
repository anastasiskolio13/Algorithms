#include <iostream>
#include <vector>
#include <algorithm>
#define MAXN 100000
using namespace std;

vector<int> A(MAXN);
vector<int> ans(MAXN);
int N;
int K;

int FirstGreaterOrEqual(int x) {
    int lo = 0;
    int hi = N - 1;
    while (lo < hi) {
        int j = (lo + hi) / 2;
        if (A[j] >= x)
            hi = j;
        else 
            lo = j + 1;
    }
    // lo == hi.
    return A[lo] >= x ? lo : -1;
}

int LastLessOrEqual(int x) {
    int lo = 0;
    int hi = N - 1;
    while (lo < hi) {
        int j = (lo + hi + 1) / 2;
        if (A[j] <= x)
            lo = j;
        else 
            hi = j - 1;
    }
    return A[lo] <= x ? lo : -1;
}

int main() {
    cin >> N;
    for (int i = 0; i < N; ++i)
        cin >> A[i];
    sort(A.begin(), A.begin() + N);
    cin >> K;
    for (int i = 0; i < K; ++i) {
        int L, R;
        cin >> L >> R;
        int leftIndex = FirstGreaterOrEqual(L);
        int rightIndex = LastLessOrEqual(R);
        if (leftIndex == -1 || rightIndex == -1)
            ans[i] = 0;
        else 
            ans[i] = rightIndex - leftIndex + 1;
    }
    for (int i = 0; i < K; ++i)
        cout << ans[i] << " ";
}