#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <stack>
#define MAXN 100
using namespace std;

stack<pair<int, int>> S;
vector<vector<vector<pair<int, int>>>> R(MAXN, vector<vector<pair<int, int>>>(MAXN));
vector<vector<bool>> visited(MAXN, vector<bool>(MAXN));
vector<vector<bool>> isLit(MAXN, vector<bool>(MAXN));
int N;
int M;

int DepthFirstSearch() {
	int litRooms = 1;
	visited[0][0] = isLit[0][0] = true;
	S.push({ 0, 0 });
	while (!S.empty()) {
		int x = S.top().first;
		int y = S.top().second;
		S.pop();
		for (auto room : R[x][y]) {
			int i = room.first;
			int j = room.second;
			if (!isLit[i][j]) {
				++litRooms;
				isLit[i][j] = true;
				bool canGo = false;
				if (i - 1 >= 0 && visited[i - 1][j])
					canGo = true;
				if (i + 1 < N && visited[i + 1][j])
					canGo = true;
				if (j - 1 >= 0 && visited[i][j - 1])
					canGo = true;
				if (j + 1 < N && visited[i][j + 1])
					canGo = true;
				if (canGo) {
					visited[i][j] = true;
					S.push({ i, j });
				}
			}
		}
		if (x - 1 >= 0 && isLit[x - 1][y] && !visited[x - 1][y]) {
			visited[x - 1][y] = true;
			S.push({ x - 1, y });
		}
		if (x + 1 < N && isLit[x + 1][y] && !visited[x + 1][y]) {
			visited[x + 1][y] = true;
			S.push({ x + 1, y });
		}
		if (y - 1 >= 0 && isLit[x][y - 1] && !visited[x][y - 1]) {
			visited[x][y - 1] = true;
			S.push({ x, y - 1 });
		}
		if (y + 1 < N && isLit[x][y + 1] && !visited[x][y + 1]) {
			visited[x][y + 1] = true;
			S.push({ x, y + 1 });
		}
	}
	return litRooms;
}

int main() {
	freopen("lightson.in", "r", stdin);
	freopen("lightson.out", "w", stdout);
	scanf("%d %d", &N, &M);
	for (int i = 0; i < M; ++i) {
		int i1, j1, i2, j2;
		scanf("%d %d %d %d", &i1, &j1, &i2, &j2);
		R[--i1][--j1].push_back({ --i2, --j2 });
	}
	printf("%d\n", DepthFirstSearch());
}