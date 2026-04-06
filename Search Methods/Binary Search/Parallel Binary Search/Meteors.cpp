#include <iostream>
#include <vector>
#include <cmath>
#define MAXN 300000
#define MAXM 300000
#define MAXK 300000
using namespace std;

struct Event {
    int L;
    int R;
    int A;
};

vector<vector<int>> S(MAXN);
vector<int> P(MAXN);
vector<Event> E(MAXK);
vector<pair<int, int>> R(MAXN);
vector<int> ans(MAXN);
int N;
int M;
int K;

class LazySegmentTree {
    int n;
    vector<unsigned long long> tree;
    vector<unsigned long long> lazy;

    void push(int node, int lo, int hi) {
        if (lazy[node] == 0)
            return;
        tree[node] += lazy[node] * (hi - lo + 1);
        if (lo != hi) {
            lazy[node * 2] += lazy[node];
            lazy[node * 2 + 1] += lazy[node];
        }
        lazy[node] = 0;
    }

    void update(const int qlo, const int qhi, const int x, int node, int lo, int hi) {
        push(node, lo, hi);
        if (qlo > hi || qhi < lo)
            return;
        if (qlo <= lo && hi <= qhi) {
            tree[node] += (unsigned long long)x * (hi - lo + 1);
            if (lo != hi) {
                lazy[node * 2] += x;
                lazy[node * 2 + 1] += x;
            }
            return;
        }
        int mid = (lo + hi) / 2;
        update(qlo, qhi, x, node * 2, lo, mid);
        update(qlo, qhi, x, node * 2 + 1, mid + 1, hi);
        tree[node] = tree[node * 2] + tree[node * 2 + 1];
    }

    unsigned long long query(const int i, int node, int lo, int hi) {
        push(node, lo, hi);
        if (lo == hi)
            return tree[node];
        int mid = (lo + hi) / 2;
        if (i <= mid)
            return query(i, node * 2, lo, mid);
        return query(i, node * 2 + 1, mid + 1, hi);
    }

public:
    explicit LazySegmentTree(int size) : n(size) {
        if (n > 0) {
            tree.assign(4 * n + 5, 0);
            lazy.assign(4 * n + 5, 0);
        }
    }

    void Update(const int qlo, const int qhi, const int x) {
        if (n == 0)
            return;
        update(qlo, qhi, x, 1, 0, n - 1);
    }

    unsigned long long Query(const int i) {
        if (n == 0)
            return 0;
        return query(i, 1, 0, n - 1);
    }
};

int main() {
    cin >> N >> M;
    for (int i = 0; i < M; ++i) {
        int owner;
        cin >> owner;
        S[--owner].push_back(i);
    }
    for (int i = 0; i < N; ++i)
        cin >> P[i]; 
    cin >> K;
    for (int i = 0; i < K; ++i) {
        cin >> E[i].L >> E[i].R >> E[i].A;
        --E[i].L;
        --E[i].R;
    }
    fill(R.begin(), R.begin() + N, make_pair(0, K - 1));
    for (int i = 0; i < ceil(log2(K)); ++i) {
        vector<vector<int>> TS(K);
        for (int j = 0; j < N; ++j) 
            if (R[j].first < R[j].second)
                TS[(R[j].first + R[j].second) / 2].push_back(j);
        LazySegmentTree T(M);
        for (int j = 0; j < K; ++j) {
            if (E[j].L <= E[j].R) {
                T.Update(E[j].L, E[j].R, E[j].A);
            }
            else {
                T.Update(E[j].L, M - 1, E[j].A);
                T.Update(0, E[j].R, E[j].A);
            }
            for (int k : TS[j]) {
                unsigned long long totalSamples = 0;
                for (int l : S[k])
                    totalSamples += T.Query(l);
                if (totalSamples >= P[k])
                    R[k].second = j;
                else 
                    R[k].first = j + 1;
            }
        }
    }
    vector<vector<int>> TS(K);
    for (int j = 0; j < N; ++j)
        TS[R[j].first].push_back(j);
    LazySegmentTree T(M);
    for (int j = 0; j < K; ++j) {
        if (E[j].L <= E[j].R) {
            T.Update(E[j].L, E[j].R, E[j].A);
        }
        else {
            T.Update(E[j].L, M - 1, E[j].A);
            T.Update(0, E[j].R, E[j].A);
        }  
        for (int k : TS[j]) {
            unsigned long long totalSamples = 0;
            for (int l : S[k])
                totalSamples += T.Query(l);
            if (totalSamples >= P[k])
                ans[k] = j + 1;
            else 
                ans[k] = -1;
        }
    }
    for (int i = 0; i < N; ++i)
        if (ans[i] == -1)
            cout << "NIE" << endl;
        else 
            cout << ans[i] << endl;
    }