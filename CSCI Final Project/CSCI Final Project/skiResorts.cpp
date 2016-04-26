// Daaniyal Haque
// Final Project
// Hoenigman


#include "skiResorts.h"
#include <vector>
#include <iostream>
#include <queue>

using namespace std;

skiResorts::skiResorts()
{
    district = 0;
}

skiResorts::~skiResorts()
{
    
}
void skiResorts::addEdge(string v1, string v2, int weight){
    
    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i].name == v1){
            for(int j = 0; j < vertices.size(); j++){
                if(vertices[j].name == v2 && i != j){
                    adjVertex av;
                    av.v = &vertices[j];
                    av.weight = weight;
                    vertices[i].adj.push_back(av);
                    //another vertex for edge in other direction
                    adjVertex av2;
                    av2.v = &vertices[i];
                    av2.weight = weight;
                    vertices[j].adj.push_back(av2);
                }
            }
        }
    }
}
void skiResorts::addVertex(string n){
    bool found = false;
    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i].name == n){
            found = true;
            cout<<vertices[i].name<<" found."<<endl;
        }
    }
    if(found == false){
        vertex v;
        v.name = n;
        v.district = -1;
        v.visited = false;
        vertices.push_back(v);
        
    }
}

void skiResorts::displayEdges(){ //loop through all vertices and adjacent vertices
    for(int i = 0; i < vertices.size(); i++){
        cout << vertices[i].district << ":";
        cout<<vertices[i].name<<"-->";
        for(int j = 0; j < vertices[i].adj.size(); j++){ //For each adjacent vertex
            cout<<vertices[i].adj[j].v->name;
            if (j != vertices[i].adj.size()-1){
                cout << "***";
            }
        }
        cout<<endl;
    }
}

void skiResorts::assignDistricts()
{
    int distID = 1;
    for(int i = 0; i < vertices.size(); i++)
    {
        if (vertices[i].district == -1)
        {
            BFTraversalLabel(vertices[i].name,distID);
            distID++;
        }
        
    }
}

void skiResorts::shortestPath(std::string startingCity, std::string endingCity){
    
    bool found = false;
    vertex * start = findVertex(startingCity);
    vertex * end = findVertex(endingCity);
    if (start == NULL || end == NULL)
    {
        cout << "One or more cities doesn't exist" << endl;
        return;
    }
    if (end->district != start->district)
    {
        cout << "No safe path between cities" << endl;
        return;
    }
    if (end->district == -1 || start->district == -1)
    {
        cout << "Please identify the districts before checking distances" << endl;
        return;
    }
    
    start->visited = true;
    start->distance = 0;
    queue<vertex*> q;
    q.push(start);
    vertex *foundVertex = NULL;
    while(q.empty()==false){
        vertex* n = q.front();
        q.pop();
        for(int x = 0; x < n->adj.size(); x++){
            if(n->adj[x].v->visited == false){
                n->adj[x].v->visited = true;
                n->adj[x].v->distance = n->distance + 1;
                n->adj[x].v->parent = n;
                if(n->adj[x].v->name == endingCity){
                    foundVertex = n->adj[x].v;
                    found = true;
                    break;
                }else{
                    q.push(n->adj[x].v);
                }
            }
        }
    }
    if(found == true){
        cout<<foundVertex->distance;
        vertex *temp = foundVertex;
        vector<string> names;
        while(temp != NULL){
            names.push_back(temp->name);
            temp = temp->parent;
        }
        for(int x = names.size()-1; x >= 0; x--){
            cout<<","<<names[x];
        }
        cout<<endl;
    }
}

