/*
 * Bipartite Matching (Maximum Bipartite Matching)
 * 
 * Algorytm znajdowania maksymalnego skojarzenia w grafie dwudzielnym.
 * 
 * Zastosowanie:
 * - Skojarzenia w grafach dwudzielnych
 * - Problem przydziału zadań
 * - Matching problemy
 * 
 * Złożoność:
 * - Czas: O(V * E) (DFS) lub O(sqrt(V) * E) (Hopcroft-Karp)
 * - Pamięć: O(V + E)
 * 
 * Uwaga:
 * - Działa tylko dla grafów dwudzielnych
 * - Implementacja używa DFS (prostsza, ale wolniejsza dla dużych grafów)
 */

#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> graph; // graf dwudzielny: lewa strona -> prawa strona
vector<int> match_left; // match_left[i] = wierzchołek z prawej strony skojarzony z i
vector<int> match_right; // match_right[j] = wierzchołek z lewej strony skojarzony z j
vector<bool> bm_visited;

bool bm_dfs(int u) {
    for (int v : graph[u]) {
        if (bm_visited[v]) continue;
        bm_visited[v] = true;
        
        if (match_right[v] == -1 || bm_dfs(match_right[v])) {
            match_left[u] = v;
            match_right[v] = u;
            return true;
        }
    }
    return false;
}

int bipartite_matching(int left_size, int right_size) {
    match_left.assign(left_size, -1);
    match_right.assign(right_size, -1);
    
    int matching = 0;
    
    for (int u = 0; u < left_size; u++) {
        bm_visited.assign(right_size, false);
        if (bm_dfs(u)) {
            matching++;
        }
    }
    
    return matching;
}

// Sprawdzanie czy graf jest dwudzielny
vector<int> bm_color;

bool bm_is_bipartite(int n) {
    bm_color.assign(n, -1);
    queue<int> q;
    
    for (int i = 0; i < n; i++) {
        if (bm_color[i] == -1) {
            bm_color[i] = 0;
            q.push(i);
            
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                
                for (int v : graph[u]) {
                    if (bm_color[v] == -1) {
                        bm_color[v] = 1 - bm_color[u];
                        q.push(v);
                    } else if (bm_color[v] == bm_color[u]) {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

// Przykład użycia:
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    int left_size, right_size, m;
    cin >> left_size >> right_size >> m;
    
    graph.resize(left_size);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--; // 0-indeksowanie, u należy do lewej strony, v do prawej
        graph[u].push_back(v);
    }
    
    int matching = bipartite_matching(left_size, right_size);
    cout << "Maksymalne skojarzenie: " << matching << '\n';
    
    return 0;
}

