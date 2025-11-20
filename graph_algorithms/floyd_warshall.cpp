/*
 * Floyd-Warshall Algorithm
 * 
 * Algorytm znajdowania najkrótszych ścieżek między wszystkimi parami wierzchołków
 * w grafie ważonym (dopuszcza ujemne wagi, ale nie ujemne cykle).
 * 
 * Zastosowanie:
 * - Wszystkie pary najkrótszych ścieżek
 * - Transitive closure
 * - Wykrywanie ujemnych cykli
 * - Najkrótsze ścieżki w małych grafach (V <= 400)
 * 
 * Złożoność:
 * - Czas: O(V^3)
 * - Pamięć: O(V^2)
 * 
 * Uwaga:
 * - Dla większych grafów użyj Dijkstra z każdym wierzchołkiem jako źródłem
 * - Może wykrywać ujemne cykle (dist[i][i] < 0)
 */

#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> dist;
const int INF = 1e9;

void floyd_warshall(int n) {
    dist.assign(n, vector<int>(n, INF));
    
    // Inicjalizacja: odległość do siebie = 0, krawędzie z grafu
    for (int i = 0; i < n; i++) {
        dist[i][i] = 0;
    }
    
    // Tutaj dodaj krawędzie grafu:
    // dist[u][v] = w; dla krawędzi (u, v) o wadze w
    
    // Algorytm Floyd-Warshall
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }
    
    // Wykrywanie ujemnych cykli
    for (int i = 0; i < n; i++) {
        if (dist[i][i] < 0) {
            // Ujemny cykl wykryty
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
    
    dist.assign(n, vector<int>(n, INF));
    
    for (int i = 0; i < n; i++) {
        dist[i][i] = 0;
    }
    
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--; v--; // 0-indeksowanie
        dist[u][v] = w;
        // dist[v][u] = w; // dla grafu nieskierowanego
    }
    
    floyd_warshall(n);
    
    // Odległość między wszystkimi parami
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (dist[i][j] == INF) {
                cout << "INF ";
            } else {
                cout << dist[i][j] << " ";
            }
        }
        cout << '\n';
    }
    
    return 0;
}

