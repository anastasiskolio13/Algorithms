#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <set>
using namespace std;

vector<vector<int>> A(N, vector<int>(M));
int N;
int M;

int main() {
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < M; ++j)
			scanf("%d", &A[i][j]);
}