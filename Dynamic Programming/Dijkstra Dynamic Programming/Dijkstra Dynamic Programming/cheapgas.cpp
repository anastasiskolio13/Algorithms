#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <cfloat>
#include <set>
#include <array>
#include <tuple>
#define MAXN 100
#define MAXM 100
#define MAX_FUEL MAXN + MAXM - 1
#define INF_PRICE DBL_MAX
#define INF_COST DBL_MAX
using namespace std;

set<tuple<double, int, int, int>> Q;
vector<vector<double>> gasPrice(MAXN, vector<double>(MAXM));
vector<vector<vector<double>>> dp(MAXN, vector<vector<double>>(MAXM, vector<double>(MAX_FUEL)));
int T;
int N;
int M;
int F; 
int K;

double Dijkstra() {
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < M; ++j)
			for (int f = 0; f <= F; ++f)
				dp[i][j][f] = INF_COST;
	dp[0][0][F] = 0;
	Q.insert({ 0, 0, 0, F });
	while (!Q.empty()) {
		auto [c, i, j, f] = *Q.begin();
		Q.erase(Q.begin());
		if (c > dp[i][j][f])
			continue;
		// Βάζω βενζίνη.
		if (gasPrice[i][j] != INF_PRICE && f != F && dp[i][j][f] + gasPrice[i][j] < dp[i][j][f + 1]) {
			dp[i][j][f + 1] = dp[i][j][f] + gasPrice[i][j];
			Q.insert({ dp[i][j][f + 1], i, j, f + 1 });
		}
		// Δεν έχω άλλη βενζίνη, δε μπορώ να πάω πουθενά.
		if (!f)
			continue;
		if (i - 1 >= 0 && dp[i][j][f] < dp[i - 1][j][f - 1]) {
			dp[i - 1][j][f - 1] = dp[i][j][f];
			Q.insert({ dp[i - 1][j][f - 1], i - 1, j, f - 1 });
		}
		if (i + 1 < N && dp[i][j][f] < dp[i + 1][j][f - 1]) {
			dp[i + 1][j][f - 1] = dp[i][j][f];
			Q.insert({ dp[i + 1][j][f - 1], i + 1, j, f - 1 });
		}
		if (j - 1 >= 0 && dp[i][j][f] < dp[i][j - 1][f - 1]) {
			dp[i][j - 1][f - 1] = dp[i][j][f];
			Q.insert({ dp[i][j - 1][f - 1], i, j - 1, f - 1 });
		}
		if (j + 1 < M && dp[i][j][f] < dp[i][j + 1][f - 1]) {
			dp[i][j + 1][f - 1] = dp[i][j][f];
			Q.insert({ dp[i][j + 1][f - 1], i, j + 1, f - 1 });
		}
	}
	double minimumCost = DBL_MAX;
	for (int f = 0; f <= F; ++f)
		minimumCost = min(minimumCost, dp[N - 1][M - 1][f]);
	return minimumCost;
}

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d %d %d", &N, &M, &F, &K);
		for (int i = 0; i < N; ++i)
			for (int j = 0; j < M; ++j)
				gasPrice[i][j] = INF_PRICE;
		for (int i = 0; i < K; ++i) {
			int A, B; double C;
			scanf("%d %d %lf", &A, &B, &C);
			gasPrice[--A][--B] = C;
		}
		// Δεν έχει νόημα σε καμία φάση να έχω παραπάνω από N + M - 2 λίτρα στο ρεζερβουάρ.
		F = min(F, N + M - 2);
		double minimumCost = Dijkstra();
		minimumCost != DBL_MAX ? printf("%.2lf\n", minimumCost) : printf("Stranded on the shoulder\n");
	}
}