#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#define MAXN 500000
using namespace std;

struct couple {
	int A;
	int B;
};

bool compareCouples(couple X, couple Y) {
	return X.A < Y.A || X.A == Y.A && X.B < Y.B;
}

vector<couple> C(MAXN);
vector<int> dp(MAXN);
int N;

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; ++i)
		scanf("%d %d", &C[i].A, &C[i].B);
	sort(C.begin(), C.begin() + N, compareCouples);
	for (int i = N - 1; i >= 0; --i) {
		dp[i] = 1;
		for (int j = i + 1; j < N; ++j)
			if (C[j].B >= C[i].B)
				dp[i] = max(dp[i], dp[j] + 1);
	}
	printf("%d\n", *max_element(dp.begin(), dp.begin() + N));
}

