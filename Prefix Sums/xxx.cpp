#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#define MAXN 1000000
using namespace std;

vector<int> H(MAXN + 1);
vector<int> suffixMax(MAXN + 2);
int N;

int main() {
	scanf("%d", &N);
	for (int i = 1; i <= N; ++i)
		scanf("%d", &H[i]);
	suffixMax[N + 1] = 0;
	for (int i = N; i >= 1; --i)
		suffixMax[i] = max(suffixMax[i + 1], H[i]);
	int ans = 0;
	for (int i = 1; i <= N; ++i)
		ans += (H[i] > suffixMax[i + 1]);
	printf("%d\n", ans);
}