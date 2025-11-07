#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stack>
#include <queue>
using namespace std;

int main() {
	// Στοίβα.
	stack<int> S;
	S.push(0); // void.
	S.pop(); // void. 
	S.top(); // int.
	S.size(); // int.
	// Ουρά.
	queue<int> Q;
	Q.push(0); // void.
	Q.pop(); // void.
	Q.front(); // int.
	Q.size(); // int.
}