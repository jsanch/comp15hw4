//----------------------------------------------------------------------------
// Filename:    Dispatcher.h
// Date:        12 November 2013
// Description: interface for the Dispatcher. There are three implementations
//              for this class.
//----------------------------------------------------------------------------
#include <iostream>
#include <cstdlib>

using namespace std;

#include "AssemblyLine.h"

class Dispatcher {
  public:
    Dispatcher(AssemblyLine *list, int size);
    void dispatch(PackageQueue *PkgBuffer, int PkgCount);
    int al_do_work(int id);
    void al_ship(int id, int timeUnit);
    void distributeArrivingPkgs(int timeUnit);
    void init_aLs(PackageQueue * arrivingPkgBuffer);
    void dispatch_to_assembly(Package newPkg);

  private:
    PackageQueue *arrivingPkgBuffer;
    AssemblyLine *aLineList;
    int length_aLineList;
    int timeUnit;

};
