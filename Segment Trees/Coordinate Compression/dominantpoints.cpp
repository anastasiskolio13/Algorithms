#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <set>
#include <cfloat>
#define MAXN 98411
#define INF DBL_MAX
using namespace std;

struct point {
	string ID;
	double F;
	double C;
};

set<string> D;
set<pair<double, int>> S;
vector<point> P(MAXN);
vector<int> I(MAXN);
vector<double> T(4 * MAXN);
int N;

void Update(int lo, int hi, int v, int i) {
	if (lo == hi) {
		T[v] = P[i].C;
		return;
	}
	int mid = (lo + hi) / 2;
	if (I[i] <= mid)
		Update(lo, mid, 2 * v + 1, i);
	else
		Update(mid + 1, hi, 2 * v + 2, i);
	T[v] = max(T[2 * v + 1], T[2 * v + 2]);
}

double Query(int lo, int hi, int v, int qlo, int qhi) {
	if (qlo <= lo && hi <= qhi)
		return T[v];
	if (qlo > hi || qhi < lo)
		return -INF;
	int mid = (lo + hi) / 2;
	double maxLeft = Query(lo, mid, 2 * v + 1, qlo, qhi);
	double maxRight = Query(mid + 1, hi, 2 * v + 2, qlo, qhi);
	return max(maxLeft, maxRight);
}

int main() {
	cin >> N;
	for (int i = 0; i < N; ++i) {
		cin >> P[i].ID >> P[i].F >> P[i].C;
		S.insert({ P[i].F, i });
	}
	int i = 0;
	for (auto [value, index] : S) {
		I[index] = i++;
		Update(0, N - 1, 0, index);
	}
	for (int i = 0; i < N; ++i) {
		auto it = S.upper_bound({ P[i].F, N });
		if (it == S.end() || it != S.end() && P[i].C >= Query(0, N - 1, 0, I[it->second], N - 1))
			D.insert(P[i].ID);
	}
	for (string ID : D)
		cout << ID << " ";
	cout << endl;
}