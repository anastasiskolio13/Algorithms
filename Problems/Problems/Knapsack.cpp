#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#define MAXS 2000
#define MAXN 100000
using namespace std;

vector<int> V(MAXN);
vector<int> W(MAXN);
vector<int> K(MAXN);
vector<vector<pair<int, int>>> T(MAXS + 1);
vector<long long> dp(MAXS + 1);
int N;
int S;

int main() {
	scanf("%d %d", &S, &N);
	for (int i = 0; i < N; ++i) {
		scanf("%d %d %d", &V[i], &W[i], &K[i]);
		T[W[i]].push_back({ V[i], K[i] });
	}
	for (int s = 1; s <= S; ++s)
		sort(T[s].begin(), T[s].end(), greater<pair<int, int>>());
	for (int s = 1; s <= S; ++s) {
		for (int w = 1; w <= s; ++w) {
			int i = 0;
			int sumOfWeights = 0;
			long long sumOfValues = 0;
			while (i < T[w].size() && sumOfWeights + w <= s) {
				int j = 0;
				while (j < T[w][i].second && sumOfWeights + w <= s) {
					sumOfWeights += w;
					sumOfValues += T[w][i].first;
					dp[s] = max(dp[s], dp[s - sumOfWeights] + sumOfValues);
					++j;
				}
				++i;
			}
		}
	}
	printf("%lld\n", dp[S]);
}