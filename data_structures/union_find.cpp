/*
 * Union-Find (Disjoint Set Union, DSU)
 * 
 * Struktura danych pozwalająca na:
 * - Sprawdzanie czy dwa elementy są w tej samej składowej w czasie O(α(n)) (praktycznie O(1))
 * - Łączenie dwóch składowych w czasie O(α(n))
 * 
 * Zastosowanie:
 * - Znajdowanie spójnych składowych w grafie
 * - Kruskal's algorithm dla MST
 * - Sprawdzanie czy graf jest spójny
 * - Grupowanie elementów
 * 
 * Złożoność:
 * - Pamięć: O(n)
 * - Find: O(α(n)) - praktycznie O(1)
 * - Union: O(α(n)) - praktycznie O(1)
 * 
 * Optymalizacje:
 * - Path compression - spłaszczanie drzewa podczas Find
 * - Union by rank/size - łączenie mniejszego drzewa do większego
 */

#include <bits/stdc++.h>

using namespace std;

vector<int> dsu_parent;
vector<int> dsu_rank; // lub dsu_size dla union by size

void dsu_init(int n) {
    dsu_parent.resize(n);
    dsu_rank.resize(n, 0);
    for (int i = 0; i < n; i++) {
        dsu_parent[i] = i;
    }
}

int dsu_find(int x) {
    if (dsu_parent[x] != x) {
        dsu_parent[x] = dsu_find(dsu_parent[x]); // path compression
    }
    return dsu_parent[x];
}

void dsu_union(int x, int y) {
    int px = dsu_find(x);
    int py = dsu_find(y);
    
    if (px == py) return;
    
    // Union by rank
    if (dsu_rank[px] < dsu_rank[py]) {
        dsu_parent[px] = py;
    } else if (dsu_rank[px] > dsu_rank[py]) {
        dsu_parent[py] = px;
    } else {
        dsu_parent[py] = px;
        dsu_rank[px]++;
    }
}

// Wersja z union by size (alternatywa)
vector<int> dsu_size;

void dsu_init_size(int n) {
    dsu_parent.resize(n);
    dsu_size.resize(n, 1);
    for (int i = 0; i < n; i++) {
        dsu_parent[i] = i;
    }
}

void dsu_union_size(int x, int y) {
    int px = dsu_find(x);
    int py = dsu_find(y);
    
    if (px == py) return;
    
    if (dsu_size[px] < dsu_size[py]) {
        swap(px, py);
    }
    dsu_parent[py] = px;
    dsu_size[px] += dsu_size[py];
}

// Przykład użycia:
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    int n = 5;
    dsu_init(n);
    
    dsu_union(0, 1);
    dsu_union(2, 3);
    dsu_union(1, 2);
    
    cout << (dsu_find(0) == dsu_find(3) ? "TAK" : "NIE") << '\n'; // TAK
    cout << (dsu_find(0) == dsu_find(4) ? "TAK" : "NIE") << '\n'; // NIE
    
    return 0;
}

