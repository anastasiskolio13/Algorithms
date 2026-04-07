#include <iostream>
#include <vector>
#include <algorithm>
#define MAXN 100000
using namespace std;

vector<int> A(MAXN);
int N;
int M;

int totalNumberOfPeopleThatWillEat(int D) {
    int totalNumberOfPeople = 0;
    for (int i = 0; i < N; ++i)
        totalNumberOfPeople += A[i] / D;
    return totalNumberOfPeople;
}

int main() {
    cin >> N >> M;
    for (int i = 0; i < N; ++i)
        cin >> A[i];
    int lo = 1;
    int hi = *max_element(A.begin(), A.begin() + N);
    while (lo < hi) {
        int mid = (lo + hi + 1) / 2;
        if (totalNumberOfPeopleThatWillEat(mid) >= M)
            lo = mid;
        else    
            hi = mid - 1;
    }
    cout << (totalNumberOfPeopleThatWillEat(lo) >= M ? lo : 0) << endl;
}