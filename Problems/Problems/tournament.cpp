#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#define MAXSCORE 1000000
#define lgMAXCORE 19
using namespace std;

vector<int> P;
vector<vector<int>> dp(MAXSCORE + 1, vector<int>(lgMAXCORE + 1));
int N;

void computePowers() {
	int power = 1; // 2^{0}
	while (power <= MAXSCORE) {
		P.push_back(power);
		power *= 2;
	}
}

int main() {
	//scanf("%d", &N);
	computePowers();
	for (int i = 0; i <= lgMAXCORE; ++i)
		dp[0][i] = 1;
	for (int score = 1; score <= MAXSCORE; ++score) {
		for (int i = 0; i <= lgMAXCORE; ++i) {
			if (P[i] > score)
				dp[score][i] = dp[score][0];
			else if (P[i] <= score && i != 0)
				dp[score][i] = dp[score][0] + dp[score - P[i]][i + 1];
			else
				dp[score][i] = dp[score - P[i]][i + 1];
		}
	}
}