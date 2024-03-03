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
#endif // HELPER_H
