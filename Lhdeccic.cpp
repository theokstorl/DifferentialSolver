#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <iomanip>
#include "Lhdeccic.h"

Lhdeccic::Lhdeccic()
{
	sett0(0);
	setB(1);
	setK0(1);
	setDiffSol("y");
}

Lhdeccic::Lhdeccic(double temB, double tempT, double tempK)
{
	sett0(tempT);
	setB(temB);
	setK0(tempK);
	setDiffSol("y");
}

//accessor function for B
double Lhdeccic::getB() const
{
	return b;
}

//accessor function for t0
double Lhdeccic::gett0() const
{
	return t0;
}

//accessor function for K0
double Lhdeccic::getK0() const
{
	return K0;
}

//accessor function for string Label
std::string Lhdeccic::getDiffSol() const
{
	return diffSolution;
}

//mutator function for B
void Lhdeccic::setB(double tempB)
{
	b = tempB;
}

//mutator function for t0
void Lhdeccic::sett0(double tempt0)
{
	t0 = tempt0;
}

//mutator function for K0
void Lhdeccic::setK0(double tempK0)
{
	K0 = tempK0;
}

//mutator function for diff solution
void Lhdeccic::setDiffSol(std::string tempSol)
{
	diffSolution = tempSol;
	solution.setLabel(tempSol);
}

//function that derived class uses toa access modified signal
Signal * Lhdeccic::modSigSol()
{
	return &solution;
}

//functions that gets text representation
std::string Lhdeccic::getTextRep() const
{
	return diffSolution + "(t) = " + solution.returnMath();
}

//member function copied and pasted from CourseWeb 
std::string Lhdeccic::textNum(double x) const	// Convert num->string for title
{
	if (x >= 100)
		return std::to_string(int(x));		// Large nums trunc. as int
	else
	{
		std::string x_exp = std::to_string(x);	// Small nums get 3 digits
		return x_exp.substr(0, 4 + (x<0));
	}
}

//virtual function that writes info to file
void Lhdeccic::baseWriter(std::ofstream &outfile) const
{
	outfile << "Solution" << std::endl;
	outfile << "--------" << std::endl;
	outfile << getTextRep() << std::endl << std::endl;
	solution.writer();
	
	solution.createPicture();
}
