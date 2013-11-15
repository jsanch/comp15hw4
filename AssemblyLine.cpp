//----------------------------------------------------------------------------
// Filename:    AssemblyLine.cpp
// Date:        12 November 2013
// Description:  Implementation of the assembly line.
//----------------------------------------------------------------------------

#include "AssemblyLine.h"

//----------------------------------------------------------------------------
// AssemblyLine():  Initializes an assembly line.
// Input:          	None
// Output:          None
//----------------------------------------------------------------------------
AssemblyLine::AssemblyLine(){
	numPkgsProcessing = 0;
	currentPkg = NULL;
}

//----------------------------------------------------------------------------
// do_work(): Does work on the current package. returns true if pkg completed.
// Input:          	None
// Output:          true or false
//----------------------------------------------------------------------------
bool AssemblyLine::do_work(){
		//adding workrate to amount worked.
		currentPkg->units_worked += workRate;
		//in case there is more worked units than the number of units.
		if (currentPkg->units_worked > currentPkg->unit_number){
			currentPkg->units_worked = currentPkg->unit_number;
		}
		//updating isCompleted value, in case it completes the package.
		if (currentPkg->units_worked >= currentPkg->unit_number){
			currentPkg->isCompleted = true;
			// cerr << "Completed a pkg!"<<endl;
			return true;

		} else {
			return false;

		}
}
//----------------------------------------------------------------------------
// shipPkg(): Ships the current package.
// Input:          	None
// Output:          true or false
//	precondition: current package is completed.
//	precondition: current Package is loaded.
//----------------------------------------------------------------------------
void AssemblyLine::shipPkg(int timeUnit){
		currentPkg->time_Shipped = timeUnit;
		currentPkg->assemblyLineID= assemblyLineID;
		print();
		Package completedPkg = *currentPkg;
		completedPkgBuffer.enqueue(completedPkg);
		processingPkgBuffer.dequeue();
		numPkgsProcessing = numPkgsProcessing -1;
		currentPkg = NULL;
}

/* helper functions */
//----------------------------------------------------------------------------
// loadCurrentPkg(): Gets a pointer to  the front of the processing queue
// Input:          	None
// Output:          true or false
// precondition: arrivingPkgBuffer is NOT EMPTY
//----------------------------------------------------------------------------
void AssemblyLine::loadCurrentPkg(){
		currentPkg = processingPkgBuffer.getFront(); //loading.
}


//----------------------------------------------------------------------------
// isPkgCompleted(Package *p): Checks if a Package is completed
// Input:  pointer to a package
// Output: true,  false
//----------------------------------------------------------------------------
bool AssemblyLine::isPkgCompleted(Package *p){
		if (p == NULL)
			return false;
		else
			return p->isCompleted;
}

//----------------------------------------------------------------------------
// setCompletedPkgCount(int n): sets the coount of completed Packages
// Input:      int, n
// Output:     none
//----------------------------------------------------------------------------
void AssemblyLine::setCompletedPkgCount(int n){
		completedPkgCount = n;
}


// ----------------------------------------------------------------------------
// isCurrentPkgLoaded(): Checks if there is a Package currently loaded.
// Input:
// Output: 	true, false
// ----------------------------------------------------------------------------
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
		<<" from "<< currentPkg->assemblyLineID + 1
		<< endl;

}


//----------------------------------------------------------------------------
// set_workRate(double r): sets the rate of work of the assembly line.
// Input:          	double, rate
// Output:          None
//----------------------------------------------------------------------------
void AssemblyLine::set_workRate(double r){
	workRate = r;
}

//----------------------------------------------------------------------------
// set_ID(int id): sets the ID of the Assembly Line
// Input:          	int, id
// Output:          None
//----------------------------------------------------------------------------
void AssemblyLine::set_ID(int id){
	assemblyLineID = id;
}


//----------------------------------------------------------------------------
// getNumUnitsLeft(int id): Gets the number of Units left in the Assembly line
// Input:          	None
// Output:          int, numUnitsProcessing + currentUnits
//----------------------------------------------------------------------------
int AssemblyLine::getNumUnitsLeft(){
	int currentUnits = 0;
	if ( isCurrentPkgLoaded())
		 currentUnits = ( currentPkg->unit_number - currentPkg->units_worked);
	return numUnitsProcessing + currentUnits;
}


//----------------------------------------------------------------------------
// getPkgETA(): gets the ETA for the packages.
// Input:          	None
// Output:          int, numUnitsProcessing + currentUnits
//----------------------------------------------------------------------------
double AssemblyLine::getPkgETA(){
	int units_left = getNumUnitsLeft();
	return units_left/workRate;
}
