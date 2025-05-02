#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#define MAXN 1024
#define MAXM 65536
using namespace std;

vector<char> A(MAXN);
vector<char> B(MAXM);
int N;
int M;

int TheyMatch(int p) {
	int i = p;
	int j = 0;
	while (j < N) {
		if (B[i] == A[j]) {
			++i;
			++j;
		}
		else {
			return -1;
		}
	}
	return p;
}

int main() {
	scanf("%d\n", &N);
	for (int i = 0; i < N; ++i) 
		A[i] = getchar();
	scanf("%d\n", &M);
	for (int i = 0; i < M; ++i)
		B[i] = getchar();
	for (int i = 0; i <= M - N; ++i) {
		if (TheyMatch(i) != -1) {
			printf("%d\n", i + 1);
			return 0;
		}
	}
	printf("F\n");
}