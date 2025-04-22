#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#define MAXN 200000
using namespace std;

struct movie {
	int A;
	int B;
};

bool compareMovies(movie X, movie Y) {
	return X.B < Y.B;
}

set<int> S;
vector<movie> M(MAXN);
int N;
int K;

int main() {
	scanf("%d %d", &N, &K);
	for (int i = 0; i < N; ++i)
		scanf("%d %d", &M[i].A, &M[i].B);
	sort(M.begin(), M.begin() + N, compareMovies);
	int totalMovies = 0;
	for (int i = 0; i < N; ++i) {
		while ()
	}
	printf("%d\n", totalMovies);
}