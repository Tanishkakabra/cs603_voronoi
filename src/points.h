#ifndef POINTS_H

#define POINTS_H

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <cmath>


// to represent inf and -inf
#define MIN_DOUBLE -1.0e+37
#define MAX_DOUBLE 1.0e+37

// Structure to represent a point with x and y coordinates
struct Point
{
    double x;
    double y;
    int isCircleEvent; // 0 for site event, 1 for circle event, -1 for false alarm
    Point(double x, double y, int isCircleEvent)
    {
        this->x = x;
        this->y = y;
        this->isCircleEvent = isCircleEvent;
    }
    Point()
    {
        this->x = 0;
        this->y = 0;
        this->isCircleEvent = 0;
    }
};

// Structure to represent an edge with start and end points
struct EdgeData
{
    Point *start;
    Point *end;
};

// Structure to represent a site (breakpoint) with 2 points and n = 0 or 1 to decide which of the 2 x coordinates to use
struct Site
{
    Point *first;
    Point *second;
    int n;
};

// Custom comparator for set of sites
struct ComparatorSet
{
    bool operator()(Site p1, Site p2) const;
};

// Custom comparator for priority queue of points
struct ComparatorQueue
{
    bool operator()(Point p1, Point p2) const;
};

// Custom comparator for map of sites
struct ComparatorMap
{
    bool operator()(const Site &a, const Site &b) const;
};

//this function isnt really used anywhere, but i wrote it anyways
bool comparePoints(const Point &p1, const Point &p2);

//this function isnt really used anywhere, but i wrote it anyways
void sortPoints(std::vector<Point> &points);

// find the breakpoint of 2 parabolas given their focus points and n = 0 or 1 to decide which of the 2 x coordinates to use
double find_breakpoint(Point *p1, Point *p2, int n);

// find the circumcentre event (bottommost point of the circle and not the actual circumcentre lol) of 3 points
Point find_circumcentre(Point *p1, Point *p2, Point *p3);

#endif // POINTS_H