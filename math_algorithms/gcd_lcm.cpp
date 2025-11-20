/*
 * NWD (GCD) i NWW (LCM)
 * 
 * Algorytm Euklidesa do znajdowania największego wspólnego dzielnika
 * i najmniejszej wspólnej wielokrotności.
 * 
 * Zastosowanie:
 * - Upraszczanie ułamków
 * - Sprawdzanie względnej pierwszości
 * - Problemy matematyczne
 * 
 * Złożoność:
 * - Czas: O(log(min(a, b)))
 * - Pamięć: O(1)
 */

#include <bits/stdc++.h>

using namespace std;

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int gcd_recursive(int a, int b) {
    if (b == 0) return a;
    return gcd_recursive(b, a % b);
}

long long lcm(int a, int b) {
    return (long long)a * b / gcd(a, b);
}

// Rozszerzony algorytm Euklidesa
// Zwraca {gcd, x, y} takie że ax + by = gcd(a, b)
tuple<int, int, int> extended_gcd(int a, int b) {
    if (b == 0) {
        return {a, 1, 0};
    }
    
    auto [g, x1, y1] = extended_gcd(b, a % b);
    int x = y1;
    int y = x1 - (a / b) * y1;
    
    return {g, x, y};
}

// Modular inverse używając rozszerzonego algorytmu Euklidesa
// Zwraca x takie że (a * x) % m = 1
int mod_inverse(int a, int m) {
    auto [g, x, y] = extended_gcd(a, m);
    if (g != 1) {
        return -1; // nie istnieje
    }
    return (x % m + m) % m;
}

// Przykład użycia:
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    int a, b;
    cin >> a >> b;
    
    cout << "NWD(" << a << ", " << b << ") = " << gcd(a, b) << '\n';
    cout << "NWW(" << a << ", " << b << ") = " << lcm(a, b) << '\n';
    
    auto [g, x, y] = extended_gcd(a, b);
    cout << "Rozszerzony NWD: " << a << "*" << x << " + " << b << "*" << y << " = " << g << '\n';
    
    return 0;
}

