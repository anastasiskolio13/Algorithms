#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <climits>
#include <deque>
#define MAXN 20000
#define MAXX 20000
#define INF INT_MAX
using namespace std;

vector<int> B(MAXN + 1);
vector<int> C(MAXN + 1);
vector<vector<int>> dp(2, vector<int>(MAXX + 1));
int N;
int X;

int main() {
	// Ανάγνωση δεδομένων.
	scanf("%d", &N);
	for (int i = 1; i <= N; ++i)
		scanf("%d", &B[i]);
	for (int i = 1; i <= N; ++i)
		scanf("%d", &C[i]);
	scanf("%d", &X);
	// Οριακές συνθήκες.
	for (int i = 0; i <= N; ++i)
		dp[i % 2][0] = 0;
	for (int x = 1; x <= X; ++x)
		dp[0][x] = INF;
	// Έπίλυση.
	for (int i = 1; i <= N; ++i) {

		vector<deque<int>> Q(B[i]);

		for (int x = 0; x < B[i]; ++x)
			Q[x].push_back(x);

		for (int x = B[i]; x <= X; ++x) {
			
			int currentQueue = x % B[i];

			if (!Q[currentQueue].empty() && x - C[i] * B[i] > Q[currentQueue].front())
				Q[currentQueue].pop_front();

			dp[i % 2][x] = dp[(i - 1) % 2][Q[currentQueue].front()] + (x - Q[currentQueue].front()) / B[i];

			while (!Q[currentQueue].empty() && dp[(i - 1) % 2][x - B[i]] <= dp[(i - 1) % 2][Q[currentQueue].back()])
				Q[currentQueue].pop_back();
			Q[currentQueue].push_back(x - B[i]);

		}
	}
	// Αρχικό πρόβλημα.
	printf("%d\n", dp[N % 2][X]);
}