#include <iostream>
using namespace std;

long long binomialCoeff(int n, int k) {
    if (k == 0 || k == n) return 1;

    long long C[n + 1][k + 1];
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= min(i, k); j++) {
            if (j == 0 || j == i)
                C[i][j] = 1;
            else
                C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
        }
    }
    return C[n][k];
}

int main() {
    int v, e;
    cin >> v >> e;
    int n = v * (v - 1) / 2; // Số lượng cạnh trong đồ thị đầy đủ v đỉnh

    if (e <= n) {
        cout << binomialCoeff(n, e) << endl;
    } else {
        cout << "Invalid input" << endl;
    }

    return 0;
}
