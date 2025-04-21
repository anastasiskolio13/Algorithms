#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cmath>
using namespace std;

long long A;
long long B;

double timeTakenToReachTheGroundWith(long long K) {
	return A / (double) sqrt(1 + K) + K * B;
}

int main() {
	scanf("%lld %lld", &A, &B);
	long long lo = 0;
	long long hi = A / B;
	while (lo < hi) {
		long long mid = (lo + hi) / 2;
		if (timeTakenToReachTheGroundWith(mid) > timeTakenToReachTheGroundWith(mid + 1))
			lo = mid + 1;
		else
			hi = mid;
	}
	printf("%.6lf\n", timeTakenToReachTheGroundWith(lo));
}