/*
 * Topological Sort (Sortowanie topologiczne)
 * 
 * Algorytm sortowania wierzchołków w DAG (Directed Acyclic Graph) tak,
 * że dla każdej krawędzi (u, v), u pojawia się przed v w kolejności.
 * 
 * Zastosowanie:
 * - Porządkowanie zadań z zależnościami
 * - Kompilacja zależności
 * - Planowanie zadań
 * - Sprawdzanie czy graf jest DAG
 * 
 * Złożoność:
 * - Czas: O(V + E)
 * - Pamięć: O(V)
 * 
 * Uwaga:
 * - Działa tylko dla DAG (grafów acyklicznych skierowanych)
 * - Może istnieć wiele poprawnych sortowań topologicznych
 */

#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> graph;
vector<int> indegree;
vector<bool> visited;
vector<int> result;

// Wersja z DFS (zwraca odwróconą kolejność)
void dfs_topological(int u) {
    visited[u] = true;
    
    for (int v : graph[u]) {
        if (!visited[v]) {
            dfs_topological(v);
        }
    }
    
    result.push_back(u);
}

vector<int> topological_sort_dfs(int n) {
    visited.assign(n, false);
    result.clear();
    
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfs_topological(i);
        }
    }
    
    reverse(result.begin(), result.end());
    return result;
}

// Wersja z Kahn's algorithm (BFS-based)
vector<int> topological_sort_kahn(int n) {
    indegree.assign(n, 0);
    result.clear();
    
    // Obliczanie stopni wejściowych
    for (int u = 0; u < n; u++) {
        for (int v : graph[u]) {
            indegree[v]++;
        }
    }
    
    queue<int> q;
    for (int i = 0; i < n; i++) {
        if (indegree[i] == 0) {
            q.push(i);
        }
    }
    
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        result.push_back(u);
        
        for (int v : graph[u]) {
            indegree[v]--;
            if (indegree[v] == 0) {
                q.push(v);
            }
        }
    }
    
    // Jeśli result.size() != n, to graf ma cykl
    if (result.size() != n) {
        return {}; // cykl wykryty
    }
    
    return result;
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
    }
    
    vector<int> order = topological_sort_kahn(n);
    
    if (order.empty()) {
        cout << "Graf zawiera cykl!\n";
    } else {
        cout << "Sortowanie topologiczne: ";
        for (int u : order) {
            cout << u + 1 << " ";
        }
        cout << '\n';
    }
    
    return 0;
}

