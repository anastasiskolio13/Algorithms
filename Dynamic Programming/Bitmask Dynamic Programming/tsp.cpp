#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#define MAXN 20
#define INF 1e9
using namespace std;

vector<vector<int>> A(MAXN, vector<int>(MAXN));
vector<vector<int>> dp(1 << MAXN, vector<int>(MAXN));
int N;

// Ξεκινώντας από την πόλη 0 πρέπει να επισκεφθώ ακριβώς μία φορά όλες τις πόλεις και αν επιστρέψω στην 0, 
// με το ελάχιστο δυνατό συνολικό κόστος.

// Θα ξεκινήσω από την πόλη 0.

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
			scanf("%d", &A[i][j]);
	// Για τον λόγο του ότι δεν μπορώ να επισκεφθώ κάποια πόλη πάνω από μία φορά, γυρνάω από την τερματική πόλη 
	// απευθίας στη 0.
	for (int i = 0; i < N; ++i)
		dp[0][i] = A[0][i];
	for (int s = 1; s < (1 << N); ++s) {
		for (int i = 0; i < N; ++i) {
			dp[s][i] = INF;
			// Αν η πόλη i είναι ενεργή στο s, το dp[s][i] δεν ορίζεται και άρα συνεχίζω στην επόμενη επανάληψη.
			if (s & (1 << i))
				continue;
			for (int j = 0; j < N; ++j)
				if (s & (1 << j))
					dp[s][i] = min(dp[s][i], dp[s & ~(1 << j)][j] + A[i][j]);
		}
	}
	printf("%d\n", dp[(1 << N) - 1 & ~(1 << 0)][0]);
}