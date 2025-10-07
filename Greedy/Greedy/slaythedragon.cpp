#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#define MAXN 200000
using namespace std;

vector<long long> A(MAXN);
int N;
int M;

int main() {
	scanf("%d", &N);
	long long sumOfStrengths = 0;
	for (int i = 0; i < N; ++i) {
		scanf("%lld", &A[i]);
		sumOfStrengths += A[i];
	}
	sort(A.begin(), A.begin() + N);
	scanf("%d", &M);
	while (M--) {
		long long X, Y;
		scanf("%lld %lld", &X, &Y);
		auto it = lower_bound(A.begin(), A.begin() + N, X);
		long long minimumNumberOfCoins;
		if (it == A.begin()) 
			minimumNumberOfCoins = max(X - A[0], 0LL) + max(Y - sumOfStrengths + A[0], 0LL);
		else if (it == A.end()) 
			minimumNumberOfCoins = max(X - A[N - 1], 0LL) + max(Y - sumOfStrengths + A[N - 1], 0LL);
		else {
			auto tmpit = --it;
			minimumNumberOfCoins = min(max(X - *it, 0LL) + max(Y - sumOfStrengths + *it, 0LL),
									   max(X - *tmpit, 0LL) + max(Y - sumOfStrengths + *it, 0LL));
		}
		printf("%lld\n", minimumNumberOfCoins);
	}
}