#include <iostream>
#include <cmath>
using namespace std;

int Q;
int A;
int B;
int C;

int main() {
    cin >> Q;
    while (Q--) {
        cin >> A >> B >> C;
        // O(lg min(A, B)).
        int lo = 0;
        int hi = min(A, B);
        while (lo < hi) {
            int mid = (lo + hi + 1) / 2;
            if (A + B + C >= 3 * mid)
                lo = mid;
            else
                hi = mid - 1;
        }
        cout << lo << endl;
    }
}