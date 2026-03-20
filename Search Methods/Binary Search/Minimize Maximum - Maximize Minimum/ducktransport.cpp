#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cmath>
using namespace std;

int N;
int D;

long DaysNeededForAllDucksToReachTheirHomesWithMaximumStep(int K) {
	long totalTimeNeeded = 0;
	for (int i = 1; i <= N - D; ++i)
		totalTimeNeeded += ceil((double)i / K);
	return totalTimeNeeded;
}

int main() {
	scanf("%d %d", &N, &D);
	if (D >= N) {
		printf("%d\n", 0);
		return 0;
	}
	int lo = 1;
	int hi = N;
	while (lo < hi) {
		int mid = (lo + hi) / 2;
		if (DaysNeededForAllDucksToReachTheirHomesWithMaximumStep(mid) <= D)
			hi = mid;
		else
			lo = mid + 1;
	}
	printf("%d\n", DaysNeededForAllDucksToReachTheirHomesWithMaximumStep(lo) <= D ? lo : -1);
}