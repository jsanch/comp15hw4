//----------------------------------------------------------------------------
// Filename:    PackageQueue.h
// Date:        22 October 2013
// Description: A queue interface for a linked list implementation. 
//----------------------------------------------------------------------------

#include <iostream>
#include <cstdlib>

using namespace std;
struct Package{
    string order_number;
    double units_worked; // so that it works with rate.
    double unit_number; // 
    int time_Arrived;
    int time_Shipped;
    bool isShipped; 
};

struct node{
    Package package;
    struct node *next;
};
class PackageQueue{
     public:
        PackageQueue();
        bool isEmpty();
        void enqueue(Package pkg);
        void dequeue();
        void display();
        //gives a pointer to a copy of the first. 
        Package * getFront();
    private:
        node *rear;
        node *front;

};

