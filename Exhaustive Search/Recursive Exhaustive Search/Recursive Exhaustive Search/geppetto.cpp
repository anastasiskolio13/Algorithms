#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <set>
#define MAXN 20
using namespace std;

vector<vector<int>> X(MAXN);
int N;
int M;

int GetCombinations(int i, set<int> S) {
	if (i == N)
		return 1;
	int doNotTakeTakeIt = GetCombinations(i + 1, S);
	for (int ingredient : X[i])
		if (S.find(ingredient) != S.end())
			return doNotTakeTakeIt;
	S.insert(i);
	int takeIt = GetCombinations(i + 1, S);
	return doNotTakeTakeIt + takeIt;
}

int main() {
	scanf("%d %d", &N, &M);
	for (int i = 0; i < M; ++i) {
		int A, B;
		scanf("%d %d", &A, &B);
		A > B ? X[--A].push_back(--B) : X[--B].push_back(--A);
	}
	set<int> S;
	printf("%d\n", GetCombinations(0, S));
}