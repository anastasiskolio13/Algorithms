#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
using namespace std;

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		vector<int> A;
		int N;
		scanf("%d", &N);
		long long numberOfPairs = 0;
		for (int i = 1; i <= N; ++i) {
			int Ai; 
			scanf("%d", &Ai);
			if (Ai < i) {
				numberOfPairs += lower_bound(A.begin(), A.end(), Ai) - A.begin();
				A.push_back(i); // A[1] < A[2] < ... < A[k].
			}
		}
		printf("%lld\n", numberOfPairs);
	}
}