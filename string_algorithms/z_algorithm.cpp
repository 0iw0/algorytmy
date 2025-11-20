/*
 * Z-Algorithm
 * 
 * Algorytm znajdowania najdłuższego prefiksu stringa, który jest również sufiksem
 * dla każdej pozycji w stringu.
 * 
 * Zastosowanie:
 * - Wyszukiwanie wzorca w tekście (podobne do KMP)
 * - Znajdowanie wszystkich wystąpień wzorca
 * - Longest prefix matching
 * 
 * Złożoność:
 * - Czas: O(n + m) gdzie n to długość tekstu, m to długość wzorca
 * - Pamięć: O(n + m)
 */

#include <bits/stdc++.h>

using namespace std;

vector<int> z_array;

void z_build(const string& s) {
    int n = s.size();
    z_array.assign(n, 0);
    
    int l = 0, r = 0;
    for (int i = 1; i < n; i++) {
        if (i <= r) {
            z_array[i] = min(r - i + 1, z_array[i - l]);
        }
        while (i + z_array[i] < n && s[z_array[i]] == s[i + z_array[i]]) {
            z_array[i]++;
        }
        if (i + z_array[i] - 1 > r) {
            l = i;
            r = i + z_array[i] - 1;
        }
    }
}

vector<int> z_search(const string& text, const string& pattern) {
    string combined = pattern + "$" + text;
    z_build(combined);
    
    vector<int> occurrences;
    int m = pattern.size();
    
    for (int i = m + 1; i < combined.size(); i++) {
        if (z_array[i] == m) {
            occurrences.push_back(i - m - 1);
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
    
    vector<int> occurrences = z_search(text, pattern);
    
    cout << "Znaleziono " << occurrences.size() << " wystąpień:\n";
    for (int pos : occurrences) {
        cout << pos << " ";
    }
    cout << '\n';
    
    return 0;
}

