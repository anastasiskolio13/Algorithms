#include <iostream>
#include <vector>
#include <memory>
#define MAXN 200000
using namespace std;

vector<int> V(MAXN);
vector<int> S(MAXN);
vector<int> E(MAXN);
vector<vector<int>> Adj(MAXN);
int N;
int Q;

struct Node {
    long long value;
    unique_ptr<Node> left;
    unique_ptr<Node> right; 
};

unique_ptr<Node> root = make_unique<Node>();

class SumSegmentTree {
public:
    SumSegmentTree() {
        for (int i = 0; i < N; ++i)
            Set(S[i], V[i]);
    }

    void Set(const int i, const int x, unique_ptr<Node>& current = root, int lo = 0, int hi = N - 1) {
        if (current == nullptr)
            current = make_unique<Node>();
        if (lo == hi) {
            current->value = x;
            return;
        }
        int mid = (lo + hi) / 2;
        if (i <= mid)
            Set(i, x, current->left, lo, mid);
        else 
            Set(i, x, current->right, mid + 1, hi);
        current->value = (current->left ? current->left->value : 0) + (current->right ? current->right->value : 0); 
    }    

    long long Sum(const int qlo, const int qhi, unique_ptr<Node>& current = root, int lo = 0, int hi = N - 1) {
        if (current == nullptr)
            return 0;
        if (qlo > hi || qhi < lo)
            return 0;
        if (qlo <= lo && hi <= qhi)
            return current->value;
        int mid = (lo + hi) / 2;
        long long sumLeft = Sum(qlo, qhi, current->left, lo, mid);
        long long sumRight = Sum(qlo, qhi, current->right, mid + 1, hi);
        return sumLeft + sumRight;
    }
};

void depthFirstSearch(int v, int p, int& timer) {
    S[v] = ++timer;
    for (int u : Adj[v])
        if (u != p)
            depthFirstSearch(u, v, timer);
    E[v] = timer;
}

int main() {
    cin >> N >> Q;
    for (int i = 0; i < N; ++i)
        cin >> V[i];
    for (int i = 0; i < N - 1; ++i) {
        int v, u;
        cin >> v >> u;
        Adj[--v].push_back(--u);
        Adj[u].push_back(v);
    }
    int timer = -1;
    depthFirstSearch(0, -1, timer);
    SumSegmentTree T;
    while (Q--) {
        int a, b, c;
        cin >> a >> b;
        --b;
        if (a == 1) {
            cin >> c;
            T.Set(S[b], c);
        }
        else {
            cout << T.Sum(S[b], E[b]) << endl;
        }
    }
}