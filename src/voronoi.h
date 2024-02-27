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

    vector<pair<Point *, Point *>> edgelist;

    // Function to retrieve the doubly-connected edge list
    // std::vector<Face> getDCEL();

private:
    // Balanced binary search tree to represent the status structure
    multiset<Site, ComparatorSet> T;

    // Event queue for handling leaf and circle events
    priority_queue<Point, vector<Point>, ComparatorQueue> Q;

    map<Site, EdgeData, ComparatorMap> edgemap; // maps a set of 2 points to the edge data

    map<set<Point *>, int> circlemap; // maps a set of 3 points to whether it is a valid (1) or not (0), or -1 (finished)

    // Doubly-connected edge list
    // std::vector<Face> DCEL;
    double parabola_at_x(Point *p);

    double parabolaatx(Point *p, double x);

    // Function to handle a leaf event
    void handleSiteEvent(Point &event);

    // Function to handle a circle event
    void handleCircleEvent(Point &event);

    // Function to finalize the construction of the Voronoi diagram
    void finalizeDiagram();

    // Function to find the arc vertically above a point
    std::multiset<Site, ComparatorSet>::iterator findArcAbove(Point &event);

    Point *findLeaf(std::multiset<Site, ComparatorSet>::iterator next, std::multiset<Site, ComparatorSet>::iterator prev);

    // void add_to_edge_map(Point *pl, Point *q, Point *pr, Point *event);

    void add_edge(Site s, Point *event);

    Point find_bound_box_intersection(Site s, EdgeData &edge);

    void print_edgemap();

    void print_circlemap();

    void print_Q();

    void print_T();
};

#endif // VORONOI_H
