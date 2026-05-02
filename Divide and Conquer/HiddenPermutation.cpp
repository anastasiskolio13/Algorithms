#include <iostream>
#include <vector>
using namespace std;

vector<int> Combine(vector<int>& A, vector<int>& B) {
    vector<int> C(A.size() + B.size());
    int i = 0;
    int j = 0;
    int k = 0;
    while (i < A.size() && j < B.size()) {
        cout << "? " << A[i] << " " << B[j] << endl;
        string AiIsSmallerThanBj;
        cin >> AiIsSmallerThanBj;
        if (AiIsSmallerThanBj == "YES")
            C[k++] = A[i++];
        else 
            C[k++] = B[j++]; 
    }
    while (i < A.size())
        C[k++] = A[i++];
    while (j < B.size())
        C[k++] = B[j++];
    return C;
}

vector<int> DivideAndConquer(int lo, int hi) {
    if (lo == hi)
        return {lo};
    int mid = (lo + hi) / 2;
    vector<int> A = DivideAndConquer(lo, mid);
    vector<int> B = DivideAndConquer(mid + 1, hi);
    return Combine(A, B);
}

int main() {
    int N;
    cin >> N;
    vector<int> A(N);
    vector<int> B = DivideAndConquer(1, N);
    for (int i = 0; i < N; ++i)
        A[B[i] - 1] = i + 1;
    cout << "! " << flush;
    for (int i = 0; i < N; ++i)
        cout << A[i] << " " << flush;
} 