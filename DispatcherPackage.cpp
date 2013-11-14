#include "Dispatcher.h"

Dispatcher::Dispatcher(AssemblyLine *list, int size){
  //copy pointer to assembly lines. and the size.
  this->aLineList = list;
  cerr << "the first aline is" << aLineList[0].assemblyLineID <<endl;
  cerr <<"the total size is " << size << endl;
  this->length_aLineList = size;

}
// MAKE SURE QUEUES IN ASSEMBLY LINE ARE NOT POINTING TO NULL.
void Dispatcher::dispatch(PackageQueue * PkgBuffer, int pkgCount){
//initial stuff
 this->arrivingPkgBuffer = PkgBuffer; // critical: must pass pointer to class.                                     // now the whole class has it.
 initAssemblies();
 // aLineList[0].arrivingPkgBuffer = this->arrivingPkgBuffer; //wow. CRITICAL.

  //Step one. all assembly lines do work.

  //Step two. check if any of the assembly lines has done a job. if so, ship.


  //Step three. PACKAGE ARRIVES. Dispatch to best assembly line.
//test
  timeUnit = 0;
  int completedPkgCount=0;
  while(completedPkgCount != pkgCount){
    cerr <<"///////////////////////////////////////////////////////////////////Starting Dispatching, TIME: " << timeUnit << endl;
    // init_aLs(&arrivingPkgBuffer);
    for (int i = 0; i < length_aLineList; i++){
        cerr << "do work in assemblyLine :" << i <<endl;
      completedPkgCount += al_do_work(i, timeUnit);

      al_ship(i, timeUnit);
    }
    if (!arrivingPkgBuffer->isEmpty()){
     distributeArrivingPkgs(timeUnit);
    }
     cerr << ".............completedPkgCount = " << completedPkgCount <<endl;
     timeUnit++;

  }
}
// void Dispatcher::init_aLs(PackageQueue * arrivingPkgBuffer){
// //must provide an arriving queue to each assembly line.
//   //test- for now just, to the first.
//   aLineList[0]->setArrivingQueue(arrivingPkgBuffer);


// }

int Dispatcher::al_do_work(int id, int timeUnit){
cerr << "/(1)Starting work in AssemblyLine: " << id <<"  TIME: "<< timeUnit << endl;
  int completedPkgCount = 0;
 AssemblyLine * aL = &aLineList[id]; // easier to work with.
    if (!( aL -> processingPkgBuffer.isEmpty()) ) {
      if (! aL->isCurrentPkgLoaded()){
        aL->loadCurrentPkg();
        completedPkgCount = aL->do_work(timeUnit);
      }else{
        completedPkgCount = aL->do_work(timeUnit);
      }
    }
    return completedPkgCount;
}
void Dispatcher::al_ship(int id, int timeUnit){
cerr << "//(2)Starting Shipping in AssemblyLine: " << id <<"  TIME: "<< timeUnit << endl;
  AssemblyLine * aL = &aLineList[id];
    if (aL->isCurrentPkgLoaded()){
      if(aL->isPkgCompleted(aL->currentPkg)){
        cerr <<"//////////////////////////////////////////////////////";
        aL->shipPkg(timeUnit); // puts package in a cmpleted Pkg Buffer.
      } else {
// cerr << "Package not Completed, Cant Ship" <<endl;
      }
    }else {
// cerr << "Package Not loaded, Cant Ship" <<endl;
    }
}

void Dispatcher::initAssemblies(){
// Creating an empty arriving buffer for each Assembly.
  for (int i = 0; i<length_aLineList; i++) {
  // create an arriving buffer for every assembly line.
  // aLineList[i].arrivingPkgBuffer = this->arrivingPkgBuffer; //wow. CRITICAL.
  aLineList[i].arrivingPkgBuffer = new PackageQueue;
  }
}

void Dispatcher::distributeArrivingPkgs(int timeUnit){
cerr << "///(3) Starting Distribution" << endl;

  //get the front.
  Package *frontPkg = this->arrivingPkgBuffer->getFront();
  //check if it 'has arrived in this current timeUnit'
  if (frontPkg ->time_Arrived == timeUnit) {
    // put in the assembly line that is wished.
    Package newPkg = *frontPkg;
    dispatch_to_assembly1(newPkg); /// this is like the enqueue.
    //remove the package from the front.
    this->arrivingPkgBuffer->dequeue();

  }
// //testing.
// AssemblyLine * aL = &aLineList[0];
//   if (!(aL->arrivingPkgBuffer->isEmpty() ) ) {
//     aL->handlePkgArrival(arrivingPkgBuffer, timeUnit);
//   }

}

//the money maker.
void Dispatcher::dispatch_to_assembly1(Package newPkg){
 // go dirctly to processing queueue , bypassig arrival queue inside assembly.

  //setting default mins.
  // int min = aLineList[0].numPkgsProcessing;
  AssemblyLine *minLine;
    minLine = &aLineList[0];

  for (int i = 0; i<length_aLineList; i++){
    //find lowest
    if ( aLineList[i].numPkgsProcessing < minLine->numPkgsProcessing) {
      minLine = &aLineList[i];
    }
  }
  minLine->processingPkgBuffer.enqueue(newPkg);
  minLine->numPkgsProcessing++;
  cerr << "PACKAGE SENT TO" <<minLine->assemblyLineID<<endl;

}

void Dispatcher::dispatch_to_assembly2(Package newPkg){
 // go dirctly to processing queueue , bypassig arrival queue inside assembly.

  //setting default mins.
  // int min = aLineList[0].numPkgsProcessing;
  AssemblyLine *minLine;
    minLine = &aLineList[0];

  for (int i = 0; i<length_aLineList; i++){
    //find lowest
    if ( aLineList[i].numPkgsProcessing < minLine->numPkgsProcessing) {
      minLine = &aLineList[i];
    }
  }
  minLine->processingPkgBuffer.enqueue(newPkg);
  minLine->numPkgsProcessing++;
  cerr << "PACKAGE SENT TO" <<minLine->assemblyLineID<<endl;

}

void Dispatcher::dispatch_to_assembly3(Package newPkg){
 // go dirctly to processing queueue , bypassig arrival queue inside assembly.

  //setting default mins.
  // int min = aLineList[0].numPkgsProcessing;
  AssemblyLine *minLine;
    minLine = &aLineList[0];

  for (int i = 0; i<length_aLineList; i++){
    //find lowest
    if ( aLineList[i].numPkgsProcessing < minLine->numPkgsProcessing) {
      minLine = &aLineList[i];
    }
  }
  minLine->processingPkgBuffer.enqueue(newPkg);
  minLine->numPkgsProcessing++;
  cerr << "PACKAGE SENT TO" <<minLine->assemblyLineID<<endl;

}
