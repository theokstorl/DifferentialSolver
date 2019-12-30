//Theodore Storl-Desmond
//ICA13

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include "Signal.cpp"
#include "Lhdeccic.cpp"
#include "Folhdeccic.cpp"
#include "Solhdeccic.cpp"

int main()
{
	//declaring ofstream object
	std::ofstream outfile;
	outfile.open("ECE 0301 - Differential Equation Reports.txt");
	
	//creating signal
	Solhdeccic secDiff1(2,101,-5,100,-100);
	secDiff1.setDiffSol("g");
	secDiff1.virtHeader(outfile);
	secDiff1.baseWriter(outfile);
	
	//creating signal
	Solhdeccic secDiff2(4,4,0,-50,500);
	secDiff2.setDiffSol("s");
	secDiff2.virtHeader(outfile);
	secDiff2.baseWriter(outfile);
	
	//creating signal
	Solhdeccic secDiff3(3,2,0,0,250);
	secDiff3.setDiffSol("y");
	secDiff3.virtHeader(outfile);
	secDiff3.baseWriter(outfile);
	
	//creating signal
	Folhdeccic  firstDiff1(2,-1.25,120);
	firstDiff1.setDiffSol("x");
	firstDiff1.virtHeader(outfile);
	firstDiff1.baseWriter(outfile);
	
	//closing outfile
	outfile.close();
	
	return 0;
}
