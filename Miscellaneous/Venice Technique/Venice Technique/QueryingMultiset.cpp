#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <set>
using namespace std;

class VeniceSet {
private:
	multiset<long long> S;
	long long waterLevel;
public:
	VeniceSet() { waterLevel = 0; }
	void Add(const int x) { S.insert(x - waterLevel); }
	void UpdateAll(const int x) { waterLevel += x; }
	long long GetMin() { long long x = *S.begin(); S.erase(S.begin()); return x + waterLevel; }
};

int Q;

int main() {
	VeniceSet S;
	scanf("%d", &Q);
	while (Q--) {
		int a, b;
		scanf("%d", &a);
		switch (a)
		{
		case 1:
			scanf("%d", &b); S.Add(b); break;
		case 2:
			scanf("%d", &b); S.UpdateAll(b); break;
		default:
			printf("%lld\n", S.GetMin());
		}
	}
}