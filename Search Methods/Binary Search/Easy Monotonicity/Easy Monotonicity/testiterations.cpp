#define _CRT_SECURE_NO_WARNINGS
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#define MAXN 1000
using namespace std;

int N;
int numberOfTests;
vector<int> A(MAXN + 1);

int BinarySearch(int lo, int hi, int x) {
	int iterationCount = 0;
	while (lo < hi) {
		++iterationCount;
		int mid = (lo + hi) / 2;
		if (x <= A[mid])
			hi = mid;
		else
			lo = mid + 1;
	}
	return iterationCount;
}

/*int BinarySearch(int lo, int hi, int x) {
	int iterationCount = 0;
	while (lo < hi) {
		++iterationCount;
		int mid = (lo + hi + 1) / 2;
		if (x < A[mid])
			hi = mid - 1;
		else
			lo = mid;
	}
	return iterationCount;
}*/

int main() {
	srand(time(nullptr));
	N = 1000;
	numberOfTests = 1000;
	for (int i = 1; i <= N; ++i)
		A[i] = 1 + rand() % (MAXN - 1) + 1;
	for (int i = 0; i < numberOfTests; ++i) {
		int iterations = BinarySearch(1, N, 1 + rand() % (MAXN - 1) + 1);
		if (iterations != floor((double)log2(N)) && iterations != ceil((double)log2(N))) {
			printf("BinarySearch doesn't always perform either floor((double)log2(N)) or ceil((double)log2(N)) iterations.");
			return 0;
		}
	}
	printf("BinarySearch performs either floor((double)log2(N)) or ceil((double)log2(N)) iterations.");
}

