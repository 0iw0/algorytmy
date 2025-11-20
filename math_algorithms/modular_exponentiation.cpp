/*
 * Modular Exponentiation (Potęgowanie modularne)
 * 
 * Algorytm szybkiego potęgowania modulo.
 * 
 * Zastosowanie:
 * - Duże potęgi modulo
 * - RSA encryption
 * - Modular arithmetic
 * 
 * Złożoność:
 * - Czas: O(log exponent)
 * - Pamięć: O(1)
 */

#include <bits/stdc++.h>

using namespace std;

long long mod_pow(long long base, long long exponent, long long mod) {
    long long result = 1;
    base %= mod;
    
    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exponent /= 2;
    }
    
    return result;
}

// Modular inverse używając małego twierdzenia Fermata
// Działa tylko gdy mod jest liczbą pierwszą
long long mod_inverse_fermat(long long a, long long mod) {
    return mod_pow(a, mod - 2, mod);
}

// Przykład użycia:
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    long long base, exponent, mod;
    cin >> base >> exponent >> mod;
    
    cout << base << "^" << exponent << " mod " << mod << " = ";
    cout << mod_pow(base, exponent, mod) << '\n';
    
    return 0;
}

