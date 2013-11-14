//----------------------------------------------------------------------------
// Filename:    PackageQueue.cpp
// Date:        22 October 2013
// Description:  A  queue implementation using linked lists.
//----------------------------------------------------------------------------

#include "PackageQueue.h"

//----------------------------------------------------------------------------
// PackageQueue():  Initializes an empty queue with rear and front pointing
//                  to NULL
// Input:           None
// Output:          None
//----------------------------------------------------------------------------
PackageQueue::PackageQueue(){
  rear = NULL;
  front = NULL;
}

//----------------------------------------------------------------------------
// isEmpty(): Returns true when the sequence is empty, and false if not.
// Input:     None
// Output:    A boolean indicating emptiness
//----------------------------------------------------------------------------
bool PackageQueue::isEmpty(){
  return (front == NULL);
}

//----------------------------------------------------------------------------
// enqueue(Package pkg):     Creates a new node with the new Package and adds
//                           it to the rear of the queue.
// Input:                    A Package, pkg.
// Output:                   None
//----------------------------------------------------------------------------
void PackageQueue::enqueue(Package pkg){
  node *temp = new node;
  temp->package = pkg;
  temp->next = NULL;
  if(front == NULL){
      front = temp;
  }else{
      rear->next = temp;
  }
  rear = temp;
}

//----------------------------------------------------------------------------
// dequeue(): Deletes the first node at the front of the queue
// Input: None
// Output: None
//----------------------------------------------------------------------------
void PackageQueue::dequeue(){
  node *temp = new node;
  if(front == NULL){
    cerr<<"PackageQueue is Emtpty" <<endl;
  }else{
    temp = front;
    front = front->next;
    // cerr<<"The data Dequeued is: "<< temp->package.order_number<<endl;
    delete temp;
  }
}

//----------------------------------------------------------------------------
// display():  Dsiplays de queue, front to back.
// Input:   None
// Output:  None
// Note : For debugging purposes.
//----------------------------------------------------------------------------
void PackageQueue::display(){
  node *p = new node;
  p = front;
  if(front == NULL){
    cerr<<"Nothing to Display"<<endl;
  }else{
    while(p!=NULL){
      cout << " ///////////////////////////" <<endl;
      cout << "order_number : ";
      cout<<p->package.order_number<<endl;
      cout << "unit_number : ";
      cout<<p->package.unit_number <<endl;
      cout << "units_worked : ";
      cout<<p->package.units_worked<<endl;
      cout << "time_Arrived : ";
      cout<<p->package.time_Arrived<<endl;
      cout << "time_Shipped : ";
      cout<<p->package.time_Shipped<<endl;
      cout << "isCompleted : ";
      cout<<p->package.isCompleted<<endl;
      cout << "assemblyLineID : ";
      cout<<p->package.assemblyLineID<<endl;

      p = p->next;
    }
  }
}

//----------------------------------------------------------------------------
// getFront():  Creates a copy to the package on front and returns a pointer
//              to it.
// Input:       None
// Output:      A pointer to a Package.
//----------------------------------------------------------------------------
Package * PackageQueue::getFront(){
  node *f = new node;
  f = front;
  if(front == NULL) {
    cerr<<"Nothing to return"<<endl;
  }

  Package *p = new Package;
    *p = f->package;
    return p;
}

// testing purposes
// int main(){
//     PackageQueue queue;
//     Package one;
//     Package two;
//     Package three;
//     one.order_number = "one";
//     one.unit_number = 1 ;
//     two.order_number = "two";
//     two.unit_number = 2 ;
//     three.order_number = "three";
//     three.unit_number = 2 ;

//      queue.enqueue(one);
//      queue.enqueue(two);
//      queue.enqueue(three);
//      queue.display();
//          cerr << "is it empty ?" << queue.isEmpty() <<endl;

//      queue.dequeue();
//      queue.dequeue();
//      queue.display();

//      queue.enqueue(two);
//      queue.display();

//      queue.dequeue();
//      queue.dequeue();
//      queue.dequeue();
//      queue.display();
//      cerr << "is it empty ?" << queue.isEmpty() <<endl;


//      queue.enqueue(one);
//      Package * first = queue.getFront();
//      cerr << first->unit_number<<endl;



//     return 0;
// }

