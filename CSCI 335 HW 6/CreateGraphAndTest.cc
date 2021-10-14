// CSCI 335 Homework #6

// Your name: Jiaming Zheng


#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#include "graph.h"

using namespace std;

int testGraphDriver(int argc, char **argv) {
    
    //Begin your code here. Feel free to add any helper functions or classes you need,
    //as long as we only have to call this function to run the specified assignment.
    fstream file; 
    file.open(argv[1]);

    int input = 0;
    file >> input;
    Graph Graph(input);

    string line;
    while(getline(file,line)){
      int vertex, connected_vertex;
      double weight;
      stringstream string_line(line);
      string_line >> vertex;
      while(string_line.peek() != -1){
        string_line >> connected_vertex;
        string_line >> weight;
        if(string_line)
          Graph.AddEdge(vertex,connected_vertex,weight);
      }
    }

    fstream query_file;
    query_file.open(argv[2]);
      while(query_file.peek() != -1){
        int vertex1 = 0;
        int vertex2 = 0;
        double weight;
        query_file >> vertex1;
        query_file >> vertex2;
          if(vertex1 == 0 && vertex2 == 0) //incase not eof but vertices didn't change
            break;
    
        weight = Graph.CheckAdj(vertex1,vertex2);
        if(weight > 0) //no weight means not adjacent
          cout<< vertex1<< " "<< vertex2<< ": connected "<< weight<< endl;
        else
          cout<< vertex1<< " "<< vertex2<< ": not_connected "<< endl;
  }
  return 0;
}

// Do not modify anything below this line

int main(int argc, char **argv) {
    if (argc != 3) {
		cout << "Usage: " << argv[0] << " <GRAPH_File>" << "<ADJACENCY_QUERYFILE>" << endl;
		return 0;
    }

    testGraphDriver(argc, argv);

    return 0;
}
