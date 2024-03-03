#include "helper.h"
#include <iostream>
#include <random>
#include "global.h"
using namespace std;

// Function to parse a CSV file and create a vector of points
std::vector<Point> parseCSV(const std::string &filename)
{
    cout << "Parsing CSV" << endl;
    std::vector<Point> points;
    std::ifstream file(filename);
    // cout << "File opened" << endl;
    if (!file.is_open())
    {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return points;
    }
    // cout << "File opened1" << endl;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<double> dist(0, 1e-3);
    double noise;
    std::string line;
    while (std::getline(file, line))
    {
        // cout << "Reading line" << endl;
        std::istringstream iss(line);
        std::string token;
        std::getline(iss, token, ','); // Read x coordinate
        double x = std::stod(token);
        noise = dist(gen);
        x += noise;
        noise = dist(gen);
        std::getline(iss, token, ','); // Read y coordinate
        double y = std::stod(token);
        y += noise;
        points.push_back({x, y, false});
    }
    // cout << "File closed" << endl;
    file.close();
    cout << "Parse complete" << endl;
    return points;
}

//Function to finally give the output to output.txt
void saveEdgelistToCSV(const std::vector<std::pair<Point *, Point *>> &edgelist, const std::string &filename)
{
    std::ofstream outfile(filename);
    if (!outfile.is_open())
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }
    std::ofstream boundfile("bounding_values.csv");
    if (!boundfile.is_open())
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    // Write header (optional)
    outfile << "point1.x,point1.y,point2.x,point2.y" << std::endl;
    boundfile << BOUNDminx << "," << BOUNDminy << "," << BOUNDmaxx << "," << BOUNDmaxy << std::endl;
    // Write each edge
    for (const auto &edge : edgelist)
    {
        outfile << edge.first->x << "," << edge.first->y << ","
                << edge.second->x << "," << edge.second->y << std::endl;
    }

    outfile.close();
    std::cout << "Edgelist saved to " << filename << std::endl;
}
