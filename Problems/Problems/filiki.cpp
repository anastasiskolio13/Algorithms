#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <stack>
#define MAXN 200000
using namespace std;

stack<pair<int, int>> S;
vector<vector<int>> Adj(MAXN);
vector<int> T(MAXN);
int N;
int K;

int PeopleNeededForAllToGetTheMessageInTimeAtMost(int x) {
	int peopleNeeded = 1;
	S.push({ 0, 0 });
	while (!S.empty()) {
		int v = S.top().first;
		int currentTime = S.top().second;
		S.pop();
		for (int u : Adj[v]) {
			if (currentTime + T[u] > x) {
				++peopleNeeded;
				S.push({ u, });
			}
			else {
				S.push({ u, });
			}
		}

	}
	return peopleNeeded;
}

int main() {
	scanf("%d %d", &N, &K);
	for (int u = 1; u < N; ++u) {
		int v;
		scanf("%d %d", &v, &T[u]);
		Adj[--v].push_back(u);
	}
	int lo = 0;
	int hi = 20000000;
	while (lo < hi) {
		int mid = (lo + hi) / 2;
		if (PeopleNeededForAllToGetTheMessageInTimeAtMost(mid) <= K)
			hi = mid;
		else
			lo = mid + 1;
	}
	printf("%d\n", lo);
}