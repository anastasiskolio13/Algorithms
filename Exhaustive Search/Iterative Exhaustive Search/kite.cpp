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
	// Για καθε αρχή i.
	for (int i = 1; i <= N; ++i) {
		// Για κάθε τέλος j.
		for (int j = i; j <= N; ++j) {
			// Πάρε το άθροισμα του υποπίνακα (i, j).
			int sumOfElements = 0;
			for (int r = i; r <= j; ++r)
				sumOfElements += M[r];
			if (sumOfElements == K)
				minimumSizeSubarraySumK = min(minimumSizeSubarraySumK, j - i + 1);
		}
	}
	// Σύντομο if: <συνθήκη> ? <εντολή για αληθή συνθήκη> : <εντολή για ψευδή συνθήκη>;
	printf("%d\n", minimumSizeSubarraySumK == N + 1 ? 0 : minimumSizeSubarraySumK);

	// O(n^3) επίσης.
	minimumSizeSubarraySumK = N + 1;
	// Για κάθε τέλος j.
	for (int j = 1; j <= N; ++j) {
		// Για καθε αρχή i.
		for (int i = 1; i <= j; ++i) {
			// Πάρε το άθροισμα του υποπίνακα (i, j).
			int sumOfElements = 0;
			for (int r = i; r <= j; ++r)
				sumOfElements += M[r];
			if (sumOfElements == K)
				minimumSizeSubarraySumK = min(minimumSizeSubarraySumK, j - i + 1);
		}
	}
	printf("%d\n", minimumSizeSubarraySumK == N + 1 ? 0 : minimumSizeSubarraySumK);
}