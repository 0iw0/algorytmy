/*
 * LIS (Longest Increasing Subsequence)
 * 
 * Algorytm znajdowania najdłuższego rosnącego podciągu.
 * 
 * Zastosowanie:
 * - Najdłuższy rosnący podciąg
 * - Problemy optymalizacyjne
 * - DP problems
 * 
 * Złożoność:
 * - Czas: O(n log n) - optymalna wersja
 * - Pamięć: O(n)
 */

#include <bits/stdc++.h>

using namespace std;

// O(n log n) - optymalna wersja
int lis_optimal(const vector<int>& arr) {
    int n = arr.size();
    vector<int> tail;
    
    for (int i = 0; i < n; i++) {
        auto it = lower_bound(tail.begin(), tail.end(), arr[i]);
        if (it == tail.end()) {
            tail.push_back(arr[i]);
        } else {
            *it = arr[i];
        }
    }
    
    return tail.size();
}

// O(n^2) - wersja z DP (zwraca również podciąg)
vector<int> lis_dp(const vector<int>& arr) {
    int n = arr.size();
    vector<int> dp(n, 1);
    vector<int> parent(n, -1);
    
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[j] < arr[i] && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
                parent[i] = j;
            }
        }
    }
    
    int max_idx = 0;
    for (int i = 1; i < n; i++) {
        if (dp[i] > dp[max_idx]) {
            max_idx = i;
        }
    }
    
    vector<int> result;
    int current = max_idx;
    while (current != -1) {
        result.push_back(arr[current]);
        current = parent[current];
    }
    reverse(result.begin(), result.end());
    
    return result;
}

// Przykład użycia:
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    int n;
    cin >> n;
    
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    
    cout << "Długość LIS: " << lis_optimal(arr) << '\n';
    
    vector<int> lis_seq = lis_dp(arr);
    cout << "LIS: ";
    for (int x : lis_seq) {
        cout << x << " ";
    }
    cout << '\n';
    
    return 0;
}

