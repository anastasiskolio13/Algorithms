#include <iostream>
#include <vector>
#include <climits>
#include <deque>
#define MAXN 150000
#define MAXM 300
#define INF LLONG_MAX
using namespace std;

vector<vector<long long>> dp(2, vector<long long>(MAXN));
vector<int> A(MAXM);
vector<int> B(MAXM);
vector<int> T(MAXM);
int N;
int M;
int D;

int main() {
    cin >> N >> M >> D;
    for (int i = 0; i < M; ++i) {
        cin >> A[i] >> B[i] >> T[i];
        --A[i];
    }
    for (int i = 0; i < N; ++i)
        dp[(M - 1) % 2][i] = B[M - 1] - abs(A[M - 1] - i);
    for (int j = M - 2; j >= 0; --j) {
        deque<int> Q;
        int k = 0;
        while (k <= min((long long)N - 1, (T[j + 1] - T[j]) * (long long)D)) {
            while (!Q.empty() && dp[(j + 1) % 2][k] >= dp[(j + 1) % 2][Q.back()])
                Q.pop_back();
            Q.push_back(k);
            ++k;
        }
        dp[j % 2][0] = dp[(j + 1) % 2][Q.front()] + B[j] - A[j]; 
        for (int i = 1; i < N; ++i) {
            if (Q.front() < i - (T[j + 1] - T[j]) * (long long)D)
                Q.pop_front();
            if (k < N) {
                while (!Q.empty() && dp[(j + 1) % 2][k] >= dp[(j + 1) % 2][Q.back()])
                    Q.pop_back();
                Q.push_back(k);
                k++;
            }
            dp[j % 2][i] = dp[(j + 1) % 2][Q.front()] + B[j] - abs(A[j] - i);
        }
    }
    long long ans = -INF;
    for (int i = 0; i < N; ++i)
        ans = max(ans, dp[0][i]);
    cout << ans << endl;
}