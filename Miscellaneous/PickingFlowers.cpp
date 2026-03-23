#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#define MAXN 200000
using namespace std;

struct flower {
    int X;
    int T;

    bool operator<(const flower& other) const {
        return X < other.X;
    }
};

multiset<int, greater<int>> S;
vector<flower> F(MAXN);
int N;
int M;

int main() {
    cin >> N >> M;
    for (int i = 0; i < N; ++i)
        cin >> F[i].X >> F[i].T;

    sort(F.begin(), F.begin() + N);

    int maximumFlowers = 0;
    long long sumOfPickTimes = 0;

    for (int i = 0; i < N; ++i) {      
        if (S.empty()) {
            if (F[i].X + F[i].T <= M) {
                sumOfPickTimes = F[i].T;
                S.insert(F[i].T);
            }
        }
        else {
            if (F[i].X + sumOfPickTimes + F[i].T <= M) {
                sumOfPickTimes += F[i].T;
                S.insert(F[i].T);
            }
            else if (F[i].T < *S.begin()) {
                sumOfPickTimes += F[i].T - *S.begin();
                S.erase(S.begin());
                S.insert(F[i].T);
            }
        }

        maximumFlowers = max(maximumFlowers, (int)S.size());
    }

    cout << maximumFlowers << endl;
}