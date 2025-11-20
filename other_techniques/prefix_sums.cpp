/*
 * Prefix Sums (Sumy prefiksowe)
 * 
 * Technika sum prefiksowych do szybkich zapytań o sumę na przedziale.
 * 
 * Zastosowanie:
 * - Suma na przedziale w O(1)
 * - Cumulative sums
 * - Range sum queries
 * 
 * Złożoność:
 * - Preprocessing: O(n)
 * - Zapytanie: O(1)
 * - Pamięć: O(n)
 */

#include <bits/stdc++.h>

using namespace std;

vector<long long> prefix_sum;

void prefix_init(const vector<int>& arr) {
    int n = arr.size();
    prefix_sum.resize(n + 1, 0);
    
    for (int i = 0; i < n; i++) {
        prefix_sum[i + 1] = prefix_sum[i] + arr[i];
    }
}

// Suma na przedziale [l, r] (0-indeksowane, zamknięty przedział)
long long prefix_query(int l, int r) {
    return prefix_sum[r + 1] - prefix_sum[l];
}

// 2D Prefix Sums
vector<vector<long long>> prefix_2d;

void prefix_2d_init(const vector<vector<int>>& matrix) {
    int n = matrix.size();
    int m = matrix[0].size();
    
    prefix_2d.assign(n + 1, vector<long long>(m + 1, 0));
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            prefix_2d[i + 1][j + 1] = prefix_2d[i][j + 1] + 
                                      prefix_2d[i + 1][j] - 
                                      prefix_2d[i][j] + 
                                      matrix[i][j];
        }
    }
}

// Suma w prostokącie [r1, c1] do [r2, c2] (0-indeksowane)
long long prefix_2d_query(int r1, int c1, int r2, int c2) {
    return prefix_2d[r2 + 1][c2 + 1] - 
           prefix_2d[r1][c2 + 1] - 
           prefix_2d[r2 + 1][c1] + 
           prefix_2d[r1][c1];
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
    
    prefix_init(arr);
    
    int l, r;
    cin >> l >> r;
    l--; r--; // 0-indeksowanie
    
    cout << "Suma na przedziale [" << l << ", " << r << "]: " 
         << prefix_query(l, r) << '\n';
    
    return 0;
}

