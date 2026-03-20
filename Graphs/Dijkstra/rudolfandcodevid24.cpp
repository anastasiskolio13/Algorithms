#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <string>
#include <set>
#define MAXN 10
#define MAXM 1000
#define INF 2e9
using namespace std;

struct medicine {
	int a;
	int b;
	int c;
};

set<pair<int, int>> Q;
vector<medicine> Medicines;
int T;
int N;
int M;
string S;

int Dijkstra(int startingNode) {
	vector<int> D(1 << N, INF);
	D[startingNode] = 0;
	Q.insert({ 0, startingNode });
	while (!Q.empty()) {
		auto [currentDays, currentNode] = *Q.begin();
		Q.erase(Q.begin());
		if (currentDays > D[currentNode])
			continue;
		for (int i = 0; i < M; ++i) {
			auto [a, b, c] = Medicines[i];
			int nextNode = (currentNode & ~b) | c;
			if (D[currentNode] + a < D[nextNode]) {
				D[nextNode] = D[currentNode] + a;
				Q.insert({ D[nextNode], nextNode });
			}
		}
	}
	return D[0];
}

int main() {
	cin >> T;
	while (T--) {
		cin >> N >> M;
		cin >> S;
		int initialState = stoi(S, nullptr, 2);
		Medicines.clear();
		Medicines.resize(M);
		for (int i = 0; i < M; ++i) {
			cin >> Medicines[i].a;
			cin >> S;
			Medicines[i].b = stoi(S, nullptr, 2);
			cin >> S;
			Medicines[i].c = stoi(S, nullptr, 2);
		}
		int res = Dijkstra(initialState);
		cout << (res != 2e9 ? res : -1) << endl;
	}
}