#include "DFA.h"

DFA::DFA(const std::set<int> K, const std::set<int> S, const int s, const std::set<int> F, std::vector<std::vector<int>> Delta) {
	this->K = K;
	this->S = S;
	this->s = s;
	this->F = F;
	this->Delta = Delta;
}

int DFA::DeltaStar(const std::vector<int> A, int i, int currentState) const {
	if (i == A.size())
		return currentState;
	return DeltaStar(A, i + 1, Delta[currentState - 1][A[i]]);
}

bool DFA::IsAcceptingState(int state) const {
	return F.find(state) != F.end();
}