#include <iostream>
#include <vector>
using namespace std;

int knapsack(int W, const vector<int>& weights, const vector<int>& values, int n) {
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (weights[i - 1] <= w) {
                dp[i][w] = max(dp[i - 1][w], dp[i - 1][w - weights[i - 1]] + values[i - 1]);
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    return dp[n][W];
}

int main() {
    int n, W;
    cout << "Enter number of items: ";
    cin >> n;
    vector<int> values(n), weights(n);

    for (int i = 0; i < n; i++) {
        cout << "Enter value of item " << i + 1 << ": ";
        cin >> values[i];
    }

    for (int i = 0; i < n; i++) {
        cout << "Enter weight of item " << i + 1 << ": ";
        cin >> weights[i];
    }

    cout << "Enter maximum weight of the knapsack: ";
    cin >> W;

    int maxValue = knapsack(W, weights, values, n);
    cout << "Maximum value in the knapsack = " << maxValue << endl;

    return 0;
}
