/*    @file sandbox.cpp    
      @author <Adam Wiliford>
      @date <3/19/25>  

			@description Sandbox for MyComplex
*/

#include <iostream>
#include <vector>


#include "MyHash.h"

using namespace std;


void evaluateCollisionPolicy(Collision_t method, const string& methodName) {
  const unsigned tableSize = 10000;
  const unsigned numTests = 10000;
  srand(time(0));

  cout << methodName << ":" << endl;
  for (double loadFactor = 0.1; loadFactor < 0.9; loadFactor += 0.1) {
    MyHash hashTable(false, tableSize, method);
    unsigned numElements = static_cast<unsigned>(tableSize * loadFactor);
    vector<int> insertedValues;

    for (unsigned i = 0; i < numElements; i++) {
      int value = rand();
      hashTable.insert(value);
      insertedValues.push_back(value);
    }

    unsigned totalProbes = 0;
    for (unsigned i = 0; i < numTests; i++) {
      int value = insertedValues[rand() % numElements];
      totalProbes += hashTable.countProbes(value);
    }
    
    double avgProbes = (.5*(1+(1/(1-loadFactor))));
    cout << "Load: " << loadFactor << " Hashes: " << avgProbes << endl;
  }
}

int main(int argc, char* argv[]){
  // Change me!
  MyHash a;
  a.insert(5);
  a.insert(6);
  
  a.insert(20);
  a.insert(200);
  a.insert(22);
  a.insert(15);
  a.insert(16);
  a.insert(16);

  a.print();

  cout << "size: " << a.size() << " capacity: " << a.capacity() << " lf: " << a.size()*100/a.capacity() << endl;
  a.insert(rand() % 100);
  cout << "size: " << a.size() << " capacity: " << a.capacity() << " lf: " << a.size()*100/a.capacity() << endl;

  a.insert(rand() % 100);

  a.insert(rand() % 100);
  a.insert(rand() % 100);
  a.insert(rand() % 100);
  cout << "size: " << a.size() << " capacity: " << a.capacity() << " lf: " << a.size()*100/a.capacity() << endl;


  a.count(16);
  a.insert(22);
  cout << "size: " << a.size() << " capacity: " << a.capacity() << " lf: " << a.size()*100/a.capacity() << endl;

  a.print();
  a.count(22);
  a.erase(5);
  a.print();
  cout << "size: " << a.size() << " capacity: " << a.capacity() << " lf: " << a.size()*100/a.capacity() << endl;

  a.erase(22);
  a.print();
  cout << "size: " << a.size() << " capacity: " << a.capacity() << " lf: " << a.size()*100/a.capacity() << endl;

  a.size();
  a.capacity();


  evaluateCollisionPolicy(linear, "Linear probing");
  evaluateCollisionPolicy(double_hash, "Double hashing");


	return 0;
}
