//----------------------------------------------------------------------------
// Filename:    factory.h
// Date:        12 November 2013
// Description: interface for Factory class. Handles input of Pkgs and runs
//				Assembly Lines.
//----------------------------------------------------------------------------

#include "Dispatcher.h"


const int INIT_SIZE= 5;
const int EXPAND_FACTOR = 2;

class Factory {
	public:
		Factory(int num_assemblyLines, double rates[] );
		void addAssemblyLines(int num_assemblyLines, double rates[]);
		// ~Factory();
		int run();
		void getPkgOrder();

	private:
		Package initPackage(Package p);
		PackageQueue packageBufferQ;
			int pkgCount;

		AssemblyLine *aLineList; //dynamic array of AssemblyLines
		int length_aLineList;
		int capacity_aLineList;


};
