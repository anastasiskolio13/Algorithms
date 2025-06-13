#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#define MAXN 2000000
using namespace std;

vector<int> M(MAXN + 1);
int N;
int K;

int main() {
	//freopen("kite.in", "r", stdin);
	//freopen("kite.out", "w", stdout);
	scanf("%d %d", &N, &K);
	for (int i = 1; i <= N; ++i)
		scanf("%d", &M[i]);
	// O(n^3).
	int minimumSizeSubarraySumK = N + 1;
	// ��� ���� ���� i.
	for (int i = 1; i <= N; ++i) {
		// ��� ���� ����� j.
		for (int j = i; j <= N; ++j) {
			// ���� �� �������� ��� ��������� (i, j).
			int sumOfElements = 0;
			for (int r = i; r <= j; ++r)
				sumOfElements += M[r];
			if (sumOfElements == K)
				minimumSizeSubarraySumK = min(minimumSizeSubarraySumK, j - i + 1);
		}
	}
	// ������� if: <�������> ? <������ ��� ����� �������> : <������ ��� ����� �������>;
	printf("%d\n", minimumSizeSubarraySumK == N + 1 ? 0 : minimumSizeSubarraySumK);

	// O(n^3) ������.
	minimumSizeSubarraySumK = N + 1;
	// ��� ���� ����� j.
	for (int j = 1; j <= N; ++j) {
		// ��� ���� ���� i.
		for (int i = 1; i <= j; ++i) {
			// ���� �� �������� ��� ��������� (i, j).
			int sumOfElements = 0;
			for (int r = i; r <= j; ++r)
				sumOfElements += M[r];
			if (sumOfElements == K)
				minimumSizeSubarraySumK = min(minimumSizeSubarraySumK, j - i + 1);
		}
	}
	printf("%d\n", minimumSizeSubarraySumK == N + 1 ? 0 : minimumSizeSubarraySumK);
}