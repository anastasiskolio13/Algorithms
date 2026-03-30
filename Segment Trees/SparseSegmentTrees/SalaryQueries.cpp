#include <iostream>
#include <vector>
#define MAXVALUE 1e9
#define MAXN 200000
using namespace std;
 
vector<int> P(MAXN);
int N;
int Q;
 
struct Node {
    int value;
    Node* left;
    Node* right;
};
 
Node* root;
 
class SparseSegmentTree {
public:
    SparseSegmentTree() {
        root = new Node();
        for (int i = 0; i < N; ++i)
            Update(P[i], 1);
    }
 
    void Update(const int i, const int x, Node* &current = root, int lo = 1, int hi = MAXVALUE) {
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
        current->value = (current->left != nullptr ? current->left->value : 0) + (current->right != nullptr ? current->right->value : 0);
    }
 
    int Query(const int qlo, const int qhi, Node* current = root, int lo = 1, int hi = MAXVALUE) {
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
};
 
int main() {
    scanf("%d %d", &N, &Q);
    for (int i = 0; i < N; ++i)
        scanf("%d", &P[i]);
    SparseSegmentTree T;
    while (Q--) {
        char a;
        int b;
        int c;
        scanf(" %c %d %d", &a, &b, &c);
        if (a == '!') {
            T.Update(P[--b], -1);
            T.Update(P[b] = c, 1);
        }
        else  {
            printf("%d\n", T.Query(b, c));
        }
    }
}