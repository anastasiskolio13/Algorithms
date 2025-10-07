#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#define MAXN 1000
using namespace std;

vector<int> A(MAXN + 1);
vector<int> PS(MAXN + 1);
int N;

int sum(int i, int j) { // 1 <= i <= j <= N.
	return PS[j] - PS[i - 1];
}

int main() {
	scanf("%d", &N);
	for (int i = 1; i <= N; ++i)
		scanf("%d", &A[i]);
	PS[0] = 0; // Δεν χρειάζεται, γιατί ο PS είναι global vector.
	for (int i = 1; i <= N; ++i) 
		PS[i] = PS[i - 1] + A[i];

	// A[i] <= 10^9.
	// -2 * 10^9 <= int <= 2 * 10^9.
}