/*
 * Binary Search (Wyszukiwanie binarne)
 * 
 * Algorytm wyszukiwania elementu w posortowanej tablicy.
 * 
 * Zastosowanie:
 * - Wyszukiwanie w posortowanej tablicy
 * - Binary search na odpowiedzi
 * - Znajdowanie granic (lower_bound, upper_bound)
 * 
 * Złożoność:
 * - Czas: O(log n)
 * - Pamięć: O(1)
 */

#include <bits/stdc++.h>

using namespace std;

// Wyszukiwanie elementu (zwraca indeks lub -1)
int binary_search(const vector<int>& arr, int target) {
    int left = 0, right = arr.size() - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return -1;
}

// Lower bound - pierwszy element >= target
int lower_bound_custom(const vector<int>& arr, int target) {
    int left = 0, right = arr.size();
    
    while (left < right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    
    return left;
}

// Upper bound - pierwszy element > target
int upper_bound_custom(const vector<int>& arr, int target) {
    int left = 0, right = arr.size();
    
    while (left < right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] <= target) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    
    return left;
}

// Binary search na odpowiedzi (przykład: znajdź najmniejsze x takie że f(x) >= target)
int binary_search_answer(int left, int right, int target) {
    // Funkcja f(x) - przykład
    auto f = [](int x) {
        return x * x; // przykładowa funkcja
    };
    
    while (left < right) {
        int mid = left + (right - left) / 2;
        
        if (f(mid) >= target) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    
    return left;
}

// Przykład użycia:
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    int n, target;
    cin >> n >> target;
    
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    
    sort(arr.begin(), arr.end());
    
    int idx = binary_search(arr, target);
    if (idx != -1) {
        cout << "Znaleziono na pozycji: " << idx << '\n';
    } else {
        cout << "Nie znaleziono\n";
    }
    
    int lb = lower_bound_custom(arr, target);
    int ub = upper_bound_custom(arr, target);
    cout << "Liczba wystąpień: " << ub - lb << '\n';
    
    return 0;
}

