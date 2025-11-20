/*
 * Trie (Drzewo prefiksowe)
 * 
 * Struktura danych pozwalająca na:
 * - Wstawianie stringa w czasie O(m) gdzie m to długość stringa
 * - Wyszukiwanie stringa w czasie O(m)
 * - Wyszukiwanie wszystkich stringów z danym prefiksem
 * 
 * Zastosowanie:
 * - Autocomplete
 * - Wyszukiwanie prefiksów
 * - Zliczanie stringów z danym prefiksem
 * - XOR queries (binary trie)
 * 
 * Złożoność:
 * - Pamięć: O(ALPHABET_SIZE * N * M) gdzie N to liczba stringów, M to średnia długość
 * - Wstawianie: O(m)
 * - Wyszukiwanie: O(m)
 */

#include <bits/stdc++.h>

using namespace std;

struct TrieNode {
    vector<int> next;
    bool is_end;
    int count; // liczba stringów kończących się w tym węźle
    
    TrieNode(int alphabet_size = 26) {
        next.resize(alphabet_size, -1);
        is_end = false;
        count = 0;
    }
};

vector<TrieNode> trie_nodes;
int trie_alphabet_size;
int trie_root;

void trie_init(int alphabet_size = 26) {
    trie_alphabet_size = alphabet_size;
    trie_nodes.clear();
    trie_nodes.push_back(TrieNode(alphabet_size));
    trie_root = 0;
}

void trie_insert(const string& s) {
    int node = trie_root;
    for (char c : s) {
        int idx = c - 'a'; // dla małych liter, można zmienić
        if (trie_nodes[node].next[idx] == -1) {
            trie_nodes[node].next[idx] = trie_nodes.size();
            trie_nodes.push_back(TrieNode(trie_alphabet_size));
        }
        node = trie_nodes[node].next[idx];
    }
    trie_nodes[node].is_end = true;
    trie_nodes[node].count++;
}

bool trie_search(const string& s) {
    int node = trie_root;
    for (char c : s) {
        int idx = c - 'a';
        if (trie_nodes[node].next[idx] == -1) {
            return false;
        }
        node = trie_nodes[node].next[idx];
    }
    return trie_nodes[node].is_end;
}

bool trie_starts_with(const string& prefix) {
    int node = trie_root;
    for (char c : prefix) {
        int idx = c - 'a';
        if (trie_nodes[node].next[idx] == -1) {
            return false;
        }
        node = trie_nodes[node].next[idx];
    }
    return true;
}

// Przykład użycia:
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    trie_init();
    
    trie_insert("abc");
    trie_insert("ab");
    trie_insert("abd");
    trie_insert("xyz");
    
    cout << (trie_search("ab") ? "TAK" : "NIE") << '\n'; // TAK
    cout << (trie_search("abc") ? "TAK" : "NIE") << '\n'; // TAK
    cout << (trie_search("abcd") ? "TAK" : "NIE") << '\n'; // NIE
    cout << (trie_starts_with("ab") ? "TAK" : "NIE") << '\n'; // TAK
    
    return 0;
}

