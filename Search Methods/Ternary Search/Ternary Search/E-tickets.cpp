#include <bits/stdc++.h>
using namespace std;

int T;
int N;
int A;
int B;
int C;
int D;

int Cost(int K) {
    int M = ceil((double)(N - K) / 2);
    return A * K * (K + 1) / 2 + B * K + C * M * (M + 1) / 2 + D * M;
}

int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d %d %d %d %d", &N, &A, &B, &C, &D);
        int lo = 0;
        int hi = N;
        while (lo < hi) {
            int mid = (lo + hi) / 2;
            if (Cost(mid) > Cost(mid + 1))
                lo = mid + 1;
            else
                hi = mid;
        }
        cout << lo << " " << ceil((double)(N - lo) / 2) << endl;
        //printf("%d %d\n", lo, (int)ceil((double)(N - lo) / 2));
    }
}
