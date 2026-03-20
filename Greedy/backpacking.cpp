#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#define MAXN 200000
using namespace std;

stack<int> S;
vector<int> D(MAXN);
vector<int> C(MAXN);
vector<int> R(MAXN);
int N;
int K;

int main() {
	// Διάβασμα εισόδου.
	cin >> N >> K;
	for (int i = 0; i < N - 1; ++i)
		cin >> D[i];
	for (int i = 0; i < N; ++i)
		cin >> C[i];
	
	// Γεμίζω τον πίνακα R με την ψευδοτιμή N.
	fill(R.begin(), R.begin() + N, N);

	// Βρίσκω για κάθε σταθμό τον πρώτο σε σειρά σταθμό με μικρότερο ή ίσο κόστος καυσίμου.
	for (int j = 0; j < N; ++j) {
		while (!S.empty() && C[j] <= C[S.top()]) {
			 S.pop();
			int i = S.top();
			S.pop();
			R[i] = j;
		} 
	}
	
	// Εύρεση ελάχιστου συνολικού κόστους.
	long long minimumTotalCost = 0;
	long long totalDistance = 0;
	int currentFuel = 0;
	int i = 0;
	int j = 0;
	while (i < N) {
		// Μέχρι που μπορώ να φτάσω με γεμάτο ντεπόζιτο;
		while (j < N - 1 && totalDistance + D[j] <= K)
			totalDistance += D[j++];
		
		// Που θα σταματήσω;
		int nextStop;

		// Αν υπάρχει σταθμός από αυτούς που μπορώ να φτάσω με μικρότερο ή ίσο κόστος καυσίμου, πηγαίνω σε εκεί.
		if (R[i] <= j) {

		}
		// Σε αντίθετη περίπτωση, γεμίζω το ντεπόζιτο. 
		else {

			
		}

	}
	cout << minimumTotalCost << endl;
}