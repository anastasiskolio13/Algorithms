#include <iostream>
#include <vector>
#include <map>
#define MAXN 200000
using namespace std;

map<int, int> C;
vector<int> A(MAXN + 1);
vector<long long> PS(MAXN + 1);
vector<int> R(MAXN + 1);
vector<long long> SM(MAXN + 2);
vector<int> index(MAXN + 2);
int N;
int K;

int main() {
    cin >> N >> K;
    for (int i = 1; i <= N; ++i) {
        cin >> A[i];
        PS[i] = PS[i - 1] + A[i];
    }
    SM[N + 1] = -1e18;
    index[N + 1] = N + 1;
    for (int i = N; i >= 1; --i) {
        if (PS[i] > SM[i + 1]) {
            SM[i] = PS[i];
            index[i] = i;
        }
        else {
            SM[i] = SM[i + 1];
            index[i] = index[i + 1];
        }
    }
    for (int i = 1, j = 1; i <= N; ++i) {
        while (j <= N && C.size() < K) 
            ++C[A[j++]];
        if (C.size() == K)
            R[i] = j;
        else 
            R[i] = N + 1;
        if (!--C[A[i]])
            C.erase(A[i]);
    }
    long long ans = -1e18;
    int opt_i = -1;
    int opt_j = -1;
    for (int i = 1; i <= N; ++i) {
        if (R[i] <= N && SM[R[i]] - PS[i - 1] > ans) {
            ans = SM[R[i]] - PS[i - 1];
            opt_i = i;
            opt_j = index[R[i]];
        }
    }
    if (opt_i == -1) {
        cout << "IMPOSSIBLE" << endl;
    }
    else {
        cout << ans << endl << opt_i << " " << opt_j << endl;
    }
}