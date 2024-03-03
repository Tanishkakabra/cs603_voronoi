#ifndef HELPER_H
#define HELPER_H

#include "points.h"
#include <fstream>
#include <sstream>

// Structure to represent a point with x and y coordinates

//Function to parse a CSV file and return a vector of points
std::vector<Point> parseCSV(const std::string &filename);

//Function to save a vector of points to a CSV file
void saveEdgelistToCSV(const std::vector<std::pair<Point *, Point *>> &edgelist, const std::string &filename);

// breakpoint function
// manage MIN_DOUBLE and MAX_DOUBLE
// if p1 == p1, return p1.x. should only be used for findingarcabove, not for storing the actual leaves.
// breakpoint chud gayaaaaaa, i need both + and - depending on whether ive asked breakpoint for p,q or q,p
// to calculate breakpoints, use 0 and 1 huihuihui. Creates 2 copies, and then i can select leaf by finding common element in both copies.
// possible bug: p,q and q,p
// moye moye
// for bounding box, you have the the map with start found and end nullpointer. if i have the 2 points, i can find
// their perpendicular bisector and then find the intersection with the bounding box. Lessgooo. Altho konsa direction wo
// ek baar dekhna padega.
// comparators may have to be changed, since comparison may be buggy.
// should i clean up my queue to avoid repetetive meows?
// maybe for comparison i need to use the fabs function as well
#endif // HELPER_H
