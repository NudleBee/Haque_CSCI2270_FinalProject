# Haque_CSCI2270_FinalProject

// Daaniyal Haque 
// CSCI2270 Final Project

Project Summary:

My project is an extension of the zombies graph assignment. The theme of the graph is ski 
resorts in the continental United States. It includes all the functionality of the 
zombie assignment, plus a few more search options and the option to delete
edges and vertexs in the graph. The graph is created by reading in the text file and 
creating the vertices and edges. My added functions include depth first traversal, breadth
first traversal, delete edge, delete vertex and an implementation of dijkstras algorithm.
This implementation finds the shortest distance between two resorts.

How to Run:

To run this program, you can simply open up the xcode project provided, or you can open 
the main.cpp, graph.cpp and graph.h in your own compiler. First initialize the districts; 
this assigns all connected components a district id. Then you can choose from any of the 
main menu options. "Show all ski resorts" will" display all the edges of the graph. If you 
choose "Print Ski Resorts", you have the option to either use breadth first traversal or 
depth first traversal. "Find shortest distance" uses dijkstra's algorithm to find the 
shortest distance between two ski resorts. If you delete an edge or vertex from a graph, 
it can no longer be accessed in any of the functions. 

Dependencies: 

Most compilers should be able to run this program. Make sure resortCities.txt is in the 
same folder as the codeprojects file. If file does not open in xcode, go to product-
>scheme->edit scheme-> and then manually choose the directory for the txt file. 

System Requirements: 

Can run on all platforms. Works best with xcode. I have included the Xcode codeproject. 

Group Members: 

None

Contributors: 

My roommates helped me with a few things along with debugging

Open issues/bugs: 


