//----------------------------------------------------------------------------
// Filename:    factory.h
// Date:        22 October 2013
// Description: interface for Factory class. Handles input of Pkgs and runs 
//				Assembly Lines. 
//----------------------------------------------------------------------------

#include "AssemblyLine.h"

const int INIT_SIZE_PKG_BUFF = 5; 
const int EXPAND_FACTOR = 2; 

class Factory { 
	public:
		Factory();
		~Factory();
		int run(int num_workers, double rates[]);  
		void getPkgOrder(); 

	private:		
		Package *PkgOrder; //dynamic array of packages to store PkgOrder.
		void expandPkgOrder(); 
		int length_PkgOrder;
		int capacity_PkgOrder; 
};
