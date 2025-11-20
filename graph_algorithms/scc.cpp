/*
 * SCC (Strongly Connected Components) - Kosaraju's Algorithm
 * 
 * Algorytm znajdowania silnie spójnych składowych w grafie skierowanym.
 * 
 * Zastosowanie:
 * - Sprawdzanie czy graf jest silnie spójny
 * - Kompresja grafu do DAG
 * - Analiza zależności
 * 
 * Złożoność:
 * - Czas: O(V + E)
 * - Pamięć: O(V + E)
 * 
 * Uwaga:
 * - Działa tylko dla grafów skierowanych
 * - Wymaga dwóch przejść DFS
 */

#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> graph;
vector<vector<int>> graph_rev;
vector<bool> visited;
vector<int> order;
vector<int> component;
int scc_count;

void scc_dfs1(int u) {
    visited[u] = true;
    for (int v : graph[u]) {
        if (!visited[v]) {
            scc_dfs1(v);
        }
    }
    order.push_back(u);
}

void scc_dfs2(int u, int comp) {
    component[u] = comp;
    for (int v : graph_rev[u]) {
        if (component[v] == -1) {
            scc_dfs2(v, comp);
        }
    }
}

void scc_kosaraju(int n) {
    visited.assign(n, false);
    component.assign(n, -1);
    order.clear();
    scc_count = 0;
    
    // Pierwszy DFS - kolejność wyjścia
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            scc_dfs1(i);
        }
    }
    
    // Drugi DFS na grafie odwróconym
    reverse(order.begin(), order.end());
    for (int u : order) {
        if (component[u] == -1) {
            scc_dfs2(u, scc_count);
            scc_count++;
        }
    }
}

// Przykład użycia:
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    int n, m;
    cin >> n >> m;
    
    graph.resize(n);
    graph_rev.resize(n);
    
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--; // 0-indeksowanie
        graph[u].push_back(v);
        graph_rev[v].push_back(u);
    }
    
    scc_kosaraju(n);
    
    cout << "Liczba silnie spójnych składowych: " << scc_count << '\n';
    for (int i = 0; i < n; i++) {
        cout << "Wierzchołek " << i+1 << " należy do składowej " << component[i] << '\n';
    }
    
    return 0;
}

