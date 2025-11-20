/*
 * Mo's Algorithm
 * 
 * Algorytm do odpowiedzi na zapytania offline na przedziałach.
 * 
 * Zastosowanie:
 * - Zapytania o sumę/liczbę unikalnych elementów na przedziale
 * - Problemy z zapytaniami offline
 * - Range queries
 * 
 * Złożoność:
 * - Czas: O((n + q) * sqrt(n)) gdzie n to rozmiar tablicy, q to liczba zapytań
 * - Pamięć: O(n + q)
 * 
 * Uwaga:
 * - Działa tylko dla zapytań offline
 * - Wymaga możliwości aktualizacji odpowiedzi przy przesuwaniu granic przedziału
 */

#include <bits/stdc++.h>

using namespace std;

struct Query {
    int l, r, idx;
};

int mos_block_size;

bool mos_compare(const Query& a, const Query& b) {
    if (a.l / mos_block_size != b.l / mos_block_size) {
        return a.l < b.l;
    }
    return (a.l / mos_block_size % 2 == 0) ? a.r < b.r : a.r > b.r;
}

vector<int> mos_algorithm(const vector<int>& arr, vector<Query>& queries) {
    int n = arr.size();
    int q = queries.size();
    mos_block_size = sqrt(n);
    
    sort(queries.begin(), queries.end(), mos_compare);
    
    vector<int> answers(q);
    int current_l = 0, current_r = -1;
    int current_answer = 0;
    vector<int> freq(1000001, 0); // dostosuj zakres
    
    for (const Query& query : queries) {
        while (current_l > query.l) {
            current_l--;
            if (freq[arr[current_l]] == 0) current_answer++;
            freq[arr[current_l]]++;
        }
        while (current_r < query.r) {
            current_r++;
            if (freq[arr[current_r]] == 0) current_answer++;
            freq[arr[current_r]]++;
        }
        while (current_l < query.l) {
            freq[arr[current_l]]--;
            if (freq[arr[current_l]] == 0) current_answer--;
            current_l++;
        }
        while (current_r > query.r) {
            freq[arr[current_r]]--;
            if (freq[arr[current_r]] == 0) current_answer--;
            current_r--;
        }
        
        answers[query.idx] = current_answer;
    }
    
    return answers;
}

// Przykład użycia - liczba unikalnych elementów na przedziale
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    int n, q;
    cin >> n >> q;
    
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    
    vector<Query> queries(q);
    for (int i = 0; i < q; i++) {
        cin >> queries[i].l >> queries[i].r;
        queries[i].l--; queries[i].r--; // 0-indeksowanie
        queries[i].idx = i;
    }
    
    vector<int> answers = mos_algorithm(arr, queries);
    
    for (int ans : answers) {
        cout << ans << '\n';
    }
    
    return 0;
}

