#pragma once
#include <set>
#include <vector>

class DFA {
private:
	std::set<int> K; // Σύνολο καταστάσεων.
	std::set<int> S; // Αλφάβητο.
	int s; // Αρχική κατάσταση.
	std::set<int> F; // Σύνολο τελικών καταστάσεων.
	std::vector<std::vector<int>> Delta; // Συνάρτηση μετάβασης.
public:
	DFA(const std::set<int> K, const std::set<int> S, const int s, const std::set<int> F, std::vector<std::vector<int>> Delta);
	int DeltaStar(const std::vector<int> A, int i, int currentState) const;
	bool IsAcceptingState(int state) const;
};

