#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#define MAXN 200000
using namespace std;

stack<int> S;
stack<int> Q;
vector<int> A(MAXN);
vector<int> L(MAXN);
vector<int> R(MAXN);
vector<pair<int, int>> B(MAXN);
vector<int> SM(MAXN + 1);
vector<vector<int>> C(MAXN);
int N;

int main() {
    cin >> N;
    for (int i = 0; i < N; ++i)
        cin >> A[i];
    fill(R.begin(), R.begin() + N, N - 1);
    for (int j = 0; j < N; ++j) {
        while (!S.empty() && A[j] < A[S.top()]) {
            int i = S.top();
            S.pop();
            R[i] = j - 1;
        }
        S.push(j);
    }
    fill(L.begin(), L.begin() + N, 0);
    for (int j = N - 1; j >= 0; --j) {
        while (!Q.empty() && A[j] < A[Q.top()]) {
            int i = Q.top();
            Q.pop();
            L[i] = j + 1;
        }
        Q.push(j);
    }
    
    // O(N log N).
    // for (int i = 0; i < N; ++i)
    //     B[i] = make_pair(R[i] - L[i] + 1, A[i]);
    // sort(B.begin(), B.begin() + N);
    // for (int i = N - 1; i >= 0; --i)
    //     SM[i] = max(SM[i + 1], B[i].second);    
    // for (int i = 0; i < N; ++i) 
    //         cout << SM[lower_bound(B.begin(), B.begin() + N, make_pair(i + 1, 0)) - B.begin()] << " ";

    // O(N).
    for (int i = 0; i < N; ++i) 
        C[R[i] - L[i]].push_back(A[i]);
    
    for (int i = 0, j = 0; i < N; ++i) 
        for (int x : C[i]) 
            B[j++] = make_pair(i + 1, x);
    
    for (int i = N - 1; i >= 0; --i)
        SM[i] = max(SM[i + 1], B[i].second);   
    
    for (int i = 0, j = 0; i < N; ++i) {
        while (B[j].first < i + 1)
            ++j;
        cout << SM[j] << " ";
    }
}
