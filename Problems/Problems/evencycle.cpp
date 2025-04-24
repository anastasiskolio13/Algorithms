#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<vector<int>> Adj;
vector<int> previsit;
vector<int> parent;
vector<int> evenCycle;
int T;
int N;
int M;
int ord;

void DepthFirstSearch(int v) {
	previsit[v] = ord++;
	for (int u : Adj[v]) {
		if (!previsit[u]) {
			parent[u] = v;
			DepthFirstSearch(u);
		}
		else {
			//  Συνθήκη άρτιου κύκλου.
			if (u != parent[v] && (previsit[v] - previsit[u]) % 2 == 1) {
				evenCycle[v] = u;
				return;
			}
		}
	}

}

void printCycle(int v) {
	printf("cycle ");
	vector<int> cycle;
	cycle.push_back(evenCycle[v] + 1);
	int u = evenCycle[v];
	while (v != u) {
		cycle.push_back(v + 1);
		v = parent[v];
	}
	cycle.push_back(v + 1);
	reverse(cycle.begin(), cycle.end());
	for (int v : cycle)
		printf("%d ", v);
	printf("\n");
}

int main() {
	//freopen("evencycle.in", "r", stdin);
	//freopen("evenecycle.out", "w", stdout);
	scanf("%d", &T); 
	while (T--) {
		scanf("%d %d", &N, &M);
		Adj.clear();
		Adj.resize(N);
		previsit.clear();
		previsit.resize(N);
		parent.clear();
		parent.resize(N);
		evenCycle.clear();
		evenCycle.resize(N, -1);
		ord = 1; // Σειρά επίσκεψης των κόμβων.
		bool thereExistsEvenCycle = false;
		for (int i = 0; i < M; ++i) {
			int v, u;
			scanf("%d %d", &v, &u);
			Adj[--v].push_back(--u);
			Adj[u].push_back(v);
		}
		for (int v = 0; v < N; ++v) {
			if (!previsit[v]) {
				parent[v] = v;
				DepthFirstSearch(v);
			}
		}

		for (int v = 0; v < N; ++v)
			cout << previsit[v] << " ";

		for (int v = 0; v < N; ++v) {
			if (evenCycle[v] != -1) {
				printCycle(v);
				thereExistsEvenCycle = true;
				break;
			}
		}
		//if (!thereExistsEvenCycle)
			//printf("none\n");
	}
}