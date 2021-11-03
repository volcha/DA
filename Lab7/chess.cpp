#include <iostream>
#include <vector>

int main() {
    vector<vector<int>> chess(int n, int m);
    for (int i = 1; i < n; ++i) {
        for (int j = 1; i < m; ++j) {
            chess[i][j] = 0;
        }
    }
    chess[0][0] = 1;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; i < m; ++j) {
            if (i - 2 >= 0 && j - 1 >= 0) {
                chess[i][j] += chess[i-2][j-1];
            }
            if (i - 1 >= 0 && j - 2 >= 0) {
                chess[i][j] += chess[i-1][j-2];
            }
        }
    }
}
