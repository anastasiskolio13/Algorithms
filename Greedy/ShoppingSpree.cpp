#include <iostream>
#include <vector>
#define MAXN 200000
using namespace std;

vector<int> C(MAXN);
int N;
int K;

int main() {
    cin >> N >> K;
    for (int i = 0; i < N; ++i)
        cin >> C[i];
    int totalCost = 0;
    int i = 0;
    for (; i < K; ++i)
        totalCost += C[i];
    for (int j = N - 1 - K; j >= i; j -= 2)
        totalCost += C[j];
    cout << totalCost << endl;
}