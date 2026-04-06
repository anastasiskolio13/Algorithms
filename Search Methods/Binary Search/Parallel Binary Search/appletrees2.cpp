#include <iostream>
#include <vector>
#include <cmath>
#define MAXN 100000
#define MAXQ 100000
using namespace std;

struct Node {
    long long value;
    long long lazyValue;
    Node* left;
    Node* right;
};

struct event {
    int L;
    int R;
    int W;
};

vector<int> A(MAXN);
vector<event> E(MAXQ);
vector<int> ans(MAXN);
vector<pair<int, int>> R(MAXN);
int N;
int Q;
Node* root = new Node();

class LazySegmentTree {
public:
    LazySegmentTree(Node*& current = root, int lo = 0, int hi = N - 1) {
        if (current == nullptr)
            current = new Node();
        if (lo == hi) 
            return;
        int mid = (lo + hi) / 2;
        LazySegmentTree(current->left, lo, mid);
        LazySegmentTree(current->right, mid + 1, hi);
    }

    void Update(const int qlo, const int qhi, const int x, Node* current = root, int lo = 0, int hi = N - 1) {
        if (current->lazyValue != 0) {
            current->value += (current->lazyValue) * (hi - lo + 1);
            if (lo != hi) {
                current->left->lazyValue += current->lazyValue;
                current->right->lazyValue += current->lazyValue;
            }
            current->lazyValue = 0;
        }
        if (qlo > hi || qhi < lo)
            return;
        if (qlo <= lo && hi <= qhi) {
            current->value += (long long)x * (hi - lo + 1);
            if (lo != hi) {
                current->left->lazyValue += x;
                current->right->lazyValue += x;                
            }
            return;
        }
        int mid = (lo + hi) / 2;
        Update(qlo, qhi, x, current->left, lo, mid);
        Update(qlo, qhi, x, current->right, mid + 1, hi);
        current->value = (current->left != nullptr ? current->left->value : 0) + (current->right != nullptr ? current->right->value : 0); // Να τσεκάρω εδώ αν υπάρχουν τα παιδιά.
    }

    long long Query(const int i, Node* current = root, int lo = 0, int hi = N - 1) {
        if (current->lazyValue != 0) {
            current->value += (current->lazyValue) * (hi - lo + 1);
            if (lo != hi) {
                current->left->lazyValue += current->lazyValue;
                current->right->lazyValue += current->lazyValue;
            }
            current->lazyValue = 0;
        }
        if (lo == hi)
            return current->value;
        int mid = (lo + hi) / 2;
        if (i <= mid)
            return Query(i, current->left, lo, mid);
        else
            return Query(i, current->right, mid + 1, hi); 
    }
private:
    void deleteTree(Node* node) {
        if (node == nullptr) return;
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
};

int main() {
    cin >> N >> Q;
    for (int i = 0; i < N; ++i)
        cin >> A[i];
    for (int i = 0; i < Q; ++i) {
        cin >> E[i].L >> E[i].R >> E[i].W;
        --E[i].L;
        --E[i].R;
    }
    fill(R.begin(), R.begin() + N, make_pair(0, Q - 1));
    for (int i = 0; i < ceil(log2(Q)); ++i) {
        vector<vector<int>> TS(Q);
        for (int j = 0; j < N; ++j) 
            if (R[j].first != R[j].second)
                TS[(R[j].first + R[j].second) / 2].push_back(j);
        LazySegmentTree T;
        for (int j = 0; j < Q; ++j) {
            T.Update(E[j].L, E[j].R, E[j].W);
            for (int k : TS[j]) 
                if (T.Query(k) >= A[k])
                    R[k].second = j;
                else 
                    R[k].first = j + 1;
        }
        root = nullptr;
    }
    vector<vector<int>> TS(Q);
    for (int i = 0; i < N; ++i)
        TS[R[i].first].push_back(i);
    LazySegmentTree T;
    for (int i = 0; i < Q; ++i) {
        T.Update(E[i].L, E[i].R, E[i].W);
        for (int j : TS[i]) {
            if (T.Query(j) >= A[j])
                ans[j] = i + 1;
            else 
                ans[j] = -1;
        }
    }
    for (int i = 0; i < N; ++i)
        cout << ans[i] << " ";
}