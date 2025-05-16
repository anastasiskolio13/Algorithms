#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <deque>
#define MAXH 1000000
#define INF 1000000000
using namespace std;

deque<int> Q;
vector<bool> isItchySpot(MAXH);
vector<int> dp(MAXH + 1);
int H;
int J;
int N;

int main() {
	scanf("%d %d %d", &H, &J, &N);
	for (int i = 0; i < N; ++i) {
		int A, B;
		scanf("%d %d", &A, &B);
		for (int spot = A; spot <= B; ++spot)
			isItchySpot[spot] = true;
	}
	dp[H] = 0;
	Q.push_back(H);
	for (int i = H - 1; i >= 0; --i) {
		if (Q.front() == i + J)
			Q.pop_front();
		if (i >= H - J) 
			dp[i] = !isItchySpot[i] ? 1 : INF;
		else 
			dp[i] = !isItchySpot[i] && !isItchySpot[i + J] ? min(!Q.empty() ? dp[Q.front()] + 2 : INF, dp[i + J] + 1) : INF;
		while (!Q.empty() && dp[i] <= dp[Q.back()])
			Q.pop_back();
		Q.push_back(i);
	}
	printf("%d\n", dp[0] >= INF ? -1 : dp[0]);
}