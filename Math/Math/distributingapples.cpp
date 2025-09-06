#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#define MAXN 1000000
#define MAXM 1000000
#define MOD 1000000007
using namespace std;

vector<int> F(MAXN + 1);
int N;
int M;

long long ModularInverse(long long b, long long mod) {
    long long x = 0, y = 1, u = 1, v = 0;
    long long a = mod, t;
    while (b != 0) {
        long long q = a / b;
        t = a - q * b; a = b; b = t;
        t = x - q * u; x = u; u = t;
        t = y - q * v; y = v; v = t;
    }
    if (x < 0) x += mod;
    return x;
}

void ComputeFactorial(int N) {
	for (int i = 1; i <= N; ++i)
		F[i] = ((long long)F[i - 1] * i) % MOD;
}

int NChooseK(int N, int K) {
	int termOne = ((F[N] - F[K]) % MOD + MOD) % MOD;
	int termTwo = ((long long)(F[K] % MOD) * (termOne % MOD)) % MOD;
    return (int)((long long)F[N] % MOD * ModularInverse(termTwo, MOD)) % MOD;
}

int main() {
	scanf("%d %d", &N, &M);
	ComputeFactorial(max(N, M));
	printf("%d\n", NChooseK(N + M - 1, M));
}