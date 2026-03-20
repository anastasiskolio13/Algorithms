#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#define MAXN 1e6
using namespace std;

vector<int> A(MAXN + 1);
vector<long long> PS(MAXN + 1);
int N;

int main() {
	scanf("%d", &N);
	PS[0] = 0;
	for (int i = 1; i <= N; ++i) {
		scanf("%d", &A[i]);
		PS[i] = PS[i - 1] + A[i];
	}
	long long sumOne = 0;
	for (int i = 1; i <= N; ++i) {
		long long sumTwo = (long long)A[i] * (N - i) + PS[N] - PS[i];
		sumOne += sumTwo;
	}
	printf("%.2lf", (double)sumOne / N / 10000);
}