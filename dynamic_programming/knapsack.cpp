/*
 * Knapsack Problem (Problem plecakowy)
 * 
 * Algorytm rozwiązujący problem plecakowy (0/1 i unbounded).
 * 
 * Zastosowanie:
 * - Optymalizacja zasobów
 * - Problemy decyzyjne
 * - Resource allocation
 * 
 * Złożoność:
 * - 0/1 Knapsack: O(n * W) gdzie n to liczba przedmiotów, W to pojemność
 * - Unbounded Knapsack: O(n * W)
 * - Pamięć: O(W) - zoptymalizowana wersja
 */

#include <bits/stdc++.h>

using namespace std;

// 0/1 Knapsack - każdy przedmiot można użyć co najwyżej raz
int knapsack_01(int capacity, const vector<int>& weights, const vector<int>& values) {
    int n = weights.size();
    vector<int> dp(capacity + 1, 0);
    
    for (int i = 0; i < n; i++) {
        for (int w = capacity; w >= weights[i]; w--) {
            dp[w] = max(dp[w], dp[w - weights[i]] + values[i]);
        }
    }
    
    return dp[capacity];
}

// Unbounded Knapsack - każdy przedmiot można użyć dowolną liczbę razy
int knapsack_unbounded(int capacity, const vector<int>& weights, const vector<int>& values) {
    int n = weights.size();
    vector<int> dp(capacity + 1, 0);
    
    for (int w = 1; w <= capacity; w++) {
        for (int i = 0; i < n; i++) {
            if (weights[i] <= w) {
                dp[w] = max(dp[w], dp[w - weights[i]] + values[i]);
            }
        }
    }
    
    return dp[capacity];
}

// Przykład użycia:
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    int n, capacity;
    cin >> n >> capacity;
    
    vector<int> weights(n), values(n);
    for (int i = 0; i < n; i++) {
        cin >> weights[i] >> values[i];
    }
    
    cout << "0/1 Knapsack: " << knapsack_01(capacity, weights, values) << '\n';
    cout << "Unbounded Knapsack: " << knapsack_unbounded(capacity, weights, values) << '\n';
    
    return 0;
}

