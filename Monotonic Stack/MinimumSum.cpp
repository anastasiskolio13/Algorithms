#include <iostream>
#include <stack>
#include <vector>
#include <numeric>
#define MAXN 200000
using namespace std;

stack<int> S;
vector<int> A(MAXN);
vector<int> R(MAXN);
vector<long long> dp(MAXN + 1);
int N;

int main() {
    // Reading Input.
    cin >> N;
    for (int i = 0; i < N; ++i)
        cin >> A[i];
    
    // Calculating R[i] for each i. 
    fill(R.begin(), R.begin() + N, N - 1);
    for (int j = 0; j < N; ++j) {
        while (!S.empty() && A[j] < A[S.top()]) {
            int i = S.top();
            S.pop();
            R[i] = j - 1;
        }
        S.push(j);
    } 

    // Calculating total cost and printing it.
    dp[N] = 0;
    for (int i = N - 1; i >= 0; --i) {
        dp[i] = (long long)A[i] * (R[i] - i + 1) + dp[R[i] + 1];
    }
    cout << accumulate(dp.begin(), dp.begin() + N, 0LL);
}