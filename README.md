Directory structure:
build - Contains the executables; no need to bother about them
inputs - can contain the input files; currently empty
src - contains the source code
    global.h - Declares some global variables. I probably didnt need to do thi explicitly; but atleast the double declaration   errors went away
    helper.cpp / helper.h - Contains the parseCSV and savetoCSV functions. parseCSV can be changed according to the input file that we want
    points.cpp / points.h - contains functions and structs related to our overall functionality
    voronoi.cpp / voronoi.h - contains the Voronoi class and the major functions to calculate the voronoi diagram
    main.cpp - uses the voronoi class to work upon the points given by input.csv
Makefile - run make to compile
my_program - the executable. Run 
        ./my_program input.csv > debug.txt
debug.txt - Contains logs of the debugging print statements
output.csv - contains the edgelist in the form point1.x, point1.y, point2.x, point2.y
plot.py - run
        python3 plot.py
draws and shows the plot.
