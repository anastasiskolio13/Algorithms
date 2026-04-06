#include <iostream>
#include <vector>
#define MAXN 30000
#define MAXQ 200000
#define MAXVAL 1000000000
using namespace std;

struct Query {
    int L;
    int R;
    int K;
    int I;
};

vector<int> ans(MAXQ);
vector<int> A(MAXN);
vector<vector<Query>> QN(MAXN);
int N;

struct Node {
    int value;
    Node* left;
    Node* right;
};

Node* root;

class SparseSegmentTree {
public:
    void Update(const int x, Node*& current = root, int lo = 1, int hi = MAXVAL) {
        if (current == nullptr)
            current = new Node();
        if (lo == hi) {
            current->value += 1;
            return;
        }
        int mid = (lo + hi) / 2;
        if (x <= mid)
            Update(x, current->left, lo, mid);
        else   
            Update(x, current->right, mid + 1, hi);
        current->value = (current->left != nullptr ? current->left->value : 0) + (current->right != nullptr ? current->right->value : 0); 
    }

    int Query(const int qlo, const int qhi, Node* current = root, int lo = 1, int hi = MAXVAL) {
        if (current == nullptr)
            return 0;
        if (qlo > hi || qhi < lo)
            return 0;
        if (qlo <= lo && hi <= qhi)
            return current->value;
        int mid = (lo + hi) / 2;
        return Query(qlo, qhi, current->left, lo, mid) + Query(qlo, qhi, current->right, mid + 1, hi);
    }

    void DeleteSparseSegmentTree(Node* current = root) {
        if (current == nullptr)
            return;
        DeleteSparseSegmentTree(current->left);
        DeleteSparseSegmentTree(current->right);
        delete current;
    }
};

void SRQ(int lo, int hi, vector<Query>& Q) {
    if (lo == hi) {
        for (auto query : Q)
            ans[query.I] = A[lo] > query.K;
        return;
    }
    int mid = (lo + hi) / 2;
    vector<Query> QL;
    vector<Query> QR;
    for (int i = lo; i <= hi; ++i)
        QN[i].clear();
    for (auto query : Q) {
        if (query.R <= mid) {
            QL.push_back(query);
        }
        else if (query.L > mid) {
            QR.push_back(query);
        }
        else {
            QN[query.L].push_back(query);
            QN[query.R].push_back(query);
        }
    }
    SparseSegmentTree T;
    for (int i = mid; i >= lo; --i) {
        T.Update(A[i]);
        for (auto query : QN[i])
            ans[query.I] += T.Query(query.K + 1, MAXVAL);
    }
    T.DeleteSparseSegmentTree();
    root = nullptr;
    for (int i = mid + 1; i <= hi; ++i) {
        T.Update(A[i]);
        for (auto query : QN[i])
            ans[query.I] += T.Query(query.K + 1, MAXVAL);
    }
    T.DeleteSparseSegmentTree();
    SRQ(lo, mid, QL);
    SRQ(mid + 1, hi, QR);
}

int main() {
    cin >> N;
    for (int i = 0; i < N; ++i)
        cin >> A[i];
    int Q;
    cin >> Q;
    vector<Query> T(Q);
    for (int i = 0; i < Q; ++i) {
        cin >> T[i].L >> T[i].R >> T[i].K;
        --T[i].L;
        --T[i].R;
        T[i].I = i;
    }  
    SRQ(0, N - 1, T);
    for (int i = 0; i < Q; ++i)
        cout << ans[i] << endl;
}