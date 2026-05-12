#include <iostream>
#include <vector>
#define MAXN 1000

std::vector<int> A(MAXN);
std::vector<bool> hasComputed(MAXN + 1, false);
std::vector<int> opt(MAXN + 1);
int N;

int S(int i) {
    if (hasComputed[i])
        return opt[i];
    if (i == N) {
        hasComputed[N] = true;
        return opt[N] = 0;
    }
    if (i == N - 1) {
        hasComputed[N - 1] = true;
        return opt[N - 1] = std::max(A[N - 1], 0);
    }
    hasComputed[i] = true;
    int takeOne = std::max(A[i], 0) + S(i + 1);
    int takeTwo = A[i] * A[i + 1] + S(i + 2);
    return opt[i] = std::max(takeOne, takeTwo);
}

int main() {
    std::cin >> N;
    for (int i = 0; i < N; ++i)
        std::cin >> A[i];
    std::cout << S(0) << std::endl;
}
