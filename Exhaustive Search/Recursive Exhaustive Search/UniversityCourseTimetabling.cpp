#include <iostream>
#include <vector>
#define MAXN 30
#define MAXM 30
#define MAXK 30
#define MAXT 30

std::vector<std::vector<int>> A(MAXN, std::vector<int>(MAXM));
std::vector<std::vector<int>> B(MAXT, std::vector<int>(MAXM));
std::vector<int> C(MAXM);
std::vector<int> D(MAXK);
std::vector<std::pair<int, int>> E(MAXM);
int N;
int M;
int K;
int T;

bool isValidAssignment(int currentCourse, int timeSlot, int room) {
    // 1. (∆ιεξαγωγή μαθήματος σε επιτρεπόμενη ώρα).
    if (!B[timeSlot][currentCourse])
        return false;
    // 2. (Όχι ίδια ώρα - ίδια αίθουσα).
    for (int i = 0; i < currentCourse; ++i)
        if (E[i].first == timeSlot && E[i].second == room)
            return false;
    // 3. (Χωρητικότητα αίθουσας).
    int registeredStudents = 0;
    for (int i = 0; i < N; ++i)
        registeredStudents += A[i][currentCourse];
    if (registeredStudents > D[room])
        return false;
    // 4. (Χρονική εξάρτηση).
    if (C[currentCourse] != -1 && E[C[currentCourse]].first >= timeSlot)
            return false;
    // 5. (Όχι διαφορετικό μάθημα - ίδια ώρα).
    for (int i = 0; i < N; ++i) {
        if (!A[i][currentCourse])
            continue;
        for (int j = 0; j < currentCourse; ++j)
            if (A[i][j] && E[j].first == timeSlot)
                return false;
    }
    // Όλοι οι περιορισμοί ικανοποιούνται.
    return true;
}

bool isFeasibleSolution(int currentCourse) {
    if (currentCourse == M)
        return true; // Έχουμε παραδεκτή λύση.
    // Δοκιμάζουμε πιθανές αναθέσεις για το τρέχον μάθημα.
    for (int timeSlot = 0; timeSlot < T; ++timeSlot) {
        for (int room = 0; room < K; ++room)
            if (isValidAssignment(currentCourse, timeSlot, room)) {
                E[currentCourse] = std::make_pair(timeSlot, room);
                if (isFeasibleSolution(currentCourse + 1))
                    return true;
            }
    }
    return false;
}

int main() {
    // Εισαγωγή δεδομένων.
    freopen("UCT.in", "r", stdin);
    freopen("UCT.out", "w", stdout);
    scanf("%d %d %d %d", &N, &M, &K, &T);
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
            scanf("%d", &A[i][j]);
    for (int i = 0; i < T; ++i)
        for (int j = 0; j < M; ++j)
            scanf("%d", &B[i][j]);
    for (int i = 0; i < M; ++i)
        scanf("%d", &C[i]);
    for (int i = 0; i < K; ++i)
        scanf("%d", &D[i]);
    // Επίλυση προβλήματος.
    if (!isFeasibleSolution(0)) {
        printf("Δεν υπάρχει λύση για την είσοδο αυτή.\n");
        return 0;
    }
    // Εκτύπωση λύσης.
    for (int i = 0; i < M; ++i)
        printf("Το μάθημα %d θα πραγματοποιηθεί τη χρονική στιγμή %d στην αίθουσα %d.\n", i, E[i].first, E[i].second);
}
