/*
 * Segment Tree (Drzewo przedziałowe)
 * 
 * Struktura danych pozwalająca na:
 * - Zapytania o wartość na przedziale [l, r] w czasie O(log n)
 * - Aktualizacje pojedynczego elementu w czasie O(log n)
 * 
 * Zastosowanie:
 * - Suma na przedziale
 * - Minimum/Maksimum na przedziale
 * - NWD na przedziale
 * - Dowolna operacja łączna (associative operation)
 * 
 * Złożoność:
 * - Pamięć: O(n)
 * - Budowanie: O(n)
 * - Zapytanie: O(log n)
 * - Aktualizacja: O(log n)
 */

#include <bits/stdc++.h>

using namespace std;

// Funkcja łącząca wartości (można zmienić na min, max, gcd, itp.)
int combine(int a, int b) {
    return a + b;
}

// Neutralny element dla operacji (0 dla sumy, INT_MAX dla min, INT_MIN dla max)
const int NEUTRAL = 0;

vector<int> seg_tree;
int seg_n;

void seg_build(const vector<int>& arr, int node, int start, int end) {
    if (start == end) {
        seg_tree[node] = arr[start];
    } else {
        int mid = (start + end) / 2;
        seg_build(arr, 2*node, start, mid);
        seg_build(arr, 2*node+1, mid+1, end);
        seg_tree[node] = combine(seg_tree[2*node], seg_tree[2*node+1]);
    }
}

void seg_init(const vector<int>& arr) {
    seg_n = arr.size();
    seg_tree.resize(4 * seg_n);
    seg_build(arr, 1, 0, seg_n-1);
}

int seg_query(int node, int start, int end, int l, int r) {
    if (r < start || end < l) {
        return NEUTRAL;
    }
    if (l <= start && end <= r) {
        return seg_tree[node];
    }
    int mid = (start + end) / 2;
    int leftRes = seg_query(2*node, start, mid, l, r);
    int rightRes = seg_query(2*node+1, mid+1, end, l, r);
    return combine(leftRes, rightRes);
}

// Zapytanie o wartość na przedziale [l, r] (0-indeksowane)
int seg_query(int l, int r) {
    return seg_query(1, 0, seg_n-1, l, r);
}

void seg_update(int node, int start, int end, int idx, int val) {
    if (start == end) {
        seg_tree[node] = val;
    } else {
        int mid = (start + end) / 2;
        if (idx <= mid) {
            seg_update(2*node, start, mid, idx, val);
        } else {
            seg_update(2*node+1, mid+1, end, idx, val);
        }
        seg_tree[node] = combine(seg_tree[2*node], seg_tree[2*node+1]);
    }
}

// Aktualizacja elementu na pozycji idx na wartość val (0-indeksowane)
void seg_update(int idx, int val) {
    seg_update(1, 0, seg_n-1, idx, val);
}

// Przykład użycia:
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    vector<int> arr = {1, 3, 5, 7, 9, 11};
    seg_init(arr);
    
    // Zapytanie o sumę na przedziale [1, 3]
    cout << seg_query(1, 3) << '\n'; // 3 + 5 + 7 = 15
    
    // Aktualizacja elementu na pozycji 2
    seg_update(2, 10);
    
    // Zapytanie o sumę na przedziale [0, 4]
    cout << seg_query(0, 4) << '\n'; // 1 + 3 + 10 + 7 + 9 = 30
    
    return 0;
}
