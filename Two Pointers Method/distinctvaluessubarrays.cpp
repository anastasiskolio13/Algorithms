#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <map>
#define MAXN 200000
using namespace std;

map<int, int> C;
vector<int> A(MAXN);
int N;

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; ++i)
		scanf("%d", &A[i]);
	long countOfSubarrays = 0;
	int countOfDistinctNumbers = 0;
	int i = 0;
	for (int j = 0; j < N; ++j) {
		countOfDistinctNumbers += !C[A[j]]++;
		while (countOfDistinctNumbers < j - i + 1)
			countOfDistinctNumbers -= !--C[A[i++]];
		countOfSubarrays += j - i + 1;
	}
	printf("%ld\n", countOfSubarrays);
}