#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#define MAXN 100000
#define MAXM 100000
#define MAXR 100000
using namespace std;


struct store {
	int Q;
	int P;
};

bool compareStores(store A, store B) {
	return A.P > B.P;
}

vector<int> C(MAXN + 1);
vector<store> S(MAXM + 2);
vector<int> T(MAXR + 2);
vector<long long> PSQ(MAXM + 2);
vector<long long> PSP(MAXM + 2);
int N;
int M;
int R;

int FindNextStore(int i, int l, int gallons) {
	int lo = l;
	int hi = M + 1;
	while (lo < hi) {
		int mid = (lo + hi) / 2;
		if (PSQ[mid] - PSQ[l] - gallons >= C[i])
			hi = mid;
		else
			lo = mid + 1;
	}
	return lo;
}

int main() {
	scanf("%d %d %d", &N, &M, &R);
	for (int i = 1; i <= N; +i)
		scanf("%d", &C[i]);
	for (int i = 1; i <= M; ++i) 
		scanf("%d %d", &S[i].Q, &S[i].P);
	S[M + 1].P = T[R + 1] = -2e9;
	S[M + 1].Q = 1e16;
	for (int i = 1; i <= R; ++i)
		scanf("%d", &T[i]);
	sort(C.begin() + 1, C.begin() + N + 1, greater<int>());
	sort(S.begin() + 1, S.begin() + M + 2, compareStores);
	sort(T.begin() + 1, T.begin() + R + 2, greater<int>());
	for (int i = 1; i <= M; ++i) {
		PSQ[i] = PSQ[i - 1] + S[i].Q;
		PSP[i] = PSP[i - 1] + S[i].P;
	}
	PSQ[M + 1] = PSQ[M] + S[M + 1].Q;
	PSP[M + 1] = PSP[M] + S[M + 1].P;
	long long maximumProfit = 0;
	int gallons = PSQ[1]; // # gallons of the last store I sold milk that were not fulfilled.
	int i = 1; 
	int j = N;
	int l = 1; // For stores.
	int k = 1; // For farmers.
	while (i <= j) {
		// Αν νοικιάσω την αγελάδα j παίρνω κέρδος T[j].
		int rentCowJ = T[j];
		// Βρίσκω μέχρι ποιο μαγαζί μπορεί να δώσει γάλα η i-οστή αγελάδα.
		int l_next = FindNextStore(i, l, gallons);
		// 
		long long sellTheMilkOfCowI;
		// Μένω στο ίδιο μαγαζί.
		if (l_next == l) {
			gallons -= C[i];
			sellTheMilkOfCowI = (long long)S[l].P * C[i];
		}
		// Έχω προχωρήσει σε επόμενο μαγαζί (l_next > l_i).
		else {
			gallons = PSQ[l_next] - PSQ[l] - gallons - C[i];
			sellTheMilkOfCowI = ;
		}
		l = l_next;
		if (sellTheMilkOfCowI > rentCowJ) {
			maximumProfit += sellTheMilkOfCowI;
			++i;
		}
		else {
			maximumProfit += rentCowJ;
			--j;
		}

	}
	printf("%lld\n", maximumProfit);
}