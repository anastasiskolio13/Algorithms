#include <iostream>
#include <vector>
#define MAXN 100000
using namespace std;

int N;
vector<int> L(MAXN);
vector<int> R(MAXN);

int main() {
    cin >> N;
    for (int i = 0; i < N; ++i)
        cin >> L[i];
    for (int i = 0; i < N; ++i)
        cin >> R[i];
    int prev = L[0];
    for (int i = 1; i < N; ++i) {
        if (R[i] < prev) {
            cout << "NO" << endl;
            return 0;
        }
        prev = max(prev, L[i]);
    }
    cout << "YES" << endl;
}