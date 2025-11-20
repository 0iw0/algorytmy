/*
 * LCA (Lowest Common Ancestor) - Binary Lifting
 * 
 * Algorytm znajdowania najniższego wspólnego przodka dwóch wierzchołków w drzewie.
 * 
 * Zastosowanie:
 * - Najkrótsza ścieżka między wierzchołkami w drzewie
 * - Zapytania o odległość między wierzchołkami
 * - Sprawdzanie relacji przodek-potomek
 * 
 * Złożoność:
 * - Preprocessing: O(n log n)
 * - Pamięć: O(n log n)
 * - Zapytanie: O(log n)
 * 
 * Uwaga:
 * - Działa tylko dla drzew (grafów acyklicznych)
 */

#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> graph;
vector<vector<int>> lca_parent; // lca_parent[k][v] = 2^k-ty przodek v
vector<int> lca_depth;
int lca_n;
int lca_max_log;

void lca_dfs(int u, int p, int d) {
    lca_parent[0][u] = p;
    lca_depth[u] = d;
    
    for (int v : graph[u]) {
        if (v != p) {
            lca_dfs(v, u, d + 1);
        }
    }
}

void lca_init(int root, int n) {
    lca_n = n;
    lca_max_log = 0;
    while ((1 << lca_max_log) <= n) {
        lca_max_log++;
    }
    
    lca_parent.assign(lca_max_log, vector<int>(n, -1));
    lca_depth.resize(n);
    
    lca_dfs(root, -1, 0);
    
    // Binary lifting
    for (int k = 1; k < lca_max_log; k++) {
        for (int v = 0; v < n; v++) {
            if (lca_parent[k-1][v] != -1) {
                lca_parent[k][v] = lca_parent[k-1][lca_parent[k-1][v]];
            }
        }
    }
}

int lca_lift(int u, int k) {
    for (int i = 0; i < lca_max_log; i++) {
        if (k & (1 << i)) {
            u = lca_parent[i][u];
            if (u == -1) break;
        }
    }
    return u;
}

int lca_query(int u, int v) {
    if (lca_depth[u] < lca_depth[v]) {
        swap(u, v);
    }
    
    // Podnieś u do poziomu v
    u = lca_lift(u, lca_depth[u] - lca_depth[v]);
    
    if (u == v) {
        return u;
    }
    
    // Podnieś oba wierzchołki do wspólnego przodka
    for (int k = lca_max_log - 1; k >= 0; k--) {
        if (lca_parent[k][u] != lca_parent[k][v]) {
            u = lca_parent[k][u];
            v = lca_parent[k][v];
        }
    }
    
    return lca_parent[0][u];
}

int lca_distance(int u, int v) {
    int w = lca_query(u, v);
    return lca_depth[u] + lca_depth[v] - 2 * lca_depth[w];
}

// Przykład użycia:
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    int n;
    cin >> n;
    
    graph.resize(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--; // 0-indeksowanie
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    
    lca_init(0, n);
    
    int u, v;
    cin >> u >> v;
    u--; v--;
    
    cout << "LCA(" << u+1 << ", " << v+1 << ") = " << lca_query(u, v) + 1 << '\n';
    cout << "Odległość: " << lca_distance(u, v) << '\n';
    
    return 0;
}

