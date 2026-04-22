#include <iostream>
#include <vector>
#include <cstdio>
#define MAXN 40000
#define MAXVAL 40000
using namespace std;

vector<int> currentScore(MAXN);
vector<int> S(MAXN);
vector<int> E(MAXN);
vector<vector<int>> Adj(MAXN);
vector<int> A(MAXN);
int N;
int Z;
int Q;
int timer = -1;
int startingNode;

void DFS(int v, int p) {
    S[v] = ++timer;
    currentScore[S[v]] = A[v];
    for (int u : Adj[v])
        if (u != p)
            DFS(u, v);
    E[v] = timer;
}

class SparseSegmentTree {
private:
    struct Node {
        int value = 0;
        Node* left;
        Node* right;
    };
    
    Node* root;

    void Update(int i, int x, Node*& current, int lo, int hi) {
        if (current == nullptr)
            current = new Node();
        if (lo == hi) {
            current->value += x;
            return;
        }
        int mid = (lo + hi) / 2;
        if (i <= mid)
            Update(i, x, current->left, lo, mid);
        else
            Update(i, x, current->right, mid + 1, hi);
        current->value = (current->left ? current->left->value : 0) + (current->right ? current->right->value : 0);
    }

    int Query(int qlo, int qhi, Node* current, int lo, int hi) {
        if (current == nullptr)
            return 0;
        if (qlo > hi || qhi < lo)
            return 0;
        if (qlo <= lo && hi <= qhi)
            return current->value;
        int mid = (lo + hi) / 2;
        int sumLeft = Query(qlo, qhi, current->left, lo, mid);
        int sumRight = Query(qlo, qhi, current->right, mid + 1, hi);
        return sumLeft + sumRight;
    }

public:
    void Update(int i, int x) {
        Update(i, x, root, 1, MAXVAL);
    }

    int Query(int qlo, int qhi) {
        return Query(qlo, qhi, root, 1, MAXVAL);
    }
};

vector<SparseSegmentTree> T(4 * MAXN);

class SegmentTree {
public:
    void InitialUpdate(int i, int x, int v = 0, int lo = 0, int hi = N - 1) {
        T[v].Update(x, 1);
        if (lo == hi)
            return;
        int mid = (lo + hi) / 2;
        if (i <= mid)
            InitialUpdate(i, x, 2 * v + 1, lo, mid);
        else
            InitialUpdate(i, x, 2 * v + 2, mid + 1, hi);
    }

    void Update(int i, int x, int v = 0, int lo = 0, int hi = N - 1) {
        T[v].Update(currentScore[i], -1);
        T[v].Update(x, 1);
        if (lo == hi) 
            return;
        int mid = (lo + hi) / 2;
        if (i <= mid)
            Update(i, x, 2 * v + 1, lo, mid);
        else 
            Update(i, x, 2 * v + 2, mid + 1, hi);
    }

    int Query(int qlo, int qhi, int l, int r, int v = 0, int lo = 0, int hi = N - 1) {
        if (qlo > hi || qhi < lo)  
            return 0;
        if (qlo <= lo && hi <= qhi)
            return T[v].Query(l, r);
        int mid = (lo + hi) / 2;
        int sumLeft = Query(qlo, qhi, l, r, 2 * v + 1, lo, mid);
        int sumRight = Query(qlo, qhi, l, r, 2 * v + 2, mid + 1, hi);
        return sumLeft + sumRight;
    }
};


int main() {
    scanf("%d %d %d", &N, &Z, &Q);
    for (int i = 0; i < N; ++i) {
        int p;
        scanf("%d %d", &p, &A[i]);
        if (p) 
            Adj[--p].push_back(i);
        else 
            startingNode = i;
    }
    DFS(startingNode, -1);
    SegmentTree Tree;
     for (int i = 0; i < N; ++i)
         Tree.InitialUpdate(S[i], currentScore[S[i]]);
    while (Q--) {
        char a;
        int b, c, d;
        scanf(" %c %d %d", &a, &b, &c);
        --b;
        if (a == 'u') {
            Tree.Update(S[b], c);
            currentScore[S[b]] = c;
        }
        else {
            scanf("%d", &d);
            printf("%d\n", Tree.Query(S[b], E[b], c, d));
        }
    }
}