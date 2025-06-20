#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <climits>
#define MAXN 1000000
using namespace std;

vector<int> A(MAXN);
int N;

int main() {
	freopen("operators.in", "r", stdin);
	freopen("operators.out", "w", stdout);
	scanf("%d", &N);
	for (int i = 0; i < N; ++i)
		scanf("%d", &A[i]);
	// O(n^2).
	int minimumDifference = INT_MAX;
	pair<int, int> pairOfIndices;
	for (int i = 0; i < N - 1; ++i) {
		for (int j = i + 1; j < N; ++j) {
			int absoluteSum = abs(A[i] + A[j]);
			if (absoluteSum < minimumDifference) {
				minimumDifference = absoluteSum;
				// Πρώτος τρόπος.
				pairOfIndices.first = i;
				pairOfIndices.second = j;
				// Δεύτερος τρόπος.
				pairOfIndices = { i, j };
				// Τρίτος τρόπος.
				pairOfIndices = make_pair(i, j);
			}
		}
	}
	printf("%d %d\n", A[pairOfIndices.first], A[pairOfIndices.second]);
}