//----------------------------------------------------------------------------
// Filename:    factory.cpp
// Date:        12 November 2013
// Description: implementation for Factory class. Handles input of Pkgs
//							and runs Assembly Lines.
//----------------------------------------------------------------------------

#include "factory.h"

//----------------------------------------------------------------------------
// Factory(): 		Initializes a dynamic Array for Pkg orders.
// Input:          	An int, num_assemblyLines and a pointer to array, rates.
// Output:          None
//----------------------------------------------------------------------------
Factory::Factory(int num_assemblyLines, double rates[]){
	 addAssemblyLines(num_assemblyLines, rates);

	// get Pkgs from file and insert to the pacakgeBuffer.
	pkgCount = 0; // to keep count of inserted packages.
	getPkgOrder();

}

void Factory::addAssemblyLines(int num_assemblyLines, double rates[] ){
	aLineList = new AssemblyLine[num_assemblyLines];

	for(int i = 0; i<num_assemblyLines; i++){
		aLineList[i].set_ID(i); //asesembly line id should at 1.
		aLineList[i].set_workRate(rates[i]);
	}
	length_aLineList = num_assemblyLines; //not sure if i need this.
	capacity_aLineList = num_assemblyLines; //not sure if i need this.
}


//----------------------------------------------------------------------------
// run(int num_workers, double rates[]):
//					Runs the factory. passes the order of packages to the
//                  assembly line so that it can process them.
// Input:          	An int, num_workers, and a pointer to array, rates.
// Output:          returns 0 if everything went well.
//----------------------------------------------------------------------------

int Factory::run(){
	Dispatcher joe(aLineList, length_aLineList );
	joe.dispatch(&packageBufferQ, pkgCount );

// // first, check it works for one assembly line
// 	aLineList[0].process(&packageBufferQ, pkgCount);

	return 0;
}

//----------------------------------------------------------------------------
// getPkgOrder(): 	Gets the packages order from cin and stores them in a
// 					dynamic array.
// Input:          	None
// Output:         	None
//----------------------------------------------------------------------------
void Factory::getPkgOrder(){
	Package tempPkg;
	tempPkg = initPackage(tempPkg);

  string junk;

  cin >> junk;
  while (junk == "Package")
  {
    cin >> junk;
    cin >> junk;
    cin >> tempPkg.order_number;
    cin >> junk;
    cin >> tempPkg.unit_number;;
    cin >> junk;
    cin >> junk;
    cin >> junk;
    cin >> junk;
    cin >> tempPkg.time_Arrived;
    packageBufferQ.enqueue(tempPkg);
    pkgCount++;
    cin >> junk;
	}
}

//initializes package variables to zero
Package Factory::initPackage(Package p){
		p.order_number= "NONE";
		p.unit_number= 0;
		p.units_worked = 0;
		p.time_Arrived= 0;
		p.time_Shipped= 0;
		p.isCompleted= false;
		p.assemblyLineID= 0;
		return p;
}
