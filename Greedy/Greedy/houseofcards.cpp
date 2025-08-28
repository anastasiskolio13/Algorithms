#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#define MAXN 2000
using namespace std;

vector<int> W(MAXN);
int N;
int K;

int main() {
	scanf("%d %d", &N, &K);
	for (int i = 0; i < N; ++i)
		scanf("%d", &W[i]);
	sort(W.begin(), W.begin() + N, greater<int>());
	int i = 0;
	int ans = 0;
	while (i < N) {
		++ans;
		int j = i + 1;
		while (j < N && W[j] + K > W[i])
			++j;
		i = j;
	}
	printf("%d\n", ans);
}