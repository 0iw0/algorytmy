/*
 * Convex Hull (Otoczka wypukła)
 * 
 * Algorytm znajdowania najmniejszego wielokąta wypukłego zawierającego wszystkie punkty.
 * 
 * Zastosowanie:
 * - Otoczka wypukła punktów
 * - Najdalsza para punktów
 * - Problemy geometryczne
 * 
 * Złożoność:
 * - Czas: O(n log n) - sortowanie + O(n) - budowanie
 * - Pamięć: O(n)
 * 
 * Uwaga:
 * - Implementacja używa Andrew's Monotone Chain (prostsza niż Graham Scan)
 */

#include <bits/stdc++.h>

using namespace std;

struct Point {
    long long x, y;
    
    Point(long long x = 0, long long y = 0) : x(x), y(y) {}
    
    bool operator<(const Point& other) const {
        if (x != other.x) return x < other.x;
        return y < other.y;
    }
    
    Point operator-(const Point& other) const {
        return Point(x - other.x, y - other.y);
    }
};

long long cross_product(const Point& a, const Point& b) {
    return a.x * b.y - a.y * b.x;
}

long long cross_product(const Point& a, const Point& b, const Point& c) {
    return cross_product(b - a, c - a);
}

vector<Point> convex_hull(vector<Point>& points) {
    int n = points.size();
    if (n <= 1) return points;
    
    sort(points.begin(), points.end());
    
    vector<Point> hull;
    
    // Dolna część otoczki
    for (int i = 0; i < n; i++) {
        while (hull.size() >= 2 && 
               cross_product(hull[hull.size()-2], hull.back(), points[i]) <= 0) {
            hull.pop_back();
        }
        hull.push_back(points[i]);
    }
    
    // Górna część otoczki
    int lower_size = hull.size();
    for (int i = n - 2; i >= 0; i--) {
        while (hull.size() > lower_size && 
               cross_product(hull[hull.size()-2], hull.back(), points[i]) <= 0) {
            hull.pop_back();
        }
        hull.push_back(points[i]);
    }
    
    hull.pop_back(); // usuń duplikat pierwszego punktu
    return hull;
}

// Przykład użycia:
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    int n;
    cin >> n;
    
    vector<Point> points(n);
    for (int i = 0; i < n; i++) {
        cin >> points[i].x >> points[i].y;
    }
    
    vector<Point> hull = convex_hull(points);
    
    cout << "Otoczka wypukła ma " << hull.size() << " punktów:\n";
    for (const Point& p : hull) {
        cout << "(" << p.x << ", " << p.y << ") ";
    }
    cout << '\n';
    
    return 0;
}

