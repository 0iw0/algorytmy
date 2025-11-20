/*
 * Prim's Algorithm
 * 
 * Algorytm znajdowania MST (Minimum Spanning Tree) w grafie ważonym.
 * 
 * Zastosowanie:
 * - Minimalne drzewo rozpinające
 * - Podobne zastosowania jak Kruskal
 * 
 * Złożoność:
 * - Czas: O(E log V) z priority_queue
 * - Pamięć: O(V + E)
 * 
 * Uwaga:
 * - Podobny do Dijkstry, ale wybiera krawędzie o najmniejszej wadze
 * - Może być szybszy dla gęstych grafów niż Kruskal
 */

#include <bits/stdc++.h>

using namespace std;

vector<vector<pair<int, int>>> graph; // {wierzchołek, waga}
vector<bool> in_mst;
const int INF = 1e9;

int prim(int start, int n) {
    in_mst.assign(n, false);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    
    int mst_cost = 0;
    pq.push({0, start});
    
    while (!pq.empty()) {
        int u = pq.top().second;
        int w = pq.top().first;
        pq.pop();
        
        if (in_mst[u]) continue;
        
        in_mst[u] = true;
        mst_cost += w;
        
        for (auto& edge : graph[u]) {
            int v = edge.first;
            int weight = edge.second;
            
            if (!in_mst[v]) {
                pq.push({weight, v});
            }
        }
    }
    
    // Sprawdzanie czy wszystkie wierzchołki są w MST
    for (int i = 0; i < n; i++) {
        if (!in_mst[i]) {
            return -1; // graf nie jest spójny
        }
    }
    
    return mst_cost;
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
    
    int mst_cost = prim(0, n);
    
    if (mst_cost == -1) {
        cout << "Graf nie jest spójny\n";
    } else {
        cout << "Koszt MST: " << mst_cost << '\n';
    }
    
    return 0;
}

