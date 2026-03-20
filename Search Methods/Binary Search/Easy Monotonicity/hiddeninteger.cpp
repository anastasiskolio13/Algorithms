#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

int main() {
	int lo = 1;
	int hi = 1000000000;
	while (lo < hi) {
		int mid = (lo + hi) / 2;
		cout << "? " << mid << endl;
		string ans;
		cin >> ans;
		if (ans == "YES")
			lo = mid + 1;
		else
			hi = mid;
	}
	cout << "! " << lo << endl;
}