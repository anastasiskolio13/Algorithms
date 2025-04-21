#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector> 
#include <set>
#include <cmath>
#define MAXN 200000
using namespace std;

set<pair<int, int>> S;
vector<int> A(MAXN);
vector<int> treePosition(MAXN); // Θέση του i-οστού στοιχείου στο δέντρο.
vector<int> elementInPosition(MAXN); // Τιμή του στοιχείου της i-οστής θέσης στο δέντρο. 
vector<pair<int, long>> T(4 * MAXN);
int N;
int K;

int Kth(int lo, int hi, int v, int k) {
	if (lo == hi)
		return lo;
	int mid = (lo + hi) / 2;
	if (T[2 * v + 1].first >= k)
		return Kth(lo, mid, 2 * v + 1, k);
	else
		return Kth(mid + 1, hi, 2 * v + 2, k - T[2 * v + 1].first);
}

void Update(int lo, int hi, int v, int i, int x) {
	if (lo == hi) {
		T[v].first = x;
		T[v].second = x * elementInPosition[lo];
		return;
	}
	int mid = (lo + hi) / 2;
	if (i <= mid)
		Update(lo, mid, 2 * v + 1, i, x);
	else
		Update(mid + 1, hi, 2 * v + 2, i, x);
	T[v].first = T[2 * v + 1].first + T[2 * v + 2].first;
	T[v].first = T[2 * v + 1].second + T[2 * v + 2].second;
}

long Sum(int lo, int hi, int v, int qlo, int qhi) {
	if (qlo > qhi)
		return 0;
	if (qlo <= lo && hi <= qhi)
		return T[v].second;
	if (qlo > hi || qhi < lo)
		return 0;
	int mid = (lo + hi) / 2;
	long sumLeft = Sum(lo, mid, 2 * v + 1, qlo, qhi);
	long sumRight = Sum(mid + 1, hi, 2 * v + 2, qlo, qhi);
	return sumLeft + sumRight;
}


int main() {
	scanf("%d %d", &N, &K);
	for (int i = 0; i < N; ++i) {
		scanf("%d", &A[i]);
		// Προετοιμάσία συμπίεσης συντεταγμένων.
		S.insert({ A[i], i });
	}
	// Συμπίεση συντεταγμένων.
	int i = 0;
	for (auto element : S) {
		treePosition[element.second] = i;
		elementInPosition[i++] = element.first;
	}
	// Υπολογισμός της ζητούμενης ποσότητας για κάθε παράθυρο.
	for (int i = 0; i < N; ++i) {
		Update(0, N - 1, 0, treePosition[i], 1);
		if (i >= K - 1) {
			int positionOfMedian = Kth(0, N - 1, 0, ceil((double)K / 2));
			int median = elementInPosition[positionOfMedian];
			long termOne = (long)median * (2 * ceil((double)K / 2) - K - 1);
			long termTwo = Sum(0, N - 1, 0, 0, positionOfMedian - 1);
			long termthree = Sum(0, N - 1, 0, positionOfMedian + 1, N - 1);
			long currentWindowCost = termOne - termTwo + termthree;
			printf("%ld ", currentWindowCost);
			Update(0, N - 1, 0, treePosition[i - K + 1], 0);
		}
	}
}