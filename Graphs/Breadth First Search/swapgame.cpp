#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#define INF 1e6
#include <queue>
using namespace std;

vector<int> D(362881);
queue<int> Q;

void Swap(int currentState, int i, int j) {
	int newState = currentState - ;
	if (D[newState] == INF) {
		D[newState] = D[currentState] + 1;
		Q.push(newState);
	}
}

int main() {
	int initialState = 0;
	for (int i = 8; i >= 0; --i) {
		int x;
		scanf("%d", &x);
		initialState += x * pow(10, i);
	}
	for (int state = 1; state <= 362880; ++state)
		D[state] = INF;
	D[initialState] = 0;
	Q.push(initialState);
	while (!Q.empty()) {
		int currentState = Q.front();
		Q.pop();
		Swap(currentState, 0, 1);
		Swap(currentState, 0, 3);
		Swap(currentState, 1, 2);
		Swap(currentState, 1, 4);
		Swap(currentState, 2, 5);
		Swap(currentState, 3, 4);
		Swap(currentState, 3, 6);
		Swap(currentState, 4, 5);
		Swap(currentState, 4, 7);
		Swap(currentState, 5, 8);
		Swap(currentState, 6, 7);
		Swap(currentState, 7, 8);
	}
	printf("%d\n", D[123456789]);
}