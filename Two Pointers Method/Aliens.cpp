#include <iostream>
#include <vector>
#define MAXN 100000
using namespace std;

vector<int> A(MAXN);
int N;
int W;

int main() {
    cin >> N >> W;
    for (int i = 0; i < N; ++i)
        cin >> A[i];
    int ans = 0;
    for (int j = 0, i = 0; j < N; ++j) {
        while (A[j] - A[i] + 1 > W)
            ++i;
        ans = max(ans, j - i + 1);
    }
    cout << ans << endl;
}