// Daaniyal Haque
// Final Project
// Hoenigman

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include "skiResorts.h"
#include <sstream> 

using namespace std;
void displayMenu();
void readFileIntoGraph(skiResorts & g, char* resortCities);

int main(int argc, char*argv[])
{
    skiResorts g;
    readFileIntoGraph(g, argv[1]);
    
    // Flag used for exiting menu
    bool quit = false;
    
    // Used for input
    string inputString1;
    string inputString2;
    int input;
    
    while(quit != true)
    {
        displayMenu();
        cin >> input;
        
        //clear out cin
        cin.clear();
        cin.ignore(10000,'\n');
        
        switch (input)
        {
                // Print Vertices
            case 1:
                g.displayEdges();
                break;
                // Find districts
            case 2:
                g.assignDistricts();
                break;
                // Find shortest path
            case 3:
                cout << "Enter a starting city:" << endl;
                getline(cin,inputString1);
                cout << "Enter an ending city:" << endl;
                getline(cin,inputString2);
                g.shortestPath(inputString1,inputString2);
                break;
                // Quit
            case 4:
                cout << "Goodbye!" << endl;
                quit = true;
                break;
                // invalid input
            default:
                cout << "Invalid Input" << endl;
                cin.clear();
                cin.ignore(10000,'\n');
                break;
        }
    }
    
    return 0;
}

void readFileIntoGraph(skiResorts & g, char* fileName)
{
    vector<string> cities;
    ifstream in_stream;
    //cout << fileName << endl;
    in_stream.open(fileName);
    if (!in_stream)
    {
        cout << "Could not open file\n";
        return;
    }
    
    string city;
    string line;
    getline(in_stream,line);
    std::stringstream ss(line);
    int y = 0;
    
    // Read a list of cities from the first line
    while (getline(ss,city,','))
    {
        if (city != "cities")
        {
            g.addVertex(city);
            cities.push_back(city);
        }
    }
    
   
    int i = 0;
    string in;
    while (!in_stream.eof())
    {
        i = -1;
        getline(in_stream,line);
        stringstream ss(line);
        
        while (getline(ss,in,','))
        {
            if (i == -1)
            {
                city = in;
            }
            else
            {
                if (in != "-1" && in != "0")
                {
                    g.addEdge(city,cities[i],atoi(in.c_str()));
                }
            }
            i++;
        }
    }

}