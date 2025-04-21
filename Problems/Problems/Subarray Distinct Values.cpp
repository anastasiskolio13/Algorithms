#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <map>
#define MAXN 200000
using namespace std;

map<int, int> C;
vector<int> A(MAXN);
int N;
int K;

int main() {
	scanf("%d %d", &N, &K);
	for (int i = 0; i < N; ++i)
		scanf("%d", &A[i]);
	int i = 0;
	int distinctValues = 0;
	long numberOfSubarraysWithAtMostKDistinctValues = 0;
	for (int j = 0; j < N; ++j) {
		distinctValues += !C[A[j]]++;
		while (distinctValues > K)
			distinctValues -= !--C[A[i++]];
		numberOfSubarraysWithAtMostKDistinctValues += j - i + 1;
	}
	printf("%ld\n", numberOfSubarraysWithAtMostKDistinctValues);
}