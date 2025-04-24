#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Function to find LCS and also return the LCS string
string LCS(const string &X, const string &Y) {
    int m = X.length();
    int n = Y.length();

    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    // Build dp table
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (X[i - 1] == Y[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    int i = m, j = n;
    string lcs = "";

    while (i > 0 && j > 0) {
        if (X[i - 1] == Y[j - 1]) {
            lcs = X[i - 1] + lcs;  // prepend character
            i--; j--;
        } else if (dp[i - 1][j] > dp[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }

    // Output length and LCS string
    cout << "Length of LCS: " << dp[m][n] << endl;
    cout << "LCS string: " << lcs << endl;

    return lcs;
}

// Main driver code
int main() {
    string str1 = "AGGTAB";
    string str2 = "GXTXAYB";

    LCS(str1, str2);

    return 0;
}
