#define _CRT_SECURE_NO_WARNINGS
#include <vector>
using namespace std;

int N;
vector<vector<int>> Adj(N);


Adj[v].push_back(u);

void explore(int v, vector<bool>& visited) {
	if (visited[v])
		return;
	visited[v] = true;
	for (int u : Adj[v])
		explore(u, visited);
}




void DFS_Explore() {
	for (int v = 0; v < N; ++v)
		visited[v] = false;
	for (int v = 0; v < N; ++v)
		explore(v);
}


5 4
1 3
2 4
1 5
5 3