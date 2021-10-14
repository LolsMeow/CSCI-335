//Jiaming Zheng
//SequenceMap that store private data members 

#ifndef SEQUENCE_MAP_H
#define SEQUENCE_MAP_H

#include <vector>
#include <iostream>
using namespace std; 

class SequenceMap{
public:
    //zero-parameter constructor
    SequenceMap() = default;

    //copy-constructor
    SequenceMap(const SequenceMap &rhs) = default;

    //copy-assignment
    SequenceMap &operator=(const SequenceMap &rhs) = default;

    //move-constructor
    SequenceMap(SequenceMap &&rhs) = default;

    //move-assignment
    SequenceMap &operator=(SequenceMap &&rhs) = default;

    //destructor
    ~SequenceMap() = default;

    //End of big five
    //constructor
    SequenceMap(const string &a_rec_seq, const string &an_enz_acro){
        recognition_sequence_ = a_rec_seq;
        enzyme_acronyms_.push_back(an_enz_acro);
    }
    
    //overload < operator for string comparison
    bool operator<(const SequenceMap &rhs) const{
        return recognition_sequence_ < rhs.recognition_sequence_;
    }

    //overload << operator to print context of vector
    friend ostream &operator<<(ostream &out, const SequenceMap &map2){   
        //iterate through vector with size
        for(int i = 0; i< map2.enzyme_acronyms_.size(); i++){
            out<< map2.enzyme_acronyms_[i]<< " ";
        }
        return out;
    } 

    //merges two string objects 
    //assumes that recognition_sequence_ and other_sequence.recognition_sequence_ are equal 
    //other_sequence object isnt affected
    void Merge(const SequenceMap &sequence2){
        for(int i = 0; i< sequence2.enzyme_acronyms_.size();i++){
            //adds other sequence to vector
            enzyme_acronyms_.push_back(sequence2.enzyme_acronyms_[i]);
        }
    }

    //return recognition sequence
    string GetRecogSeq() const {
        return recognition_sequence_;
    }
private:
    string recognition_sequence_;
    vector<string> enzyme_acronyms_;
};

#endif