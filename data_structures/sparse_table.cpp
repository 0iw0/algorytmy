/*
 * Sparse Table
 * 
 * Struktura danych pozwalająca na:
 * - Zapytania RMQ (Range Minimum Query) w czasie O(1) po O(n log n) preprocessingu
 * - Działa dla operacji idempotentnych (min, max, gcd, AND, OR)
 * 
 * Zastosowanie:
 * - Minimum/Maksimum na przedziale
 * - NWD na przedziale
 * - Operacje bitowe na przedziale
 * 
 * Złożoność:
 * - Pamięć: O(n log n)
 * - Preprocessing: O(n log n)
 * - Zapytanie: O(1)
 * 
 * Uwaga:
 * - Nie obsługuje aktualizacji (statyczna struktura)
 * - Działa tylko dla operacji idempotentnych
 */

#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> sparse_table;
vector<int> sparse_log;
int sparse_n;

// Funkcja łącząca wartości (min, max, gcd, itp.)
int sparse_combine(int a, int b) {
    return min(a, b); // dla RMQ - minimum
}

void sparse_init(const vector<int>& arr) {
    sparse_n = arr.size();
    int max_log = 0;
    while ((1 << max_log) <= sparse_n) {
        max_log++;
    }
    
    sparse_table.assign(max_log, vector<int>(sparse_n));
    sparse_log.resize(sparse_n + 1);
    
    // Precompute logarytmy
    sparse_log[1] = 0;
    for (int i = 2; i <= sparse_n; i++) {
        sparse_log[i] = sparse_log[i / 2] + 1;
    }
    
    // Pierwsza warstwa to oryginalna tablica
    for (int i = 0; i < sparse_n; i++) {
        sparse_table[0][i] = arr[i];
    }
    
    // Budowanie tabeli
    for (int j = 1; j < max_log; j++) {
        for (int i = 0; i + (1 << j) <= sparse_n; i++) {
            sparse_table[j][i] = sparse_combine(
                sparse_table[j-1][i],
                sparse_table[j-1][i + (1 << (j-1))]
            );
        }
    }
}

// Zapytanie o wartość na przedziale [l, r] (0-indeksowane, zamknięty przedział)
int sparse_query(int l, int r) {
    int j = sparse_log[r - l + 1];
    return sparse_combine(sparse_table[j][l], sparse_table[j][r - (1 << j) + 1]);
}

// Przykład użycia:
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    vector<int> arr = {1, 3, 2, 7, 9, 11, 5, 6};
    sparse_init(arr);
    
    // Zapytanie o minimum na przedziale [1, 4]
    cout << sparse_query(1, 4) << '\n'; // min(3, 2, 7, 9) = 2
    
    // Zapytanie o minimum na przedziale [0, 7]
    cout << sparse_query(0, 7) << '\n'; // min całej tablicy = 1
    
    return 0;
}

