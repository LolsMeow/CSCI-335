// CSCI 335 Homework #6

// Your name: Jiaming Zheng
 
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#include "graph.h"

using namespace std;

int findPathDriver(int argc, char **argv) {
    //Begin your code here. Feel free to add any helper functions or classes you need,
    //as long as we only have to call this function to run the specified assignment.
    //open given file
    fstream file;
    file.open(argv[1]);

    //create graph
    int input_num = 0;
    file >> input_num; //first line is number of vertices
    Graph Graph(input_num); //graphs size of vector

    string line;
    while(getline(file,line)){
      int vertex, connected_vertex;
      double weight;
      stringstream string_line(line);
      string_line >> vertex; //main vertex
      while(string_line.peek() != -1){ //not the EOF
        string_line >> connected_vertex;
        string_line >> weight;
        if(string_line)
          Graph.AddEdge(vertex,connected_vertex,weight);
      }
    }

    //dijkstra algorithm
  Graph.Dijkstra(atoi(argv[2])); //convert char to int
  return 0;
}

// Do not modify anything below this line

int main(int argc, char **argv) {
    if (argc != 3) {
		cout << "Usage: " << argv[0] << " <GRAPH_FILE>" << "<STARTING_VERTEX>" << endl;
		return 0;
    }

    findPathDriver(argc, argv);

    return 0;
}
