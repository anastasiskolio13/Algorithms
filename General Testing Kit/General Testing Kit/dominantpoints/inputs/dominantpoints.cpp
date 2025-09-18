#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <set>
#include <cfloat>
#include <fstream>
#define MAXN 100000
#define INF DBL_MAX
using namespace std;

struct point {
    string ID;
    double F;
    double C;
};

vector<string> A(50);
vector<point> P;
vector<int> I;
vector<double> T;
int maxN;

void Update(int lo, int hi, int v, int i) {
    if (lo == hi) {
        T[v] = P[i].C;
        return;
    }
    int mid = (lo + hi) / 2;
    if (I[i] <= mid)
        Update(lo, mid, 2 * v + 1, i);
    else
        Update(mid + 1, hi, 2 * v + 2, i);
    T[v] = max(T[2 * v + 1], T[2 * v + 2]);
}

double Query(int lo, int hi, int v, int qlo, int qhi) {
    if (qlo <= lo && hi <= qhi)
        return T[v];
    if (qlo > hi || qhi < lo)
        return -INF;
    int mid = (lo + hi) / 2;
    double maxLeft = Query(lo, mid, 2 * v + 1, qlo, qhi);
    double maxRight = Query(mid + 1, hi, 2 * v + 2, qlo, qhi);
    return max(maxLeft, maxRight);
}

void SolveTestCase(int j) {
    P.clear();
    I.clear();
    T.clear();
    string filenameOne = "input_" + A[j] + "_alloy.in";
    string filenameTwo = "input_" + A[j] + "_alloy.ans";
    ifstream fin(filenameOne);
    int N;
    fin >> N;
    maxN = max(maxN, N);
    P.resize(N);
    I.resize(N);
    T.resize(4 * N);
    set<string> D;
    set<pair<double, int>> S;
    for (int i = 0; i < N; ++i) {
        fin >> P[i].ID >> P[i].F >> P[i].C;
        S.insert({ P[i].F, i });
    }
    fin.close();
    int i = 0;
    for (auto [value, index] : S) {
        I[index] = i++;
        Update(0, N - 1, 0, index);
    }

    for (int i = 0; i < N; ++i) {
        auto it = S.upper_bound({ P[i].F, N });
        if (it == S.end() || it != S.end() && P[i].C >= Query(0, N - 1, 0, I[it->second], N - 1))
            D.insert(P[i].ID);
    }
    ifstream fout(filenameTwo);
    set<string> ans;
    string ID;
    while (fout >> ID) {
        ans.insert(ID);
    }
    fout.close();
    if (ans.size() != D.size()) {
        cout << "WA" << endl;
        return;
    }
    for (string s : ans) {
        if (D.find(s) == D.end()) {
            cout << "WA" << endl;
            return;
        }
    }
    cout << "AC" << endl;
}

int main() {
    int numberOfTestCases = 23;
    for (int i = 0; i <= numberOfTestCases; ++i) {
        A[i] = i < 10 ? '0' + to_string(i) : to_string(i);
        SolveTestCase(i);
    }
}
