#include <iostream>
#include <vector>
#include <climits>
#define INF LLONG_MAX
using namespace std;

int N;

class LazySegmentTree {
private:
    struct Node {
        long long value;
        long long lazyValue;
        Node* left;
        Node* right;
    }; 

public:
    Node* root; 

    LazySegmentTree(Node* current, int lo = 0, int hi = N + 1) {
        if (lo == hi) {
            current->value = -INF;
            current->lazyValue = 0;
            current->left = nullptr;
            current->right = nullptr;
        }
        int mid = (lo + hi) / 2;
        current->left = new Node;
        current->right = new Node;
        LazySegmentTree(current->left, lo, mid);
        LazySegmentTree(current->right, mid + 1, hi);
        current->value = max(current->left->value, current->right->value);
    }

    void Update(Node* current, int qlo, int qhi, long long x, int lo = 0, int hi = N + 1) {
        if (current->lazyValue != 0) {
            current->value += current->lazyValue;
            if (lo != hi) {
                current->left->lazyValue += current->lazyValue;
                current->right->lazyValue += current->lazyValue;
            }
            current->lazyValue = 0;
        }
        if (qlo > hi || qhi < lo)
            return;
        if (qlo <= lo && hi <= qhi) {
            current->value += x;
            if (lo != hi) {
                current->left->lazyValue += x;
                current->right->lazyValue += x;               
            }
            return;
        }
        int mid = (lo + hi) / 2;
        Update(current->left, qlo, qhi, x, lo, mid);
        Update(current->right, qlo, qhi, x, mid + 1, hi);
        current->value = max(current->left->value, current->right->value);
    }

    long long Query(Node* current, int qlo, int qhi, int lo = 0, int hi = N + 1) {
        if (current->lazyValue != 0) {
            current->value += current->lazyValue;
            if (lo != hi) {
                current->left->lazyValue += current->lazyValue;
                current->right->lazyValue += current->lazyValue;
            }
            current->lazyValue = 0;
        }
        if (qlo > hi || qhi < lo)
            return -INF;
        if (qlo <= lo && hi <= qhi) 
            return current->value;
        int mid = (lo + hi) / 2;
        long long maxLeft = Query(current->left, qlo, qhi, lo, mid);
        long long maxRight = Query(current->right, qlo, qhi, mid + 1, hi);
        return max(maxLeft, maxRight);
    }
};

int main() {

}

