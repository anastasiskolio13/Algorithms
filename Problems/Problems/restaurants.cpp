#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#define MAXN 1000000
using namespace std;

vector<int> A(MAXN + 1);
vector<int> B(MAXN + 1);
vector<int> C(MAXN + 1);
vector<vector<int>> dp1(MAXN + 1, vector<int>(2));
vector<vector<int>> dp2(MAXN + 1, vector<int>(2));
int N;

int main() {
	freopen("restaurants.in", "r", stdin);
	freopen("restaurants.out", "w", stdout);
	scanf("%d", &N);
	for (int i = 1; i <= N; ++i)
		scanf("%d", &A[i]);
	for (int i = 1; i <= N; ++i)
		scanf("%d", &B[i]);
	for (int i = 2; i <= N - 1; ++i)
		scanf("%d", &C[i]);
	dp1[N][0] = dp2[N][0] = 0;
	dp1[N][1] = dp2[N][1] = B[N];
	for (int i = N - 1; i >= 2; --i) {
		dp1[i][0] = max(dp1[i + 1][1] + B[i], dp2[i + 1][1] + A[i]);
		dp1[i][1] = max(dp1[i + 1][1] + C[i], dp2[i + 1][1] + B[i]);
		dp2[i][0] = max(dp1[i + 1][0] + B[i], dp2[i + 1][0] + A[i]);
		dp2[i][1] = max(dp1[i + 1][0] + C[i], dp2[i + 1][0] + B[i]);
	}
	printf("%d\n", max(dp1[2][0], dp1[2][1]));
}