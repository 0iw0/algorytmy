/*
 * Bellman-Ford Algorithm
 * 
 * Algorytm znajdowania najkrótszych ścieżek z jednego źródła w grafie ważonym,
 * dopuszczający ujemne wagi (ale nie ujemne cykle osiągalne).
 * 
 * Zastosowanie:
 * - Najkrótsze ścieżki z ujemnymi wagami
 * - Wykrywanie ujemnych cykli
 * - Arbitraż walutowy
 * 
 * Złożoność:
 * - Czas: O(V * E)
 * - Pamięć: O(V)
 * 
 * Uwaga:
 * - Wykrywa ujemne cykle osiągalne ze źródła
 * - Wolniejszy niż Dijkstra, ale bardziej uniwersalny
 */

#include <bits/stdc++.h>

using namespace std;

struct Edge {
    int u, v, w;
};

vector<Edge> edges;
vector<int> dist;
vector<int> parent;
const int INF = 1e9;

bool bellman_ford(int start, int n) {
    dist.assign(n, INF);
    parent.assign(n, -1);
    dist[start] = 0;
    
    // Relaksacja krawędzi (V-1) razy
    for (int i = 0; i < n - 1; i++) {
        for (const Edge& e : edges) {
            if (dist[e.u] != INF && dist[e.u] + e.w < dist[e.v]) {
                dist[e.v] = dist[e.u] + e.w;
                parent[e.v] = e.u;
            }
        }
    }
    
    // Sprawdzanie ujemnych cykli
    for (const Edge& e : edges) {
        if (dist[e.u] != INF && dist[e.u] + e.w < dist[e.v]) {
            return false; // ujemny cykl wykryty
        }
    }
    
    return true; // brak ujemnych cykli
}

// Rekonstrukcja ścieżki z start do end
vector<int> bellman_ford_path(int start, int end) {
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
    
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--; v--; // 0-indeksowanie
        edges.push_back({u, v, w});
    }
    
    if (bellman_ford(0, n)) {
        cout << "Brak ujemnych cykli\n";
        for (int i = 0; i < n; i++) {
            cout << "Odległość od 0 do " << i << ": " << dist[i] << '\n';
        }
    } else {
        cout << "Wykryto ujemny cykl!\n";
    }
    
    return 0;
}

