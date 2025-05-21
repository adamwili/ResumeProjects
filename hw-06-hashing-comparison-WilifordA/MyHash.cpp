/*    @file MyHash.cpp   
      @author < Adam Wiliford >
      @date < 3/12/25 >

			@description Implements a hash table class (unordered multiset)
*/

#include <string>
#include <iostream>

#include "MyHash.h"

# define RESIZE_LIMIT 0.7

MyHash::MyHash(bool resize, unsigned start_size, Collision_t method):n(0),method(method), resize(resize){
  // Change me!
  data = new Bucket[start_size];
  max_size = start_size;
};   

MyHash::MyHash(MyHash &other){
  // Change me!
  method = other.method;
  resize = other.resize;
  max_size = other.max_size;
  data = new Bucket[max_size];
  n = 0;
  for(unsigned i =0; i <max_size; i++) {
    if(other.data[i].used) { //other[i]
      insert(other.data[i].value);
    }
  }
}


MyHash& MyHash::operator=(const MyHash& other){
  // Change me!
  method = other.method;
  resize = other.resize;
  max_size = other.max_size;
  delete[] data;
  data =new Bucket[max_size];
  n = 0;
  for(unsigned i =0; i <max_size; i++) {
    if(other.data[i].used) { //other[i]
      insert(other.data[i].value);
    }
  }
  return *this;
}

MyHash::~MyHash(){
  // Change me!
  delete[] data;
}

void MyHash::print(){
  cout << "Stored " << n << " values: ";
  for(unsigned i = 0; i < max_size; i++){
    if(data[i].used){
      cout << data[i].value << ", ";
    }
  }
  cout << endl;
}

int MyHash::hashFunction(int value, int tried) {
  
  // If linear probing is selected, return the next index with linear probing
  if (method == linear) {
      return (value + tried) % max_size;  // Linear probing
  } 
  else if (method == double_hash) {
      int secondaryIndex = ((value % 7) +1); 
      return (value + tried * secondaryIndex) % max_size;  // Double hashing
  }
  else {
    return 0;
    //previously had return -1; here, caused tests to fail and was hard to determine that this was the cause
  }
  }



void MyHash::insert(int value){
  // Change me!
  if ((float)(n+1)/max_size > RESIZE_LIMIT && resize) {
    makeLarger();
  }
  for (unsigned int tried = 0; tried < max_size*2; tried++) {
    unsigned int index = hashFunction(value, tried);
    if (!data[index].used || data[index].deleted) {
      data[index].value = value;
      data[index].used = true;
      data[index].deleted = false;
      n++;
      return;
    }
  }
 // cout << "Giving up on insert" << endl;
}

void MyHash::makeLarger() {
  //cout << "Making larger!" << endl;

    unsigned old_size = max_size; 
    max_size = max_size * 2 + 1; 
    
    Bucket* old_data = data;  
    data = new Bucket[max_size]; 
    n = 0;  
    bool old_resize = resize; 
    resize = false;  // Disable resizing while reinserting elements
    // Rehash and reinsert all elements from the old table into the new table
    for (unsigned i = 0; i < old_size; i++) {
        if (old_data[i].used) {
            insert(old_data[i].value);  // Reinsert the element into the new table
        }
    }
    resize = old_resize;  // Restore the resize value
    delete[] old_data;
}



bool MyHash::contains(int value){
  // Change me!
  for (unsigned int tried = 0; tried < max_size; tried++) {
      int index = hashFunction(value, tried);  
      if (data[index].used && data[index].value == value) {
          return true;
      }
      if (!data[index].used && !data[index].deleted) {
          return false;  
      }
  }
  return false; 

}

unsigned MyHash::count(int value){
  // Change me!
  int numOccurrences = 0;

 
  for (unsigned int tried = 0; tried < max_size; tried++) {
    int index = hashFunction(value, tried);  // Get the index based on probing
    if (data[index].used && data[index].value == value) {
      numOccurrences++;
    }

    if (!data[index].used && !data[index].deleted) {
      break;
    }
  }
  return numOccurrences;
 // cout << numOccurrences << " occurrences of " << value << endl;
}

void MyHash::erase(int value) {
  
  for (unsigned int tried = 0; tried < max_size; tried++) {
      int index = hashFunction(value, tried);  // Probe to find the correct index

      // If the value is found, erase it
      if (data[index].used && data[index].value == value) {
          data[index].used = false; 
          data[index].deleted = true;     
          n--;
          return;                    
      }

      // If an empty bucket is reached, stop the search (value is not in the table)
      if (!data[index].used && !data[index].deleted) {
          return;
      }
  }
}

unsigned MyHash::size(){
 // cout << n << " elements" << endl;
  return n;
  
}

unsigned MyHash::capacity(){
  // Change me!
  //cout << "Current size of array: " << max_size << endl;
  return max_size;
}

unsigned MyHash::countProbes(int value) {
  int i = value % max_size;
  for (unsigned int tried = 0; tried < max_size; tried++) {
    int index = hashFunction(i, tried);
    if (data[index].used && data[index].value == value) {
      return tried + 1; // Number of probes needed to find the value
    }
    if (!data[index].used && !data[index].deleted) {
      return tried + 1; // Number of probes needed to determine the value is not in the table
    }
  }
  return max_size;

}





