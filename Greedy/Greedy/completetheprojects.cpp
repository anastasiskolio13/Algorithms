#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#define MAXN 100
using namespace std;

struct project {
	int A;
	int B;
};

bool compareProjects(project X, project Y) {
	if (X.B >= 0)
		return Y.B >= 0 ? X.A < Y.A : true;
	if (Y.B >= 0)
		return X.B >= 0 ? X.A < Y.A : false;
	if ()

}

vector<project> P(MAXN);
int N;
int R;

int main() {
	scanf("%d %d", &N, &R);
	for (int i = 0; i < N; ++i)
		scanf("%d %d", &P[i].A, &P[i].B);
}