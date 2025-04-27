#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <climits>
#define MAXH 1000000
#define INF 1000000000
using namespace std;

vector<bool> isItchySpot(MAXH);
vector<int> dp(MAXH + 1);
vector<int> T(4 * MAXH + 1);
int H;
int J;
int N;

void Update(int lo, int hi, int v, int i) {
	if (lo == hi) {
		T[v] = dp[i];
		return;
	}
	int mid = (lo + hi) / 2;
	if (i <= mid)
		Update(lo, mid, 2 * v, i);
	else
		Update(mid + 1, hi, 2 * v + 1, i);
	T[v] = min(T[2 * v], T[2 * v + 1]);
}

int Query(int lo, int hi, int v, int qlo, int qhi) {
	if (qlo <= lo && hi <= qhi)
		return T[v];
	if (qlo > hi || qhi < lo)
		return INF;
	int mid = (lo + hi) / 2;
    int minLeft = Query(lo, mid, 2 * v, qlo, qhi);
	int minRight = Query(mid + 1, hi, 2 * v + 1, qlo, qhi);
	return min(minLeft, minRight);
}

int main() {
	scanf("%d %d %d", &H, &J, &N);
	for (int i = 0; i < N; ++i) {
		int A, B;
		scanf("%d %d", &A, &B);
		for (int spot = A; spot <= B; ++spot)
			isItchySpot[spot] = true;
	}
	dp[H] = 0;
	Update(0, H, 1, H);
	for (int i = H - J; i < H; ++i) {
		dp[i] = !isItchySpot[i] ? 1 : INF;
		Update(0, H, 1, i);
	}
	for (int i = H - J - 1; i >= 0; --i) {
		dp[i] = !isItchySpot[i] && !isItchySpot[i + J] ? min(Query(0, H, 1, i + 1, i + J - 1) + 2, dp[i + J] + 1) : INF;
		Update(0, H, 1, i);
	}
	printf("%d\n", dp[0] >= INF ? -1 : dp[0]);
}