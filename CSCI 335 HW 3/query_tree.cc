// <Jiaming Zheng>
// Main file for Part 2.1 of Homework 3.

#include "avl_tree.h"
#include "sequence_map.h"

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <math.h>
using namespace std;

namespace {

// @db_filename: an input filename.
// @a_tree: an input tree of the type TreeType. It is assumed to be
//  empty.
template <typename TreeType>
void QueryTree(const string &dbx_filename, TreeType &a_tree) {
  // Code for running Part 2.1
  // You can use public functions of TreeType. For example:
  //a_tree.insert(10);
  //a_tree.printTree();
  ifstream myfile;
  myfile.open(dbx_filename);
  
  string db_line;
  //skips first 10 lines of file
  for(int i = 0; i< 10; i++) {
    getline(myfile,db_line);
  }
  
  // Read the file line-by-line to populate tree
  while(getline(myfile,db_line)){
    //line shouldn't be empty
    if(!db_line.empty()) {
      //reads line as string
      stringstream ss(db_line); 
      string an_enz_acro;
      //get enzyme acronym from line
      getline(ss,an_enz_acro,'/');
      string a_reco_seq;
      while(getline(ss,a_reco_seq,'/')){
        //new SequenceMap object
        SequenceMap new_sequence_map(a_reco_seq, an_enz_acro);
        //populating tree with sequencemap
        a_tree.insert(new_sequence_map);
      } 
    } 
  }
  myfile.close();

  //asking for inputs
  std::cout << "Enter THREE sequences\n";
  std::string user_input1, user_input2, user_input3;
  cin >> user_input1;
  cin >> user_input2;
  cin >> user_input3;
  SequenceMap map1(user_input1, " ");
  SequenceMap map2(user_input2, " ");
  SequenceMap map3(user_input3, " ");
  if (a_tree.contains(map1) || a_tree.contains(map2) || a_tree.contains(map3)) {
    a_tree.printNode(map1); 
    a_tree.printNode(map2);
    a_tree.printNode(map3); 
  } 
  else {
      std::cout << "Not Found\n";
  }
}
}  // namespace

int
main(int argc, char **argv) {
  if (argc != 2) {
    cout << "Usage: " << argv[0] << " <databasefilename>" << endl;
    return 0;
  }
  const string db_filename(argv[1]);
  cout << "Input filename is " << db_filename << endl;
  // Note that you will replace AvlTree<int> with AvlTree<SequenceMap>
  AvlTree<SequenceMap> a_tree;
  QueryTree(db_filename, a_tree);
  return 0;
}