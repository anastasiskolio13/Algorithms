#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <set>
#include <cfloat>
#include <fstream>
#include <algorithm>
#define INF DBL_MAX
using namespace std;

struct point {
    string ID;
    double X;
    double Y;
};

bool comparePoints(point A, point B) {
    return A.X < B.X;
}

vector<string> A(50);
set<string> D;
vector<point> P;
vector<double> SMY;
int N;

void SolveTestCase(int k) {
    P.clear();
    SMY.clear();
    string filenameOne = "input_" + A[k] + "_alloy.in";
    string filenameTwo = "input_" + A[k] + "_alloy.ans";
    ifstream fin(filenameOne);
    int N;
    fin >> N;
    P.resize(N);
    SMY.resize(N + 1);
    set<string> D;
    for (int i = 0; i < N; ++i) 
        fin >> P[i].ID >> P[i].X >> P[i].Y;
    fin.close();
    sort(P.begin(), P.begin() + N, comparePoints);
    SMY[N] = -INF;
    for (int i = N - 1; i >= 0; --i)
        SMY[i] = max(SMY[i + 1], P[i].Y);
    int j = 0;
    for (int i = 0; i < N; ++i) {
        while (j < N && P[i].X == P[j].X)
            ++j;
        if (P[i].Y >= SMY[j])
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
