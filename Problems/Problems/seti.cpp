#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#define MAXN 10000
using namespace std;

vector<int> A(MAXN);
vector<int> P;
int N;

int main() {
	freopen("seti.in", "r", stdin);
	freopen("seti.out", "w", stdout);
	scanf("%d", &N);
	for (int i = 0; i < N; ++i)
		scanf("%d", &A[i]);
	for (int i = 1; i < N - 1; ++i) {
		int left = i - 1;
		int right = i + 1;
		while (left >= 0 && right < N) {
			if (A[left] == A[right] && 2 * A[left] < A[i]) {
				P.push_back(i + 1);
				break;
			}
			--left;
			++right;
		}
	}
	printf("%d\n", P.size());
	for (int i = 0; i < P.size(); ++i)
		printf("%d\n", P[i]);
}