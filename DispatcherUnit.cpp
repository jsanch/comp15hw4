//----------------------------------------------------------------------------
// Filename:    DispatcherPackage.cpp
// Date:        12 November 2013
// Description: implementation for Dispatcher class.
//----------------------------------------------------------------------------


#include "Dispatcher.h"

//----------------------------------------------------------------------------
// Dispatcher():  Initializes the Dispatcher.
// Input:         array of Assembly lines, an their size.
// Output:          None
//----------------------------------------------------------------------------
Dispatcher::Dispatcher(AssemblyLine *list, int size){
  this->aLineList = list;
  this->length_aLineList = size;
}
//----------------------------------------------------------------------------
// dispatch(): processes a the list of incoming Packages.
// Input:       A queue of packages and a count of packages.
// Output:      None
//----------------------------------------------------------------------------
void Dispatcher::dispatch(PackageQueue * PkgBuffer, int pkgCount){
 this->arrivingPkgBuffer = PkgBuffer;

  timeUnit = 0;
  int completedPkgCount=0;
  while(completedPkgCount != pkgCount){
    for (int i = 0; i < length_aLineList; i++){
      completedPkgCount += al_do_work(i); //step one
      al_ship(i, timeUnit);               //step two
    }
    if (!arrivingPkgBuffer->isEmpty()){
      distributeArrivingPkgs(timeUnit);   //step three (critical)
    }
     timeUnit++;
  }
}

//----------------------------------------------------------------------------
// al_do_work(int id): works on a specified assmebly line
// Input:      an id. (the assembly line's id. )
// Output:      int, returns 1 if a package was completed, 0 if not.
//----------------------------------------------------------------------------
int Dispatcher::al_do_work(int id){
  int completedPkgCount = 0;
 AssemblyLine * aL = &aLineList[id]; // easier to work with.
    if (!( aL -> processingPkgBuffer.isEmpty()) ) {
      if (! aL->isCurrentPkgLoaded()){
        aL->loadCurrentPkg();
        completedPkgCount = aL->do_work();
      }else{
        completedPkgCount = aL->do_work();
      }
    }
    return completedPkgCount;
}
//----------------------------------------------------------------------------
// al_ship(int id, int timeUnit): ships in a specified assemby line.
// Input:      an id (int) , the time (int)
// Output:     None
//----------------------------------------------------------------------------
void Dispatcher::al_ship(int id, int timeUnit){
  AssemblyLine * aL = &aLineList[id];
    if (aL->isCurrentPkgLoaded()){
      if(aL->isPkgCompleted(aL->currentPkg)){
         aL->numUnitsProcessing -=  aL->currentPkg->unit_number;
        aL->shipPkg(timeUnit); // puts package in a cmpleted Pkg Buffer.
      }
    }
}

//----------------------------------------------------------------------------
// distributeArrivingPkgs(int timeUnit): distribute Arriving Packages into a
//                                       an assembly line.
// Input:     the time (int)
// Output:    None
//----------------------------------------------------------------------------
void Dispatcher::distributeArrivingPkgs(int timeUnit){
  Package *frontPkg = this->arrivingPkgBuffer->getFront();
  if (frontPkg ->time_Arrived == timeUnit) {
    Package newPkg = *frontPkg;
    dispatch_to_assembly(newPkg); /// this is like the enqueue.
    this->arrivingPkgBuffer->dequeue();
  }
}

//----------------------------------------------------------------------------
// dispatch_to_assembly(Pkg): Algortithm that decides which assembly to
//                            dispatch the incoming Pkg.
// Input:     Package newPkg.
// Output:    None
//----------------------------------------------------------------------------
void Dispatcher::dispatch_to_assembly(Package newPkg){
  AssemblyLine *minLine;
    minLine = &aLineList[0];
  for (int i = 0; i<length_aLineList; i++){
    //find lowest
    if ( aLineList[i].getNumUnitsLeft() < minLine->getNumUnitsLeft()) {
      minLine = &aLineList[i];
    }
  }
  minLine->processingPkgBuffer.enqueue(newPkg);
  minLine->numUnitsProcessing += newPkg.unit_number;
}
