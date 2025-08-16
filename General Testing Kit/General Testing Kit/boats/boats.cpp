#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <string>
using namespace std;

struct couple {
	int A;
	int B;
};

bool compareCouples(couple X, couple Y) {
	return X.A < Y.A || X.A == Y.A && X.B < Y.B;
}

set<pair<int, int>> S;
vector<couple> C;
vector<int> P;
vector<int> T;
vector<int> dp;
int N;

void Update(int lo, int hi, int v, int i, int x) {
	if (lo == hi) {
		T[v] = x;
		return;
	}
	int mid = (lo + hi) / 2;
	if (i <= mid)
		Update(lo, mid, 2 * v + 1, i, x);
	else
		Update(mid + 1, hi, 2 * v + 2, i, x);
	T[v] = max(T[2 * v + 1], T[2 * v + 2]);
}

int Query(int lo, int hi, int v, int qlo, int qhi) {
	if (qlo <= lo && hi <= qhi)
		return T[v];
	if (qlo > hi || qhi < lo)
		return 0;
	int mid = (lo + hi) / 2;
	int maxLeft = Query(lo, mid, 2 * v + 1, qlo, qhi);
	int maxRight = Query(mid + 1, hi, 2 * v + 2, qlo, qhi);
	return max(maxLeft, maxRight);
}

void SolveTestCase(int j) {
	S.clear();
	C.clear();
	P.clear();
	T.clear();
	dp.clear();
	string filenameOne = "input" + to_string(j) + ".txt";
	string filenameTwo = "output" + to_string(j) + ".txt";
	freopen(filenameOne.c_str(), "r", stdin);
	scanf("%d", &N);
	C.resize(N);
	P.resize(N);
	T.resize(4 * N);
	dp.resize(N);
	for (int i = 0; i < N; ++i) 
		scanf("%d %d", &C[i].A, &C[i].B);
	sort(C.begin(), C.begin() + N, compareCouples);
	for (int i = 0; i < N; ++i)
		S.insert({ C[i].B, i });
	int i = 0;
	for (auto [value, index] : S)
		P[index] = i++;
	for (int i = N - 1; i >= 0; --i) {
		dp[i] = Query(0, N - 1, 0, P[i] + 1, N - 1) + 1;
		Update(0, N - 1, 0, P[i], dp[i]);
	}
	int myAnswer = *max_element(dp.begin(), dp.begin() + N);
	freopen(filenameTwo.c_str(), "r", stdin);
	int correctAnswer;
	scanf("%d", &correctAnswer);
	if (myAnswer == correctAnswer)
		printf("AC\n");
	else
		printf("WA\n");
}

int main() {
	int numberOfTestCases = 12;
	for (int i = 1; i <= numberOfTestCases; ++i)
		SolveTestCase(i);
}