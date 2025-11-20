/*
 * Binomial Coefficient (Symbol Newtona)
 * 
 * Obliczanie współczynników dwumianowych (n choose k).
 * 
 * Zastosowanie:
 * - Kombinatoryka
 * - Prawdopodobieństwo
 * - Trójkąt Pascala
 * 
 * Złożoność:
 * - Preprocessing: O(n^2) dla tablicy
 * - Zapytanie: O(1) po preprocessingu
 * - Pojedyncze zapytanie: O(k)
 */

#include <bits/stdc++.h>

using namespace std;

vector<vector<long long>> binomial_table;

void binomial_init(int max_n) {
    binomial_table.assign(max_n + 1, vector<long long>(max_n + 1, 0));
    
    for (int n = 0; n <= max_n; n++) {
        binomial_table[n][0] = 1;
        for (int k = 1; k <= n; k++) {
            binomial_table[n][k] = binomial_table[n-1][k-1] + binomial_table[n-1][k];
        }
    }
}

long long binomial(int n, int k) {
    if (k > n || k < 0) return 0;
    if (k == 0 || k == n) return 1;
    
    k = min(k, n - k); // symetria
    
    long long result = 1;
    for (int i = 0; i < k; i++) {
        result = result * (n - i) / (i + 1);
    }
    
    return result;
}

// Modular binomial coefficient (wymaga mod_inverse z gcd_lcm.cpp lub modular_exponentiation.cpp)
// long long binomial_mod(int n, int k, long long mod) {
//     if (k > n || k < 0) return 0;
//     if (k == 0 || k == n) return 1;
//     
//     k = min(k, n - k);
//     
//     long long result = 1;
//     for (int i = 0; i < k; i++) {
//         result = (result * (n - i)) % mod;
//         result = (result * mod_inverse(i + 1, mod)) % mod;
//     }
//     
//     return result;
// }

// Przykład użycia:
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    int n, k;
    cin >> n >> k;
    
    cout << "C(" << n << ", " << k << ") = " << binomial(n, k) << '\n';
    
    return 0;
}

