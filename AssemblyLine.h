//----------------------------------------------------------------------------
// Filename:    AssemblyLine.h
// Date:        22 October 2013
// Description: interface for the Assembly Line class 
//----------------------------------------------------------------------------
#include "PackageQueue.h"

#include <cstdlib>
#include <iostream>

using namespace std;

struct Worker{
	double rate;
};

class AssemblyLine {

	public:
		AssemblyLine(int workers, double *rateslist); 
		void process(Package * PkgOrder, int orderSize); 
		void ship(Package * currentPkg);
	private:
		Worker worker; //only has one worker. In the future will have a list. 
		PackageQueue PkgQueue; // queue for handling the packages. 
	};
		
