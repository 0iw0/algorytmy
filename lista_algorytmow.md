# Lista algorytmów i struktur danych - I etap OI

## Struktury danych

### Podstawowe kontenery STL
- `vector` - dynamiczna tablica
- `set` / `multiset` - zbiór uporządkowany
- `map` / `multimap` - mapa uporządkowana
- `unordered_set` / `unordered_map` - hash set/map
- `priority_queue` - kolejka priorytetowa (kopiec)
- `deque` - kolejka dwustronna
- `stack` / `queue` - stos i kolejka

### Zaawansowane struktury danych

#### **Drzewo przedziałowe (Segment Tree)** - `data_structures/segment_tree.cpp`
- **Kiedy użyć:** Zapytania o wartość na przedziale [l, r] + aktualizacje pojedynczych elementów
- **Zastosowanie:** 
  - Suma/minimum/maksimum/NWD na przedziale z aktualizacjami
  - Operacje łączne (associative operations)
  - Range queries z single point updates
- **Złożoność:** O(n) pamięć, O(log n) zapytanie/aktualizacja
- **Uwaga:** Działa dla dowolnych operacji łącznych (suma, min, max, gcd)

#### **Drzewo przedziałowe z lazy propagation** - `data_structures/segment_tree_lazy.cpp`
- **Kiedy użyć:** Zapytania na przedziale + aktualizacje całego przedziału [l, r]
- **Zastosowanie:**
  - Dodawanie wartości do wszystkich elementów w przedziale
  - Range updates + range queries
  - Problemy z masowymi aktualizacjami przedziałów
- **Złożoność:** O(n) pamięć, O(log n) zapytanie/aktualizacja przedziału
- **Uwaga:** Rozszerzenie Segment Tree o opóźnione aktualizacje

#### **Fenwick Tree (Binary Indexed Tree)** - `data_structures/fenwick_tree.cpp`
- **Kiedy użyć:** Suma prefiksowa z aktualizacjami pojedynczych elementów
- **Zastosowanie:**
  - Suma prefiksowa z aktualizacjami
  - Inwersje w permutacji
  - Liczenie elementów mniejszych/większych
  - Range sum queries (jako query(r) - query(l-1))
- **Złożoność:** O(n) pamięć, O(log n) zapytanie/aktualizacja
- **Zalety:** Prostsza implementacja, mniejsza stała niż Segment Tree
- **Wady:** Tylko operacje z odwrotnością (suma, nie min/max), tylko single point updates

#### **Union-Find (DSU)** - `data_structures/union_find.cpp`
- **Kiedy użyć:** Sprawdzanie czy elementy są w tej samej składowej + łączenie składowych
- **Zastosowanie:**
  - Spójne składowe w grafie
  - Kruskal's algorithm dla MST
  - Sprawdzanie czy graf jest spójny
  - Grupowanie elementów
- **Złożoność:** O(α(n)) praktycznie O(1) dla find/union
- **Uwaga:** Wymaga path compression i union by rank/size

#### **Sparse Table** - `data_structures/sparse_table.cpp`
- **Kiedy użyć:** Zapytania RMQ (Range Minimum/Maximum Query) bez aktualizacji
- **Zastosowanie:**
  - Minimum/maksimum na przedziale (statyczna tablica)
  - NWD na przedziale
  - Operacje idempotentne (min, max, gcd, AND, OR)
- **Złożoność:** O(n log n) preprocessing, O(1) zapytanie, O(n log n) pamięć
- **Uwaga:** Nie obsługuje aktualizacji, tylko operacje idempotentne

#### **Trie** - `data_structures/trie.cpp`
- **Kiedy użyć:** Wyszukiwanie stringów z danym prefiksem
- **Zastosowanie:**
  - Autocomplete
  - Wyszukiwanie prefiksów
  - Zliczanie stringów z danym prefiksem
  - XOR queries (binary trie)
- **Złożoność:** O(m) wstawianie/wyszukiwanie gdzie m to długość stringa
- **Uwaga:** Można rozszerzyć o binary trie dla problemów XOR

## Algorytmy grafowe

### Przeszukiwanie grafu

#### **BFS (Breadth-First Search)** - `graph_algorithms/bfs.cpp`
- **Kiedy użyć:** Najkrótsze ścieżki w grafie nieważonym, przeszukiwanie wszerz
- **Zastosowanie:**
  - Najkrótsza ścieżka w grafie nieważonym
  - Sprawdzanie czy graf jest dwudzielny
  - Znajdowanie poziomów wierzchołków
  - BFS na siatce (grid problems)
  - Shortest path w grafie 0-1
- **Złożoność:** O(V + E)
- **Uwaga:** Używa kolejki, zwraca najkrótsze ścieżki w grafie nieważonym

#### **DFS (Depth-First Search)** - `graph_algorithms/dfs.cpp`
- **Kiedy użyć:** Przeszukiwanie wszystkich wierzchołków, znajdowanie cykli, topologiczny porządek
- **Zastosowanie:**
  - Przeszukiwanie grafu
  - Znajdowanie cykli
  - Topological sort
  - Sprawdzanie dwudzielności
  - Znajdowanie mostów i punktów artykulacji
  - Sprawdzanie spójności
- **Złożoność:** O(V + E)
- **Uwaga:** Może być rekurencyjny (O(V) na stosie) lub iteracyjny

#### **Topological Sort** - `graph_algorithms/topological_sort.cpp`
- **Kiedy użyć:** Porządkowanie wierzchołków w DAG (Directed Acyclic Graph)
- **Zastosowanie:**
  - Porządkowanie zadań z zależnościami
  - Kompilacja zależności
  - Planowanie zadań
  - Sprawdzanie czy graf jest DAG
- **Złożoność:** O(V + E)
- **Uwaga:** Działa tylko dla DAG, może istnieć wiele poprawnych sortowań
- **Implementacje:** DFS-based i Kahn's algorithm (BFS-based)

### Najkrótsze ścieżki

#### **Dijkstra** - `graph_algorithms/dijkstra.cpp`
- **Kiedy użyć:** Najkrótsze ścieżki z jednego źródła w grafie z nieujemnymi wagami
- **Zastosowanie:**
  - Najkrótsze ścieżki w grafie ważonym (nieujemne wagi)
  - Routing w sieciach
  - Planowanie tras
  - Single-source shortest path
- **Złożoność:** O((V + E) log V) z priority_queue
- **Uwaga:** Działa tylko dla nieujemnych wag, dla ujemnych użyj Bellman-Ford

#### **Bellman-Ford** - `graph_algorithms/bellman_ford.cpp`
- **Kiedy użyć:** Najkrótsze ścieżki z ujemnymi wagami (ale bez ujemnych cykli osiągalnych)
- **Zastosowanie:**
  - Najkrótsze ścieżki z ujemnymi wagami
  - Wykrywanie ujemnych cykli
  - Arbitraż walutowy
  - Single-source shortest path z ujemnymi wagami
- **Złożoność:** O(V * E)
- **Uwaga:** Wolniejszy niż Dijkstra, ale bardziej uniwersalny, wykrywa ujemne cykle

#### **Floyd-Warshall** - `graph_algorithms/floyd_warshall.cpp`
- **Kiedy użyć:** Wszystkie pary najkrótszych ścieżek w małych grafach
- **Zastosowanie:**
  - Wszystkie pary najkrótszych ścieżek
  - Transitive closure
  - Wykrywanie ujemnych cykli
  - Najkrótsze ścieżki w małych grafach (V <= 400)
- **Złożoność:** O(V³)
- **Uwaga:** Dla większych grafów użyj Dijkstra z każdym wierzchołkiem jako źródłem

### Drzewa i lasy

#### **Kruskal (MST)** - `graph_algorithms/kruskal.cpp`
- **Kiedy użyć:** Minimalne drzewo rozpinające (Minimum Spanning Tree)
- **Zastosowanie:**
  - Minimalne drzewo rozpinające
  - Sieci komputerowe
  - Planowanie infrastruktury
  - Minimalizacja kosztów połączeń
- **Złożoność:** O(E log E) = O(E log V) (sortowanie krawędzi)
- **Uwaga:** Wymaga Union-Find, działa dla grafów skierowanych i nieskierowanych

#### **Prim (MST)** - `graph_algorithms/prim.cpp`
- **Kiedy użyć:** Minimalne drzewo rozpinające (alternatywa dla Kruskala)
- **Zastosowanie:**
  - Podobne jak Kruskal
  - Może być szybszy dla gęstych grafów
- **Złożoność:** O(E log V) z priority_queue
- **Uwaga:** Podobny do Dijkstry, ale wybiera krawędzie o najmniejszej wadze

#### **LCA (Lowest Common Ancestor)** - `graph_algorithms/lca.cpp`
- **Kiedy użyć:** Najniższy wspólny przodek dwóch wierzchołków w drzewie
- **Zastosowanie:**
  - Najkrótsza ścieżka między wierzchołkami w drzewie
  - Zapytania o odległość między wierzchołkami
  - Sprawdzanie relacji przodek-potomek
  - Range queries na ścieżkach w drzewie
- **Złożoność:** O(n log n) preprocessing, O(log n) zapytanie
- **Uwaga:** Działa tylko dla drzew, implementacja używa Binary Lifting

### Inne algorytmy grafowe

#### **SCC (Strongly Connected Components)** - `graph_algorithms/scc.cpp`
- **Kiedy użyć:** Silnie spójne składowe w grafie skierowanym
- **Zastosowanie:**
  - Sprawdzanie czy graf jest silnie spójny
  - Kompresja grafu do DAG
  - Analiza zależności
  - Znajdowanie silnie spójnych składowych
- **Złożoność:** O(V + E)
- **Uwaga:** Działa tylko dla grafów skierowanych, implementacja Kosaraju

#### **Articulation Points / Bridges** - `graph_algorithms/articulation_points.cpp`
- **Kiedy użyć:** Punkty artykulacji i mosty w grafie nieskierowanym
- **Zastosowanie:**
  - Znajdowanie krytycznych węzłów w sieci
  - Analiza odporności grafu
  - Znajdowanie mostów w grafie
  - Sprawdzanie spójności grafu
- **Złożoność:** O(V + E)
- **Uwaga:** Działa tylko dla grafów nieskierowanych, używa DFS

#### **Bipartite Matching** - `graph_algorithms/bipartite_matching.cpp`
- **Kiedy użyć:** Maksymalne skojarzenie w grafie dwudzielnym
- **Zastosowanie:**
  - Skojarzenia w grafach dwudzielnych
  - Problem przydziału zadań
  - Matching problemy
  - Maksymalne skojarzenie
- **Złożoność:** O(V * E) (DFS) lub O(√V * E) (Hopcroft-Karp)
- **Uwaga:** Działa tylko dla grafów dwudzielnych, implementacja używa DFS

## Algorytmy sortowania i wyszukiwania

#### **Binary Search** - `search_algorithms/binary_search.cpp`
- **Kiedy użyć:** Wyszukiwanie w posortowanej tablicy, binary search na odpowiedzi
- **Zastosowanie:**
  - Wyszukiwanie elementu w posortowanej tablicy
  - Binary search na odpowiedzi (znajdź najmniejsze x takie że f(x) >= target)
  - Lower bound / Upper bound
  - Znajdowanie granic
- **Złożoność:** O(log n)
- **Uwaga:** Wymaga posortowanej tablicy lub funkcji unimodalnej

#### **Ternary Search** - `search_algorithms/ternary_search.cpp`
- **Kiedy użyć:** Znajdowanie minimum/maksimum funkcji unimodalnej
- **Zastosowanie:**
  - Funkcje unimodalne (jedno ekstremum)
  - Optymalizacja
  - Problemy geometryczne
  - Znajdowanie ekstremum funkcji
- **Złożoność:** O(log n) gdzie n to zakres
- **Uwaga:** Funkcja musi być unimodalna (jedno minimum/maksimum)

## Algorytmy na stringach

#### **KMP (Knuth-Morris-Pratt)** - `string_algorithms/kmp.cpp`
- **Kiedy użyć:** Wyszukiwanie wzorca w tekście w czasie liniowym
- **Zastosowanie:**
  - Wyszukiwanie wzorca w tekście
  - Znajdowanie wszystkich wystąpień wzorca
  - Longest prefix which is also suffix
  - Pattern matching
- **Złożoność:** O(n + m) gdzie n to długość tekstu, m to długość wzorca
- **Uwaga:** Lepszy niż naiwny algorytm dla długich wzorców

#### **Z-Algorithm** - `string_algorithms/z_algorithm.cpp`
- **Kiedy użyć:** Wyszukiwanie wzorca w tekście (alternatywa dla KMP)
- **Zastosowanie:**
  - Podobne jak KMP
  - Znajdowanie wszystkich wystąpień wzorca
  - Longest prefix matching
- **Złożoność:** O(n + m)
- **Uwaga:** Prostsza implementacja niż KMP, podobna złożoność

#### **Rabin-Karp** - `string_algorithms/rabin_karp.cpp`
- **Kiedy użyć:** Wyszukiwanie wzorca używając hashowania
- **Zastosowanie:**
  - Wyszukiwanie wzorca w tekście
  - Wyszukiwanie wielu wzorców jednocześnie
  - Rolling hash dla substringów
- **Złożoność:** Średnio O(n + m), najgorszy O(n * m)
- **Uwaga:** Może mieć kolizje hashów (użyj podwójnego hashowania dla pewności)

#### **Manacher** - `string_algorithms/manacher.cpp`
- **Kiedy użyć:** Znajdowanie najdłuższego palindromu w stringu
- **Zastosowanie:**
  - Najdłuższy palindrom w stringu
  - Wszystkie palindromy w stringu
  - Liczenie palindromów
- **Złożoność:** O(n) gdzie n to długość stringa
- **Uwaga:** Najszybszy algorytm do znajdowania palindromów

## Algorytmy matematyczne

### Podstawowe

#### **NWD/NWW** - `math_algorithms/gcd_lcm.cpp`
- **Kiedy użyć:** Największy wspólny dzielnik, najmniejsza wspólna wielokrotność
- **Zastosowanie:**
  - Upraszczanie ułamków
  - Sprawdzanie względnej pierwszości
  - Problemy matematyczne
  - Rozszerzony algorytm Euklidesa dla równań diofantycznych
  - Modular inverse
- **Złożoność:** O(log(min(a, b)))
- **Uwaga:** Zawiera również rozszerzony algorytm Euklidesa i modular inverse

#### **Sito Eratostenesa** - `math_algorithms/sieve.cpp`
- **Kiedy użyć:** Lista liczb pierwszych do n, sprawdzanie pierwszości
- **Zastosowanie:**
  - Lista liczb pierwszych
  - Sprawdzanie pierwszości
  - Faktoryzacja (z modyfikacją)
  - Problemy z liczbami pierwszymi
- **Złożoność:** O(n log log n)
- **Uwaga:** Najszybszy sposób na znalezienie wszystkich liczb pierwszych do n

#### **Faktoryzacja** - `math_algorithms/factorization.cpp`
- **Kiedy użyć:** Rozkład liczby na czynniki pierwsze
- **Zastosowanie:**
  - Rozkład na czynniki pierwsze
  - Liczba dzielników
  - Suma dzielników
  - Euler's totient function
- **Złożoność:** O(√n)
- **Uwaga:** Zawiera również funkcje pomocnicze (liczba dzielników, suma dzielników)

#### **Potęgowanie modularne** - `math_algorithms/modular_exponentiation.cpp`
- **Kiedy użyć:** Duże potęgi modulo
- **Zastosowanie:**
  - Duże potęgi modulo
  - RSA encryption
  - Modular arithmetic
  - Szybkie potęgowanie
- **Złożoność:** O(log exponent)
- **Uwaga:** Zawiera również modular inverse używając małego twierdzenia Fermata

#### **Symbol Newtona** - `math_algorithms/binomial_coefficient.cpp`
- **Kiedy użyć:** Współczynniki dwumianowe (n choose k)
- **Zastosowanie:**
  - Kombinatoryka
  - Prawdopodobieństwo
  - Trójkąt Pascala
  - Współczynniki dwumianowe
- **Złożoność:** O(n²) preprocessing, O(1) zapytanie lub O(k) dla pojedynczego
- **Uwaga:** Można rozszerzyć o modular binomial coefficient

## Geometria

#### **Convex Hull** - `geometry/convex_hull.cpp`
- **Kiedy użyć:** Otoczka wypukła punktów
- **Zastosowanie:**
  - Otoczka wypukła punktów
  - Najdalsza para punktów
  - Problemy geometryczne
  - Minimalny wielokąt zawierający wszystkie punkty
- **Złożoność:** O(n log n) - sortowanie + O(n) - budowanie
- **Uwaga:** Implementacja używa Andrew's Monotone Chain

#### **Podstawowe funkcje geometryczne** - `geometry/geometry_basics.cpp`
- **Kiedy użyć:** Podstawowe operacje geometryczne
- **Zastosowanie:**
  - Pole wielokąta (Shoelace formula)
  - Sprawdzanie położenia punktów
  - Odległości
  - Przecinanie się odcinków
  - Point in polygon
- **Złożoność:** Różna w zależności od operacji
- **Uwaga:** Zbiór podstawowych funkcji pomocniczych

## Programowanie dynamiczne

#### **LIS (Longest Increasing Subsequence)** - `dynamic_programming/lis.cpp`
- **Kiedy użyć:** Najdłuższy rosnący podciąg
- **Zastosowanie:**
  - Najdłuższy rosnący podciąg
  - Problemy optymalizacyjne
  - DP problems
  - Sequence problems
- **Złożoność:** O(n log n) - optymalna wersja
- **Uwaga:** Zawiera wersję O(n log n) i O(n²) z rekonstrukcją

#### **LCS (Longest Common Subsequence)** - `dynamic_programming/lcs.cpp`
- **Kiedy użyć:** Najdłuższy wspólny podciąg dwóch stringów
- **Zastosowanie:**
  - Porównywanie stringów
  - Diff algorithms
  - DNA sequence alignment
  - String comparison
- **Złożoność:** O(n * m) gdzie n, m to długości stringów
- **Uwaga:** Można zoptymalizować pamięć do O(min(n, m))

#### **Edit Distance (Levenshtein)** - `dynamic_programming/edit_distance.cpp`
- **Kiedy użyć:** Minimalna liczba operacji do przekształcenia jednego stringa w drugi
- **Zastosowanie:**
  - Porównywanie stringów
  - Spell checking
  - DNA sequence alignment
  - String similarity
- **Złożoność:** O(n * m)
- **Uwaga:** Operacje: wstawianie, usuwanie, zamiana

#### **Knapsack** - `dynamic_programming/knapsack.cpp`
- **Kiedy użyć:** Problem plecakowy
- **Zastosowanie:**
  - Optymalizacja zasobów
  - Problemy decyzyjne
  - Resource allocation
  - 0/1 i unbounded knapsack
- **Złożoność:** O(n * W) gdzie n to liczba przedmiotów, W to pojemność
- **Uwaga:** Zawiera implementacje dla 0/1 i unbounded knapsack

## Algorytmy numeryczne i techniki

#### **Two Pointers** - `other_techniques/two_pointers.cpp`
- **Kiedy użyć:** Problemy na tablicach/listach wymagające dwóch wskaźników
- **Zastosowanie:**
  - Suma na przedziale
  - Usuwanie duplikatów
  - Merging sorted arrays
  - Sliding window problems
  - Najdłuższy podciąg bez powtórzeń
- **Złożoność:** O(n) - liniowy
- **Uwaga:** Bardzo użyteczna technika dla problemów liniowych

#### **Mo's Algorithm** - `other_techniques/mos_algorithm.cpp`
- **Kiedy użyć:** Zapytania offline na przedziałach
- **Zastosowanie:**
  - Zapytania o sumę/liczbę unikalnych elementów na przedziale
  - Problemy z zapytaniami offline
  - Range queries offline
- **Złożoność:** O((n + q) * √n) gdzie n to rozmiar tablicy, q to liczba zapytań
- **Uwaga:** Działa tylko dla zapytań offline, wymaga możliwości aktualizacji odpowiedzi

#### **Prefix Sums** - `other_techniques/prefix_sums.cpp`
- **Kiedy użyć:** Suma na przedziale w O(1)
- **Zastosowanie:**
  - Suma na przedziale w O(1)
  - Cumulative sums
  - Range sum queries
  - 2D prefix sums dla prostokątów
- **Złożoność:** O(n) preprocessing, O(1) zapytanie
- **Uwaga:** Najprostsza struktura dla sum na przedziałach

## Przewodnik wyboru algorytmu

### Zapytania na przedziałach:
- **Tylko zapytania, bez aktualizacji:** Sparse Table (O(1) zapytanie)
- **Zapytania + aktualizacje pojedynczych elementów:** 
  - Suma → Fenwick Tree (prostsze) lub Segment Tree
  - Min/Max/GCD → Segment Tree
- **Zapytania + aktualizacje przedziałów:** Segment Tree z lazy propagation
- **Suma prefiksowa z aktualizacjami:** Fenwick Tree
- **Proste sumy bez aktualizacji:** Prefix Sums

### Najkrótsze ścieżki:
- **Graf nieważony:** BFS
- **Graf ważony, nieujemne wagi:** Dijkstra
- **Graf ważony, ujemne wagi (bez cykli):** Bellman-Ford
- **Wszystkie pary (mały graf V ≤ 400):** Floyd-Warshall
- **Wszystkie pary (duży graf):** Dijkstra z każdym wierzchołkiem jako źródłem

### Wyszukiwanie wzorca w tekście:
- **Ogólne zastosowanie:** KMP lub Z-Algorithm
- **Wiele wzorców:** Rabin-Karp
- **Palindromy:** Manacher

### Problemy na drzewach:
- **Najkrótsza ścieżka między wierzchołkami:** LCA
- **Przeszukiwanie:** DFS lub BFS
- **MST:** Kruskal lub Prim

### Problemy kombinatoryczne:
- **Współczynniki dwumianowe:** Symbol Newtona
- **Permutacje/kombinacje:** STL next_permutation lub własna implementacja

### Problemy geometryczne:
- **Otoczka wypukła:** Convex Hull
- **Pole wielokąta:** Shoelace formula (geometry_basics.cpp)
- **Point in polygon:** Ray casting (geometry_basics.cpp)

## Uwagi

- Wszystkie algorytmy powinny być zoptymalizowane pod kątem czasu wykonania
- Ważne są również wersje zoptymalizowane pamięciowo
- Przygotuj szablony z komentarzami wyjaśniającymi parametry
- Przetestuj każdy algorytm przed zawodami
- Każdy plik zawiera przykład użycia w funkcji `main()`
