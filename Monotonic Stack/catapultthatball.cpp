#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#define MAXN 50000
using namespace std;

stack<int> S;
vector<int> H(MAXN);
vector<int> R(MAXN);
int N;
int Q;

int main() {
	scanf("%d %d", &N, &Q);
	for (int i = 0; i < N; ++i)
		scanf("%d", &H[i]);
	fill(R.begin(), R.begin() + N, N);
	for (int j = 0; j < N; ++j) {
		while (!S.empty() && H[j] > H[S.top()]) {
			int i = S.top();
			S.pop();
			R[i] = j;
		}
		S.push(j);
	}
	int ans = 0;
	while (Q--) {
		int A, B;
		scanf("%d %d", &A, &B);
		ans += R[--A] >= --B;
	}
	printf("%d\n", ans);
}