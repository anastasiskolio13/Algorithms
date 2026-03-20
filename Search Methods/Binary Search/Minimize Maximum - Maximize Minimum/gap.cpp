#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#define MAXN 100000
using namespace std;

vector<char> A(MAXN);
vector<char> B(MAXN);
int N;
int K;

int canAchieveMaximumGapSize(int S) {
	for (int i = 0; i < N; ++i)
		B[i] = A[i];
	int roadsNeeded = 0;
	int i = 0;
	while (i < N) {
		int j = i;
		while (j < N && A[j] == '.' && j - i + 1 <= S)
			++j;
		if (j < N && A[j] == '.' && j - i + 1 > S) {
			++roadsNeeded;
			B[j] = '#';
		}
		i = j + 1;
	}
	return roadsNeeded <= K;
}

int main() {
	scanf("%d %d", &N, &K);
	for (int i = 0; i < N; ++i)
		scanf(" %c", &A[i]);
	int lo = 0;
	int hi = N;
	while (lo < hi) {
		int mid = (lo + hi) / 2;
		if (canAchieveMaximumGapSize(mid))
			hi = mid;
		else
			lo = mid + 1;
	}
	printf("%d\n", lo);
	canAchieveMaximumGapSize(lo);
	for (int i = 0; i < N; ++i)
		printf("%c", B[i]);
}