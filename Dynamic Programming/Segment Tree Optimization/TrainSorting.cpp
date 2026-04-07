#include <iostream>
#include <vector>
#include <memory>
#define MAXN 200000
using namespace std;

vector<int> A(MAXN);
int N;

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; ++i)
        scanf("%d", &A[i]);
}