#include <iostream>
#include <vector>
using namespace std;

class LazySegmentTree {
private:
    struct Node {
        long long value;
        long long lazyValue;

        Node* left;
        Node* right;
    };

    void Update(Node* current, int qlo, int qhi, int lo, int hi, int x) {
        if (current->lazyValue )
    } 

    long long Query(Node* current, int qlo, int qhi, int lo, int hi) {

    }

};

struct race {
    int L;
    int R;
    int P;
};

int main() {
}