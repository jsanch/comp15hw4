//----------------------------------------------------------------------------
// Filename:    PackageQueue.h
// Date:        12 November 2013
// Description: A queue interface for a linked list implementation.
//----------------------------------------------------------------------------

#include <iostream>
#include <cstdlib>

using namespace std;
struct Package{
  string order_number;
  double unit_number;
  double units_worked;
  int time_Arrived;
  int time_Shipped;
  bool isCompleted;
  int assemblyLineID;
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
    Package * getFront();

  private:
    node *rear;
    node *front;

};

