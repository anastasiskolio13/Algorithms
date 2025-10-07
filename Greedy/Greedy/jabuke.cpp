#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#define MAXJ 20
using namespace std;

vector<int> A(MAXJ);
int N;
int M;
int J;

int main() {
	scanf("%d %d %d", &N, &M, &J);
	for (int i = 0; i < J; ++i)
		scanf("%d", &A[i]);
	int currentPosition = 1;
	int totalCost = 0;
	for (int i = 0; i < J; ++i) {
		int movingCost;
		if (currentPosition < A[i]) {
			movingCost = max(0, A[i] - M - currentPosition + 1);
			currentPosition += movingCost;
		}
		else {
			movingCost = currentPosition - A[i];
			currentPosition -= movingCost;
		}
		totalCost += movingCost;
	}
	printf("%d\n", totalCost);
}