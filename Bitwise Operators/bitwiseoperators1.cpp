#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

unsigned int X;
int Q;
int T;
int K;

int main() {
	scanf("%d", &Q);
	while (Q--) {
		scanf("%d %d", &T, &K);
		switch (T) {
		case 1: X |= (1 << K); break;
		case 2: X &= ~(1 << K); break;
		default: X ^= (1 << K);
		}
		printf("%u\n", X);
	}
}