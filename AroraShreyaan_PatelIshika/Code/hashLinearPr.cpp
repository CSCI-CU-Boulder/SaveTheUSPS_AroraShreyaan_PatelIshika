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

    if(table[index] == 0) //conditional for: if collision does not occur
    {
        table[index] = newNode;

        return true; //insertion completed
    }
    else //conditional for: if collision DOES not occur
    {
        numOfInsertCol++;

        while(true)
        {
            index++;
            if(index == tableSize)
            {
                index = 0;
            } 

            if (table[index] == 0) 
            {
                table[index] = newNode;
                return true;
            }
        }
        
    }
}


unsigned int HashTable::hashFunction(int key) 
{
 return (key % tableSize); //h(x) = x % m, x  is  the  key  value  and  m  is  the  table  size
}

void HashTable::printTable() 
{
    for(int index = 0; index < tableSize; index++)
    {
        if(table[index] != 0) //the node must have a value
        {
            cout << "|" << index << "| -> " << table[index]->key; 
        }
        
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
    int index = hashFunction(key);
    int origin = index;

    if(table[index] == 0)//empty, see ˇ
    { 
        return 0; // terminate searching process
    } 
    
    if(table[index]->key == key)  //@1st index
    {
        return table[index];
    }
    numOfSearchCol++;
    
    while(true)
    {
        index++;
            if(table[index] == 0)
            {
                return 0;
            }

            if(table[index]->key == key) 
            {
                return table[index];
            }
            if(index == tableSize - 1) //Conditional: @end --> back to start
            {
                index = 0;
            }
            if (index == origin) //completed one full loop
            {
                return 0;
            }
    }
}
