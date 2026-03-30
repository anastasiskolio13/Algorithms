#include <iostream>
#include <unordered_map>
#define MAXR 1e8
using namespace std;

struct Node {
    int value;
    int correspondingID;
    Node* left;
    Node* right;
};

Node* root;

class SparseSegmentTree {
public:
    SparseSegmentTree() { root = new Node(); };

    void Update(const int i, const int x, const int y, Node* &current = root, int lo = 1, int hi = MAXR) {
        if (current == nullptr)
            current = new Node();     
        if (lo == hi) {
            current->value += x;
            current->correspondingID = y;
            return;
        }
        int mid = (lo + hi) / 2;
        if (i <= mid) 
            Update(i, x, y, current->left, lo, mid);
        else 
            Update(i, x, y, current->right, mid + 1, hi); 
        current->value = (current->left != nullptr ? current->left->value : 0) + (current->right != nullptr ? current->right->value : 0);
    }

    int Kth(const int k, Node* &current = root, int lo = 1, int hi = MAXR) {
        if (lo == hi)
            return current->correspondingID;
        int mid = (lo + hi) / 2;
        if (current->left != nullptr && current->left->value >= k)
            return Kth(k, current->left, lo, mid);
        else 
            return Kth(k - (current->left != nullptr ? current->left->value : 0), current->right, mid + 1, hi);
    }
};

unordered_map<int, int> R;
int N;
char A;
int B;
int C;

int main() {
    SparseSegmentTree T;
    scanf("%d", &N);
    for (int i = 0; i < N; ++i) {
        scanf(" %c %d", &A, &B);
        if (A == 'N') {
            scanf("%d", &C);
            T.Update(R[B] = C, 1, B);
        }
        else if (A == 'M') {
            scanf("%d", &C);
            T.Update(R[B], -1, -1);
            T.Update(R[B] = C, 1, B);
        }
        else {
            printf("%d\n", T.Kth(R.size() - B + 1));
        }
    }
}