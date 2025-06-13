#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <queue>
#define MAXH 100
#define MAXW 100
#define INF 1e9
using namespace std;

vector<vector<char>> A(MAXH, vector<char>(MAXW));
vector<vector<vector<int>>> D(MAXH, vector<vector<int>>(MAXW, vector<int>(3)));
int T;
int H;
int W;
int Xi;
int Xj;
int Yi;
int Yj;

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d", &H, &W);
		for (int i = 0; i < H; ++i) {
			for (int j = 0; j < W; ++j) {
				scanf(" %c", &A[i][j]);
				D[i][j][0] = D[i][j][1] = D[i][j][2] = INF;
				if ()
			}
		}
	}
}