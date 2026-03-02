#include <bits/stdc++.h>
#define MAXN 200000
using namespace std;

priority_queue<long long, vector<long long>, greater<long long>> Q;
vector<int> A(MAXN);
int N;

int main() {
    cin >> N;
    bool evenExists = false;
    bool oddExists = false;
    for (int i = 0; i < N; ++i) {
        cin >> A[i];
        A[i] % 2 == 0 ? evenExists = true : oddExists = true;
        Q.push(A[i]);
    }
    if (evenExists && oddExists) {
        cout << "-1";
        return 0;
    }
    long long minimumTotalCost = 0;
    for (int i = 0; i < N - 1; ++i) {
        // Pop the smallest elements.
        long long minimumElement = Q.top();
        Q.pop();
        // Pop the second smallest element.
        long long secondMinimumElement = Q.top();
        Q.pop();
        // Merge the two smallest elements and push the merged element back to the priority queue.
        long long mergedElement = minimumElement + secondMinimumElement + 8 * evenExists + 7 * oddExists;
        Q.push(mergedElement);
        // Increase the total cost by the merged element.
        minimumTotalCost += mergedElement;
    }
    cout << minimumTotalCost << endl;
}