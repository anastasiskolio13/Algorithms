#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
#define MAXN 1000
using namespace std;

vector<int> A(MAXN + 1);
int N;

int main() {
	scanf("%d", &N);
	for (int i = 1; i <= N; ++i)
		scanf("%d", &A[i]);
	int maximumSum = INT_MIN;
	//  ��� ���� ����,
	for (int i = 1; i <= N; ++i) {
		// �������� ���� �����.
		for (int j = i; j <= N; ++j) {
			// ���� �� ��������.
			int currentSum = 0;
			for (int k = i; k <= j; ++k)
				currentSum += A[k];
			maximumSum = max(maximumSum, currentSum);
		}
	}
	printf("%d\n", maximumSum);
	maximumSum = INT_MIN;
	// ��� ���� �����, 
	for (int j = 1; j <= N; ++j) {
		// �������� ���� ����.
		for (int i = 1; i <= j; ++i) {
			// ���� �� ��������.
			int currentSum = 0;
			for (int k = i; k <= j; ++k)
				currentSum += A[k];
			maximumSum = max(maximumSum, currentSum);
		}
	}
	printf("%d\n", maximumSum);
}