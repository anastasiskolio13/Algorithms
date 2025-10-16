#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#define MAXN 200000
using namespace std;

struct flower {
	int X;
	int T;
};

bool CompareFlowers(flower A, flower B) {
	return A.X < B.X;
}

vector<flower> F(MAXN);
int N;
int M;

void Update(int lo, int hi, int v, int i) {

}



int main() {
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; ++i)
		scanf("%d %d", &F[i].X, &F[i].T);
	sort(F.begin(), F.begin() + N, CompareFlowers);

}