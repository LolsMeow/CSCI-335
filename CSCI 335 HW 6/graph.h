#ifndef STUDENT_GRAPH
#define STUDENT_GRAPH


#include <vector>
#include <climits>
#include <algorithm>
#include <iostream>
#include "binary_heap.h"

//This file is for your graph implementation.
//Add everything you need in between the "ifndef and "endif" statements.
//Do not put anything outside those statements

class Graph{
public:
    Graph(int number_of_vectors){
        size = number_of_vectors;
        vertices.resize(size);

        //intialize vector 
        for(auto& i : vertices){
            i = new Vertex;
        }
        
        //sets source vertex numbers to vectors
        for(int i = 0; i< size; ++i){
            vertices[i]->source = i+1;
        }
    }

    void AddEdge(int& vertex1, int& vertex2, double& weight){
        Vertex::Edge connect;
        connect.destination = vertex2; //set edge adjacent to vertex2
        connect.weight = weight;

        vertices[vertex1-1]->Adjacent.push_back(connect); //adds vertex2 to connection list
    }

    double CheckAdj(int vertex1, int vertex2){
        Vertex* check = vertices[vertex1-1];
        const auto& list = check->Adjacent;
        //checks through vertex's connection list
        for(auto i = list.begin(); i != list.end(); ++i){
            if(i->destination == vertex2){ 
                return i->weight;
            }
        }
        return 0;
    }

    void Dijkstra(const int& position){
        for(auto& i: vertices){
            i->distance = INT_MAX;
            i->visit = false;
        }
        Vertex* current = vertices[position-1];
		current->distance = 0;

        heap.insert(current);
        while(!heap.isEmpty()){
            Vertex* temp = heap.findMin();
            heap.deleteMin();
            temp->visit = true;

            const auto& list = temp->Adjacent;
            for(auto i = list.begin(); i != list.end(); ++i){
                Vertex* placement = vertices[(i->destination)-1];
                if(temp->distance + i->weight < placement->distance){
                    placement->distance = temp->distance + i->weight;
                    placement->path = temp;
                    heap.insert(placement);
                }
            }
        }
        PrintPath(position);
    }

    void PrintPath(int position){
        vector<int> path;
        for(unsigned int i = 0; i< vertices.size(); ++i){
            cout<< i+1<< ": ";
            Vertex* placement = vertices[i];
            double cost = placement->distance;
            while(placement != nullptr){
                if(placement->source == 0){
                    placement->source = i+1;
                }
                path.push_back(placement->source);
                placement = placement->path;
            }
            reverse(path.begin(),path.end());

            if((cost == INT_MAX)){
				cout<< "not_possible" << endl;
			}else{
                for(unsigned int i = 0; i< path.size(); ++i){
                    cout<< path[i]<< " ";
                }
                cout<< "cost: "<< cost << endl;      
            }
            path.clear();           
        }
    }
private: 
    struct Vertex{
        struct Edge{
            int destination;
            double weight;

            //default
            Edge(){
                destination = 0;
                weight = 0; 
            }
        };

        vector<Edge> Adjacent; //vertex connection list
        int source;
        int distance;
        bool visit;
        Vertex* path;

        Vertex(){
            Adjacent.resize(0);
            source = 0;
            distance = 0;
            visit = false;
            path = NULL;
        }    
    };

    int size; 
    vector<Vertex*> vertices;
    BinaryHeap<Vertex*> heap;
};



#endif
