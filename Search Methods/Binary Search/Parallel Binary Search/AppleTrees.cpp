#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <cmath>
#define MAXN 100000
#define MAXQ 100000
using namespace std;

struct Query {
    int L;
    int R;
    int K;
};

vector<int> A(MAXN);
vector<vector<pair<int, bool>>> B(MAXN); 
vector<Query> C(MAXQ);
vector<int> numberOfSmallerOrEqualElements(MAXQ);
vector<pair<int, int>> R(MAXQ);
int N;
int Q;

class SparseSegmentTree {
private:
    struct Node {
        int value;
        unique_ptr<Node> left;
        unique_ptr<Node> right;
    };

    unique_ptr<Node> root;

    const int maximumElement;

    void Update(const int x, unique_ptr<Node>& current, int lo, int hi) {
        if (current == nullptr)
            current = make_unique<Node>();
        if (lo == hi) {
            current->value += 1;
            return;
        }
        int mid = (lo + hi) / 2;
        if (x <= mid)
            Update(x, current->left, lo, mid);
        else 
            Update(x, current->right, mid + 1, hi);
        current->value = (current->left ? current->left->value : 0) + (current->right ? current->right->value : 0);
    }
    
    int Query(const int qlo, const int qhi, unique_ptr<Node>& current, int lo, int hi) {
        if (current == nullptr)
            return 0;
        if (qlo > hi || qhi < lo)
            return 0;
        if (qlo <= lo && hi <= qhi)
            return current->value;
        int mid = (lo + hi) / 2;
        int countLeft = Query(qlo, qhi, current->left, lo, mid);
        int countRight = Query(qlo, qhi, current->right, mid + 1, hi);
        return countLeft + countRight;
    }
    
public:
    SparseSegmentTree(int maximumElement) : root(make_unique<Node>()), maximumElement(maximumElement) {}

    void Update(const int x) { Update(x, root, 1, maximumElement); }

    int Query(const int qlo, const int qhi) { return Query(qlo, qhi, root, 1, maximumElement); }
};

int main() {
    // Reading input.
    cin >> N >> Q;
    for (int i = 0; i < N; ++i) 
        cin >> A[i];
    for (int i = 0; i < Q; ++i) {
        cin >> C[i].L >> C[i].R >> C[i].K;
        if (--C[i].L >= 1)
            B[C[i].L - 1].push_back(make_pair(i, 1));
        B[--C[i].R].push_back(make_pair(i, 0));
    }

    // Finding the maximum element in A.
    int maximumElement = *max_element(A.begin(), A.begin() + N);
    
    // Preparing the Parallel Binary Search.
    fill(R.begin(), R.begin() + Q, make_pair(1, maximumElement));

    // Parallel Binary Search.
    for (int i = 0; i < ceil(log2(maximumElement)); ++i) {
        // Initializing numberOfSmallerOrEqualElements vector.
        fill(numberOfSmallerOrEqualElements.begin(), numberOfSmallerOrEqualElements.begin() + Q, 0);
        
        // Declaring a Sparse Segment Tree.
        SparseSegmentTree T(maximumElement);

        // Performing the Binary Searches.
        for (int j = 0; j < N; ++j) {
            T.Update(A[j]);
            for (const auto& entry : B[j]) {
                int index = entry.first;
                bool isL = entry.second;
                if (R[index].first < R[index].second) {
                    int mid = (R[index].first + R[index].second) / 2;
                    int ans = T.Query(1, mid);
                    isL ? numberOfSmallerOrEqualElements[index] -= ans : numberOfSmallerOrEqualElements[index] += ans;
                }
            } 
        }

        // Changing the lower and upper bounds.
        for (int j = 0; j < Q; ++j) {
            if (R[j].first == R[j].second) 
                continue;
            int mid = (R[j].first + R[j].second) / 2;
            if (numberOfSmallerOrEqualElements[j] >= C[j].K)
                R[j].second = mid;
            else 
                R[j].first = mid + 1;
        }
    }

    // Printing the answer.
    for (int i = 0; i < Q; ++i)
        cout << R[i].first << endl;
}