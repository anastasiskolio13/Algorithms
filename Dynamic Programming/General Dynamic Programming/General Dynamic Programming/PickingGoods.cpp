#include <iostream>
#include <vector>
#include <algorithm>
#define MAXN 3000
#define MAXM 3000
using namespace std;

vector<vector<int>> A(MAXN, vector<int>(MAXM));
vector<vector<vector<long long>>> dp(MAXN, vector<vector<long long>>(MAXM, vector<long long>(4)));
int N;
int M;
int K;

int main() {
    // Input.
    cin >> N >> M >> K;
    for (int i = 0; i < K; ++i) {
        int row;
        int column;
        int value;
        cin >> row >> column >> value;
        A[row - 1][column - 1] = value;
    }

    // Base cases.
    dp[N - 1][M - 1][0] = 0;
    dp[N - 1][M - 1][1] = A[N - 1][M - 1];
    dp[N - 1][M - 1][2] = A[N - 1][M - 1];
    dp[N - 1][M - 1][3] = A[N - 1][M - 1];

    // Last row.
    for (int j = M - 2; j >= 0; --j) {
        dp[N - 1][j][0] = dp[N - 1][j + 1][0];
        dp[N - 1][j][1] = max(dp[N - 1][j + 1][0] + A[N - 1][j], dp[N - 1][j + 1][1]);
        dp[N - 1][j][2] = max(dp[N - 1][j + 1][1] + A[N - 1][j], dp[N - 1][j + 1][2]); 
        dp[N - 1][j][3] = max(dp[N - 1][j + 1][2] + A[N - 1][j], dp[N - 1][j + 1][3]);
    }

    // Last column.
    for (int i = N - 2; i >= 0; --i) {
        dp[i][M - 1][0] = dp[i + 1][M - 1][3];
        dp[i][M - 1][1] = dp[i + 1][M - 1][3] + A[i][M - 1];
        dp[i][M - 1][2] = dp[i + 1][M - 1][3] + A[i][M - 1];
        dp[i][M - 1][3] = dp[i + 1][M - 1][3] + A[i][M - 1];
    }

    // Internal cells.
    for (int i = N - 2; i >= 0; --i) {
        for (int j = M - 2; j >= 0; --j) {
            dp[i][j][0] = max(dp[i + 1][j][3], dp[i][j + 1][0]);
            dp[i][j][1] = max({dp[i + 1][j][3] + A[i][j], dp[i][j + 1][0] + A[i][j], dp[i][j + 1][1]});
            dp[i][j][2] = max({dp[i + 1][j][3] + A[i][j], dp[i][j + 1][1] + A[i][j], dp[i][j + 1][2]});
            dp[i][j][3] = max({dp[i + 1][j][3] + A[i][j], dp[i][j + 1][2] + A[i][j], dp[i][j + 1][3]});
        }
    }

    // Solution.
    cout << dp[0][0][3] << endl;
}