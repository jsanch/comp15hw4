//----------------------------------------------------------------------------
// Filename:    factory.cpp
// Date:        22 October 2013
// Description: implementation for Factory class. Handles input of Pkgs
//							and runs Assembly Lines.
//----------------------------------------------------------------------------

#include "factory.h"

//----------------------------------------------------------------------------
// Factory(): 		Initializes a dynamic Array for Pkg orders.
// Input:          	None
// Output:          None
//----------------------------------------------------------------------------
Factory::Factory(){

 	PkgOrder = new Package[INIT_SIZE_PKG_BUFF];

	// sets values to null.
	for (int i = 0; i < INIT_SIZE_PKG_BUFF; i++) {
		PkgOrder[i].order_number = '\0';
		PkgOrder[i].unit_number = '\0';
		PkgOrder[i].time_Arrived = '\0';
		PkgOrder[i].time_Shipped = '\0';
		PkgOrder[i].isShipped = '\0';
	}

	length_PkgOrder = 0;
	capacity_PkgOrder = INIT_SIZE_PKG_BUFF;

}

//----------------------------------------------------------------------------
// run(int num_workers, double rates[]):
//					Runs the factory. passes the order of packages to the
//                  assembly line so that it can process them.
// Input:          	An int, num_workers, and a pointer to array, rates.
// Output:          returns 0 if everything went well.
//----------------------------------------------------------------------------

int Factory::run(int num_workers, double rates[]){
	//initialises an assembly line with specified workers and rates.
	AssemblyLine l(num_workers, rates);
	// gets Packages from cin stream and stores in PkgOrder array.
	getPkgOrder();

	l.process(PkgOrder,length_PkgOrder );

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

	while( !cin.eof()){
 		 cin >> str;
 		 if (str == "number"){
 		 	cin >> PkgOrder[length_PkgOrder].order_number;
 		 }
 		 if (str == "with"){
 		 	cin >> PkgOrder[length_PkgOrder].unit_number;
 		 }
		if (str == "time"){
 		 	cin >> PkgOrder[length_PkgOrder].time_Arrived;
			PkgOrder[length_PkgOrder].isShipped = false; //for further use.
			length_PkgOrder ++;
			str = "null";
 		 }

 		 if ( length_PkgOrder == capacity_PkgOrder) expandPkgOrder();
	}
}

//----------------------------------------------------------------------------
// expandPkgOrder(): Resizes the PkgOrder array in case it is needed.
// Input:          	None
// Output:         	None
//----------------------------------------------------------------------------
void Factory::expandPkgOrder(){
	capacity_PkgOrder *= EXPAND_FACTOR;
	Package * temp = new Package[capacity_PkgOrder];

	for (int i = 0; i < length_PkgOrder; i++) {
		temp[i].order_number  = PkgOrder[i].order_number ;
		temp[i].unit_number  = PkgOrder[i].unit_number ;
		temp[i].time_Arrived  = PkgOrder[i].time_Arrived ;
		temp[i].time_Shipped  = PkgOrder[i].time_Shipped ;
		temp[i].isShipped  = PkgOrder[i].isShipped ;
		cerr << "Expanding" <<endl;
	}

	for (int e = length_PkgOrder; e < capacity_PkgOrder; e ++){
			temp[e].order_number = '\0';  // Null terminator for de-bugging
			temp[e].unit_number = '\0';
			temp[e].time_Arrived = '\0';
			temp[e].time_Shipped = '\0';
			temp[e].isShipped = '\0';
	}


	delete[] PkgOrder;
	PkgOrder = temp;

}


Factory::~Factory(){
	delete[] PkgOrder;
}



//add something.
