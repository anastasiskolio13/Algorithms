#include <iostream>
#include <vector>
#include <algorithm>
#define MAXN 200000
using namespace std;

vector<int> A(MAXN);
int N;
int Q;

struct Node {
    vector<int> A;
    vector<long long> PS;
    Node* left;
    Node* right;
};

Node* root;

class MergeSortTree {
public:
    MergeSortTree(Node*& current = root, int lo = 0, int hi = N - 1) {
        if (current == nullptr) 
            current = new Node();
        if (lo == hi) {
            current->A = {A[lo]};
            current->PS = {A[lo]};
            return;
        }
        int mid = (lo + hi) / 2;
        MergeSortTree(current->left, lo, mid);
        MergeSortTree(current->right, mid + 1, hi);
        merge(current->left->A.begin(), current->left->A.end(), current->right->A.begin(), current->right->A.end(), back_inserter(current->A));
        current->PS.resize(current->A.size());
        current->PS[0] = current->A[0];
        for (int i = 1; i < current->PS.size(); ++i)
            current->PS[i] = current->PS[i - 1] + current->A[i];
    }

    long long FindSumOfNotGreater(const int qlo, const int qhi, const int x, Node* current = root, int lo = 0, int hi = N - 1) const {
        if (current == nullptr)
            return 0;
        if (qlo > hi || qhi < lo)
            return 0;
        if (qlo <= lo && hi <= qhi) {
            auto it = upper_bound(current->A.begin(), current->A.end(), x);
            return it != current->A.begin() ? current->PS[(--it) - current->A.begin()] : 0;
        }
        int mid = (lo + hi) / 2;
        long long sumLeft = FindSumOfNotGreater(qlo, qhi, x, current->left, lo, mid);
        long long sumRight = FindSumOfNotGreater(qlo, qhi, x, current->right, mid + 1, hi);
        return sumLeft + sumRight;
    }
};

int main() {
    cin >> N;
    for (int i = 0; i < N; ++i)
        cin >> A[i];
    MergeSortTree T;
    cin >> Q;
    long long prevAns = 0;
    while (Q--) {
        long long a, b, c;
        cin >> a >> b >> c;
        prevAns = T.FindSumOfNotGreater((a ^ prevAns) - 1, (b ^ prevAns) - 1, c ^ prevAns);
        cout << prevAns << endl;
    }
}