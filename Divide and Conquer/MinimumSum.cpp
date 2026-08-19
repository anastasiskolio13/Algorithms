#include <iostream>
#include <vector>
#define INF 2e9
using namespace std;

long long DivideAndConquer(const vector<int>& A, vector<int>& PrefixMinimum, vector<long long>& PrefixSum, int lo, int hi)
{
	if (lo == hi)
	{
		return A[lo];
	}

	int mid = (lo + hi) / 2;

	long long sumLeft = DivideAndConquer(A, PrefixMinimum, PrefixSum, lo, mid);
	
	long long sumRight = DivideAndConquer(A, PrefixMinimum, PrefixSum, mid + 1, hi);

	long long sumLeftRight = 0;

	PrefixMinimum[mid] = INF;

	PrefixSum[mid] = 0;

	for (int j = mid + 1; j <= hi; ++j)
	{
		PrefixMinimum[j] = min(PrefixMinimum[j - 1], A[j]);

		PrefixSum[j] = PrefixSum[j - 1] + PrefixMinimum[j];
	}

	int suffixMinimum = INF;

	for (int i = mid, j = mid + 1; i >= lo; --i)
	{
		suffixMinimum = min(suffixMinimum, A[i]);

		while (j <= hi && suffixMinimum <= PrefixMinimum[j])
		{
			++j;
		}

		sumLeftRight += (long long)(j - mid - 1) * suffixMinimum + PrefixSum[hi] - PrefixSum[j - 1];
	}

	return sumLeft + sumRight + sumLeftRight;
}

int main()
{
	int N;

	cin >> N;

	vector<int> A(N);

	for (int i = 0; i < N; ++i)
	{
		cin >> A[i];
	}

	vector<int> PrefixMinimum(N);

	vector<long long> PrefixSum(N);

	cout << DivideAndConquer(A, PrefixMinimum, PrefixSum, 0, N - 1) << endl;
}