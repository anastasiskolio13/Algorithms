#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;

void DivideAndConquer(vector<int>& A, vector<pair<int, int>>& Q, vector<int>& B, int lo, int hi) {
    if (lo > hi)
        return;

    int mid = (A[lo] + A[hi]) / 2;
    
    long long totalSum = accumulate(A.begin() + lo, A.begin() + hi + 1, 0LL);
    
    int i = lo;
    long long leftSum = 0;
    while (i <= hi && A[i] <= mid)
        leftSum += A[i++];
    
    vector<pair<int, int>> QL;
    vector<pair<int, int>> QR;

    for (auto x : Q) {
        int s = x.first;
        int i = x.second;
        if (s == totalSum)
            B[i] = 1;
        else if (s > leftSum)
            QR.push_back(make_pair(s, i));
        else 
            QL.push_back(make_pair(s, i));
    }
    
    if (i == hi + 1)
        return;

    DivideAndConquer(A, QL, B, lo, i - 1);
    DivideAndConquer(A, QR, B, i, hi);
}

int main() {
    int T;
    int N;
    int K;
    cin >> T;
    while (T--) {
        cin >> N >> K;
        vector<int> A(N);
        for (int i = 0; i < N; ++i)
            cin >> A[i];
        vector<pair<int, int>> Q(K);
        for (int i = 0; i < K; ++i) {
            cin >> Q[i].first;
            Q[i].second = i;
        }
        vector<int> B(K, 0);
        sort(A.begin(), A.end());
        DivideAndConquer(A, Q, B, 0, N - 1);
        for (int ans : B)
            cout << (ans == 1 ? "YES" : "NO") << endl;
    }
}