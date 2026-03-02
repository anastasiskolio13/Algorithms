#include <iostream>
#include <vector>
#include <stack>
#include <numeric>
#define MAXN 1000
using namespace std;

class Point {
public:
    int X;
    int Y;

    static int D(const Point& A, const Point& B) {
        return (A.X - B.X) * (A.X - B.X) + (A.Y - B.Y) * (A.Y - B.Y);
    }
};

vector<Point> P(MAXN);
int N;

bool isGraphConnectedWithMaximumEdgeOfLength(int D) {
    vector<bool> V(N, false);
    stack<int> S;

    S.push(0);
    V[0] = true;

    while (!S.empty()) {
        int v = S.top();
        S.pop();
        for (int u = 0; u < N; u++) {
            if (!V[u] && D >= Point::D(P[v], P[u])) {
                S.push(u);
                V[u] = true;
            }
        }
    }

    return accumulate(V.begin(), V.end(), 0) == N;
}

int main() {
    freopen("moocast.in", "r", stdin);
    freopen("moocast.out", "w", stdout);
    cin >> N;
    for (int i = 0; i < N; ++i)
        cin >> P[i].X >> P[i].Y;
    int lo = 0;
    int hi = 1e9;
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        if (isGraphConnectedWithMaximumEdgeOfLength(mid))
            hi = mid;
        else 
            lo = mid + 1;
    }
    cout << lo << endl;
}