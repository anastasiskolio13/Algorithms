#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <tuple>
#define MAXN 1000000
using namespace std;

vector<int> A(MAXN);
int N;

tuple<int, int, int> maximumGoldCoins(int lo, int hi) {
	if (lo == hi)
		return { A[lo], lo, lo };
	int mid = (lo + hi) / 2;
	auto [sumLeft, minLeft, maxLeft] = maximumGoldCoins(lo, mid);
	auto [sumRight, minRight, maxRight] = maximumGoldCoins(mid + 1, hi);
	if (maxLeft == mid && minRight == mid + 1) {
		if (A[mid] > A[mid + 1]) {
			if (minRight == maxRight)
				maxRight = maxLeft;
			sumRight -= A[mid + 1];
		}
		else {
			if (minLeft == maxLeft)
				minLeft = minRight;
			sumLeft -= A[mid];
		}
	}
	return { sumLeft + sumRight, minLeft, maxRight };
}

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; ++i)
		scanf("%d", &A[i]);
	printf("%d\n", get<0>(maximumGoldCoins(0, N - 1)));
}