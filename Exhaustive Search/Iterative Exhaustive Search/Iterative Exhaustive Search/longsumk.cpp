#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#define MAXN 1000000
using namespace std;

vector<int> A(MAXN);
int N;
int K;

int main() {
	freopen("longsumk.in", "r", stdin);
	freopen("longsumk.out", "w", stdout);
	scanf("%d %d", &N, &K);
	for (int i = 0; i < N; ++i)
		scanf("%d", &A[i]);
	// O(n^2). 
	int maxLength = 0;
	for (int i = 0; i < N; ++i) {
		int sum = 0;
		for (int j = i; j < N; ++j) {
			sum += A[j];
			if (sum == K)
				maxLength = max(maxLength, j - i + 1);
			else if (sum > K)
				break;
		}
	}
	printf("%d\n", maxLength);

	// O(n^3).
	for (int i = 0; i < N; ++i) {
		for (int j = i; j < N; ++j) {
			int sum = 0;
			for (int r = i; r <= j; ++r)
				sum += A[j];
			if (sum == K)
				maxLength = max(maxLength, j - i + 1);
		}
	}
}