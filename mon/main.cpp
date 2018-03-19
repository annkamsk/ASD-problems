#include <iostream>
using namespace std;

long int max(long int a, long int b) {
    if (a > b) return a;
    return b;
}

int main() {
    int n;
    int *A = new int[n];
    cin
    for (int i = 0; i < n; ++i) {
        cin >> A[i];
    }
    long int *F = new long int[n + 1];
    F[0] = 0;
    F[1] = A[0];

    for (int i = 2; i <= n; ++i) {
        F[i] = max(F[i - 1], A[i - 1] + F[i - 2]);
    }

    cout << F[n];

    delete [] A;

    return 0;
}