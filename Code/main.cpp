/*
 * main.cpp
 *
 *  Created on: Oct 31, 2017
 *      Author: Anish Gupta
 */
#include "fstream"
#include "iostream"
#include "ctime"
#include "Node.hpp"
#include "NonSlicingFloorplanner.hpp"
#include "PolishUtilities.hpp"
#include "RandomizeUtilites.hpp"
#include "FloorplannerConstants.hpp"
#include "IOUtilites.hpp"
#include "Vertex.hpp"
#include <list>
using namespace std;
void unitTest();
int main(){
	try {
		unitTest();
		return 0;
	}
	catch (...) {
		cout << "EXCEPTION!!";
	}
}
void unitTest() {
	//Setup outputstream for analysis
//	ofstream output;
//	output.open("stats.txt");
	//Read data from input file
	list<Node> data = IOUtilites::getInstance().readData();
	//Setup constants for analysis
	//double avgPercent = 0, avgRuntime = 0;
	for(int i=0;i<1;i++){
		int start = clock();
		NonSlicingFloorplanner myPlanner(data);
		myPlanner.floorplan();
		double totalArea = myPlanner.computeUsedArea();
		double blackArea = myPlanner.computeBlackArea();
		IOUtilites::getInstance().writeData(*myPlanner.processCords(),totalArea,blackArea);
		//double runtime = (clock() - start) / double(CLOCKS_PER_SEC);
		//double percent = 100*blackArea/totalArea;
		/*output << to_string(runtime) << "," << to_string(percent) << endl;
		avgPercent = avgPercent + percent;
		avgRuntime = avgRuntime + runtime;*/
	}
//	cout<<endl<<"Runtime: "<< avgRuntime << " \tPercentBlack: " << avgPercent <<endl;
//	output.close();
}
