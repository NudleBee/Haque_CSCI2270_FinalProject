// Daaniyal Haque
// Final Project

#include "Graph.h"
#include <vector>
#include <iostream>
#include <stack>
#include <queue>
using namespace std;
Graph::Graph(){
districtindex = 1;
}

Graph::~Graph()
{
}

void Graph::addEdge(string v1, string v2, int weight){
    
    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i].name == v1){
            for(int j = 0; j < vertices.size(); j++){
                if(vertices[j].name == v2 && i != j){
                    adjVertex av;
                    av.v = &vertices[j];
                    av.weight = weight;
                    vertices[i].adj.push_back(av);
                    adjVertex av2;
                    av2.v = &vertices[i];
                    av2.weight = weight;
                    vertices[j].adj.push_back(av2);
                }
            }
        }
    }
}

void Graph::addVertex(string n){
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

void Graph::displayEdges(){ //loop through all vertices and adjacent vertices
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

void Graph::findDistricts(string startskiResort){
    vertex *s = NULL;
    vertex u;
    queue<vertex> myQueue;
    for (int i = 0; i < vertices.size(); i++){
        if (vertices[i].name == startskiResort){
            s = &vertices[i];
        }
    }
    if (district > 0 && s->visited == true){
        //does nothing
    }else{
        if (s->visited == false){
            district++;
        }
        s->visited = true;
        s->district = district;
        myQueue.push(*s);
        while (!myQueue.empty()){
            u = myQueue.front();
            myQueue.pop();
            vertex *v;
            for (int i = 0; i < u.adj.size(); i++){
                v = u.adj[i].v;
                if (v->visited == false){
                    u.adj[i].v->visited = true;
                    if (u.adj[i].weight != -1){
                        v->district = s->district;
                        
                    }
                    myQueue.push(*v);
                }
            }
        }
    }
}

void Graph::findShortestPath(string startskiResort, string endskiResort){
    vector<vertex> path;
    int distance;
    vertex *s = NULL;
    vertex *e = NULL;
    vertex u;
    bool found1 = false;
    bool found2 = false;
    bool dist = true;
    queue<queueVertex> myQueue;
    for (int i = 0; i < vertices.size(); i++){
        if (vertices[i].name == startskiResort){
            found1 = true;
            s = &vertices[i];
        }else if (vertices[i].name == endskiResort){
            found2 = true;
            e = &vertices[i];
        }
    }if (found1 && found2){
        if (s->district == -1){
            dist = false;
        }if ((s->district == e->district) && (s->district != -1) && (s->district == e->district)){
            for (int i = 0; i < vertices.size(); i++){
                if (vertices[i].name != s->name){
                    vertices[i].visited = false;
                }else{
                    vertices[i].visited = true;
                }
            }
            s->visited = true;
            queueVertex qv;
            qv.distance = 0;
            qv.path.push_back(*s);
            myQueue.push(qv);
            while (!(myQueue.empty())){
                qv = myQueue.front();
                myQueue.pop();
                vertex *v = NULL;
                int end = qv.path.size();
                for (int i = 0; i < qv.path[end-1].adj.size(); i++){
                    v = qv.path[end-1].adj[i].v;
                    if (v->visited == false){
                        path = qv.path;
                        v->visited = true;
                        distance = qv.distance + 1;
                        path.push_back(*v);
                        queueVertex temp;
                        temp.path = path;
                        temp.distance = distance;
                        if (v->name == endskiResort){
                            //return temp;
                            cout << temp.distance;
                            for (int j = 0; j < temp.path.size(); j++){
                                cout << "," << temp.path[j].name;
                            }
                        }else {
                            myQueue.push(temp);
                        }
                    }
                }
            }
            cout << endl;
        }
    }if(found1 == false || found2 == false){
        cout << "One or more resort not found" << endl;
    }else if (!dist){
        cout << "One or more resorts not found" << endl;
    }else if (s->district != e->district){
    }
}

void Graph::deleteVertex(string skiResort){
    vertex *v = NULL;   //Vertex to store the resort to be deleted
    bool resortfound = false;
    for (int i = 0; i < vertices.size(); i++){  //Loop through the vertices and find the vertex
        if (vertices[i].name == skiResort){
            v = &vertices[i];
            resortfound = true;
        }
    }if(!resortfound){
        cout << "Resort not found" << endl;
        return;
    }if(v->district == -1){
        cout << "Initialize Districts" << endl;
        return;
    }
    
    v->adj.erase(v->adj.begin(), v->adj.end()); //Delete all of the adj vertexes to the one being deleted
    for(int i = 0; i < vertices.size(); i ++){ //Delete any other edges connected to the vertex
        for(int k = 0; k < vertices[i].adj.size(); k++){
            if (vertices[i].adj[k].v->name == skiResort){
                deleteEdge(vertices[i].name, vertices[i].adj[k].v->name);
            }
        }
    }for (int i = 0; i < vertices.size(); i++){
        if (vertices[i].name == skiResort){
            vertices[i].name = "";
            vertices[i].distance = 0;
        }
    }
}

void Graph::deleteEdge(string startskiResort, string endskiResort){
    vertex *startResort = NULL;
    vertex *endResort = NULL;
    bool foundStart = false;
    bool foundEnd = false;
    for(int i = 0; i < vertices.size(); i++){ //Loop through all vertices looking for the starting and ending resorts
        if(vertices[i].name == startskiResort){
            startResort = &vertices[i];
            foundStart = true;
        }
        if(vertices[i].name == endskiResort && startskiResort != endskiResort){
        endResort = &vertices[i];
        foundEnd = true;
        }
    }
    if(!foundEnd || !foundStart){
    cout << "This resort doesnt exist" << endl;
    return;

    }if(startResort->district == -1){
        cout << "Initialize Districts" << endl;
        return;
    }else if(startResort->district != endResort->district){
        cout << "The two resorts have different districts" << endl;
        return;
    }
    bool adjacentVertices = false;
    for(int i = startResort->adj.size()-1; i >= 0; i--){
        if(startResort->adj[i].v->name == endskiResort){
            startResort->adj.erase(startResort->adj.begin()+i);
            adjacentVertices = true;
            break;
        }
    }if(!adjacentVertices){
        cout << "The vertices are not adjacent" << endl;
        return;
    }for(int i = endResort->adj.size()-1; i >= 0; i--){
        if(endResort->adj[i].v->name == startskiResort){
            endResort->adj.erase(endResort->adj.begin()+i);
            break;
        }
    }
    districtindex = 1;
    for(int i = 0; i < vertices.size(); i++)
    vertices[i].district = -1;
    findDistricts(startskiResort);
}

void Graph::dijkstra(string startskiResort, string endskiResort){
    vertex A;
    A.name = "NULL";
    vertex B;
    B.name = "NULL";
    vertex *finalResort;  //Vertex to store the final landmark of the shortest distance path
    //Loop through the vertices looking for starting city and ending city
    for(int i = 0; i < vertices.size(); i++){
        if(startskiResort == vertices[i].name){
            A = vertices[i];
            
        }if(endskiResort == vertices[i].name && endskiResort != startskiResort){
            B = vertices[i];
        }
    }
    //If one or more cities is not found, one or more cities does not exist
    
    if(A.name == "NULL" || B.name == "NULL"){
        cout << "That resort doesnt exist" << endl;
        return;
    }if(A.district == -1){
        cout << "Districts have not been initialized" << endl;
        return;
    }else if(A.district != B.district){
        cout << "The two resorts are in different districts" << endl;
        return;
    }
    vertex *startresort = NULL;
    vertex temp;
    int minDistance = 0;
    for(int j = 0; j < vertices.size(); j++){
        vertices[j].visited = false;
        vertices[j].previous = NULL;
        vertices[j].distance = 0;
    }
    A.visited = false;
    B.visited = false;
    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i].name == startskiResort){
            vertices[i].visited = true;
            vertices[i].previous = NULL;
            startresort = &vertices[i];
            break;
        }
    }
    startresort->visited = true;
    startresort->distance = 0;
    startresort->previous = NULL;
    //This keeps track of the resort with the least distance and the adjacent resort with the least distance
    int minIndex = -1;
    int minAdjIndex = -1;
    int distance;   //Variable to store the temp distance measurement
    vector <vertex*> solved; //Create a vector of vertices which are solved
    solved.push_back(startresort);  //Add starting resort to solved
    while(B.visited == false){
        minDistance = INT_MAX;
        for(int k = 0; k < solved.size(); k++) { //Loop through all solved vertices
            for(int a = 0; a < solved[k]->adj.size(); a++){ //Loop through adjacent vertices
                if(solved[k]->adj[a].v->visited == false){
                    distance = solved[k]->distance+solved[k]->adj[a].weight;
                    //Calculate the distance to the adjacent vertex
                    //Set the minimum distance if it has not been set yet
                    //Keep track of the minDistance index and minDistance adjacent vertex
                    
                    if(minDistance == INT_MAX){
                        minDistance = distance;
                        minIndex = k;
                        minAdjIndex = a;
                    }else if(minDistance > distance){ //If min distance>calculated distance
                        minDistance = distance;
                        minIndex = k;
                        minAdjIndex = a;
                    }
                }
            }
        }
        solved[minIndex]->adj[minAdjIndex].v->distance = minDistance;
        solved[minIndex]->adj[minAdjIndex].v->visited = true;
        solved[minIndex]->adj[minAdjIndex].v->previous = solved[minIndex];
        finalResort = solved[minIndex]->adj[minAdjIndex].v; //Set final to be the final adjacent vertex
        if(solved[minIndex]->adj[minAdjIndex].v->name == B.name) //Check if the ending city has been visited
            B.visited = true;
        solved.push_back(solved[minIndex]->adj[minAdjIndex].v); 
        
    }
    vector<vertex*> finalPath; //Makes vector for final path
    cout << minDistance << ", "; //Prints final path and its distance
    while(finalResort != NULL){
        finalPath.push_back(finalResort);
        finalResort = finalResort->previous;
    }for(int j = finalPath.size()-1; j >= 0; j--){
        if(j != 0)
            cout << finalPath[j]->name << ", ";
        else
            cout << finalPath[j]->name << endl;
    }return;
}
 
void Graph::depthFirstTraversal(std::string startskiResort){
    int tracker = 0;
    vertex *startResort = NULL;
    bool resort1 = false;
    for (int i = 0; i < vertices.size(); i ++){
        vertices[i].visited = false;
        if (vertices[i].name == startskiResort){
            startResort = &vertices[i];
            vertices[i].visited = true;
            resort1 = true;
        }
    }if(resort1 == false){
        cout << "The resort was not found" << endl;
        return;
    }if(startResort->district == -1){
        cout << "" << endl;
        return;
    }
    vertex u;
    stack<vertex> depthStack;
    depthStack.push(*startResort);
    while (!(depthStack.empty()))
    {
        u = depthStack.top();
        depthStack.pop();
        tracker++;
        if (tracker == 10)
        {
            cout << u.district << ":" << u.name << endl;
        }
        else{
            cout << u.district << ":" << u.name << " ";
        }for (int i = 0; i < u.adj.size(); i++){
            if (u.adj[i].v->visited == false){
                u.adj[i].v->visited = true;
                depthStack.push(*u.adj[i].v);
            }
        }
    }
    cout << endl;
}

void Graph::breadthFirstTraversal(std::string startskiResort){
    vertex *startResort = NULL;    //Vertex to store the starting resort
    bool resort1 = false; //Boolean to check if the starting vertex has been found
    for (int i = 0; i < vertices.size(); i ++){
        vertices[i].visited = false;
        if (vertices[i].name == startskiResort){
            startResort = &vertices[i];
            vertices[i].visited = true;
            resort1 = true;
        }
    }if(resort1 == false){
        cout << "The resort was not found" << endl;
        return;
    }if(startResort->district == -1){
        cout << "Districts have not been initialized" << endl;
        return;
    }cout << startResort->district << ":" << startResort->name << " "; //Prints the starting vertex
    vertex u;
    queue<vertex> breadthQueue; //Queue to store the traversal path
    breadthQueue.push(*startResort); //Push the starting resort
    while (!(breadthQueue.empty())){
        u = breadthQueue.front();  //pop off vertex and store
        breadthQueue.pop();
        for (int i = 0; i < u.adj.size(); i++){
            if (u.adj[i].v->visited == false){
                u.adj[i].v->visited = true;
                bool visited = true;
                for (int i = 0; i < vertices.size(); i ++){
                    if (vertices[i].visited == false){
                        visited = false;
                    }
                }if (visited){
                    cout << u.adj[i].v->district << ":" << u.adj[i].v->name << endl;
                }else{
                    cout << u.adj[i].v->district << ":" << u.adj[i].v->name << " ";
                }
                breadthQueue.push(*u.adj[i].v);
            }
        }
    }
    cout << endl;
}
