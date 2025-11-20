/*
 * Two Pointers Technique
 * 
 * Technika dwóch wskaźników do rozwiązywania problemów na tablicach/listach.
 * 
 * Zastosowanie:
 * - Suma na przedziale
 * - Usuwanie duplikatów
 * - Merging sorted arrays
 * - Sliding window problems
 * 
 * Złożoność:
 * - Czas: O(n) - liniowy
 * - Pamięć: O(1)
 */

#include <bits/stdc++.h>

using namespace std;

// Znajdź parę elementów o sumie równej target w posortowanej tablicy
pair<int, int> two_sum(const vector<int>& arr, int target) {
    int left = 0, right = arr.size() - 1;
    
    while (left < right) {
        int sum = arr[left] + arr[right];
        
        if (sum == target) {
            return {left, right};
        } else if (sum < target) {
            left++;
        } else {
            right--;
        }
    }
    
    return {-1, -1}; // nie znaleziono
}

// Usuwanie duplikatów z posortowanej tablicy
vector<int> remove_duplicates(const vector<int>& arr) {
    if (arr.empty()) return {};
    
    vector<int> result;
    result.push_back(arr[0]);
    
    for (int i = 1; i < arr.size(); i++) {
        if (arr[i] != arr[i-1]) {
            result.push_back(arr[i]);
        }
    }
    
    return result;
}

// Merging dwóch posortowanych tablic
vector<int> merge_sorted(const vector<int>& arr1, const vector<int>& arr2) {
    vector<int> result;
    int i = 0, j = 0;
    
    while (i < arr1.size() && j < arr2.size()) {
        if (arr1[i] <= arr2[j]) {
            result.push_back(arr1[i++]);
        } else {
            result.push_back(arr2[j++]);
        }
    }
    
    while (i < arr1.size()) {
        result.push_back(arr1[i++]);
    }
    while (j < arr2.size()) {
        result.push_back(arr2[j++]);
    }
    
    return result;
}

// Najdłuższy podciąg bez powtórzeń
int longest_unique_substring(const string& s) {
    vector<int> last_occurrence(256, -1);
    int max_len = 0;
    int start = 0;
    
    for (int end = 0; end < s.size(); end++) {
        if (last_occurrence[s[end]] >= start) {
            start = last_occurrence[s[end]] + 1;
        }
        last_occurrence[s[end]] = end;
        max_len = max(max_len, end - start + 1);
    }
    
    return max_len;
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
    
    auto result = two_sum(arr, target);
    if (result.first != -1) {
        cout << "Znaleziono parę: " << arr[result.first] << " + " 
             << arr[result.second] << " = " << target << '\n';
    }
    
    return 0;
}

