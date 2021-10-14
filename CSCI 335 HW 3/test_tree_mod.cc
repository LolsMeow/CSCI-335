// <Jiaming Zheng>
// Main file for Part 2.2 of Homework 3.

#include "avl_tree.h"
#include "sequence_map.h"

#include <iostream>
#include <string>
#include <cctype>
#include <sstream>
#include <fstream>
#include <math.h>
using namespace std;
namespace {
// @dbx_filename: an input database filename.
// @seq_filename: an input sequences filename.
// @a_tree: an input tree of the type TreeType. It is assumed to be
//  empty.
template <typename TreeType>
void TestTree(const string &dbx_filename, const string &seq_filename, TreeType &a_tree) {
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
        a_tree.insert(new_sequence_map);
      } // End second while.
    } // End first while.
  }
  myfile.close();

  //prints the number of nodes in your tree n
  int node_count = a_tree.nodeCount();
  cout<< "2: "<< node_count<< endl;

  //computes the average depth of your search tree
  float average_depth = a_tree.internalNode()/a_tree.nodeCount();
  cout<< "3a: "<< average_depth << endl;
  //prints the ratio of the average depth to log2n
  cout<< "3b: "<< average_depth/log2(node_count) << endl;
  //opening sequence file to determine 4a and 4b
  ifstream twofile;
  twofile.open(seq_filename);
  string seq_line;
  //declaring variables
  int querriesFound = 0, totalCalls = 0, calls = 0, querriesCount = 0;
  float average_recur_calls = 0;
  // Read the file line-by-line to populate tree
  while(getline(twofile, seq_line)){
      querriesCount++;
      if(a_tree.find(seq_line,calls))
        querriesFound++;
      totalCalls += calls;
      calls = 0;  
  }
  average_recur_calls = (static_cast<float>(totalCalls)/static_cast<float>(querriesCount));
  cout << "4a: " << querriesFound << endl;
  cout << "4b: " << average_recur_calls << endl;

  twofile.close();
  //opening sequence file to determine 5a and 5b
  twofile.open(seq_filename);
  string sequence_line, every_other_seq;
  //declaring variables
  int removedCount = 0, totalCount = 0, removedCalls = 0, removedTotal = 0;
  float average_removed_calls = 0;
  while(getline(twofile, every_other_seq)){
    removedTotal++;
      if(a_tree.RemoveOtherSeq(every_other_seq, removedCalls))
        removedCount++;
      totalCount += removedCalls;
      removedCalls = 0;
    getline(twofile,seq_line);
  }
  average_removed_calls = (static_cast<float>(totalCount)/static_cast<float>(removedTotal));
  cout << "5a: " << removedCount << endl; 
  cout << "5b :" << average_removed_calls << endl;
  //print out data after node removal of every other sequence for 6a, 6b, 6c
  node_count = a_tree.nodeCount();
  average_depth = a_tree.internalNode()/a_tree.nodeCount();
  cout << "6a: " << node_count << endl;
  cout << "6b: " << average_depth << endl;
  cout << "6c: "<< average_depth/log2(node_count) << endl;
} 

}// namespace
int
main(int argc, char **argv) {
  if (argc != 3) {
    cout << "Usage: " << argv[0] << " <databasefilename> <queryfilename>" << endl;
    return 0;
  }
  const string dbx_filename(argv[1]);
  const string seq_filename(argv[2]);
  cout << "Input file is " << dbx_filename << ", and sequences file is " << seq_filename << endl;
  // Note that you will replace the type AvlTree<int> with AvlTree<SequenceMap>
  AvlTree<SequenceMap> a_tree;
  TestTree(dbx_filename, seq_filename, a_tree);

  return 0;
}
