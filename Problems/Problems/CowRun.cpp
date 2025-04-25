#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#define MAXN 1000
#define left 0
#define right 1
using namespace std;

vector<int> X(MAXN);
vector<int> XL;
vector<int> XR;
vector<vector<vector<long long>>> dp(MAXN + 2, vector<vector<long long>>(MAXN + 2, vector<long long>(2)));
int N;

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; ++i) {
		scanf("%d", &X[i]);
		X[i] < 0 ? XL.push_back(X[i]) : XR.push_back(X[i]);
	}
	dp[0][XR.size() - 1][left] = dp[0][XR.size() - 1][right] = 0;
	for (int j = XR.size() - 2; j >= 0; j--) {

	}
}