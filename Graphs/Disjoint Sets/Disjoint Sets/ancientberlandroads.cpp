#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <tuple>
#include <set>
#define MAXN 500000
#define MAXM 500000
#define MAXQ 500000
using namespace std;

multiset<long long, greater<long long>> J;
set<int> Z;
vector<tuple<char, int, int>> T(MAXQ);
vector<pair<int, int>> E(MAXM);
vector<vector<int>> R(MAXN);
vector<long long> C(MAXN);
vector<int> P(MAXN);
vector<int> S(MAXN);
vector<int> B(MAXN);
vector<int> I(MAXN);
vector<int> K(MAXQ);
int N;
int M;
int Q;

void DSU() {
	for (int a = 0; a < N; ++a) {
		P[a] = a;
		S[a] = 1;
		C[a] = R[a][R[a].size() - 1];
	}
}

int Find(int a) {
	if (P[a] == a)
		return a;
	return P[a] = Find(P[a]);
}

void Unite(int a, int b) {
	a = Find(a);
	b = Find(b);
	if (a == b)
		return;
	if (S[b] > S[a])
		swap(a, b);
	P[b] = a;
	S[a] += S[b];
	C[a] += C[b];
}

int main() {
	scanf("%d %d %d", &N, &M, &Q);
	for (int i = 0; i < N; ++i) {
		scanf("%d", &B[i]);
		R[i].push_back(B[i]);
	}
	for (int i = 0; i < M; ++i) {
		scanf("%d %d", &E[i].first, &E[i].second);
		--E[i].first;
		--E[i].second;
	}
	for (int i = 0; i < Q; ++i) {
		char a;
		int b, c = -1;
		scanf(" %c %d", &a, &b);
		--b;
		if (a == 'D') {
			Z.insert(b);
		}
		else {
			scanf("%d", &c);
			R[b].push_back(c);
		}
		T[i] = { a, b, c };
	}
	for (int i = 0; i < N; ++i)
		I[i] = R[i].size() - 1;
	for (int i = 0; i < N; ++i)
		J.insert(R[i][R[i].size() - 1]);
	DSU();
	for (int i = 0; i < M; ++i) {
		if (Z.find(i) == Z.end()) {
			auto iteratorOne = J.find(C[Find(E[i].first)]);
			auto iteratorTwo = J.find(C[Find(E[i].second)]);
			J.erase(iteratorOne);
			if (iteratorTwo != J.end())
				J.erase(iteratorTwo);
			Unite(E[i].first, E[i].second);
			J.insert(C[Find(E[i].first)]);
		}
	}
	for (int i = Q - 1; i >= 0; --i) {
		K[i] = *J.begin();
		if (get<0>(T[i]) == 'D') {
			auto iteratorOne = J.find(C[Find(E[get<1>(T[i])].first)]);
			auto iteratorTwo = J.find(C[Find(E[get<1>(T[i])].second)]);
			J.erase(iteratorOne);
			if (iteratorTwo != J.end())
				J.erase(iteratorTwo);
			Unite(E[get<1>(T[i])].first, E[get<1>(T[i])].second);
			J.insert(C[Find(E[get<1>(T[i])].first)]);
		}
		else {
			auto iteratorOne = J.find(C[Find(get<1>(T[i]))]);
			J.erase(iteratorOne);
			C[Find(get<1>(T[i]))] += get<2>(T[i]) - R[get<1>(T[i])][I[get<1>(T[i])]];
			J.insert(C[Find(get<1>(T[i]))]);
			I[get<1>(T[i])]--;
		}
	}
	for (int i = 0; i < Q; ++i)
		printf("%lld\n", K[i]);
}