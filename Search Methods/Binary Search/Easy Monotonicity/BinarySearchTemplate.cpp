#include <iostream>
#include <vector>
using namespace std;

int FindFirstOccurrence(const vector<int>& A, int lo, int hi, const int x) {
    if (lo == hi)
        return A[lo] == x ? lo : -1;
    int mid = (lo + hi) / 2; // floor((lo + hi) / 2.0).
    if (x <= A[mid])
        return FindFirstOccurrence(A, lo, mid, x);
    else 
        return FindFirstOccurrence(A, mid + 1, hi, x);
}

int FindLastOccurrence(const vector<int>& A, int lo, int hi, const int x) {
    if (lo == hi)
        return A[lo] == x ? lo : -1;
    int mid = (lo + hi + 1) / 2; // ceil((lo + hi) / 2.0).
    if (x < A[mid])
        return FindLastOccurrence(A, lo, mid - 1, x);
    else 
        return FindLastOccurrence(A, mid, hi, x);
}

int FindFirstOccurrenceIterative(const vector<int>& A, int lo, int hi, const int x) {
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        if (x <= A[mid])
            hi = mid;
        else 
            lo = mid + 1;
    }
    return A[lo] == x ? lo : -1;
}

int main() {
    vector<int> A = {1, 3, 7, 14, 25, 30};
    cout << FindFirstOccurrence(A, 0, A.size() - 1, 3) << endl;
}