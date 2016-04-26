#ifndef skiResorts_h
#define skiResorts_h

#include<vector>
#include<iostream>

struct vertex;

struct adjVertex{
    vertex *v;
    int weight;
};

struct vertex{
    int ID;
    vertex *parent;
    std::string name;
    int district;
    bool visited;
    int distance;
    std::vector<adjVertex> adj;
};

struct queueVertex{
    int distance;
    //std::vector<vertex> path;
    std::vector<vertex *> path;
};
class skiResorts
{
public:
    skiResorts();
    ~skiResorts();
    void addEdge(std::string v1, std::string v2, int weight);
    void addVertex(std::string name);
    void displayEdges();
    void assignDistricts();
    void shortestPath(std::string startingCity,std::string endingCity);
    void shortestDistance(std::string city1, std::string city2);
    //vertex * findVertex(std::string name);
    int district;
    
protected:
private:
    std::vector<vertex> vertices;
    vertex * findVertex(std::string name);
    void BFTraversalLabel(std::string startingCity, int distID);
    
};

#endif /* skiResorts_h */
