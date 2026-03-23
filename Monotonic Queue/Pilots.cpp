#include <iostream>
#include <vector>
#include <deque>
#define MAXN 3000000
using namespace std;

vector<int> A(MAXN);
deque<int> minQ;
deque<int> maxQ;
int N;
int K;

void pushToQueues(int i) {
    while (!minQ.empty() && A[i] <= A[minQ.back()])
        minQ.pop_back();
    minQ.push_back(i);

    while (!maxQ.empty() && A[i] >= A[maxQ.back()])
        maxQ.pop_back();
    maxQ.push_back(i);
}

void popFromQueues(int i) {
    if (i == minQ.front())
        minQ.pop_front();

    if (i == maxQ.front())
        maxQ.pop_front();
}

int main() {
    // Input.
    scanf("%d %d", &K, &N);
    for (int i = 0; i < N; ++i)
        scanf("%d", &A[i]);
    
    // Solution.
    int maximumLength = 0;
    int i = 0;
    for (int j = 0; j < N; ++j) {
        pushToQueues(j);
        while (A[maxQ.front()] - A[minQ.front()] > K)
            popFromQueues(i++);
        maximumLength = max(maximumLength, j - i + 1);
    }

    // Results.
    printf("%d\n", maximumLength);
}