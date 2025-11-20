/*
 * Factorization (Faktoryzacja)
 * 
 * Algorytm rozkładu liczby na czynniki pierwsze.
 * 
 * Zastosowanie:
 * - Rozkład na czynniki pierwsze
 * - Liczba dzielników
 * - Suma dzielników
 * - Euler's totient function
 * 
 * Złożoność:
 * - Czas: O(sqrt(n))
 * - Pamięć: O(1)
 */

#include <bits/stdc++.h>

using namespace std;

vector<pair<int, int>> factorize(int n) {
    vector<pair<int, int>> factors;
    
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            int count = 0;
            while (n % i == 0) {
                n /= i;
                count++;
            }
            factors.push_back({i, count});
        }
    }
    
    if (n > 1) {
        factors.push_back({n, 1});
    }
    
    return factors;
}

// Liczba dzielników
int num_divisors(int n) {
    auto factors = factorize(n);
    int result = 1;
    for (auto& [p, exp] : factors) {
        result *= (exp + 1);
    }
    return result;
}

// Suma dzielników
long long sum_divisors(int n) {
    auto factors = factorize(n);
    long long result = 1;
    for (auto& [p, exp] : factors) {
        long long sum = 1;
        long long power = 1;
        for (int i = 0; i <= exp; i++) {
            sum += power;
            power *= p;
        }
        result *= sum;
    }
    return result;
}

// Przykład użycia:
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    int n;
    cin >> n;
    
    vector<pair<int, int>> factors = factorize(n);
    
    cout << n << " = ";
    for (int i = 0; i < factors.size(); i++) {
        if (i > 0) cout << " * ";
        cout << factors[i].first;
        if (factors[i].second > 1) {
            cout << "^" << factors[i].second;
        }
    }
    cout << '\n';
    
    cout << "Liczba dzielników: " << num_divisors(n) << '\n';
    cout << "Suma dzielników: " << sum_divisors(n) << '\n';
    
    return 0;
}

