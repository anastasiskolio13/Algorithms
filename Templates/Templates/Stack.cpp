#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#define MAXC 1000
using namespace std;

vector<int> S(MAXC + 1);
int top;

// O(1).
void Init() {
	// Αρχικοποιεί τη στοίβα.
	top = 0;
}

// O(1).
void Push(int x) {
	// Βάζει ένα στοιχείο στην κορυφή της στοίβας, αν το ίδιο είναι εφικτό.
	if (top == MAXC)
		cout << "Overflow" << endl;
	else 
		S[++top] = x;
}

// O(1).
void Pop() {
	// Βγάζει το στοιχείο που είναι στην κορυφή της στοίβας, αν η ίδια δεν είναι άδεια.
	if (top == 0) 
		cout << "Stack is empty" << endl;
	else {
		cout << "Number removed: " << S[top] << endl;
		--top;
	}
}

// O(1).
int Top() {
	// Επιστρέφει το στοιχείο που είναι στην κορυφή της στοίβας, αν η ίδια δεν είναι άδεια.
	if (top == 0) {
		cout << "Stack is empty" << endl;
		return -1;
	}
	else {
		return S[top];
	}
}


// O(1).
int Size() {
	// Επιστρέφει πόσα στοιχεία είναι στη στοίβα.
	return top;
}

int main() {
	Init();
	Push(3);
	Push(5);
	Pop();
	Push(7);
	Pop();
	Pop();
	Pop();
	Push(8);
	Pop();
}