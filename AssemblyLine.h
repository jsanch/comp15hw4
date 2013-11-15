//----------------------------------------------------------------------------
// Filename:    AssemblyLine.h
// Date:        12 November 2013
// Description: interface for the Assembly Line class
//----------------------------------------------------------------------------
#include "PackageQueue.h"

#include <cstdlib>
#include <iostream>

using namespace std;


class AssemblyLine {

	public:
		AssemblyLine();

		bool do_work();
		void shipPkg(int timeUnit);
		int getNumUnitsLeft();
		double getPkgETA();
		void print();
		void set_workRate(double r);
		void set_ID(int id);
		void loadCurrentPkg();
		bool isPkgCompleted(Package *p);
		bool isCurrentPkgLoaded();
		void setCompletedPkgCount(int n);
		void setArrivingQueue(PackageQueue *PkgBuffer);

		int assemblyLineID;
		double workRate;

		int timeUnit;

		PackageQueue processingPkgBuffer;
		PackageQueue completedPkgBuffer;
		Package * currentPkg;

		int numPkgsProcessing;
		int arrivedPkgCount;
		int completedPkgCount;
 		int numUnitsProcessing;

	};

