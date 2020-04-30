#include <iostream>
#include "hash.hpp"

using namespace std;


//Hash Table Reference: Visualizing Data Structure(Hoenigman, 2015)

HashTable::HashTable(int bsize) //constructor
{
    tableSize = bsize;
    node* *nTab = new node*[tableSize];
    table = nTab;

    for(int i = 0; i < bsize; i++) //all pointers should start as '0'
    {
        table[i] = 0;
    }
}

node* HashTable::createNode(int key, node *next) 
{
    node* newNode = new node(); //new node created
    newNode->key = key; //setting the passed 'key' parameter for the node
    newNode->next = next;
    return newNode;
}

bool HashTable::insertItem(int key) 
{
    int index = hashFunction(key); //hashing the key
    node* newNode = createNode(key, 0);
    bool collision = false;

    if(table[index] == 0) //conditional for: if collision does not occur
    {
        table[index] = n;

        return true; //insertion completed
    }
    else //conditional for: if collision DOES not occur
    {
        collision = true;
        numOfInsertCol++;
        node* curr = table[index];
        table[index] = newNode;
        n->next = curr;
        return collision;
    }
}


unsigned int HashTable::hashFunction(int key) 
{
 return (key % tableSize); //h(x) = x % m, x  is  the  key  value  and  m  is  the  table  size
}

void HashTable::printTable() 
{
    int index = 0;
    while(index < tableSize) 
    {
        if(table[index] != 0) //the node must have a value
        {
            cout << "[" << index << "] -> " << table[index]->key;
            cout << endl;
        }
        index++;
    }
}

int HashTable::getNumOfInsertCol() 
{
    return numOfInsertCol;
}
int HashTable::getNumOfSearchCol() 
{
    return numOfSearchCol;
}

node* HashTable::searchItem(int key)
{
    int index = hashFunction(key); //empty, terminate searching process

    if(table[index] == 0) return 0;
    
    else if(table[index]->key == key) return table[index];
    
    else
    {
        numOfSearchCol++; //increment collision count (as needed for searches yielding nothing)
        node* curr = table[index]->next;

        while(curr != 0)
        {
            if(curr->key == key) return curr;
            curr = curr->next;
        }
    }

    return 0;
}
