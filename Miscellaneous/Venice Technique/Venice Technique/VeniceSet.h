#pragma once
#include <map>

class VeniceSet
{
private:
	std::map<int, int> S;
	int waterLevel;

public:
	VeniceSet();

	void Add(const int height);

	void Remove(const int height);

	void UpdateAll(const int height);

	int Query() const;
};

