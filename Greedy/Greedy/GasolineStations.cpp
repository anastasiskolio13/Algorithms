#include <iostream>
#include <vector>
#define MAXN 1000000

std::vector<int> P(MAXN);
std::vector<int> G(MAXN);
int N;

int main() {
    std::cin >> N;
    for (int i = 0; i < N; ++i)
        std::cin >> P[i];
    for (int i = 0; i < N; ++i)
        std::cin >> G[i];
    long minimumCost = 0;
    int i = 0;
    while (i < N) {
        int j = i;
        while (j < N && P[j] >= P[i])
            minimumCost += (long)P[i] * G[j++];
        i = j;
    }
    std::cout << minimumCost << std::endl;
}
