#include "points.h"
// #include "helper.h"
#include <iostream>
#include <cmath>
using namespace std;

// Custom comparison function to sort points by y-coordinate with x-coordinate as tiebreaker

double BOUNDmaxx = MAX_DOUBLE;
double BOUNDminx = MAX_DOUBLE;
double BOUNDminy = MAX_DOUBLE;
double BOUNDmaxy = MIN_DOUBLE;
Point sweeper; // global to be able to access sweep coordinates from multiple functions lol.
bool comparePoints(const Point &p1, const Point &p2)
{
    if (p1.y != p2.y)
    {
        return p1.y < p2.y; // Sort by y-coordinate
    }
    return p1.x < p2.x; // Use x-coordinate as tiebreaker
}

// Function to sort points by y-coordinate with x-coordinate as tiebreaker
void sortPoints(std::vector<Point> &points)
{
    std::sort(points.begin(), points.end(), comparePoints);
}

double find_breakpoint(Point *p1, Point *p2, int n)
{
    double ly = sweeper.y;
    // if (n > 1)
    //     cout << "aayein? 0 ya 1 do na" << endl;
    if (p1 == p2 || (p1->x == p2->x && p1->y == p2->y)) // used when searching for arcabove
        return p1->x;
    if (p1->x == MIN_DOUBLE || p2->x == MIN_DOUBLE)
        return MIN_DOUBLE;
    if (p1->x == MAX_DOUBLE || p2->x == MAX_DOUBLE)
        return MAX_DOUBLE;
    double x1 = p1->x;
    double y1 = p1->y;
    double x2 = p2->x;
    double y2 = p2->y;

    if (x1 == x2)
    {
        double ymid = (y1 + y2) / 2;
        if (n == 1)
            return x1 + sqrt((ly - ymid) * (ly - ymid) - (y1 - y2) * (y1 - y2) / 4);
        else if (n == 0)
            return x1 - sqrt((ly - ymid) * (ly - ymid) - (y1 - y2) * (y1 - y2) / 4);
    }

    double m = (y2 - y1) / (-x2 + x1);
    double c = (x1 + x2) / 2 - m * (y1 + y2) / 2;

    // x = my + c
    double a = m * m;
    double b = 2 * (m * c - m * x1 - y1 + ly);
    double c1 = (c - x1) * (c - x1) + y1 * y1 - ly * ly;

    double ans;
    if (n == 0)
        ans = ((-1) * b - sqrt(b * b - 4 * a * c1)) / (2 * a);
    else if (n == 1)
        ans = ((-1) * b + sqrt(b * b - 4 * a * c1)) / (2 * a);
    else if (n == 2)
    {
        // cout << "sweeper   " << sweeper.x << ", " << sweeper.y << endl;
        // cout << "m: " << m << " c: " << c << endl;
        // cout << "a: " << a << " b: " << b << " c1: " << c1 << endl;
        cout << m * (((-1) * b - sqrt(b * b - 4 * a * c1)) / (2 * a)) + c << endl;
        cout << m * (((-1) * b + sqrt(b * b - 4 * a * c1)) / (2 * a)) + c << endl;
    }

    return m * ans + c;
}

bool ComparatorSet::operator()(Site p1, Site p2) const
{
    double ans1 = (round(find_breakpoint(p1.first, p1.second, p1.n) * 1000.0) / 1000.0);
    double ans2 = (round(find_breakpoint(p2.first, p2.second, p2.n) * 1000.0) / 1000.0);
    // if (ans1 == ans2 && p1.first->x == p2.first->x && p1.first->y == p2.first->y && p1.second->x == p2.second->x && p1.second->y == p2.second->y)
    // {
    //     // this case is for when i'm inserting 0 and 1 of 2 parabolas
    //     double m = (p1.first->y - p1.second->y) / (-p1.first->x + p1.second->x);
    //     if (m > 0)
    //         return (p1.first->x > p2.first->x);
    //     else
    //         return (p1.first->x < p2.first->x);
    // }
    // {
    //     // this case is for when i'm inserting 0 and 1 of 2 parabolas
    //     double m = (p1.first->y - p1.second->y) / (-p1.first->x + p1.second->x);
    //     if (m > 0)
    //     {
    //         if (p1.n == 0)
    //             return (ans1 < ans2);
    //         else
    //             return (ans1 > ans2);
    //     }
    //     else
    //     {
    //         if (p1.n == 0)
    //             return (ans1 > ans2);
    //         else
    //             return (ans1 < ans2);
    //     }
    // }

    return ans1 < ans2;
}

bool ComparatorQueue::operator()(Point p1, Point p2) const
{
    return p1.y < p2.y;
}

bool ComparatorMap::operator()(const Site &a, const Site &b) const
{
    if (a.first->x != b.first->x)
        return a.first->x < b.first->x;
    else if (a.first->y != b.first->y)
        return a.first->y < b.first->y;
    else if (a.second->x != b.second->x)
        return a.second->x < b.second->x;
    else if (a.second->y != b.second->y)
        return a.second->y < b.second->y;
    else
        return a.n < b.n;
}

Point find_circumcentre(Point *p1, Point *p2, Point *p3)
{
    // Calculate midpoints
    if (p1->x == MIN_DOUBLE || p1->x == MAX_DOUBLE)
        return {MIN_DOUBLE, MAX_DOUBLE, -1};
    else if (p3->x == MAX_DOUBLE || p3->x == MIN_DOUBLE)
        return {MAX_DOUBLE, MAX_DOUBLE, -1};
    else if (p2->x == MIN_DOUBLE || p2->x == MAX_DOUBLE)
        return {p2->x, MAX_DOUBLE, -1};
    else if (p1 == p3 || p1 == p2 || p2 == p3)
        return {MAX_DOUBLE, MAX_DOUBLE, -1}; // 2 same points, no circumcentre huihuihui
    Point midAB = {(p1->x + p2->x) / 2, (p1->y + p2->y) / 2, false};
    Point midBC = {(p2->x + p3->x) / 2, (p2->y + p3->y) / 2, false};
    // Calculate slopes of perpendicular bisectors
    double slopeAB = (-p2->x + p1->x) / (p2->y - p1->y);
    double slopeBC = (-p3->x + p2->x) / (p3->y - p2->y);

    // Calculate circumcenter coordinates
    double x_U = (midAB.y - midBC.y + slopeBC * midBC.x - slopeAB * midAB.x) / (slopeBC - slopeAB);
    double y_U = slopeAB * (x_U - midAB.x) + midAB.y;
    y_U = y_U - sqrt((p1->x - x_U) * (p1->x - x_U) + (p1->y - y_U) * (p1->y - y_U));
    // y_U now is the bottommost point of circle, not circumcentre

    if (y_U > sweeper.y)
        return {x_U, y_U, -1};

    return {x_U, y_U, 1};
}