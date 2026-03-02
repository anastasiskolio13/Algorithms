#include <iostream>
#include <vector>
#include <algorithm>
#include <cfloat>
#define MAXN 20000
using namespace std;

struct segment {
    double L;
    double R;
    int I;
    bool operator==(const segment& other) const {return L == other.L && R == other.R && I == other.I;}
    bool operator<(const segment& other) const {return L < other.L;}
};

double A;
double B;
int N;
vector<segment> S(MAXN);

int main() {
    for (int testCase = 0; testCase < 30; ++testCase) {
        cin >> A >> B >> N;
        segment startingSegment = {DBL_MIN, DBL_MIN, -1};
        for (int i = 0; i < N; ++i) {
            cin >> S[i].L >> S[i].R;
            S[i].I = i;
            if (S[i].L <= A && S[i].R > startingSegment.R) 
                startingSegment = S[i];
        }
        if (startingSegment.I == -1) {
            cout << "impossible" << endl;
            continue;
        }
        // Ταξινομώ τα διαστήματα με κριτήριο το αριστερό τους άκρο.
        sort(S.begin(), S.begin() + N);
        vector<segment> selectedSegments = {startingSegment};
        int i = distance(S.begin(), find(S.begin(), S.begin() + N, startingSegment)) + 1;
        while (i < N && selectedSegments.back().R < B) {
            segment bestSegment = {DBL_MIN, DBL_MIN, -1};
            while (i < N && S[i].L <= selectedSegments.back().R) 
                if (S[i].R > bestSegment.R) 
                    bestSegment = S[i++];
            if (bestSegment.R <= selectedSegments.back().R) 
                break;
            selectedSegments.push_back(bestSegment);
        }
        if (selectedSegments.back().R < B) {
            cout << "impossible" << endl;
            continue;
        }
        // Εκτύπωση λύσης.
        cout << selectedSegments.size() << endl;
        for (int i = 0; i < selectedSegments.size(); ++i) 
            cout << selectedSegments[i].I << " ";
        cout << endl;
    }
}