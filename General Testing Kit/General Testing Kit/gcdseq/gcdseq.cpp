#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#define MAXN 500000
using namespace std;

vector<int> SGCD(MAXN);
vector<int> PGCD(MAXN);

int Gcdseq(vector<int>& A, int lo, int hi) {
	if (lo == hi)
		return 1;
	int j = (lo + hi) / 2;
	int s_l = Gcdseq(A, lo, j);
	int s_r = Gcdseq(A, j + 1, hi);
	SGCD[j] = A[j];
	for (int i = j - 1; i >= lo; --i)
		SGCD[i] = __gcd(SGCD[i + 1], A[i]);
	PGCD[j + 1] = A[j + 1];
	for (int i = j + 2; i <= hi; ++i)
		PGCD[i] = __gcd(PGCD[i - 1], A[i]);
	int s_lr = 0;
	int k = hi;
	for (int i = j; i >= lo; --i) {
		while (k >= j + 1 && __gcd(SGCD[i], PGCD[k]) == 1)
			--k;
		if (k >= j + 1)
			s_lr = max(s_lr, k - i + 1);
	}
	return max({ s_l, s_lr, s_r });
}

void SolveTestCase(int j) {
	string filenameOne = "gcdseq.in" + to_string(j);
	freopen(filenameOne.c_str(), "r", stdin);
	int N;
	scanf("%d", &N);
	vector<int> A(N);
	for (int i = 0; i < N; ++i)
		scanf("%d", &A[i]);
	int myAnswer = Gcdseq(A, 0, N - 1);
	string filenameTwo = "gcdseq.out" + to_string(j);
	freopen(filenameTwo.c_str(), "r", stdin);
	int correctAnswer;
	scanf("%d", &correctAnswer);
	printf(myAnswer == correctAnswer ? "AC\n" : "WA\n");
}

int main() {
	int numberOfTestCases = 31;
	for (int i = 1; i <= numberOfTestCases; ++i)
		SolveTestCase(i);
}