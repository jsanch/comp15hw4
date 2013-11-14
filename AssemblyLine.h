//----------------------------------------------------------------------------
// Filename:    AssemblyLine.h
// Date:        22 October 2013
// Description: interface for the Assembly Line class
//----------------------------------------------------------------------------
#include "PackageQueue.h"

#include <cstdlib>
#include <iostream>

using namespace std;


class AssemblyLine {

	public:
		AssemblyLine();
		void process(PackageQueue arrivingPkgBuffer, int pkgCount);
		void shipPkg(int timeUnit);
		void set_workRate(double r);
		void set_ID(int id);
		void print();
	private:
		void loadCurrentPkg();
		bool isPkgCompleted(Package *p);
		void handlePkgArrival(PackageQueue * arrivingPkgBuffer,int timeUnit);
		int do_work(int completedPkgCount, int timeUnit);
		// bool loadCurrentPkg();
		bool isCurrentPkgLoaded();
		void setCompletedPkgCount(int n);
		int timeUnit;

		int assemblyLineID;
		double workRate;
		PackageQueue processingPkgBuffer; // queue for handling the packages.

		//arrivingPkgBuffer
		// PackageQueue arrivingPkgBuffer;
		int arrivedPkgCount;
		//completedPkgBuffer
		PackageQueue completedPkgBuffer;
		int  completedPkgCount;

		//variables to be used by the process
		Package * currentPkg; // usually is the first of proccessingPkgBuffer.


	};

