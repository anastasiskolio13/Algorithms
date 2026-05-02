#include <iostream>
#include <vector>
#include <climits>
#define MAXN 100000
#define MAXM 100000
using namespace std;

vector<int> H(MAXN);
vector<int> S(MAXM);
vector<int> P(MAXM);
vector<int> C(MAXN, INT_MAX);
int N;
int M;

int main() {
    cin >> N >> M;
    for (int i = 0; i < N; ++i)
        cin >> H[i];
    for (int i = 0; i < M; ++i)
        cin >> S[i];
    for (int i = 0; i < M; ++i)
        cin >> P[i];
    int prefixMinimum = INT_MAX;
    for (int i = 0, j = 0; i < N; ++i) {
        while (j < M && S[j] < H[i])
            prefixMinimum = min(prefixMinimum, P[j] - S[j++]);
        if (j > 0)
            C[i] = prefixMinimum + H[i];
    }
    int suffixMinimum = INT_MAX;
    for (int i = N - 1, j = M - 1; i >= 0; --i) {
        while (j >= 0 && S[j] > H[i])
            suffixMinimum = min(suffixMinimum, P[j] + S[j--]);
        if (j < M - 1)
            C[i] = min(C[i], suffixMinimum - H[i]);
    }
    for (int i = 0; i < N; ++i)
        cout << C[i] << " ";
}