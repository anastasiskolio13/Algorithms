#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#define MAXN 100000
using namespace std;

struct teamOfCows {
	int C;
	int T;
};

bool compareTeamsOfCows(teamOfCows A, teamOfCows B) {
	return A.T < B.T;
}

vector<teamOfCows> A(MAXN);
int N;

int main() {
	freopen("pairup.in", "r", stdin);
	freopen("pairup.out", "w", stdout);
	scanf("%d", &N);
	for (int i = 0; i < N; ++i)
		scanf("%d %d", &A[i].C, &A[i].T);
	sort(A.begin(), A.begin() + N, compareTeamsOfCows);
	int maximumTime = 0;
	int i = 0;
	int j = N - 1;
	while (i <= j) {
		maximumTime = max(maximumTime, A[i].T + A[j].T);
		if (A[i].C < A[j].C) {
			A[j].C -= A[i++].C;
		}
		else if (A[i].C > A[j].C) {
			A[i].C -= A[j--].C;
		}
		else {
			++i;
			--j;
		}

	}
	printf("%d\n", maximumTime);
}