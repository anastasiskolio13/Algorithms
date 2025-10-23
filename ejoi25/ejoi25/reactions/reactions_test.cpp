#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <set>
using namespace std;

vector<int> A;
vector<long long> B;
vector<long long> PS;
vector<long long> T;
vector<int> I;
int N;

void Update(int lo, int hi, int v, int i) {
	if (lo == hi) {
		T[v] = 1;
		return;
	}
	int mid = (lo + hi) / 2;
	if (I[i] <= mid)
		Update(lo, mid, 2 * v + 1, i);
	else
		Update(mid + 1, hi, 2 * v + 2, i);
	T[v] = T[2 * v + 1] + T[2 * v + 2];
}

int Query(int lo, int hi, int v, int qlo, int qhi) {
	if (qlo <= lo && hi <= qhi)
		return T[v];
	if (qlo > hi || qhi < lo)
		return 0;
	int mid = (lo + hi) / 2;
	int sumLeft = Query(lo, mid, 2 * v + 1, qlo, qhi);
	int sumRight = Query(mid + 1, hi, 2 * v + 2, qlo, qhi);
	return sumLeft + sumRight;
}

void SolveTestcase(int j) {
	string filenameOne = j < 10 ? "reactions." + '0' + to_string(j) + ".in" : "reactions." + to_string(j) + ".in";
	freopen(filenameOne.c_str(), "r", stdin);
	set<pair<long long, int>> S;
	A.clear();
	B.clear();
	PS.clear();
	T.clear();
	I.clear();
	scanf("%d", &N);
	A.resize(N + 1);
	B.resize(N + 1);
	PS.resize(N + 1, 0);
	T.resize(4 * N, 0);
	I.resize(N + 1);
	for (int i = 1; i <= N; ++i) {
		scanf("%d", &A[i]);
		PS[i] = PS[i - 1] + A[i];
	}
	for (int i = 1; i <= N; ++i) {
		scanf("%lld", &B[i]);
		S.insert({ PS[i] - B[i], i });
	}
	int i = 0;
	for (auto [_, index] : S)
		I[index] = i++;
	int ans = 0;
	for (int i = N; i >= 1; --i) {
		Update(0, N - 1, 0, i);
		auto iteratorOne = S.lower_bound({ PS[i - 1], 1e9 });
		if (iteratorOne != S.end())
			ans = max(ans, Query(0, N - 1, 0, I[iteratorOne->second], N - 1));
	}
	string filenameTwo = j < 10 ? "reactions." + '0' + to_string(j) + ".sol" : "reactions." + to_string(j) + ".sol";
	freopen(filenameTwo.c_str(), "r", stdin);
	int correctAns;
	scanf("%d", &correctAns);
	if (ans == correctAns)
		printf("AC\n");
	else
		printf("WA\n");
}

int main() {
	int numberOfTestCases = 99;
	for (int i = 1; i <= numberOfTestCases; ++i)
		SolveTestcase(i);
}