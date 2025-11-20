/*
 * Fenwick Tree (Binary Indexed Tree, BIT)
 * 
 * Struktura danych pozwalająca na:
 * - Zapytania o sumę prefiksową [0, idx] w czasie O(log n)
 * - Aktualizacje pojedynczego elementu w czasie O(log n)
 * 
 * Zastosowanie:
 * - Suma prefiksowa z aktualizacjami
 * - Inwersje w permutacji
 * - Liczenie elementów mniejszych/większych
 * - Zapytania o sumę na przedziale [l, r] (jako query(r) - query(l-1))
 * 
 * Zalety w porównaniu do Segment Tree:
 * - Prostsza implementacja
 * - Mniejsza stała w złożoności
 * - Mniej pamięci (n zamiast 4n)
 * 
 * Wady:
 * - Tylko operacje łączne z odwrotnością (suma, nie min/max)
 * - Tylko aktualizacje pojedynczych elementów (nie przedziałów)
 * 
 * Złożoność:
 * - Pamięć: O(n)
 * - Budowanie: O(n log n) lub O(n) z optymalizacją
 * - Zapytanie: O(log n)
 * - Aktualizacja: O(log n)
 */

#include <bits/stdc++.h>

using namespace std;

vector<int> fenw_tree;
int fenw_n;

// Funkcja zwracająca ostatni ustawiony bit w liczbie
// np. fenw_lsb(12) = fenw_lsb(1100) = 4 (100)
int fenw_lsb(int x) {
    return x & -x;
}

void fenw_init(int size) {
    fenw_n = size;
    fenw_tree.resize(fenw_n + 1, 0);
}

void fenw_init(const vector<int>& arr) {
    fenw_n = arr.size();
    fenw_tree.resize(fenw_n + 1, 0);
    for (int i = 0; i < fenw_n; i++) {
        fenw_update(i, arr[i]);
    }
}

// Aktualizacja elementu na pozycji idx - dodaje val (0-indeksowane)
void fenw_update(int idx, int val) {
    idx++; // przejście na 1-indeksowanie
    while (idx <= fenw_n) {
        fenw_tree[idx] += val;
        idx += fenw_lsb(idx);
    }
}

// Zapytanie o sumę prefiksową [0, idx] (0-indeksowane)
int fenw_query(int idx) {
    idx++; // przejście na 1-indeksowanie
    int sum = 0;
    while (idx > 0) {
        sum += fenw_tree[idx];
        idx -= fenw_lsb(idx);
    }
    return sum;
}

// Zapytanie o sumę na przedziale [l, r] (0-indeksowane)
int fenw_queryRange(int l, int r) {
    if (l == 0) {
        return fenw_query(r);
    }
    return fenw_query(r) - fenw_query(l - 1);
}

// Zwraca wartość elementu na pozycji idx (0-indeksowane)
int fenw_get(int idx) {
    return fenw_queryRange(idx, idx);
}

// Ustawia wartość elementu na pozycji idx na val (0-indeksowane)
void fenw_set(int idx, int val) {
    int current = fenw_get(idx);
    fenw_update(idx, val - current);
}

// Przykład użycia:
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    vector<int> arr = {1, 3, 5, 7, 9, 11};
    fenw_init(arr);
    
    // Zapytanie o sumę prefiksową [0, 3]
    cout << fenw_query(3) << '\n'; // 1 + 3 + 5 + 7 = 16
    
    // Zapytanie o sumę na przedziale [1, 3]
    cout << fenw_queryRange(1, 3) << '\n'; // 3 + 5 + 7 = 15
    
    // Aktualizacja - dodajemy 2 do elementu na pozycji 2
    fenw_update(2, 2);
    
    // Zapytanie o sumę na przedziale [0, 4]
    cout << fenw_query(4) << '\n'; // 1 + 3 + (5+2) + 7 + 9 = 27
    
    // Ustawienie wartości elementu na pozycji 1 na 10
    fenw_set(1, 10);
    
    // Zapytanie o sumę na przedziale [0, 2]
    cout << fenw_query(2) << '\n'; // 1 + 10 + 7 = 18
    
    return 0;
}
