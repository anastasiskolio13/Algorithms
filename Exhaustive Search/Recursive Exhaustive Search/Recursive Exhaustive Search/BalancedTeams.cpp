#include <bits/stdc++.h>
#define INF 1e9
using namespace std;

vector<int> S(12);

// 4^12.
int optimalSplit(int i, int sumOne, int countOne, int sumTwo, int countTwo, int sumThree, int countThree, int sumFour, int countFour) {
    if (i == 12)
        return max({sumOne, sumTwo, sumThree, sumFour}) - min({sumOne, sumTwo, sumThree, sumFour}) + INF * (countOne != 3 || countTwo != 3 || countThree != 3 || countFour != 3);
    int joinFirstTeam = optimalSplit(i + 1, sumOne + S[i], countOne + 1, sumTwo, countTwo, sumThree, countThree, sumFour, countFour);
    int joinSecondTeam = optimalSplit(i + 1, sumOne, countOne, sumTwo + S[i], countTwo + 1, sumThree, countThree, sumFour, countFour);
    int joinThirdTeam = optimalSplit(i + 1, sumOne, countOne, sumTwo, countTwo, sumThree + S[i], countThree + 1, sumFour, countFour);
    int joinFourthTeam = optimalSplit(i + 1, sumOne, countOne, sumTwo, countTwo, sumThree, countThree, sumFour + S[i], countFour + 1);
    return min({joinFirstTeam, joinSecondTeam, joinThirdTeam, joinFourthTeam});
}

int main() {
    for (int i = 0; i < 12; ++i)
        scanf("%d", &S[i]);
    printf("%d\n", optimalSplit(0, 0, 0, 0, 0, 0, 0, 0, 0));
}
