#include <iostream>
#include <vector>
#include <climits>
using namespace std;

const int INF = INT_MAX;
int n; // Number of cities
vector<vector<int>> dist; // Adjacency matrix for distances
vector<vector<int>> dp;

// Recursive function with memoization
int tsp(int mask, int pos) {
    if (mask == (1 << n) - 1) {
        // All cities visited, return to starting city
        return dist[pos][0];
    }

    if (dp[mask][pos] != -1) return dp[mask][pos];

    int ans = INF;

    for (int city = 0; city < n; city++) {
        if ((mask & (1 << city)) == 0) { // If the city is not visited
            int newAns = dist[pos][city] + tsp(mask | (1 << city), city);
            ans = min(ans, newAns);
        }
    }

    return dp[mask][pos] = ans;
}

int main() {
    cout << "Enter number of cities: ";
    cin >> n;

    dist.assign(n, vector<int>(n));
    cout << "Enter the distance matrix:\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> dist[i][j];

    dp.assign(1 << n, vector<int>(n, -1));

    int minCost = tsp(1, 0); // Start from city 0 with only city 0 visited

    cout << "Minimum cost of visiting all cities: " << minCost << endl;
    return 0;
}
