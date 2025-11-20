/*
 * Manacher's Algorithm
 * 
 * Algorytm znajdowania najdłuższego palindromu w stringu w czasie liniowym.
 * 
 * Zastosowanie:
 * - Najdłuższy palindrom w stringu
 * - Wszystkie palindromy w stringu
 * - Liczenie palindromów
 * 
 * Złożoność:
 * - Czas: O(n) gdzie n to długość stringa
 * - Pamięć: O(n)
 */

#include <bits/stdc++.h>

using namespace std;

string manacher_preprocess(const string& s) {
    string result = "#";
    for (char c : s) {
        result += c;
        result += "#";
    }
    return result;
}

pair<int, int> manacher_longest_palindrome(const string& s) {
    string t = manacher_preprocess(s);
    int n = t.size();
    
    vector<int> p(n, 0);
    int center = 0, right = 0;
    int max_len = 0, max_center = 0;
    
    for (int i = 1; i < n - 1; i++) {
        int mirror = 2 * center - i;
        
        if (i < right) {
            p[i] = min(right - i, p[mirror]);
        }
        
        // Rozszerz palindrom
        while (i + p[i] + 1 < n && i - p[i] - 1 >= 0 &&
               t[i + p[i] + 1] == t[i - p[i] - 1]) {
            p[i]++;
        }
        
        if (i + p[i] > right) {
            center = i;
            right = i + p[i];
        }
        
        if (p[i] > max_len) {
            max_len = p[i];
            max_center = i;
        }
    }
    
    int start = (max_center - max_len) / 2;
    return {start, max_len};
}

// Przykład użycia:
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    string s;
    cin >> s;
    
    auto result = manacher_longest_palindrome(s);
    int start = result.first;
    int len = result.second;
    
    cout << "Najdłuższy palindrom: " << s.substr(start, len) << '\n';
    cout << "Długość: " << len << '\n';
    
    return 0;
}

