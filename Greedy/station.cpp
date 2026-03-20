#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#define MAXN 500000
using namespace std;

vector<int> L(MAXN);
int N;
int K;

int main() {
	scanf("%d %d", &N, &K);
	for (int i = 0; i < N; ++i)
		scanf("%d", &L[i]);
	int i = 0;
	int minimumNumberOfDays = 0;
	while (i < N - 1) {
		++minimumNumberOfDays;
		int j = i + 1;
		int kilometresRemaining = K;
		int lastLodge = i;
		while (j < N && kilometresRemaining > 0) {
			--kilometresRemaining;
			if (L[j])
				lastLodge = j;
			++j;
		}
		if (lastLodge == i) {
			printf("%d\n", -1);
			return 0;
		}
		i = lastLodge;
	}
	printf("%d\n", minimumNumberOfDays);
}