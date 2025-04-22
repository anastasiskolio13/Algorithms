#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <stack>
#include <numeric>
#define MAXN 100
using namespace std;

stack<int> S;
vector<vector<pair<int, double>>> Adj(MAXN);
vector<double> Q(MAXN);
int N;

void DepthFirstSearch() {
	Q[0] = 1;
	S.push(0);
	while (!S.empty()) {
		int v = S.top();
		S.pop();
		for (auto adjacent : Adj[v]) {
			int u = adjacent.first;
			double w = adjacent.second;
			if (!Q[u]) {
				Q[u] = Q[v] * w;
				S.push(u);
			}
		}
	}
}

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N - 1; ++i) {
		int A, B, P, Q;
		scanf("%d %d %d %d", &A, &B, &P, &Q);
		Adj[A].push_back({ B, (double)Q / P });
		Adj[B].push_back({ A, (double)P / Q });
	}
	DepthFirstSearch();
	double S = accumulate(Q.begin(), Q.begin() + N, (double)0);
	for (int i = 0; i < N; ++i)
		printf("%.2lf\n", Q[i] / S * 100);
}