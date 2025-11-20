/*
 * LCS (Longest Common Subsequence)
 * 
 * Algorytm znajdowania najdłuższego wspólnego podciągu dwóch stringów.
 * 
 * Zastosowanie:
 * - Porównywanie stringów
 * - Diff algorithms
 * - DNA sequence alignment
 * 
 * Złożoność:
 * - Czas: O(n * m) gdzie n, m to długości stringów
 * - Pamięć: O(n * m) - można zoptymalizować do O(min(n, m))
 */

#include <bits/stdc++.h>

using namespace std;

int lcs_length(const string& s1, const string& s2) {
    int n = s1.size();
    int m = s2.size();
    
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (s1[i-1] == s2[j-1]) {
                dp[i][j] = dp[i-1][j-1] + 1;
            } else {
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }
    
    return dp[n][m];
}

string lcs_string(const string& s1, const string& s2) {
    int n = s1.size();
    int m = s2.size();
    
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (s1[i-1] == s2[j-1]) {
                dp[i][j] = dp[i-1][j-1] + 1;
            } else {
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }
    
    // Rekonstrukcja stringa
    string result = "";
    int i = n, j = m;
    
    while (i > 0 && j > 0) {
        if (s1[i-1] == s2[j-1]) {
            result = s1[i-1] + result;
            i--;
            j--;
        } else if (dp[i-1][j] > dp[i][j-1]) {
            i--;
        } else {
            j--;
        }
    }
    
    return result;
}

// Przykład użycia:
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    string s1, s2;
    cin >> s1 >> s2;
    
    cout << "Długość LCS: " << lcs_length(s1, s2) << '\n';
    cout << "LCS: " << lcs_string(s1, s2) << '\n';
    
    return 0;
}

