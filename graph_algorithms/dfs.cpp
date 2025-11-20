/*
 * DFS (Depth-First Search)
 * 
 * Algorytm przeszukiwania grafu w głąb pozwalający na:
 * - Przeszukiwanie wszystkich wierzchołków osiągalnych z danego wierzchołka
 * - Znajdowanie cykli
 * - Topological sort
 * - Sprawdzanie spójności
 * 
 * Zastosowanie:
 * - Przeszukiwanie grafu
 * - Znajdowanie cykli
 * - Topological sort
 * - Sprawdzanie dwudzielności
 * - Znajdowanie mostów i punktów artykulacji
 * 
 * Złożoność:
 * - Czas: O(V + E)
 * - Pamięć: O(V) (rekurencyjna może być O(V) na stosie)
 */

#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> graph;
vector<bool> visited;

void dfs(int u) {
    visited[u] = true;
    
    for (int v : graph[u]) {
        if (!visited[v]) {
            dfs(v);
        }
    }
}

// Wersja iteracyjna (używa mniej pamięci na stosie)
void dfs_iterative(int start) {
    stack<int> st;
    st.push(start);
    visited[start] = true;
    
    while (!st.empty()) {
        int u = st.top();
        st.pop();
        
        for (int v : graph[u]) {
            if (!visited[v]) {
                visited[v] = true;
                st.push(v);
            }
        }
    }
}

// DFS z informacją o czasie wejścia/wyjścia (przydatne dla wielu algorytmów)
vector<int> dfs_time_in;
vector<int> dfs_time_out;
int dfs_timer;

void dfs_timed(int u) {
    dfs_time_in[u] = dfs_timer++;
    visited[u] = true;
    
    for (int v : graph[u]) {
        if (!visited[v]) {
            dfs_timed(v);
        }
    }
    
    dfs_time_out[u] = dfs_timer++;
}

// Przykład użycia:
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    int n, m;
    cin >> n >> m;
    
    graph.resize(n);
    visited.assign(n, false);
    
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--; // 0-indeksowanie
        graph[u].push_back(v);
        graph[v].push_back(u); // dla grafu nieskierowanego
    }
    
    // Zliczanie spójnych składowych
    int components = 0;
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfs(i);
            components++;
        }
    }
    
    cout << "Liczba spójnych składowych: " << components << '\n';
    
    return 0;
}

