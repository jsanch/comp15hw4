
#include <iostream>
#include <cstdlib>

using namespace std;

#include "AssemblyLine.h"

class Dispatcher {
  public:
    Dispatcher(AssemblyLine *list, int size);
    void dispatch(PackageQueue *PkgBuffer, int PkgCount);
    int al_do_work(int id, int timeUnit);
    void al_ship(int id, int timeUnit);
    void distributeArrivingPkgs(int timeUnit);
    void init_aLs(PackageQueue * arrivingPkgBuffer);
    void initAssemblies();
    void dispatch_to_assembly1(Package newPkg);
    void dispatch_to_assembly2(Package newPkg);
    void dispatch_to_assembly3(Package newPkg);
  private:
    PackageQueue *arrivingPkgBuffer;

    AssemblyLine *aLineList;
    int length_aLineList;
    int timeUnit;
    // int completedPkgCount;

};



//storyline
// dispactcher recieves pkg queue.
// dispactcher distributes pkgs,
  //options;
    //in 'real time', getting feedback from the assemblyline.
      //dispatcher sends a package to assembly line 1.
        // assembly line 1 stores package.
        // assembly line works with time set forth by dispatcer.
        // so at every turn, dispatcher sends a package, or not, and al1
        //  works on it
      //dispatcher sends a package to assembly line 1.
    //with secret algorithm( forsees in artificial time)
