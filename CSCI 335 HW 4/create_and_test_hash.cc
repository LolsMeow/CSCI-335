// Jiaming Zheng

#include "quadratic_probing.h"
#include "linear_probing.h"
#include "double_hashing.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;


template <typename HashTableType>
void TestFunctionForHashTable(HashTableType &hash_table, const string &words_filename, const string &query_filename) {
  /* cout << "TestFunctionForHashTables..." << endl;
  cout << "Words filename: " << words_filename << endl;
  cout << "Query filename: " << query_filename << endl; */
  hash_table.MakeEmpty();  
  ifstream in(words_filename);
  vector<string> vecOfStrs;
  string str;
  while (getline(in, str)){
    if (str.size() > 0)
      vecOfStrs.push_back(str);
  }
  in.close();
  ifstream in2(query_filename);
  vector<string> vecOfQue;
  string que;
  while (getline(in2, que)){
    if (que.size() > 0)
      vecOfQue.push_back(que);
  }
  in.close();
  for(int i = 0; i < vecOfStrs.size(); i++){
    hash_table.Insert(vecOfStrs[i]);
  }
  cout << "number_of_elements: " << hash_table.getNumber() << endl;
  cout << "size_of_table: " << hash_table.getSize() << endl;
  cout << "load_factor: " << hash_table.getLoad() << endl;
  cout << "average_collisions: " << hash_table.getAvg() << endl;
  cout << "total_collisions: " << hash_table.getCollisions() << endl;
  cout << endl;
  for(int i = 0; i < vecOfQue.size(); i++){
    cout << vecOfQue[i] << hash_table.found(vecOfQue[i]) << hash_table.getProbes(vecOfQue[i]) << endl;
  }
}

// namespace PROTECTED {

int testHashingWrapper(int argument_count, char **argument_list) {
    const string words_filename(argument_list[1]);
    const string query_filename(argument_list[2]);
    const string param_flag(argument_list[3]);
    int R = 0;
    if (argument_count == 5) {
        const string rvalue(argument_list[4]);
        R = stoi(rvalue);
    }

    if (param_flag == "linear") {
        cout << "Linear:" << endl;
        HashTableLinear<string> linear_probing_table;
        TestFunctionForHashTable(linear_probing_table, words_filename, query_filename);
    } else if (param_flag == "quadratic") {
        cout << "Quadratic:" << endl;
        HashTable<string> quadratic_probing_table;
        TestFunctionForHashTable(quadratic_probing_table, words_filename, query_filename);
    } else if (param_flag == "double") {
        cout << "Double:" << endl;
        cout << "r_value: " << R << endl;
        HashTableDouble<string> double_probing_table;
        double_probing_table.SetR(R);
        TestFunctionForHashTable(double_probing_table, words_filename, query_filename);
    } else {
        cout << "Unknown hash type " << param_flag << " (User should provide linear, quadratic, or double)" << endl;
    }
    return 0;
}

// Sample main for program create_and_test_hash.
// WE WILL NOT USE YOUR MAIN IN TESTING. DO NOT CODE FUNCTIONALITY INTO THE
// MAIN. WE WILL DIRECTLY CALL testHashingWrapper. ALL FUNCTIONALITY SHOULD BE
// THERE. This main is only here for your own testing purposes.
int main(int argc, char **argv) {
    if (argc != 4 and argc != 5) {
        cout << "Usage: " << argv[0]
             << " <wordsfilename> <queryfilename> <flag>" << endl;
        cout << "or Usage: " << argv[0]
             << " <wordsfilename> <queryfilename> <flag> <rvalue>" << endl;
        return 0;
    }

    testHashingWrapper(argc, argv);
    return 0;
}

//};  // namespace PROTECTED

