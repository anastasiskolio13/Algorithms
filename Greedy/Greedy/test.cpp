#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
using namespace std;

string S;

int main() {
	cin >> S;
	int i = 0;
	int ans = 0;
	while (i < S.size()) {
		int j = i;
		while (j < S.size() && S[j] == S[i])
			++j;
		ans = max(ans, j - i);
		i = j;
	}
	printf("%d\n", ans);
}