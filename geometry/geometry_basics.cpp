/*
 * Podstawowe funkcje geometryczne
 * 
 * Zbiór podstawowych funkcji do operacji geometrycznych.
 * 
 * Zastosowanie:
 * - Pole wielokąta (Shoelace formula)
 * - Sprawdzanie położenia punktów
 * - Odległości
 * - Przecinanie się odcinków
 */

#include <bits/stdc++.h>

using namespace std;

struct Point {
    long long x, y;
    
    Point(long long x = 0, long long y = 0) : x(x), y(y) {}
    
    Point operator+(const Point& other) const {
        return Point(x + other.x, y + other.y);
    }
    
    Point operator-(const Point& other) const {
        return Point(x - other.x, y - other.y);
    }
    
    long long operator*(const Point& other) const {
        return x * other.x + y * other.y;
    }
    
    long long cross(const Point& other) const {
        return x * other.y - y * other.x;
    }
};

long long cross_product(const Point& a, const Point& b, const Point& c) {
    return (b - a).cross(c - a);
}

// Pole wielokąta (Shoelace formula)
long long polygon_area(const vector<Point>& polygon) {
    int n = polygon.size();
    long long area = 0;
    
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        area += polygon[i].x * polygon[j].y;
        area -= polygon[j].x * polygon[i].y;
    }
    
    return abs(area) / 2;
}

// Sprawdzanie czy punkt jest w wielokącie (ray casting)
bool point_in_polygon(const Point& p, const vector<Point>& polygon) {
    int n = polygon.size();
    bool inside = false;
    
    for (int i = 0, j = n - 1; i < n; j = i++) {
        if (((polygon[i].y > p.y) != (polygon[j].y > p.y)) &&
            (p.x < (polygon[j].x - polygon[i].x) * (p.y - polygon[i].y) / 
                   (polygon[j].y - polygon[i].y) + polygon[i].x)) {
            inside = !inside;
        }
    }
    
    return inside;
}

// Odległość między punktami
double distance(const Point& a, const Point& b) {
    long long dx = a.x - b.x;
    long long dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}

// Sprawdzanie czy odcinki się przecinają
bool segments_intersect(const Point& a, const Point& b, 
                        const Point& c, const Point& d) {
    long long o1 = cross_product(a, b, c);
    long long o2 = cross_product(a, b, d);
    long long o3 = cross_product(c, d, a);
    long long o4 = cross_product(c, d, b);
    
    if (o1 * o2 < 0 && o3 * o4 < 0) {
        return true;
    }
    
    // Sprawdzanie przypadków brzegowych (punkt na odcinku)
    if (o1 == 0 && (c.x >= min(a.x, b.x) && c.x <= max(a.x, b.x) &&
                    c.y >= min(a.y, b.y) && c.y <= max(a.y, b.y))) {
        return true;
    }
    if (o2 == 0 && (d.x >= min(a.x, b.x) && d.x <= max(a.x, b.x) &&
                    d.y >= min(a.y, b.y) && d.y <= max(a.y, b.y))) {
        return true;
    }
    if (o3 == 0 && (a.x >= min(c.x, d.x) && a.x <= max(c.x, d.x) &&
                    a.y >= min(c.y, d.y) && a.y <= max(c.y, d.y))) {
        return true;
    }
    if (o4 == 0 && (b.x >= min(c.x, d.x) && b.x <= max(c.x, d.x) &&
                    b.y >= min(c.y, d.y) && b.y <= max(c.y, d.y))) {
        return true;
    }
    
    return false;
}

// Przykład użycia:
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    int n;
    cin >> n;
    
    vector<Point> polygon(n);
    for (int i = 0; i < n; i++) {
        cin >> polygon[i].x >> polygon[i].y;
    }
    
    cout << "Pole wielokąta: " << polygon_area(polygon) << '\n';
    
    return 0;
}

