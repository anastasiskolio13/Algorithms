#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#define MAXN 100000
using namespace std;

set<char> S;
map<char, int> C;
vector<char> A(MAXN);
int N;

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; ++i) {
		scanf(" %c", &A[i]);
		S.insert(A[i]);
	}
	int minimumSizeSegmentContainingAllCharacters = N;
	int distinctCharacters = 0;
	int j = 0;
	for (int i = 0; i < N; ++i) {
		while (j < N && distinctCharacters < S.size())
			distinctCharacters += !C[A[j++]]++;
		if (distinctCharacters == S.size())
			minimumSizeSegmentContainingAllCharacters = min(minimumSizeSegmentContainingAllCharacters, j - i);
		distinctCharacters -= !--C[A[i]];
	}
	printf("%d\n", minimumSizeSegmentContainingAllCharacters);
}