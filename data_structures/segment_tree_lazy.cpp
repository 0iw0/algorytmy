/*
 * Segment Tree z Lazy Propagation (Drzewo przedziałowe z opóźnionymi aktualizacjami)
 * 
 * Rozszerzenie Segment Tree pozwalające na:
 * - Zapytania o wartość na przedziale [l, r] w czasie O(log n)
 * - Aktualizacje pojedynczego elementu w czasie O(log n)
 * - Aktualizacje całego przedziału [l, r] w czasie O(log n)
 * 
 * Zastosowanie:
 * - Suma na przedziale + dodawanie wartości do przedziału
 * - Minimum/Maksimum na przedziale + aktualizacja przedziału
 * - NWD na przedziale + aktualizacja przedziału
 * 
 * Złożoność:
 * - Pamięć: O(n)
 * - Budowanie: O(n)
 * - Zapytanie: O(log n)
 * - Aktualizacja pojedynczego elementu: O(log n)
 * - Aktualizacja przedziału: O(log n)
 */

#include <bits/stdc++.h>

using namespace std;

// Funkcja łącząca wartości (można zmienić na min, max, gcd, itp.)
int combine(int a, int b) {
    return a + b;
}

// Funkcja aplikująca aktualizację do wartości
int applyUpdate(int value, int update, int len) {
    return value + update * len; // dla sumy: dodajemy update * długość przedziału
}

// Funkcja łącząca dwie aktualizacje
int combineUpdates(int update1, int update2) {
    return update1 + update2; // dla sumy: aktualizacje się sumują
}

// Neutralny element dla operacji (0 dla sumy, INT_MAX dla min, INT_MIN dla max)
const int NEUTRAL = 0;
// Neutralna wartość dla aktualizacji (0 oznacza brak aktualizacji)
const int NO_UPDATE = 0;

vector<int> seg_tree_lazy;
vector<int> seg_lazy;
int seg_n_lazy;

void seg_lazy_build(const vector<int>& arr, int node, int start, int end) {
    if (start == end) {
        seg_tree_lazy[node] = arr[start];
    } else {
        int mid = (start + end) / 2;
        seg_lazy_build(arr, 2*node, start, mid);
        seg_lazy_build(arr, 2*node+1, mid+1, end);
        seg_tree_lazy[node] = combine(seg_tree_lazy[2*node], seg_tree_lazy[2*node+1]);
    }
}

void seg_lazy_init(const vector<int>& arr) {
    seg_n_lazy = arr.size();
    seg_tree_lazy.resize(4 * seg_n_lazy);
    seg_lazy.resize(4 * seg_n_lazy, NO_UPDATE);
    seg_lazy_build(arr, 1, 0, seg_n_lazy-1);
}

void seg_lazy_push(int node, int start, int end) {
    if (seg_lazy[node] != NO_UPDATE) {
        int len = end - start + 1;
        seg_tree_lazy[node] = applyUpdate(seg_tree_lazy[node], seg_lazy[node], len);
        
        if (start != end) {
            seg_lazy[2*node] = combineUpdates(seg_lazy[2*node], seg_lazy[node]);
            seg_lazy[2*node+1] = combineUpdates(seg_lazy[2*node+1], seg_lazy[node]);
        }
        
        seg_lazy[node] = NO_UPDATE;
    }
}

int seg_lazy_query(int node, int start, int end, int l, int r) {
    seg_lazy_push(node, start, end);
    
    if (r < start || end < l) {
        return NEUTRAL;
    }
    if (l <= start && end <= r) {
        return seg_tree_lazy[node];
    }
    
    int mid = (start + end) / 2;
    int leftRes = seg_lazy_query(2*node, start, mid, l, r);
    int rightRes = seg_lazy_query(2*node+1, mid+1, end, l, r);
    return combine(leftRes, rightRes);
}

// Zapytanie o wartość na przedziale [l, r] (0-indeksowane)
int seg_lazy_query(int l, int r) {
    return seg_lazy_query(1, 0, seg_n_lazy-1, l, r);
}

void seg_lazy_updateRange(int node, int start, int end, int l, int r, int val) {
    seg_lazy_push(node, start, end);
    
    if (r < start || end < l) {
        return;
    }
    if (l <= start && end <= r) {
        seg_lazy[node] = combineUpdates(seg_lazy[node], val);
        seg_lazy_push(node, start, end);
        return;
    }
    
    int mid = (start + end) / 2;
    seg_lazy_updateRange(2*node, start, mid, l, r, val);
    seg_lazy_updateRange(2*node+1, mid+1, end, l, r, val);
    
    seg_lazy_push(2*node, start, mid);
    seg_lazy_push(2*node+1, mid+1, end);
    seg_tree_lazy[node] = combine(seg_tree_lazy[2*node], seg_tree_lazy[2*node+1]);
}

// Aktualizacja przedziału [l, r] - dodaje val do każdego elementu (0-indeksowane)
void seg_lazy_updateRange(int l, int r, int val) {
    seg_lazy_updateRange(1, 0, seg_n_lazy-1, l, r, val);
}

void seg_lazy_update(int node, int start, int end, int idx, int val) {
    seg_lazy_push(node, start, end);
    
    if (start == end) {
        seg_tree_lazy[node] = val;
    } else {
        int mid = (start + end) / 2;
        if (idx <= mid) {
            seg_lazy_update(2*node, start, mid, idx, val);
        } else {
            seg_lazy_update(2*node+1, mid+1, end, idx, val);
        }
        seg_lazy_push(2*node, start, mid);
        seg_lazy_push(2*node+1, mid+1, end);
        seg_tree_lazy[node] = combine(seg_tree_lazy[2*node], seg_tree_lazy[2*node+1]);
    }
}

// Aktualizacja elementu na pozycji idx na wartość val (0-indeksowane)
void seg_lazy_update(int idx, int val) {
    seg_lazy_update(1, 0, seg_n_lazy-1, idx, val);
}

// Przykład użycia:
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    vector<int> arr = {1, 3, 5, 7, 9, 11};
    seg_lazy_init(arr);
    
    // Zapytanie o sumę na przedziale [1, 3]
    cout << seg_lazy_query(1, 3) << '\n'; // 3 + 5 + 7 = 15
    
    // Dodajemy 2 do każdego elementu w przedziale [1, 4]
    seg_lazy_updateRange(1, 4, 2);
    
    // Zapytanie o sumę na przedziale [1, 3]
    cout << seg_lazy_query(1, 3) << '\n'; // (3+2) + (5+2) + (7+2) = 22
    
    // Zapytanie o sumę na przedziale [0, 5]
    cout << seg_lazy_query(0, 5) << '\n'; // 1 + 5 + 7 + 9 + 11 + 11 = 44
    
    return 0;
}
