#include <iostream>
#include <cmath>
using namespace std;

int T;
int N;
int A;
int B;
int C;
int D;

long long Cost(long long M) {
    long long K = max(N - 2 * M, 0LL);
    return A * K * (K + 1) / 2 + B * K + C * M * (M + 1) / 2 + D * M;
}

int main() {
    cin >> T;
    while (T--) {
        cin >> N >> A >> B >> C >> D;
        int lo = 0;
        int hi = ceil((double)N / 2);
        while (lo < hi) {
            int mid = (lo + hi) / 2;
            if (Cost(mid) > Cost(mid + 1))
                lo = mid + 1;
            else 
                hi = mid;
        }
        cout << max(N - 2 * lo, 0) << " " << lo << endl;
    }
}