#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <iomanip>
#include "Folhdeccic.h"

//default constructor
Folhdeccic::Folhdeccic() : Lhdeccic::Lhdeccic()
{
	fillSignal();
}

//second constructor
Folhdeccic::Folhdeccic(double tempB, double tempT0, double tempK0) : Lhdeccic::Lhdeccic(tempB, tempT0, tempK0)
{
	fillSignal();
}

//first virtual function
std::string Folhdeccic::firstVirt() const
{
	return getDiffSol() + "'(t) + " + textNum(getB()) + " " + getDiffSol() + "(t) = 0"; 
}

//member fuction to return initial condition
std::string Folhdeccic::getInitCond() const
{
	return getDiffSol() + "(" + textNum(gett0())  + ") = " + textNum(getK0()); 
}
//member virtual function that fills signal
void Folhdeccic::fillSignal()
{
	Signal * signalPtr = modSigSol();
	signalPtr->setSamples(501);
	signalPtr->setFrequency(200);
	signalPtr->setInitialTime(gett0());
	signalPtr->fillSinExp(1/getB(),getK0());
	signalPtr->roundSin();
}

//virtual mutators
void Folhdeccic::setb(double a)
{
	setB(a);
	fillSignal();
}
void Folhdeccic::setk(double b)
{
	setK0(b);
	fillSignal();
}
void Folhdeccic::sett(double c)
{
	sett0(c);
	fillSignal();
}

//member virtual function to write header info
void Folhdeccic::virtHeader(std::ofstream &outfile) const
{
	outfile << "---------------------------------" << std::endl;
	outfile << "First-Order Differential Equation" << std::endl;
	outfile << "---------------------------------" << std::endl;
	outfile << firstVirt() << std::endl << std::endl;
	outfile << "Initial Condition" << std::endl;
	outfile << "-----------------" << std::endl;
	outfile << getInitCond() << std::endl << std::endl; 
}
