#include <iostream>
#include <string>
using namespace std;    

int N;

void recurse(int i, char prev, string s) {
    if (i == N) {
        cout << s << endl;
        return;
    }
    if (prev != 'A')
        recurse(i + 1, 'A', s + 'A');
    if (prev != 'B')
        recurse(i + 1, 'B', s + 'B');
    if (prev != 'C')
        recurse(i + 1, 'C', s + 'C');
}

int main() {
    cin >> N;
    recurse(0, '-', "");
}
