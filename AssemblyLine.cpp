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
	cerr <<"ASSEMBLYLINE construtor"<< endl;
	double workRate = 0;
	numPkgsProcessing = 0;
	currentPkg = NULL;
	arrivingPkgBuffer = NULL;
	cerr <<"arrivingPkgBuffer: "<<  arrivingPkgBuffer << " in " << assemblyLineID<<endl;

	int numUnitsProcessing = 0;
}

void AssemblyLine::set_workRate(double r){
	workRate = r;
	cerr <<"arrivingPkgBuffer: "<<  arrivingPkgBuffer << " in " << assemblyLineID<<endl;

}

void AssemblyLine::set_ID(int id){
	assemblyLineID = id;
		cerr <<"arrivingPkgBuffer: "<<  arrivingPkgBuffer << " in " << assemblyLineID<<endl;

}
// void AssemblyLine::testARR(){
// 	cerr << "testing..." <<endl;
// 	cerr << arrivingPkgBuffer <<endl; //why is this segfaulting.
// 	cerr << NULL;
// }
// void AssemblyLine::setArrivingQueue(PackageQueue * pkgBuffer){
// 	cerr<< "///////////////ñññññ///////////////" <<endl;
// 	cerr<<"BEFORE SETTING THE ARRIVING QUEUE, incoming pkgs are:" <<endl;
// 	pkgBuffer->display();
// 	cerr <<"1"<< arrivingPkgBuffer <<endl;
// 	this->arrivingPkgBuffer = pkgBuffer;
// 	cerr<< "ARRIVING QUEUE WAS SET IN AL" <<endl;
// 	arrivingPkgBuffer->display();
// }

//----------------------------------------------------------------------------
// process(PackageQueue  pkgBufferQ):	"The brains" of the Assembly
//			Line. Takes in an order of packages, works on them on simulated
//			real time and finally ships them.
// Input:   Aa queue, PkgOrder.
// Output:  None
//----------------------------------------------------------------------------
// void AssemblyLine::process(PackageQueue * PkgBuffer, int pkgCount){
// 	cerr <<"2"<<arrivingPkgBuffer <<endl;
// 	this->arrivingPkgBuffer = PkgBuffer;
// 	int timeUnit=0;
// 	int arrivedPkgCount = pkgCount;
// 	int	completedPkgCount = 0;

// 	while( completedPkgCount != arrivedPkgCount  ){

// 		//STEP 1
// 		if (!processingPkgBuffer.isEmpty()) {
// 			if (!isCurrentPkgLoaded()){
// 				loadCurrentPkg();
// 				completedPkgCount =  do_work(completedPkgCount, timeUnit);
// 			}else{
// 				completedPkgCount =  do_work(completedPkgCount, timeUnit);
// 			}
// 		}
// 		//STEP 2  ship if completed
// 		if (isCurrentPkgLoaded()){
// 			if(isPkgCompleted(currentPkg)){
// 				shipPkg(timeUnit); // puts package in a cmpleted Pkg Buffer.
// 			}
// 		}
// 		//STEP 3 add packages that arrive to Pkgqueue
// 			if (!arrivingPkgBuffer->isEmpty()){
// 				handlePkgArrival(arrivingPkgBuffer,timeUnit);
// 			}

// 		// tick tock
// 			timeUnit++;
// 	}
// 	// completedPkgBuffer.display();

// }

bool AssemblyLine::do_work(int timeUnit){
		//adding workrate to amount worked.
		currentPkg->units_worked += workRate;
		//in case there is more worked units than the number of units.
		if (currentPkg->units_worked > currentPkg->unit_number){
			currentPkg->units_worked = currentPkg->unit_number;
		}
		//updating isCompleted value, in case it completes the package.
		if (currentPkg->units_worked >= currentPkg->unit_number){
			currentPkg->isCompleted = true;
			cerr << "Completed a pkg!"<<endl;
			return true;

		} else {
			return false;

		}
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
		numPkgsProcessing = numPkgsProcessing -1;
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

}

// checks if there is a current Package Laoded
bool AssemblyLine::isCurrentPkgLoaded(){
	return !(currentPkg == NULL);
}

int AssemblyLine::getNumUnitsLeft(){
cerr << "calcultating number of units left in Assembly line " << assemblyLineID;
	int currentUnits = 0;
	if ( isCurrentPkgLoaded())
		int currentUnits = ( currentPkg->unit_number - currentPkg->units_worked);

	return numUnitsProcessing + currentUnits;
}

double AssemblyLine::getPkgETA(){
	int units_left = getNumUnitsLeft();
	return units_left/workRate;
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
		<<" from "<< currentPkg->assemblyLineID + 1
		<< endl;

}
