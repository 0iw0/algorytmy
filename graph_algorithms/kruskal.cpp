/*
 * Kruskal's Algorithm
 * 
 * Algorytm znajdowania MST (Minimum Spanning Tree) w grafie ważonym.
 * 
 * Zastosowanie:
 * - Minimalne drzewo rozpinające
 * - Sieci komputerowe
 * - Planowanie infrastruktury
 * 
 * Złożoność:
 * - Czas: O(E log E) = O(E log V) (sortowanie krawędzi)
 * - Pamięć: O(V + E)
 * 
 * Uwaga:
 * - Wymaga Union-Find
 * - Działa dla grafów skierowanych i nieskierowanych
 */

#include <bits/stdc++.h>

using namespace std;

struct Edge {
    int u, v, w;
    bool operator<(const Edge& other) const {
        return w < other.w;
    }
};

vector<Edge> edges;
vector<int> dsu_parent;
vector<int> dsu_rank;

int dsu_find(int x) {
    if (dsu_parent[x] != x) {
        dsu_parent[x] = dsu_find(dsu_parent[x]);
    }
    return dsu_parent[x];
}

void dsu_union(int x, int y) {
    int px = dsu_find(x);
    int py = dsu_find(y);
    
    if (px == py) return;
    
    if (dsu_rank[px] < dsu_rank[py]) {
        dsu_parent[px] = py;
    } else if (dsu_rank[px] > dsu_rank[py]) {
        dsu_parent[py] = px;
    } else {
        dsu_parent[py] = px;
        dsu_rank[px]++;
    }
}

int kruskal(int n) {
    sort(edges.begin(), edges.end());
    
    dsu_parent.resize(n);
    dsu_rank.resize(n, 0);
    for (int i = 0; i < n; i++) {
        dsu_parent[i] = i;
    }
    
    int mst_cost = 0;
    int edges_used = 0;
    
    for (const Edge& e : edges) {
        if (dsu_find(e.u) != dsu_find(e.v)) {
            dsu_union(e.u, e.v);
            mst_cost += e.w;
            edges_used++;
            
            if (edges_used == n - 1) {
                break; // MST ma n-1 krawędzi
            }
        }
    }
    
    if (edges_used != n - 1) {
        return -1; // graf nie jest spójny
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
    
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--; v--; // 0-indeksowanie
        edges.push_back({u, v, w});
    }
    
    int mst_cost = kruskal(n);
    
    if (mst_cost == -1) {
        cout << "Graf nie jest spójny\n";
    } else {
        cout << "Koszt MST: " << mst_cost << '\n';
    }
    
    return 0;
}

