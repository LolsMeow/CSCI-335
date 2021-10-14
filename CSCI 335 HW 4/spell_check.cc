// Jiaming Zheng.

#include "quadratic_probing.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//Checks for spelling of the word and tries to correct it if it is wrong
template <typename HashTableType>
void SpellChecker( HashTableType &hash_table, const string &document_filename){
  string line;

  ifstream file(document_filename);
  while(file >> line){
    string word,letter;
    //gets each word
    for(int i = 0; i< line.length(); ++i){
      letter = line[i];
      
      //only adds alphabet
      if((letter >= "a" && letter <= "z" )||(letter >= "A" && letter <= "Z" )){
        //lowercases letter
        letter = tolower(line[i]);
        word += letter;
      }
      //if punctuation isnt at the beginning or end adds to word
      if((i != 0 || i == line.length()-1)){
        if(letter == "\'" || letter == "-" ){
          word += letter;
        }
      }
    }
    //word is found in dictionary
    if(hash_table.Contains(word)){
      cout<< word<< " is CORRECT"<< endl;
    }

    //check misspelled word with 3 rules
    string check_word = word;
    //no middle punctuation and not found in dictionary
    if(!hash_table.Contains(check_word) && check_word != ""){
      cout<< word<< " is INCORRECT"<< endl;
      
      //RULE a) Adding one character in any possible position
      for(int i = 0; i< word.length()+1; ++i){
        //iterates through ever alphabet letter
        for(char letter = 'a'; letter<= 'z'; ++letter){
          //inserts into i position (1 letter)
            check_word.insert(i, 1, letter);

            if(hash_table.Contains(check_word)){
              cout<< "*** "<<word<< " -> "<< check_word<< " *** case A"<< endl;
            }
            check_word = word;
        }
      }

      //RULE b) Removing one character from the word
      for(int i = 0; i< word.length(); ++i){
        //erases letter as position i (1 length)
        check_word.erase(i,1);

        if(hash_table.Contains(check_word)){
          cout<< "*** "<<word<< " -> "<< check_word<< " *** case B"<< endl;
        }
        check_word = word;
      }

      //RULE c) Swapping adjacent characters in the word
      for(int i = 0; i< word.length()-1; ++i){
        //swap letter i and letter to the right
        swap(check_word[i], check_word[i+1]);
        if(hash_table.Contains(check_word)){
          cout<< "*** "<<word<< " -> "<< check_word<< " *** case C"<< endl;
        }
        check_word = word;
      }
    }
  }
  file.close();
}

// HashTableDouble<string> dictionary = MakeDictionary(dictionary_filename);
HashTable<string> MakeDictionary(const string &dictionary_filename){
    HashTable<string> hash_table;
    string word;
    ifstream file(dictionary_filename);
     while(file >> word){
        hash_table.Insert(word);
    }
    file.close();
    return hash_table;
}

int testSpellingWrapper(int argument_count, char** argument_list) {
  const string document_filename(argument_list[1]);
  const string dictionary_filename(argument_list[2]);

  // Call functions implementing the assignment requirements.
  // HashTableDouble<string> dictionary = MakeDictionary(dictionary_filename);
  HashTable<string> dictionary = MakeDictionary(dictionary_filename);
  SpellChecker(dictionary,document_filename);
  return 0;
}

// Sample main for program spell_check.
// WE WILL NOT USE YOUR MAIN IN TESTING. DO NOT CODE FUNCTIONALITY INTO THE
// MAIN. WE WILL DIRECTLY CALL testSpellingWrapper. ALL FUNCTIONALITY SHOULD BE
// THERE. This main is only here for your own testing purposes.
int main(int argc, char** argv) {
    if (argc != 3) {
        cout << "Usage: " << argv[0] << " <document-file> <dictionary-file>"
             << endl;
        return 0;
    }

    testSpellingWrapper(argc, argv);

    return 0;
}
