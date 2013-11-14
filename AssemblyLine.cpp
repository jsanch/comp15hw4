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
AssemblyLine::AssemblyLine(){
	double workRate = 0;
	currentPkg = NULL;
}

void AssemblyLine::set_workRate(double r){
	workRate = r;
}

void AssemblyLine::set_ID(int id){
	assemblyLineID = id;
}

//----------------------------------------------------------------------------
// process(PackageQueue  pkgBufferQ):	"The brains" of the Assembly
//			Line. Takes in an order of packages, works on them on simulated
//			real time and finally ships them.
// Input:   Aa queue, PkgOrder.
// Output:  None
//----------------------------------------------------------------------------
void AssemblyLine::process(PackageQueue arrivingPkgBuffer, int pkgCount){
	// arrivingPkgBuffer.display();
	int timeUnit=0;
	int arrivedPkgCount = pkgCount;
	int	completedPkgCount = 0;

	while( completedPkgCount != arrivedPkgCount  ){

		//STEP 1
		if (!processingPkgBuffer.isEmpty()) {
			if (!isCurrentPkgLoaded()){
				loadCurrentPkg();
				completedPkgCount =  do_work(completedPkgCount, timeUnit);
			}else{
				completedPkgCount =  do_work(completedPkgCount, timeUnit);
			}
		}
		//STEP 2  ship if completed
		if (isCurrentPkgLoaded()){
			if(isPkgCompleted(currentPkg)){
				shipPkg(timeUnit); // puts package in a cmpleted Pkg Buffer.
			}
		}
		//STEP 3 add packages that arrive to Pkgqueue
			if (!arrivingPkgBuffer.isEmpty()){
				handlePkgArrival(&arrivingPkgBuffer,timeUnit);
			}

		// tick tock
			timeUnit++;
	}
	// completedPkgBuffer.display();

}

int AssemblyLine::do_work(int completedPkgCount, int timeUnit){
		//adding workrate to amount worked.
		currentPkg->units_worked += workRate;

		//updating isCompleted value, in case it completes the package.
		if (currentPkg->units_worked >= currentPkg->unit_number){
			currentPkg->isCompleted = true;
			completedPkgCount ++;

		}
	return completedPkgCount;
}

//precondition: arrivingPkgBuffer is NOT EMPTY
void AssemblyLine::loadCurrentPkg(){
		currentPkg = processingPkgBuffer.getFront(); //loading.
}

bool AssemblyLine::isPkgCompleted(Package *p){
		if (p == NULL)
			return false;
		else
			return p->isCompleted;
}
void AssemblyLine::setCompletedPkgCount(int n){
		completedPkgCount = n;
}

//precondition: current package is completed.
//precondition: CurrentPackage is loaded.
void AssemblyLine::shipPkg(int timeUnit){
		currentPkg->time_Shipped = timeUnit;
		currentPkg->assemblyLineID= assemblyLineID;
		print();
		//add completed package to completed Pkg buffer
		Package completedPkg = *currentPkg;
		completedPkgBuffer.enqueue(completedPkg);
		processingPkgBuffer.dequeue();

		currentPkg = NULL;


}

void AssemblyLine::handlePkgArrival(PackageQueue * arrivingPkgBuffer, int timeUnit){

	// getting the front of the arriving PkgBuffer.
	Package * frontPkg = arrivingPkgBuffer->getFront();
	// check if the frontPkg has arrived for the current timeUnit.
	if ( frontPkg->time_Arrived == timeUnit) { //solo se mete una vez.
		//add package to processsing queue
		Package  newPkg = *frontPkg; //creating new, because other was a pointer.
		processingPkgBuffer.enqueue (newPkg);
		//remove arrived pacakge from arriving PkgBufferr
		 arrivingPkgBuffer->dequeue();
		 // frontPkg = arrivingPkgBuffer->getFront();
	}
	// else, dont do anything.

}



// checks if there is a current Package Laoded
bool AssemblyLine::isCurrentPkgLoaded(){
	return !(currentPkg == NULL);
}


// ----------------------------------------------------------------------------
// ship():  prints a package's shipping info.
// Input:   A Pointer to a Package.
// Output: 	None
// ----------------------------------------------------------------------------
void AssemblyLine::print(){
	cout<<"Package order number "<<currentPkg->order_number
		<<" with "<<currentPkg->unit_number
		<<" units arrived at time "<<currentPkg->time_Arrived
		<<" and left at time "<<currentPkg->time_Shipped
		<<" from "<< currentPkg->assemblyLineID
		<< endl;

}




//precondition: there are always Pkg left in buffer.
// bool AssemblyLine::loadCurrentPkg(){
// 	// it is called when there are no current packages.
// 	// it assigns the next package in the buffer to the queue
// 			if ( processingPkgBuffer.isEmpty && currentPkg == NULL ){
// 			// if the Pkg queue is not empty and there is no current Pkg,
// 			// load current Package.
// 		}
// }

	// Package * currentPkg = NULL; // used to mark if there is a pkg being worked
	// bool endloop = false;  // used to break the loop.
	// int i=0;  //the simulated time counter.

	// while ( endloop != true) { // start loop. each loop represents a minute.
	// //Case 1: Do work on current Pkg. If no current Pkg, get it from processingPkgBuffer.
	// 	if ( ! processingPkgBuffer.isEmpty() )  {
	// 		if(currentPkg == NULL){
	// 				currentPkg =  processingPkgBuffer.getFront();
	// 				currentPkg->units_worked  += worker.rate;
	// 		} else {
	// 			currentPkg->units_worked  += worker.rate;
	// 		}
	// 	}
	// //Case 2: Check if currentPkg is proccessed. If so, Ship.
	// 	if(currentPkg != NULL) {
	// 		//case 1: is the current package ready for shipping? if so ship.
	// 		if (currentPkg->units_worked >= currentPkg->unit_number){
	// 			processingPkgBuffer.dequeue();
	// 			currentPkg->time_Shipped = i;
	// 			ship (currentPkg);
	// 				// if last packagehas shipped, end it.
	// 				if (currentPkg->order_number ==  PkgOrder[orderSize-1].order_number ) {
	// 					endloop = true;
	// 				}
	// 			currentPkg = NULL; // signal that there is no current package to work on.
	// 		}
	// 	}
	// 	// Use a  Timer
	// //Case3: Check if Pkg has arrived. if so, put on the queue.
	// 	for (int j=0; j < orderSize; j++){
	// 		if ( PkgOrder[j].time_Arrived == i ) {
	// 			processingPkgBuffer.enqueue( PkgOrder[j]);
	// 			break;
	// 		}
	// 	}
	// 	i++;
	// }
// }





////LAST ALGO.
// void AssemblyLine::process(PackageQueue pkgBufferQ , int orderSize){
// 	Package * currentPkg = NULL; // used to mark if there is a pkg being worked
// 	bool endloop = false;  // used to break the loop.
// 	int i=0;  //the simulated time counter.

// 	while ( endloop != true) { // start loop. each loop represents a minute.
// 	//Case 1: Do work on current Pkg. If no current Pkg, get it from processingPkgBuffer.
// 		if ( ! processingPkgBuffer.isEmpty() )  {
// 			if(currentPkg == NULL){
// 					currentPkg =  processingPkgBuffer.getFront();
// 					currentPkg->units_worked  += worker.rate;
// 			} else {
// 				currentPkg->units_worked  += worker.rate;
// 			}
// 		}
// 	//Case 2: Check if currentPkg is proccessed. If so, Ship.
// 		if(currentPkg != NULL) {
// 			//case 1: is the current package ready for shipping? if so ship.
// 			if (currentPkg->units_worked >= currentPkg->unit_number){
// 				processingPkgBuffer.dequeue();
// 				currentPkg->time_Shipped = i;
// 				ship (currentPkg);
// 					// if last packagehas shipped, end it.
// 					if (currentPkg->order_number ==  PkgOrder[orderSize-1].order_number ) {
// 						endloop = true;
// 					}
// 				currentPkg = NULL; // signal that there is no current package to work on.
// 			}
// 		}
// 		// Use a  Timer
// 	//Case3: Check if Pkg has arrived. if so, put on the queue.
// 		for (int j=0; j < orderSize; j++){
// 			if ( PkgOrder[j].time_Arrived == i ) {
// 				processingPkgBuffer.enqueue( PkgOrder[j]);
// 				break;
// 			}
// 		}
// 		i++;
// 	}
// }
