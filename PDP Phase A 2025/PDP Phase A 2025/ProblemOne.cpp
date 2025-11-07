#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#define MAXN 200000
using namespace std;

vector<int> H(MAXN);
int N;

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; ++i)
		scanf("%d", &H[i]);
	sort(H.begin(), H.begin() + N);
	int i = 0;
	int ans = 0;
	while (i < N) {
		++ans;
		int j = i;
		while (j < N && H[j] == H[i])
			++j;
		i = j;
	}
	printf("%d\n", ans);
}