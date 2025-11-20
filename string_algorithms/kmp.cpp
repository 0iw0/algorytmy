/*
 * KMP (Knuth-Morris-Pratt) Algorithm
 * 
 * Algorytm wyszukiwania wzorca w tekście w czasie liniowym.
 * 
 * Zastosowanie:
 * - Wyszukiwanie wzorca w tekście
 * - Znajdowanie wszystkich wystąpień wzorca
 * - Longest prefix which is also suffix
 * 
 * Złożoność:
 * - Preprocessing: O(m) gdzie m to długość wzorca
 * - Wyszukiwanie: O(n) gdzie n to długość tekstu
 * - Całkowita: O(n + m)
 */

#include <bits/stdc++.h>

using namespace std;

vector<int> kmp_prefix;

void kmp_build_prefix(const string& pattern) {
    int m = pattern.size();
    kmp_prefix.assign(m, 0);
    
    int j = 0;
    for (int i = 1; i < m; i++) {
        while (j > 0 && pattern[i] != pattern[j]) {
            j = kmp_prefix[j - 1];
        }
        if (pattern[i] == pattern[j]) {
            j++;
        }
        kmp_prefix[i] = j;
    }
}

vector<int> kmp_search(const string& text, const string& pattern) {
    kmp_build_prefix(pattern);
    
    vector<int> occurrences;
    int n = text.size();
    int m = pattern.size();
    int j = 0;
    
    for (int i = 0; i < n; i++) {
        while (j > 0 && text[i] != pattern[j]) {
            j = kmp_prefix[j - 1];
        }
        if (text[i] == pattern[j]) {
            j++;
        }
        if (j == m) {
            occurrences.push_back(i - m + 1);
            j = kmp_prefix[j - 1];
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
    
    vector<int> occurrences = kmp_search(text, pattern);
    
    cout << "Znaleziono " << occurrences.size() << " wystąpień:\n";
    for (int pos : occurrences) {
        cout << pos << " ";
    }
    cout << '\n';
    
    return 0;
}

