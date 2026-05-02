#include <iostream>
#include <vector>
#include <climits>
#define MAXN 20
#define MAXM 10
using namespace std;

vector<int> S(MAXN);
vector<int> T(MAXN);
vector<int> C(MAXN);
vector<int> A(MAXM);
vector<int> B(MAXM);
vector<int> P(MAXM);
vector<int> K(MAXM);
int N;
int M;

int main() {
    cin >> N >> M;
    for (int i = 0; i < N; ++i)
        cin >> S[i] >> T[i] >> C[i];
    for (int i = 0; i < M; ++i)
        cin >> A[i] >> B[i] >> P[i] >> K[i];
    int minimumTotalCost = INT_MAX;
    for (int s = 0; s < 1 << M; ++s) {
        int totalCost = 0;
        vector<int> X(101, 0);
        for (int i = 0; i < M; ++i) {
            if (!(s & (1 << i)))
                continue;
            totalCost += K[i];
            for (int j = A[i]; j <= B[i]; ++j)
                X[j] += P[i];
        }
        bool allCowsSatisfied = true;
        for (int i = 0; i < N; ++i) {
            bool isSatisfied = true;
            for (int j = S[i]; j <= T[i]; ++j) {
                if (X[j] < C[i]) {
                    isSatisfied = false;
                    break;
                }
            }
            if (!isSatisfied) {
                allCowsSatisfied = false;
                break;
            }
        }
        if (allCowsSatisfied)
            minimumTotalCost = min(minimumTotalCost, totalCost);
    }
    cout << minimumTotalCost << endl;
}