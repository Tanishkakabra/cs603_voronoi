#ifndef POINTS_H

#define POINTS_H

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <cmath>

// Structure to represent a point with x and y coordinates
#define MIN_DOUBLE -1.0e+37
#define MAX_DOUBLE 1.0e+37
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

struct EdgeData
{
    Point *start;
    // Point *vertex3;
    Point *end;
};

struct CirclePoints
{
    Point *pr;
    Point *q;
    Point *pl;
};

struct Site
{
    Point *first;
    Point *second;
    int n;
};

struct ComparatorSet
{
    bool operator()(Site p1, Site p2) const;
};

struct ComparatorQueue
{
    bool operator()(Point p1, Point p2) const;
};

struct ComparatorMap
{
    bool operator()(const Site &a, const Site &b) const;
};

bool comparePoints(const Point &p1, const Point &p2);
void sortPoints(std::vector<Point> &points);
std::vector<Point> parseCSV(const std::string &filename);
double find_breakpoint(Point *p1, Point *p2, int n);

Point find_circumcentre(Point *p1, Point *p2, Point *p3);

#endif // POINTS_H