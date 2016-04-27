#ifndef GRAPH_H
#define GRAPH_H
#include <vector>
#include <iostream>

struct vertex;

struct adjVertex{
    vertex *v;
    int weight;
};

struct vertex{
    std::string name;
    bool visited;
    int distance;
    std::vector<adjVertex> adj;
    vertex *previous;   
    int district; 
};

struct queueVertex{
    int distance;
    std::vector<vertex> path;
};

class Graph{
public:
    Graph();
    ~Graph();
    void addEdge(std::string v1, std::string v2, int weight);
    void addVertex(std::string name);
    void findShortestPath(std::string startskiResort, std::string endskiResort);
    void depthFirstTraversal(std::string startskiResort);
    void dijkstra(std::string startskiResort, std::string endskiResort);
    void breadthFirstTraversal(std::string startskiResort);
    void findDistricts(std::string startskiResort);
    void deleteEdge(std::string startskiResort, std::string endskiResort);
    void deleteVertex(std::string skiResort);
    void displayEdges();
    vertex * findVertex(std::string name);
    int district;
protected:
private:
    std::vector<vertex> vertices;
    int districtindex;

};

#endif // GRAPH_H