/*
 * Articulation Points and Bridges
 * 
 * Algorytm znajdowania punktów artykulacji i mostów w grafie nieskierowanym.
 * 
 * Zastosowanie:
 * - Znajdowanie krytycznych węzłów w sieci
 * - Analiza odporności grafu
 * - Znajdowanie mostów w grafie
 * 
 * Złożoność:
 * - Czas: O(V + E)
 * - Pamięć: O(V)
 * 
 * Uwaga:
 * - Działa tylko dla grafów nieskierowanych
 * - Punkt artykulacji to wierzchołek, którego usunięcie zwiększa liczbę składowych
 * - Most to krawędź, której usunięcie zwiększa liczbę składowych
 */

#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> graph;
vector<int> ap_time_in;
vector<int> ap_low;
vector<bool> ap_visited;
vector<bool> ap_is_articulation;
vector<pair<int, int>> ap_bridges;
int ap_timer;

void ap_dfs(int u, int parent) {
    ap_visited[u] = true;
    ap_time_in[u] = ap_low[u] = ap_timer++;
    int children = 0;
    
    for (int v : graph[u]) {
        if (v == parent) continue;
        
        if (ap_visited[v]) {
            ap_low[u] = min(ap_low[u], ap_time_in[v]);
        } else {
            ap_dfs(v, u);
            ap_low[u] = min(ap_low[u], ap_low[v]);
            
            // Most: ap_low[v] > ap_time_in[u]
            if (ap_low[v] > ap_time_in[u]) {
                ap_bridges.push_back({u, v});
            }
            
            // Punkt artykulacji: ap_low[v] >= ap_time_in[u] i u nie jest korzeniem
            if (ap_low[v] >= ap_time_in[u] && parent != -1) {
                ap_is_articulation[u] = true;
            }
            children++;
        }
    }
    
    // Korzeń jest punktem artykulacji jeśli ma więcej niż jedno dziecko
    if (parent == -1 && children > 1) {
        ap_is_articulation[u] = true;
    }
}

void ap_find(int n) {
    ap_visited.assign(n, false);
    ap_time_in.assign(n, -1);
    ap_low.assign(n, -1);
    ap_is_articulation.assign(n, false);
    ap_bridges.clear();
    ap_timer = 0;
    
    for (int i = 0; i < n; i++) {
        if (!ap_visited[i]) {
            ap_dfs(i, -1);
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
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--; // 0-indeksowanie
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    
    ap_find(n);
    
    cout << "Punkty artykulacji: ";
    for (int i = 0; i < n; i++) {
        if (ap_is_articulation[i]) {
            cout << i + 1 << " ";
        }
    }
    cout << '\n';
    
    cout << "Mosty: ";
    for (auto& bridge : ap_bridges) {
        cout << "(" << bridge.first + 1 << ", " << bridge.second + 1 << ") ";
    }
    cout << '\n';
    
    return 0;
}

