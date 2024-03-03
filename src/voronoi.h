// voronoi.h

#ifndef VORONOI_H
#define VORONOI_H

#include <vector>
#include <set>
#include "points.h"
#include <queue>
#include <map>
#include "global.h"

using namespace std;

class Voronoi
{
public:
    // Constructor
    Voronoi();

    // Destructor
    ~Voronoi();

    // Function to construct the Voronoi diagram
    void construct(const std::vector<Point> &points);

    // the edgelist
    vector<pair<Point *, Point *>> edgelist;

private:
    // Balanced binary search tree to represent the status structure
    multiset<Site, ComparatorSet> T;

    // Event queue for handling leaf and circle events
    priority_queue<Point, vector<Point>, ComparatorQueue> Q;

    map<Site, EdgeData, ComparatorMap> edgemap; // maps a set of 2 points to the edge data

    map<set<Point *>, int> circlemap; // maps a set of 3 points to whether it is a valid (1) or not (0), or -1 (finished)

    // Function to calculate the parabola at the x coordinate of current event point
    double parabola_at_x(Point *p);

    // Function to calculate the x of intersection of two parabolas
    double parabolaatx(Point *p, double x);

    // Function to handle a site event
    void handleSiteEvent(Point &event);

    // Function to handle a circle event
    void handleCircleEvent(Point &event);

    // Function to finalize the construction of the Voronoi diagram add bounding box etc
    void finalizeDiagram();

    // Function to find the common point between two Sites
    Point *findLeaf(std::multiset<Site, ComparatorSet>::iterator next, std::multiset<Site, ComparatorSet>::iterator prev);

    // Function to add an edge to the edgemap
    void add_edge(Site s, Point *event);

    // function to complete half edges
    Point find_bound_box_intersection(Site s, EdgeData edge);

    // debugging funcions to print the status structure, event queue, edgemap and circlemap
    void print_edgemap();

    void print_circlemap();

    void print_Q();

    void print_T();
};

#endif // VORONOI_H
