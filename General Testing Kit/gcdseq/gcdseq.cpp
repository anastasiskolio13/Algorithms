// #define _CRT_SECURE_NO_WARNINGS
// #include <iostream>
// #include <vector>
// #include <algorithm>
// #define MAXN 500000
// using namespace std;

// vector<int> SGCD(MAXN);
// vector<int> PGCD(MAXN);

// int Gcdseq(vector<int>& A, int lo, int hi) {
// 	if (lo == hi)
// 		return 1;
// 	int j = (lo + hi) / 2;
// 	int s_l = Gcdseq(A, lo, j);
// 	int s_r = Gcdseq(A, j + 1, hi);
// 	SGCD[j] = A[j];
// 	for (int i = j - 1; i >= lo; --i)
// 		SGCD[i] = __gcd(SGCD[i + 1], A[i]);
// 	PGCD[j + 1] = A[j + 1];
// 	for (int i = j + 2; i <= hi; ++i)
// 		PGCD[i] = __gcd(PGCD[i - 1], A[i]);
// 	int s_lr = 0;
// 	int k = hi;
// 	for (int i = j; i >= lo; --i) {
// 		while (k >= j + 1 && __gcd(SGCD[i], PGCD[k]) == 1)
// 			--k;
// 		if (k >= j + 1)
// 			s_lr = max(s_lr, k - i + 1);
// 	}
// 	return max({ s_l, s_lr, s_r });
// }

// void SolveTestCase(int j) {
// 	string filenameOne = "gcdseq.in" + to_string(j);
// 	freopen(filenameOne.c_str(), "r", stdin);
// 	int N;
// 	scanf("%d", &N);
// 	vector<int> A(N);
// 	for (int i = 0; i < N; ++i)
// 		scanf("%d", &A[i]);
// 	int myAnswer = Gcdseq(A, 0, N - 1);
// 	string filenameTwo = "gcdseq.out" + to_string(j);
// 	freopen(filenameTwo.c_str(), "r", stdin);
// 	int correctAnswer;
// 	scanf("%d", &correctAnswer);
// 	printf(myAnswer == correctAnswer ? "AC\n" : "WA\n");
// }

// ===================================================================================================================================================================================================

#include <iostream>
#include <numeric>
#include <stack>
#include <vector>
#include <string>
using namespace std;

class Queue
{
private:
	stack<pair<int, int>> S;
	stack<pair<int, int>> Q;

	void MoveAndUpdate()
	{
		int currentGCD = 0;

		while (!S.empty())
		{
			currentGCD = gcd(currentGCD, S.top().first);

			Q.push(make_pair(S.top().first, currentGCD));

			S.pop();
		}
	}

public:
	void Push(int a)
	{
		if (S.empty())
		{
			S.push(make_pair(a, a));
		}
		else
		{
			S.push(make_pair(a, gcd(S.top().second, a)));
		}
	}

	void Pop()
	{
		if (Q.empty())
		{
			MoveAndUpdate();
		}

		Q.pop();
	}

	int GetGCD() const
	{
		if (S.empty())
		{
			return Q.top().second;
		}

		if (Q.empty())
		{
			return S.top().second;
		}

		return gcd(S.top().second, Q.top().second);
	}
};

void SolveTestCase(int j)
{
	string filenameOne = "gcdseq.in" + to_string(j);
	freopen(filenameOne.c_str(), "r", stdin);

	int N;

	cin >> N;

	vector<int> A(N);

	for (int i = 0; i < N; ++i)
	{
		cin >> A[i];
	}

	int maximumLength = 0;

	Queue Q;

	for (int i = 0, j = 0; j < N; ++j)
	{
		Q.Push(A[j]);

		while (i < j && Q.GetGCD() == 1)
		{
			Q.Pop();

			++i;
		}

		maximumLength = max(maximumLength, j - i + 1);
	}

	int myAnswer = maximumLength;

	string filenameTwo = "gcdseq.out" + to_string(j);
	freopen(filenameTwo.c_str(), "r", stdin);
	int correctAnswer;
	scanf("%d", &correctAnswer);
	printf(myAnswer == correctAnswer ? "AC\n" : "WA\n");
}

int main()
{
	int numberOfTestCases = 31;
	for (int i = 1; i <= numberOfTestCases; ++i)
		SolveTestCase(i);
}
