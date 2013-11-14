//----------------------------------------------------------------------------
// Filename:    factory.cpp
// Date:        22 October 2013
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
	 pkgCount = 0;
	getPkgOrder();

}

void Factory::addAssemblyLines(int num_assemblyLines, double rates[] ){
	aLineList = new AssemblyLine[num_assemblyLines];

	for(int i = 0; i<num_assemblyLines; i++){
		aLineList[i].set_ID(i+1); //asesembly line id starts at 1.
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

	Dispatch

// first, check it works for one assembly line
	// aLineList[0].process(packageBufferQ, pkgCount);

	return 0;
}

//----------------------------------------------------------------------------
// getPkgOrder(): 	Gets the packages order from cin and stores them in a
// 					dynamic array.
// Input:          	None
// Output:         	None
//----------------------------------------------------------------------------
void Factory::getPkgOrder(){
	string str;
	Package tempPkg;
	tempPkg = initPackage(tempPkg);
	// must handle no packages !!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	while( !cin.eof()){
 		 cin >> str;
 		 if (str == "number"){
 		 	cin >> tempPkg.order_number;
 		 }
 		 if (str == "with"){
 		 	cin >> tempPkg.unit_number;
 		 }
		if (str == "time"){
 		 	cin >> tempPkg.time_Arrived;
			packageBufferQ.enqueue(tempPkg);
			pkgCount++;
			str = "null";
 		 }
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
