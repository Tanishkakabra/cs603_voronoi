#include "points.h"
#include "voronoi.h"
#include <iostream>
#include <fstream>
#include <utility>
#include "helper.h"

int main(int argc, char *argv[])
{
    cout << "Hello World" << endl;
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <filename.csv>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    cout << "Filename: " << filename << endl;
    std::vector<Point> points = parseCSV(filename);
    cout << "Points: " << points.size() << endl;
    Voronoi vor;
    vor.construct(points);
    cout << "Edges: " << vor.edgelist.size() << endl;
    saveEdgelistToCSV(vor.edgelist, "output.csv");
    cout << "Done" << endl;

    return 0;
}
