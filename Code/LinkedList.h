/*
CSCI 2270 USPS Project
Shreyaan Arora: Hash Table, Report
Ishika Patel: BST, LL, Report
*/

#include <iostream>

struct Node{
      int key;
      Node *next;
};

class LinkedList
{
  private:
    Node *head;

  public:
    LinkedList()
    {
    	head = NULL;
    }
    void insert(Node *prev, int newKey);
    Node* searchList(int key);
    void printList();
};
