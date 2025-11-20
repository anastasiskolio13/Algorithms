#include <bits/stdc++.h>
using namespace std;

int main() {
    set<int> S;
    int Q;
    scanf("%d", &Q);
    vector<array<int, 3>> T;
    for (int q = 0; q < Q; ++q) {
        int a, b, c;
        scanf("%d %d", &a, &b);
        if (a != 3) {
            T.push_back({a, b, -1});
            S.insert(b);
        }
        else {
            scanf("%d", &c);
            T.push_back({a, b, c});
        }
    }
    map<int, int> I;
    int i = 0;
    for (int x : S)
        I[x] = i++;
}
