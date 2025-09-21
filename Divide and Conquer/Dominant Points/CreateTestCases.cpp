#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <set>
#define MINN 1
#define MAXN 1000
#define MINVAL -1000
#define MAXVAL 1000
using namespace std;

void createTestCase(int j) {
	string filename = "in" + to_string(j) + ".txt";
	freopen(filename.c_str(), "w", stdout);
	set<pair<int, int>> S; // Set of points for the j-th testcase.
	int N = MINN + rand() % ((MAXN - MINN) + 1);
	while (S.size() < N) {
		int Y = MINVAL + rand() % ((MAXVAL - MINVAL) + 1);
		int X = MINVAL + rand() % ((MAXVAL - MINVAL) + 1);
		if (S.find({ X, Y }) == S.end())
			S.insert({ X, Y });
	}
	printf("%d\n", N);
	for (auto [X, Y] : S)
		printf("%d %d\n", X, Y);
}

int main() {
	srand(time(nullptr));
	int numberOfTestCases = 20;
	for (int i = 1; i <= numberOfTestCases; ++i)
		createTestCase(i);
}