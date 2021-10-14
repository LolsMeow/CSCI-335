#ifndef DOUBLE_HASHING_H
#define DOUBLE_HASHING_H

#include <vector>
#include <algorithm>
#include <functional>
#include <iostream>

namespace {

// Internal method to test if a positive number is prime.
bool IsPrimeD(size_t n) {
  if( n == 2 || n == 3 )
    return true;
  
  if( n == 1 || n % 2 == 0 )
    return false;
  
  for( int i = 3; i * i <= n; i += 2 )
    if( n % i == 0 )
      return false;
  
  return true;
}


// Internal method to return a prime number at least as large as n.
int NextPrimeD(size_t n) {
  if (n % 2 == 0)
    ++n;  
  while (!IsPrimeD(n)) n += 2;  
  return n;
}

}  // namespace


// Double hashing implementation.
template <typename HashedObj>
class HashTableDouble {
 public:
  enum EntryType {ACTIVE, EMPTY, DELETED};

  explicit HashTableDouble(size_t size = 101) : array_(NextPrimeD(size))
    { MakeEmpty(); }
  
  bool Contains(const HashedObj & x) const {
    return IsActive(FindPos(x));
  }
  
  void MakeEmpty() {
    current_size_ = 0;
    for (auto &entry : array_)
      entry.info_ = EMPTY;
  }

  bool Insert(const HashedObj & x) {
    // Insert x as active
    size_t current_pos = FindPos(x);
    if (IsActive(current_pos))
      return false;
    
    array_[current_pos].element_ = x;
    array_[current_pos].info_ = ACTIVE;
    
    // Rehash; see Section 5.5
    if (++current_size_ > array_.size() / 2)
      Rehash();    
    return true;
  }
    
  bool Insert(HashedObj && x) {
    // Insert x as active
    size_t current_pos = FindPos(x);
    if (IsActive(current_pos))
      return false;
    
    array_[current_pos] = std::move(x);
    array_[current_pos].info_ = ACTIVE;

    // Rehash; see Section 5.5
    if (++current_size_ > array_.size() / 2)
      Rehash();

    return true;
  }

  bool Remove(const HashedObj & x) {
    size_t current_pos = FindPos(x);
    if (!IsActive(current_pos))
      return false;

    array_[current_pos].info_ = DELETED;
    return true;
  }

  int getNumber(){
    return current_size_;
  }

  int getSize(){
    return array_.size();
  }

  float getLoad(){
    return ((float)current_size_ / (float)array_.size());
  }

  int getCollisions(){
    return tCollisions;
  }

  float getAvg(){
    return ((float)tCollisions / (float)current_size_);
  }

  HashedObj getArray(int i){
    return array_[i].element_;
  }

  std::string found(std::string que){
    if(Contains(que)){
      return " Found ";
    }else{
      return " Not_Found ";
    }
  }

  int getProbes(std::string que){
    Contains(que);
    return probe;
  }

  void SetR(int r){
    r_value = r;
  }

 private:        
  struct HashEntry {
    HashedObj element_;
    EntryType info_;
    
    HashEntry(const HashedObj& e = HashedObj{}, EntryType i = EMPTY)
    :element_{e}, info_{i} { }
    
    HashEntry(HashedObj && e, EntryType i = EMPTY)
    :element_{std::move(e)}, info_{ i } {}
  };
  
  std::vector<HashEntry> array_;  
  size_t current_size_;
  
  mutable int tCollisions = 0;
  mutable int probe = 1;
  int r_value;

  bool IsActive(size_t current_pos) const
  { return array_[current_pos].info_ == ACTIVE; }

  //modify FindPos
  size_t FindPos(const HashedObj & x) const{
    size_t offset = 1;
    size_t current_pos = InternalHash(x);
    size_t new_current_pos = current_pos;
    probe = 1;
    int index = SecondHash(x);
      
    while (array_[new_current_pos].info_ != EMPTY &&
	   array_[new_current_pos].element_ != x) {
      //std::cout << new_current_pos << std::endl;
      //std::cout << index << std::endl;
      new_current_pos = (current_pos + (offset * index)) % array_.size();
      ++offset;
      ++tCollisions;
      ++probe;
      //if (new_current_pos >= array_.size()) 
      //new_current_pos -= array_.size();
    }
    return new_current_pos;
    }

  void Rehash() {
    std::vector<HashEntry> old_array = array_;

    // Create new double-sized, empty table.
    array_.resize(NextPrimeD(2 * old_array.size()));
    for (auto & entry : array_)
      entry.info_ = EMPTY;
    
    // Copy table over.
    current_size_ = 0;
    for (auto & entry :old_array)
      if (entry.info_ == ACTIVE)
	Insert(std::move(entry.element_));
  }
  
  size_t InternalHash(const HashedObj & x) const {
    static std::hash<HashedObj> hf;
    return hf(x) % array_.size( );
  }

  //added SecondHash Function
  size_t SecondHash(const HashedObj & x) const{
    static std::hash<HashedObj> hf;
    return r_value - (hf(x) % r_value);
  }
};

#endif  // DOUBLE_HASHING_H
