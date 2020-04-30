#include "LinkedList.h"
#include <chrono>
using namespace std::chrono;
using namespace std;

// Add a new node to the list
void LinkedList::insert(Node* prev, int newKey)
{
    //int startTime, endTime;

    //Check if head is Null i.e list is empty
    if(head == NULL)
    {
    head = new Node;
    head->key = newKey;
    head->next = NULL;
    }
    // if list is not empty, look for prev and append our node there
    else if(prev == NULL)
    {
    Node* newNode = new Node;
    newNode->key = newKey;
    newNode->next = head;
    head = newNode;
    }
    else
    {
    Node* newNode = new Node;
    newNode->key = newKey;
    newNode->next = prev->next;
    prev->next = newNode;
    }

}

// Search for a specified key and return a pointer to that node
Node* LinkedList::searchList(int key)
{
    Node* ptr = head;

    while (ptr != NULL && ptr->key != key)
    {
        ptr = ptr->next;
    }

    return ptr;
}

// Print the keys in your list
void LinkedList::printList()
{
    Node* temp = head;

    while(temp->next != NULL)
    {
        cout<< temp->key <<" -> ";
        temp = temp->next;
    }

    cout<<temp->key<<endl;
}