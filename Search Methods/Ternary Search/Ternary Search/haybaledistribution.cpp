#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#define MAXN 200000
#define MAXY 1000000
using namespace std;

vector<int> X(MAXN + 1);
vector<long long> PS(MAXN + 1);
vector<int> P(MAXY + 1);
int N;
int Q;
int A;
int B;

long long C(int Y) {
	return A * (P[Y] * (long long) Y - PS[P[Y]]) + B * (PS[N] - PS[P[Y]] - (N - P[Y]) * (long long) Y);
}

int main() {
	scanf("%d", &N);
	for (int i = 1; i <= N; ++i)
		scanf("%d", &X[i]);
	// Ταξινόμηση΄.
	sort(X.begin() + 1, X.begin() + N + 1);
	// Υπολογισμός μερικών αθροισμάτων.
	for (int i = 1; i <= N; ++i)
		PS[i] = PS[i - 1] + X[i];
	// Υπολογισμός για κάθε Y το μεγαλύτερο i : X[i] <= Y.
	int i = 1;
	for (int Y = X[1]; Y <= X[N]; ++Y) {
		while (i <= N && X[i] <= Y)
			++i;
		P[Y] = i - 1;
	}
	// Απάντηση ερωτημάτων.
	scanf("%d", &Q);
	while (Q--) {
		scanf("%d %d", &A, &B);
		int lo = X[1];
		int hi = X[N];
		while (lo < hi) {
			int mid = (lo + hi) / 2;
			if (C(mid) > C(mid + 1))
				lo = mid + 1;
			else
				hi = mid;
		}
		printf("%lld\n", C(lo));
	}
}