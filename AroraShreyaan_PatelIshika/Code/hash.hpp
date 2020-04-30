
//--Project 3, Part: Hash--//

//|/////////////////////DOWNLOADED VIA MOODLE & Partially Modified\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\|//

#ifndef HASH_HPP
#define HASH_HPP

#include <string>
#include <math.h>


using namespace std;

struct node
{
    int key;
    struct node* next;
};

class HashTable
{
    int tableSize;  // No. of buckets (linked lists)

    // Pointer to an array containing buckets
    node* *table;
    int numOfInsertCol = 0;// - addition
    int numOfSearchCol = 0;// - addition
    node* createNode(int key, node* next);

public:
    HashTable(int bsize);  // Constructor

  
    bool insertItem(int key);   // inserts a key into hash table


    unsigned int hashFunction(int key);     // hash function to map values to key

    void printTable();
    int getNumOfInsertCol(); //getter for insertion collisions - addition
    int getNumOfSearchCol(); //getter for search collisions - addition
    node* searchItem(int key);
};

#endif
