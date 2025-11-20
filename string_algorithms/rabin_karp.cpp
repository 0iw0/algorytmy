/*
 * Rabin-Karp Algorithm
 * 
 * Algorytm wyszukiwania wzorca w tekście używający hashowania.
 * 
 * Zastosowanie:
 * - Wyszukiwanie wzorca w tekście
 * - Wyszukiwanie wielu wzorców jednocześnie
 * - Rolling hash dla substringów
 * 
 * Złożoność:
 * - Średni czas: O(n + m) gdzie n to długość tekstu, m to długość wzorca
 * - Najgorszy czas: O(n * m) (rzadko)
 * - Pamięć: O(1)
 * 
 * Uwaga:
 * - Może mieć kolizje hashów (użyj podwójnego hashowania dla pewności)
 */

#include <bits/stdc++.h>

using namespace std;

const int BASE = 256;
const int MOD1 = 1e9 + 7;
const int MOD2 = 1e9 + 9;

long long rk_power1, rk_power2;

vector<int> rabin_karp(const string& text, const string& pattern) {
    int n = text.size();
    int m = pattern.size();
    
    if (m > n) return {};
    
    // Obliczanie potęg BASE
    rk_power1 = 1;
    rk_power2 = 1;
    for (int i = 0; i < m - 1; i++) {
        rk_power1 = (rk_power1 * BASE) % MOD1;
        rk_power2 = (rk_power2 * BASE) % MOD2;
    }
    
    // Hash wzorca
    long long hash_pattern1 = 0, hash_pattern2 = 0;
    for (int i = 0; i < m; i++) {
        hash_pattern1 = (hash_pattern1 * BASE + pattern[i]) % MOD1;
        hash_pattern2 = (hash_pattern2 * BASE + pattern[i]) % MOD2;
    }
    
    // Hash pierwszego okna w tekście
    long long hash_text1 = 0, hash_text2 = 0;
    for (int i = 0; i < m; i++) {
        hash_text1 = (hash_text1 * BASE + text[i]) % MOD1;
        hash_text2 = (hash_text2 * BASE + text[i]) % MOD2;
    }
    
    vector<int> occurrences;
    
    // Sprawdzenie pierwszego okna
    if (hash_text1 == hash_pattern1 && hash_text2 == hash_pattern2) {
        if (text.substr(0, m) == pattern) {
            occurrences.push_back(0);
        }
    }
    
    // Rolling hash
    for (int i = m; i < n; i++) {
        // Usuń pierwszy znak, dodaj nowy
        hash_text1 = (hash_text1 - text[i - m] * rk_power1) % MOD1;
        hash_text1 = (hash_text1 * BASE + text[i]) % MOD1;
        if (hash_text1 < 0) hash_text1 += MOD1;
        
        hash_text2 = (hash_text2 - text[i - m] * rk_power2) % MOD2;
        hash_text2 = (hash_text2 * BASE + text[i]) % MOD2;
        if (hash_text2 < 0) hash_text2 += MOD2;
        
        if (hash_text1 == hash_pattern1 && hash_text2 == hash_pattern2) {
            if (text.substr(i - m + 1, m) == pattern) {
                occurrences.push_back(i - m + 1);
            }
        }
    }
    
    return occurrences;
}

// Przykład użycia:
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    string text, pattern;
    cin >> text >> pattern;
    
    vector<int> occurrences = rabin_karp(text, pattern);
    
    cout << "Znaleziono " << occurrences.size() << " wystąpień:\n";
    for (int pos : occurrences) {
        cout << pos << " ";
    }
    cout << '\n';
    
    return 0;
}

