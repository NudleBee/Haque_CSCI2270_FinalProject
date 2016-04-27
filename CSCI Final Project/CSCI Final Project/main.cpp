#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "Graph.h"

using namespace std;

int main(){
    ifstream inFile;
    string strLine;
    string *skiResort;
    int **skiresortdistance;
    int numLines = 0;  //Variable to store the number of lines in the file
    Graph g;    //Create an instance of the graph class
    inFile.open("resortCities.txt");    //Open the file to read in the data
    if(inFile.fail())
        cout << "File didn't open" << endl;
    else{
        while(inFile.good()){
            getline(inFile, strLine);
            numLines++;
        }
        skiResort = new string [numLines-1]; //Initialize both dynamic arrays
        skiresortdistance = new int *[numLines-1];
        for(int i = 0; i < numLines-1; i++)
            skiresortdistance[i] = new int[numLines-1];
        
        //Clear the file and reset to beginning of file to read in data
        inFile.clear();
        inFile.seekg(0, ios::beg);
        

        getline(inFile, strLine);         //Get the first line of the file
        

        int comma1 = strLine.find(',');         //Finds each comma separating the words
        int comma2 = strLine.find(',', comma1+1);
        
        for(int i = 0; i < numLines-1; i++)
        {
            //Loop through just the first line adding in all resorts to the resort array
            skiResort[i] = strLine.substr(comma1+1, comma2-comma1-1); //Loops through first line adding resorts to the array
            comma1 = comma2;
            comma2 = strLine.find(',', comma2+1);
        }
        int index = 0;  //Variable to keep track of all of the lines traversed in the file
        while(inFile.good()){
            getline(inFile, strLine); //Get line in file
            int comma3 = strLine.find(',');
            int comma4 = strLine.find(',', comma3+1);
            for(int i = 0; i < numLines-1; i++){     //Loop through the remaining lines and add numbers to array
                skiresortdistance[index][i] = atoi(strLine.substr(comma3+1, comma4-comma3-1).c_str());//Update the comma values for each numerical value
                comma3 = comma4;
                comma4 = strLine.find(',', comma4+1);
            }
            
            index++;
            if(index == numLines-1)
                break;
            
        }
    }
    inFile.close();
    for(int k = 0; k < numLines-1; k++){ //Add all resorts to the graph as vertices
        g.addVertex(skiResort[k]);
    }for(int i = 0; i < numLines-1; i++){
        for(int j = 0; j < numLines-1; j++){
            if(skiresortdistance[i][j] > 0){
                g.addEdge(skiResort[i], skiResort[j], skiresortdistance[i][j]);
                skiresortdistance[j][i] = -10;
            }
        }
    }
    
LOOP:while(1 == 1){         //Main Menu
    cout << "===== Welcome =====" << endl;
    cout << "1. Show all ski resorts" << endl;
    cout << "2. Print ski resorts" << endl;
    cout << "3. Initialize Districts" << endl;
    cout << "4. Find Shortest Path" << endl;
    cout << "5. Find Shortest Distance" << endl;
    cout << "6. Delete Route" << endl;
    cout << "7. Delete Resort" << endl;
    cout << "8. Quit" << endl;
    
    string input = "";
    getline(cin, input);
    
    if(input == "1"){
        g.displayEdges();
        
    }else if(input == "2"){     //Print ski resorts
        cout << "1. Depth First Traversal" << endl;
        cout << "2. Breadth First Traversal" << endl;
        string resort1;
        input = "";
        getline(cin, input);
        if (input == "1"){      // Depth first traversal
            cout << "Enter a starting resort:" << endl;
            getline(cin, resort1);
            input = "";
            g.depthFirstTraversal(resort1);
        }else if (input == "2"){  //Breadth first traversal
            cout << "Enter a starting resort:" << endl;
            getline(cin, resort1);
            input = "";
            g.breadthFirstTraversal(resort1);
        }
    }else if(input == "3"){ //Initializes districts
        input = "";
        g.findDistricts(skiResort[0]);
    }else if(input == "4"){ //Find shortest path
        string resort1;
        string resort2;
        cout << "Enter a starting resort:" << endl;
        getline(cin, resort1);
        cout << "Enter an ending resort:" << endl;
        getline(cin, resort2);
        input = ""; //Resets the value of user input
        g.findShortestPath(resort1, resort2);
    }else if(input == "5"){ //Find shortest distance (dijkstra)
        string resort1;
        string resort2;
        cout << "Enter a starting resort:" << endl;
        getline(cin, resort1);
        cout << "Enter an ending resort:" << endl;
        getline(cin, resort2);
        g.dijkstra(resort1, resort2);
    }else if(input == "6"){ //Delete route
        string resort1;
        string resort2;
        cout << "Enter a starting resort:" << endl;
        getline(cin, resort1);
        cout << "Enter an adjacent resort:" << endl;
        getline(cin, resort2);
        input = "";
        g.deleteEdge(resort1, resort2);
    }else if(input == "7"){ //Delete Resort
        string resort1;
        cout << "Enter a resort to delete:" << endl;
        getline(cin, resort1);
        input = "";
        g.deleteVertex(resort1);
    }else if (input == "8"){ //Quit
        cout << "Goodbye!" << endl;
        return 0;
    }else{
        goto LOOP;
    }
}
return 0;
}