//----------------------------------------------------------------------------
// Filename:    AssemblyLine.cpp
// Date:        22 October 2013
// Description:  Implementation of the assembly line.
//----------------------------------------------------------------------------

#include "AssemblyLine.h"

//----------------------------------------------------------------------------
// AssemblyLine():  Initializes an assembly line with workers.
// Input:          	An Integer, workers. And a double (array), ratesList.
// Output:          None
//----------------------------------------------------------------------------
AssemblyLine::AssemblyLine(int workers, double *rateslist){
	if ( workers != 1){
		cerr << " Expecting only 1 worker for this assigment";
		exit(1);
	}
	worker.rate = rateslist[0]; // for this assigment,
}								// assuming only one worker, with one rate.



//----------------------------------------------------------------------------
// process(Package * PkgOrder , int orderSize):	"The brains" of the Assembly
//			Line. Takes in an order of packages, works on them on simulated
//			real time and finally ships them.
// Input:   An Array, PkgOrder, of size orderSize.
// Output:  None
//----------------------------------------------------------------------------
void AssemblyLine::process(Package * PkgOrder , int orderSize){
	Package * currentPkg = NULL; // used to mark if there is a pkg being worked
	bool endloop = false;  // used to break the loop.
	int i=0;  //the simulated time counter.

	while ( endloop != true) { // start loop. each loop represents a minute.
	//Case 1: Do work on current Pkg. If no current Pkg, get it from PkgQueue.
		if ( ! PkgQueue.isEmpty() )  {
			if(currentPkg == NULL){
					currentPkg =  PkgQueue.getFront();
					currentPkg->units_worked  += worker.rate;
			} else {
				currentPkg->units_worked  += worker.rate;
			}
		}
	//Case 2: Check if currentPkg is proccessed. If so, Ship.
		if(currentPkg != NULL) {
			//case 1: is the current package ready for shipping? if so ship.
			if (currentPkg->units_worked >= currentPkg->unit_number){
				PkgQueue.dequeue();
				currentPkg->time_Shipped = i;
				ship (currentPkg);
					// if last packagehas shipped, end it.
					if (currentPkg->order_number ==  PkgOrder[orderSize-1].order_number ) {
						endloop = true;
					}
				currentPkg = NULL; // signal that there is no current package to work on.
			}
		}
		// Use a  Timer
	//Case3: Check if Pkg has arrived. if so, put on the queue.
		for (int j=0; j < orderSize; j++){
			if ( PkgOrder[j].time_Arrived == i ) {
				PkgQueue.enqueue( PkgOrder[j]);
				break;
			}
		}
		i++;
	}
}

//----------------------------------------------------------------------------
// ship():  prints a package's shipping info.
// Input:   A Pointer to a Package.
// Output: 	None
//----------------------------------------------------------------------------
void AssemblyLine::ship(Package * p){
	cout<<"Package order number "<<p->order_number
		<<" with "<<p->unit_number
		<<" units arrived at time "<<p->time_Arrived
		<<" and left at time "<<p->time_Shipped
		<< endl;

}


// int main(){
// 	//this is how run will use it...
// 	int workers = 1;
// 	double rates[1];
// 	rates[0] = 2.00;
// 	AssemblyLine l(workers,rates);

// 	int orderSize = 5 ; // must be  the ACTUAL amount of pkgs.
// 	Package * PkgOrder = new Package[orderSize];

// 	PkgOrder[0].order_number= "S000"  	;	//from data5.
// 	PkgOrder[0].unit_number = 8 ;
// 	PkgOrder[0].time_Arrived =  6;

// 	PkgOrder[1].order_number ="S001";
// 	PkgOrder[1].unit_number = 8;
// 	PkgOrder[1].time_Arrived =  7;

// 	PkgOrder[2].order_number ="S002";
// 	PkgOrder[2].unit_number = 4;
// 	PkgOrder[2].time_Arrived =  13;

// 	PkgOrder[3].order_number ="S003";
// 	PkgOrder[3].unit_number = 9;
// 	PkgOrder[3].time_Arrived =  14;

// 	PkgOrder[4].order_number ="S004";
// 	PkgOrder[4].unit_number = 8;
// 	PkgOrder[4].time_Arrived =  21;



// 	l.process(PkgOrder, orderSize);


// 	return 0;
// }

