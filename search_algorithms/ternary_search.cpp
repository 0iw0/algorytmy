/*
 * Ternary Search
 * 
 * Algorytm znajdowania minimum/maksimum funkcji unimodalnej.
 * 
 * Zastosowanie:
 * - Funkcje unimodalne (jedno ekstremum)
 * - Optymalizacja
 * - Problemy geometryczne
 * 
 * Złożoność:
 * - Czas: O(log n) gdzie n to zakres
 * - Pamięć: O(1)
 * 
 * Uwaga:
 * - Funkcja musi być unimodalna (jedno minimum/maksimum)
 */

#include <bits/stdc++.h>

using namespace std;

// Znajdź minimum funkcji unimodalnej na przedziale [left, right]
double ternary_search_min(double left, double right, double epsilon = 1e-9) {
    // Przykładowa funkcja - można zmienić
    auto f = [](double x) {
        return (x - 2) * (x - 2) + 1; // minimum w x = 2
    };
    
    while (right - left > epsilon) {
        double m1 = left + (right - left) / 3;
        double m2 = right - (right - left) / 3;
        
        if (f(m1) < f(m2)) {
            right = m2;
        } else {
            left = m1;
        }
    }
    
    return (left + right) / 2;
}

// Znajdź maksimum funkcji unimodalnej na przedziale [left, right]
double ternary_search_max(double left, double right, double epsilon = 1e-9) {
    // Przykładowa funkcja - można zmienić
    auto f = [](double x) {
        return -(x - 2) * (x - 2) + 1; // maksimum w x = 2
    };
    
    while (right - left > epsilon) {
        double m1 = left + (right - left) / 3;
        double m2 = right - (right - left) / 3;
        
        if (f(m1) > f(m2)) {
            right = m2;
        } else {
            left = m1;
        }
    }
    
    return (left + right) / 2;
}

// Dla funkcji całkowitoliczbowych
int ternary_search_int(int left, int right) {
    // Przykładowa funkcja - można zmienić
    auto f = [](int x) {
        return abs(x - 10); // minimum w x = 10
    };
    
    while (right - left > 2) {
        int m1 = left + (right - left) / 3;
        int m2 = right - (right - left) / 3;
        
        if (f(m1) < f(m2)) {
            right = m2;
        } else {
            left = m1;
        }
    }
    
    int best = left;
    for (int i = left; i <= right; i++) {
        if (f(i) < f(best)) {
            best = i;
        }
    }
    
    return best;
}

// Przykład użycia:
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    double min_x = ternary_search_min(0, 10);
    cout << "Minimum funkcji w x = " << min_x << '\n';
    
    return 0;
}

