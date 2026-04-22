#include <iostream>
#include <vector>
#include <stack>
#include <climits>
#define MAXN 1000000
#define MAXVAL 1000
using namespace std;

stack<int> S;
vector<int> A(MAXN);
vector<int> B(MAXN);
vector<int> R(MAXN);
vector<int> L(MAXN);
vector<long long> C(MAXN);
int N;
int X;
int Y;

struct Node {
    int value;
    Node* left;
    Node* right;
};

Node* root = new Node();

class SparseSegmentTree {
public:
    void Update(const int i, const int x, Node*& current = root, int lo = 0, int hi = N - 1) {
        if (current == nullptr)
            current = new Node();
        current->value += x;
        if (lo == hi) 
            return;
        int mid = (lo + hi) / 2;
        if (i <= mid)
            Update(i, x, current->left, lo, mid);
        else 
            Update(i, x, current->right, mid + 1, hi);
    }

    int Query(const int qlo, const int qhi, Node* current = root, int lo = 0, int hi = N - 1) {
        if (current == nullptr)
            return 0;
        if (qlo > hi || qhi < lo)
            return 0;
        if (qlo <= lo && hi <= qhi)
            return current->value;
        int mid = (lo + hi) / 2;
        return Query(qlo, qhi, current->left, lo, mid) + Query(qlo, qhi, current->right, mid + 1, hi);
    }
};


int main() {
    cin >> N;
    for (int i = 0; i < N; ++i) {
        cin >> A[i] >> B[i];
        L[i] = 0;
        R[i] = N - 1;
    }
    cin >> X >> Y;

    for (int j = N - 1; j >= 0; --j) {
        while (!S.empty() && A[j] >= A[S.top()]) {
            int i = S.top();
            S.pop();
            L[i] = j;
        }
        S.push(j);
    }
    
    SparseSegmentTree T;
    for (int i = N - 1; i >= 0; --i) {
        C[i] += T.Query(0, i);
        T.Update(L[i], B[i]);
    }

    S = stack<int>();
    for (int j = 0; j < N; ++j) {
        while (!S.empty() && A[j] >= A[S.top()]) {
            int i = S.top();
            S.pop();
            R[i] = j;
        }
        S.push(j);
    
    }
    root = new Node();
    for (int i = 0; i < N; ++i) {
        C[i] += T.Query(i, N - 1);
        T.Update(R[i], B[i]);
    }

    long long ans = LLONG_MIN;
    for (int i = 0; i < N; ++i)
        ans = max(ans, Y * (C[i] + B[i]) - A[i] * X);
    cout << ans << endl;
}