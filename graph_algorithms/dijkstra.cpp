/*
 * Dijkstra's Algorithm
 * 
 * Algorytm znajdowania najkrótszych ścieżek z jednego źródła w grafie ważonym
 * z nieujemnymi wagami.
 * 
 * Zastosowanie:
 * - Najkrótsze ścieżki w grafie z nieujemnymi wagami
 * - Routing w sieciach
 * - Planowanie tras
 * 
 * Złożoność:
 * - Czas: O((V + E) log V) z priority_queue
 * - Pamięć: O(V + E)
 * 
 * Uwaga:
 * - Działa tylko dla nieujemnych wag
 * - Dla ujemnych wag użyj Bellman-Ford
 */

#include <bits/stdc++.h>

using namespace std;

vector<vector<pair<int, int>>> graph; // {wierzchołek, waga}
vector<int> dist;
vector<int> parent;
const int INF = 1e9;

void dijkstra(int start) {
    int n = graph.size();
    dist.assign(n, INF);
    parent.assign(n, -1);
    
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    dist[start] = 0;
    pq.push({0, start});
    
    while (!pq.empty()) {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();
        
        if (d > dist[u]) continue; // stara wartość w kolejce
        
        for (auto& edge : graph[u]) {
            int v = edge.first;
            int w = edge.second;
            
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }
}

// Rekonstrukcja ścieżki z start do end
vector<int> dijkstra_path(int start, int end) {
    dijkstra(start);
    
    if (dist[end] == INF) {
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
        int u, v, w;
        cin >> u >> v >> w;
        u--; v--; // 0-indeksowanie
        graph[u].push_back({v, w});
        graph[v].push_back({u, w}); // dla grafu nieskierowanego
    }
    
    dijkstra(0);
    
    for (int i = 0; i < n; i++) {
        cout << "Odległość od 0 do " << i << ": " << dist[i] << '\n';
    }
    
    return 0;
}

