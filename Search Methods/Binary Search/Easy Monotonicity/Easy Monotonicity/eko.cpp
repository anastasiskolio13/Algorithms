#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#define MAXN 1000000
using namespace std;

vector<int> H(MAXN);
int N;
int M;

long long MetersCut(int height) {
	long long totalMetersCut = 0;
	for (int i = 0; i < N; ++i)
		totalMetersCut += max(H[i] - height, 0);
	return totalMetersCut;
}

int main() {
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; ++i)
		scanf("%d", &H[i]);
	int lo = 0;
	int hi = *max_element(H.begin(), H.begin() + N);
	while (lo < hi) {
		int mid = (lo + hi + 1) / 2;
		if (MetersCut(mid) >= M)
			lo = mid;
		else
			hi = mid - 1;
	}
	printf("%d\n", lo);
}