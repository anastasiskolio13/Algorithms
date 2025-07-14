#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#define MAXN 1e6
using namespace std;

vector<int> A(MAXN + 1);
int N;

int main() {
	scanf("%d", &N);
	for (int i = 1; i <= N; ++i)
		scanf("%d", &A[i]);
	long long sumOne = 0;
	for (int i = 1; i <= N; ++i) {
		long long sumTwo = 0;
		for (int j = i + 1; j <= N; ++j)
			sumTwo += A[i] + A[j];
		sumOne += sumTwo;
	}
	printf("%.2lf", (double)sumOne / N / 10000);
}