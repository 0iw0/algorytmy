/*
 * Edit Distance (Levenshtein Distance)
 * 
 * Algorytm obliczania minimalnej liczby operacji potrzebnych do przekształcenia
 * jednego stringa w drugi (wstawianie, usuwanie, zamiana).
 * 
 * Zastosowanie:
 * - Porównywanie stringów
 * - Spell checking
 * - DNA sequence alignment
 * 
 * Złożoność:
 * - Czas: O(n * m) gdzie n, m to długości stringów
 * - Pamięć: O(n * m) - można zoptymalizować do O(min(n, m))
 */

#include <bits/stdc++.h>

using namespace std;

int edit_distance(const string& s1, const string& s2) {
    int n = s1.size();
    int m = s2.size();
    
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    
    // Inicjalizacja
    for (int i = 0; i <= n; i++) {
        dp[i][0] = i; // usuwanie wszystkich znaków z s1
    }
    for (int j = 0; j <= m; j++) {
        dp[0][j] = j; // wstawianie wszystkich znaków do s1
    }
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (s1[i-1] == s2[j-1]) {
                dp[i][j] = dp[i-1][j-1]; // bez zmian
            } else {
                dp[i][j] = 1 + min({
                    dp[i-1][j],     // usunięcie
                    dp[i][j-1],     // wstawienie
                    dp[i-1][j-1]    // zamiana
                });
            }
        }
    }
    
    return dp[n][m];
}

// Przykład użycia:
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    string s1, s2;
    cin >> s1 >> s2;
    
    cout << "Edit distance: " << edit_distance(s1, s2) << '\n';
    
    return 0;
}

