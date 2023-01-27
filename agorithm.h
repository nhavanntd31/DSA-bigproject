#include <bits/stdc++.h>
using namespace std;
const int INF = 1e9;
const int radius = 10;
struct Vertex
{
    int x;
    int y;
    string name;
};
float tinhKhoangCach (pair<float,float> diem1, pair<float,float> diem2){
    return sqrt((diem1.first-diem2.first)*(diem1.first-diem2.first)+(diem1.second-diem2.second)*(diem1.second-diem2.second));
}
using Point = std::pair<float, float>;
constexpr auto eps = 1e-14;

double sq(double x) {
    return x * x;
}

std::vector<Point> intersects( Point &p1,  Point &p2,  Point &cp, double r, bool segment) {
    std::vector<Point> res;
    auto x0 = cp.first;
    auto y0 = cp.second;
    auto x1 = p1.first;
    auto y1 = p1.second;
    auto x2 = p2.first;
    auto y2 = p2.second;
    auto A = y2 - y1;
    auto B = x1 - x2;
    auto C = x2 * y1 - x1 * y2;
    auto a = sq(A) + sq(B);
    double b, c;
    bool bnz = true;
    if (abs(B) >= eps) {
        b = 2 * (A * C + A * B * y0 - sq(B) * x0);
        c = sq(C) + 2 * B * C * y0 - sq(B) * (sq(r) - sq(x0) - sq(y0));
    } else {
        b = 2 * (B * C + A * B * x0 - sq(A) * y0);
        c = sq(C) + 2 * A * C * x0 - sq(A) * (sq(r) - sq(x0) - sq(y0));
        bnz = false;
    }
    auto d = sq(b) - 4 * a * c; // discriminant
    if (d < 0) {
        return res;
    }

    // checks whether a point is within a segment
    auto within = [x1, y1, x2, y2](double x, double y) {
        auto d1 = sqrt(sq(x2 - x1) + sq(y2 - y1));  // distance between end-points
        auto d2 = sqrt(sq(x - x1) + sq(y - y1));    // distance from point to one end
        auto d3 = sqrt(sq(x2 - x) + sq(y2 - y));    // distance from point to other end
        auto delta = d1 - d2 - d3;
        return abs(delta) < eps;                    // true if delta is less than a small tolerance
    };

    auto fx = [A, B, C](double x) {
        return -(A * x + C) / B;
    };

    auto fy = [A, B, C](double y) {
        return -(B * y + C) / A;
    };

    auto rxy = [segment, &res, within](double x, double y) {
        if (!segment || within(x, y)) {
            res.push_back(std::make_pair(x, y));
        }
    };

    double x, y;
    if (d == 0.0) {
        // line is tangent to circle, so just one intersect at most
        if (bnz) {
            x = -b / (2 * a);
            y = fx(x);
            rxy(x, y);
        } else {
            y = -b / (2 * a);
            x = fy(y);
            rxy(x, y);
        }
    } else {
        // two intersects at most
        d = sqrt(d);
        if (bnz) {
            x = (-b + d) / (2 * a);
            y = fx(x);
            rxy(x, y);
            x = (-b - d) / (2 * a);
            y = fx(x);
            rxy(x, y);
        } else {
            y = (-b + d) / (2 * a);
            x = fy(y);
            rxy(x, y);
            y = (-b - d) / (2 * a);
            x = fy(y);
            rxy(x, y);
        }
    }

    return res;
}
pair<pair<float,float>,pair<float,float>> getIntersectionCoordinates(Vertex v1, Vertex v2){
    pair<float, float> tam1 = {v1.x, v1.y};
    pair<float, float> tam2 = {v2.x, v2.y};
    vector<Point> set1= intersects(tam1,tam2,tam1,radius,false);
    vector<Point> set2= intersects(tam1,tam2,tam2,radius,false);
    float minDistance = min(min(tinhKhoangCach(set1[0],set2[0]),tinhKhoangCach(set1[0],set2[1])),min(tinhKhoangCach(set1[1],set2[0]),tinhKhoangCach(set1[1],set2[1])));
     if (minDistance == tinhKhoangCach(set1[0],set2[0]))
    {
        pair<float,float> g1 = set1[0];
        pair<float,float> g2 = set2[0];
        return {g1,g2};
    } else if (minDistance == tinhKhoangCach(set1[0],set2[1]))
    {
        pair<float,float> g1 = set1[0];
        pair<float,float> g2 = set2[1];
        return {g1,g2};
    } else if (minDistance == tinhKhoangCach(set1[1],set2[0]) )
    {
        pair<float,float> g1 = set1[1];
        pair<float,float> g2 = set2[0];
        return {g1,g2};
    } else 
    {
        pair<float,float> g1 = set1[1];
        pair<float,float> g2 = set2[1];
        return {g1,g2};
    }   
}
pair<pair<int, int>, pair<int, int>> getArrowCoordinates(pair<int, int> c1, pair<int, int> c2)
{
    if (c2.second - c1.second > 0 && c2.first - c1.first > 0)
    {
        return {{c2.first,c2.second -10},{c2.first-10,c2.second}};
    }
    else if (c2.second - c1.second > 0 && c2.first - c1.first < 0 )
    {
        return {{c2.first,c2.second -10},{c2.first+10,c2.second}};
    } else if (c2.second - c1.second < 0 && c2.first - c1.first > 0)
    {
        return {{c2.first,c2.second +10},{c2.first-10,c2.second}};
    }
    else if (c2.second - c1.second < 0 && c2.first - c1.first < 0 )
    {
        return {{c2.first,c2.second +10},{c2.first +10,c2.second}};
    } else if ( c2.second == c1.second )
    {
        if ( c2.first > c1.first) 
            return {{c2.first-10,c2.second -10},{c2.first -10,c2.second+10}};
        else
            return {{c2.first+10,c2.second -10},{c2.first +10,c2.second+10}}; 
    } else if (c2.first == c1.first)
    {
        if (c2.second > c1.second)
            return  {{c2.first-10,c2.second -10},{c2.first +10,c2.second-10}};
        else 
            return {{c2.first-10,c2.second +10},{c2.first +10,c2.second+10}};
    }
    
}

char *stringToChars(string s)
{
    char *name = &s[0];
    return name;
}; 
char *numberToChars(int n)
{
    string s = to_string(n);
    return stringToChars(s);
};

