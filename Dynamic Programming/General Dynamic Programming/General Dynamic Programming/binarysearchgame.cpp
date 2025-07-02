#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#define MAXN 2000
using namespace std;

vector<int> A(MAXN + 1);
vector<int> PS(MAXN + 1);
vector<vector<long long>> dp(MAXN + 1, vector<long long>(MAXN + 1));
int N;

int main() {
	scanf("%d", &N);
	for (int i = 1; i <= N; ++i) {
		scanf("%d", &A[i]);
		PS[i] = PS[i - 1] + A[i];
	}
	for (int i = 1; i <= N; ++i)
		dp[i][i] = 0;
	for (int l = 2; l <= N; ++l) {
		for (int i = 1; i <= N - l + 1; ++i) {
			int j = i + l - 1;
			dp[i][j] = min(dp[i][(i + j) / 2] + PS[(i + j) / 2] - PS[i - 1], dp[(i + j) / 2 + 1][j] + PS[j] - PS[(i + j) / 2]);
		}
	}
	printf("%lld\n", dp[1][N]);


	//for (int i = 1; i < N; ++i) 
		//for (int j = i + 1; j <= N; ++j)
			//cout << i << " " << j << ": " << i << " " << (i + j) / 2 << " and " << (i + j) / 2 + 1 << " " << j << endl;
}