#include "VeniceSet.h"

VeniceSet::VeniceSet() {
	waterLevel = 0;
}

void VeniceSet::Add(const int height) {
	++S[height + waterLevel];
}

void VeniceSet::Remove(const int height) {
	auto iteratorOne = S.find(height + waterLevel);
	if (iteratorOne != S.end()) {
		if (iteratorOne->second == 1)
			S.erase(iteratorOne);
		else
			--iteratorOne->second;
	}
}

void VeniceSet::UpdateAll(const int height) {
	waterLevel += height;
}

int VeniceSet::Query() const {
	auto iteratorOne = S.upper_bound(waterLevel);
	if (iteratorOne == S.end())
		return -1;
	else
		return iteratorOne->first;
}