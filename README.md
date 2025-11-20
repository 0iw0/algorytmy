## Struktura folderów

### 📁 data_structures/
Struktury danych:
- `segment_tree.cpp` - Drzewo przedziałowe
- `segment_tree_lazy.cpp` - Drzewo przedziałowe z lazy propagation
- `fenwick_tree.cpp` - Fenwick Tree (Binary Indexed Tree)
- `union_find.cpp` - Union-Find (DSU)
- `sparse_table.cpp` - Sparse Table (RMQ)
- `trie.cpp` - Trie (drzewo prefiksowe)

### 📁 graph_algorithms/
Algorytmy grafowe:
- `bfs.cpp` - Breadth-First Search
- `dfs.cpp` - Depth-First Search
- `topological_sort.cpp` - Sortowanie topologiczne
- `dijkstra.cpp` - Algorytm Dijkstry
- `bellman_ford.cpp` - Algorytm Bellman-Forda
- `floyd_warshall.cpp` - Algorytm Floyd-Warshalla
- `kruskal.cpp` - Algorytm Kruskala (MST)
- `prim.cpp` - Algorytm Prima (MST)
- `lca.cpp` - Lowest Common Ancestor (Binary Lifting)
- `scc.cpp` - Strongly Connected Components (Kosaraju)
- `articulation_points.cpp` - Punkty artykulacji i mosty
- `bipartite_matching.cpp` - Skojarzenia w grafie dwudzielnym

### 📁 string_algorithms/
Algorytmy na stringach:
- `kmp.cpp` - Knuth-Morris-Pratt
- `z_algorithm.cpp` - Z-Algorithm
- `rabin_karp.cpp` - Rabin-Karp
- `manacher.cpp` - Manacher's Algorithm

### 📁 math_algorithms/
Algorytmy matematyczne:
- `gcd_lcm.cpp` - NWD, NWW, rozszerzony algorytm Euklidesa
- `sieve.cpp` - Sito Eratostenesa
- `factorization.cpp` - Faktoryzacja
- `modular_exponentiation.cpp` - Potęgowanie modularne
- `binomial_coefficient.cpp` - Symbol Newtona

### 📁 geometry/
Geometria:
- `convex_hull.cpp` - Otoczka wypukła
- `geometry_basics.cpp` - Podstawowe funkcje geometryczne

### 📁 dynamic_programming/
Programowanie dynamiczne:
- `lis.cpp` - Longest Increasing Subsequence
- `lcs.cpp` - Longest Common Subsequence
- `edit_distance.cpp` - Edit Distance (Levenshtein)
- `knapsack.cpp` - Problem plecakowy (0/1 i unbounded)

### 📁 search_algorithms/
Algorytmy wyszukiwania:
- `binary_search.cpp` - Wyszukiwanie binarne
- `ternary_search.cpp` - Wyszukiwanie trójkowe

### 📁 other_techniques/
Inne techniki:
- `two_pointers.cpp` - Technika dwóch wskaźników
- `mos_algorithm.cpp` - Mo's Algorithm
- `prefix_sums.cpp` - Sumy prefiksowe

## Uwagi

- Wszystkie implementacje używają funkcji i globalnych zmiennych (bez klas)
- Każdy plik zawiera komentarz wyjaśniający działanie algorytmu
- Przykłady użycia znajdują się w funkcji `main()` każdego pliku
- Wszystkie pliki używają `#include <bits/stdc++.h>` i `using namespace std;`

## Lista algorytmów

Pełna lista wszystkich algorytmów z szczegółowymi opisami, zastosowaniami i przewodnikiem wyboru znajduje się w pliku `lista_algorytmow.md`.

## Szybki przewodnik wyboru algorytmu

### Zapytania na przedziałach:
- **Tylko zapytania:** Sparse Table
- **Suma + aktualizacje:** Fenwick Tree lub Segment Tree
- **Min/Max + aktualizacje:** Segment Tree
- **Aktualizacje przedziałów:** Segment Tree z lazy propagation

### Najkrótsze ścieżki:
- **Graf nieważony:** BFS
- **Graf ważony (nieujemne wagi):** Dijkstra
- **Graf ważony (ujemne wagi):** Bellman-Ford
- **Wszystkie pary (mały graf):** Floyd-Warshall

### Wyszukiwanie wzorca:
- **Ogólne:** KMP lub Z-Algorithm
- **Palindromy:** Manacher

Więcej szczegółów w `lista_algorytmow.md`.

