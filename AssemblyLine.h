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
		void process(PackageQueue * PkgBuffer, int pkgCount);
		void shipPkg(int timeUnit);
		void set_workRate(double r);
		void set_ID(int id);
		void print();

		void loadCurrentPkg();
		bool isPkgCompleted(Package *p);
		void handlePkgArrival(PackageQueue * arrivingPkgBuffer,int timeUnit);
		bool do_work(int timeUnit);
		// bool loadCurrentPkg();
		bool isCurrentPkgLoaded();
		void setCompletedPkgCount(int n);

		int timeUnit;

		int assemblyLineID;
		double workRate;
		PackageQueue processingPkgBuffer; // queue for handling the packages.
		int numPkgsProcessing;
		void setArrivingQueue(PackageQueue *PkgBuffer);
		void testARR();
		//arrivingPkgBuffer
		PackageQueue * arrivingPkgBuffer;
		int arrivedPkgCount;
		//completedPkgBuffer
		PackageQueue completedPkgBuffer;
		int  completedPkgCount;

		//variables to be used by the process
		Package * currentPkg; // usually is the first of proccessingPkgBuffer.
		private:

	};

