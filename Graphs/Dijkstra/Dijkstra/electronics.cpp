#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <set>
#include <tuple>
#define MAXL 1000
#define MAXW 1000
using namespace std;

set<tuple<long long, int, int, int>> Q;
vector<vector<int>> A(MAXL, vector<int>(MAXW));
int L;
int W;
int Si;
int Sj;
int Ti;
int Tj;

void Dijksta() {
	while (!Q.empty()) {
		auto [distance, i, j, direction] = *Q.begin();
		Q.erase(Q.begin());
		// Μετακίνηση κάτω.
		if (i + 1 < L && A[i][j] != 4000) {
			// Αρχίζω καινούργιο σύρμα.
			if (!direction) {
				if (distance + )
			}
			else {

			}
		}
	}
}

int main() {
	Si = Sj = -1;
	scanf("%d %d", &L, &W);
	for (int i = 0; i < L; ++i) {
		for (int j = 0; j < W; ++j) {
			scanf("%d", &A[i][j]);
			if (A[i][j] == 0) {
				if (Si == -1 && Sj == -1) { Si = i; Sj = j; }
				else { Ti = i; Tj = j; }
			}
		}
	}
}