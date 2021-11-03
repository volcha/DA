#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<long long> cost(n + 1, 0);
    for (int i = 2; i <= n; ++i) {
        if (i % 2 == 0 && i % 3 == 0) {
            cost[i] = i + min(cost[i - 1], min(cost[i / 2], cost[i / 3]));
        }
        else if (i % 2 == 0) {
            if (cost[i / 2] < cost[i - 1]) {
                cost[i] = i + cost[i / 2];
            }
            else {
                cost[i] = i + cost[i - 1];
            }
        }
        else if (i % 3 == 0) {
            if (cost[i / 3] < cost[i - 1]) {
                cost[i] = i + cost[i / 3];
            }
            else {
                cost[i] = i + cost[i - 1];
            }
        }
        else {
            cost[i] = i + cost[i - 1];
        }
    }
    cout << cost[n] << '\n';
    while (n > 1) {
        if (n % 2 != 0 && n % 3 != 0) {
            cout << "-1 ";
            n = n - 1;
        }
        else if (n % 3 != 0) {
            if (cost[n / 2] < cost[n - 1]) {
                cout << "/2 ";
                n = n / 2;
            }
            else {
                cout << "-1 ";
                n = n - 1;
            }
        }
        else if (n % 2 != 0) {
            if (cost[n / 3] < cost[n - 1]) {
                cout << "/3 ";
                n = n / 3;
            }
            else {
                cout << "-1 ";
                n = n - 1;
            }
        }
        else {
            if (cost[n / 3] < cost[n - 1] && cost[n / 3] < cost[n / 2]) {
                cout << "/3 ";
                n = n / 3;
            }
            else if (cost[n / 2] < cost[n - 1] && cost[n / 2] < cost[n / 3]) {
                cout << "/2 ";
                n = n / 2;
            }
            else {
                cout << "-1 ";
                n = n - 1;
            }
        }
    }
    cout << '\n';
}
