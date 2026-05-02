#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

long long MaximumProduct(const vector<int>& A, int lo, int hi)
{
	if (lo == hi)
	{
		return A[lo];
	}

	int mid = (lo + hi) / 2;

	long long maximumProductLeft = MaximumProduct(A, lo, mid);
	long long maximumProductRight = MaximumProduct(A, mid + 1, hi);

	int i = mid;
	int j = mid + 1;

	int currentMinimum = min(A[i], A[j]);

	long long maximumProductCrossing = currentMinimum * 2;

	while (true)
	{
		if (i == lo && j == hi)
		{
			break;
		}

		if (i == lo)
		{
			currentMinimum = min(currentMinimum, A[++j]);
		}
		else if (j == hi)
		{
			currentMinimum = min(currentMinimum, A[--i]);
		}
		else if (A[i - 1] > A[j + 1])
		{
			currentMinimum = min(currentMinimum, A[--i]);
		}
		else
		{
			currentMinimum = min(currentMinimum, A[++j]);
		}

		maximumProductCrossing = max(maximumProductCrossing, currentMinimum * (long long)(j - i + 1));
	}

	return max({ maximumProductLeft, maximumProductCrossing, maximumProductRight });

}

int main()
{
	int N;
	cin >> N;
	vector<int> A(N);
	for (int i = 0; i < N; i++)
	{
		cin >> A[i];
	}
	cout << MaximumProduct(A, 0, N - 1) << endl;
}