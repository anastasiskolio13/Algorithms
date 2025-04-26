#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#define MAXN 200000
using namespace std;

vector<vector<int>> Adj(MAXN);
vector<int> subordinates(MAXN);
int N;

int calculateSubordinates(int v) {
	for (int u : Adj[v])
		subordinates[v] += calculateSubordinates(u);
	return subordinates[v] + 1;
}

int main() {
	scanf("%d", &N);
	for (int i = 1; i < N; ++i) {
		int directBoss;
		scanf("%d", &directBoss);
		Adj[--directBoss].push_back(i);
	}
	subordinates[0] = calculateSubordinates(0) - 1;
	for (int v = 0; v < N; ++v)
		printf("%d ", subordinates[v]);
}