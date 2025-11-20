/*
 * BFS (Breadth-First Search)
 * 
 * Algorytm przeszukiwania grafu wszerz pozwalający na:
 * - Znajdowanie najkrótszych ścieżek w grafie nieważonym
 * - Sprawdzanie spójności grafu
 * - Znajdowanie poziomów wierzchołków
 * 
 * Zastosowanie:
 * - Najkrótsza ścieżka w grafie nieważonym
 * - Sprawdzanie czy graf jest dwudzielny
 * - Znajdowanie odległości od źródła
 * - BFS na siatce (grid)
 * 
 * Złożoność:
 * - Czas: O(V + E)
 * - Pamięć: O(V)
 */

#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> graph;
vector<int> dist;
vector<int> parent;

void bfs(int start) {
    int n = graph.size();
    dist.assign(n, -1);
    parent.assign(n, -1);
    
    queue<int> q;
    q.push(start);
    dist[start] = 0;
    
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        
        for (int v : graph[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                parent[v] = u;
                q.push(v);
            }
        }
    }
}

// Rekonstrukcja ścieżki z start do end
vector<int> bfs_path(int start, int end) {
    bfs(start);
    
    if (dist[end] == -1) {
        return {}; // brak ścieżki
    }
    
    vector<int> path;
    int current = end;
    while (current != -1) {
        path.push_back(current);
        current = parent[current];
    }
    reverse(path.begin(), path.end());
    return path;
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
        graph[v].push_back(u); // dla grafu nieskierowanego
    }
    
    bfs(0);
    
    for (int i = 0; i < n; i++) {
        cout << "Odległość od 0 do " << i << ": " << dist[i] << '\n';
    }
    
    return 0;
}

