/*
 * Sieve of Eratosthenes (Sito Eratostenesa)
 * 
 * Algorytm znajdowania wszystkich liczb pierwszych do n.
 * 
 * Zastosowanie:
 * - Lista liczb pierwszych
 * - Sprawdzanie pierwszości
 * - Faktoryzacja (z modyfikacją)
 * 
 * Złożoność:
 * - Czas: O(n log log n)
 * - Pamięć: O(n)
 */

#include <bits/stdc++.h>

using namespace std;

vector<bool> sieve_is_prime;
vector<int> sieve_primes;

void sieve(int n) {
    sieve_is_prime.assign(n + 1, true);
    sieve_is_prime[0] = sieve_is_prime[1] = false;
    sieve_primes.clear();
    
    for (int i = 2; i * i <= n; i++) {
        if (sieve_is_prime[i]) {
            for (int j = i * i; j <= n; j += i) {
                sieve_is_prime[j] = false;
            }
        }
    }
    
    for (int i = 2; i <= n; i++) {
        if (sieve_is_prime[i]) {
            sieve_primes.push_back(i);
        }
    }
}

// Sprawdzanie pierwszości pojedynczej liczby
bool is_prime(int n) {
    if (n < 2) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    
    for (int i = 3; i * i <= n; i += 2) {
        if (n % i == 0) return false;
    }
    return true;
}

// Przykład użycia:
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    int n;
    cin >> n;
    
    sieve(n);
    
    cout << "Liczby pierwsze do " << n << ":\n";
    for (int p : sieve_primes) {
        cout << p << " ";
    }
    cout << '\n';
    
    return 0;
}

