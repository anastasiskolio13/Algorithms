#include <bits/stdc++.h>
#define MAXN 200000
using namespace std;

struct CompareElements {
    bool operator()(pair<int, int> A, pair<int, int> B) const {
        return A.first > B.first || A.first == B.first && A.second < B.second;
    }
};

set<pair<int, int>, CompareElements> S;
map<int, int> C;
vector<int> A(MAXN);
int N;
int K;

int main() {
    scanf("%d %d", &N, &K);
    for (int i = 0; i < N; ++i)
        scanf("%d", &A[i]);
    for (int i = 0; i < N; ++i) {
        auto it = S.find({C[A[i]], A[i]});
        if (it != S.end())
            S.erase(it);
        S.insert({++C[A[i]], A[i]});
        if (i >= K - 1) {
            printf("%d ", S.begin()->second);
            it = S.find({C[A[i - K + 1]], A[i - K + 1]});
            S.erase(it);
            S.insert({--C[A[i - K + 1]], A[i - K + 1]});
        }
    }
}
