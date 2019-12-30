#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <iomanip>
#include "Solhdeccic.h"

//Default constructor for Solhdeccic
Solhdeccic::Solhdeccic() : Lhdeccic::Lhdeccic()
{
	setA(3);
	setB(2);
	sett0(0);
	setK0(0);
	setK1(1);
	setDiffSol("y");
	
	fillSignal();
}

//alternate constructor for Solhdeccic
Solhdeccic::Solhdeccic(double xa, double xb, double xt0, double xK0, double xK1) : Lhdeccic::Lhdeccic(xb, xt0, xK0)
{
	setA(xa);
	setK1(xK1);
	setDiffSol("y");
	
	fillSignal();
}

//mutator function for a
void Solhdeccic::setA(double tempa)
{
	a = tempa;
}

//mutator function for K1
void Solhdeccic::setK1(double tempK1)
{
	K1 = tempK1;
}

//accessor fucntion for a
double Solhdeccic::getA() const
{
	return a;
}

//accessor function for K1
double Solhdeccic::getK1() const
{
	return K1;
}

//returns text representation
std::string Solhdeccic::firstVirt() const
{
	if (getB() >= 0)
		return getDiffSol() + "''(t) + " + textNum(getA()) + " " + getDiffSol() + "'(t) + " + textNum(getB()) + " " + getDiffSol() + "(t) = 0"; 
	else
		return getDiffSol() + "''(t) + " + textNum(getA()) + " " + getDiffSol() + "'(t) - " + textNum(-1*getB()) + " " + getDiffSol() + "(t) = 0"; 
}

//member fuction to return initial condition
std::string Solhdeccic::getInitCond() const
{
	return getDiffSol() + "(" + textNum(gett0())  + ") = " + textNum(getK0()) + ", " + getDiffSol() + "'(" + textNum(gett0())  + ") = " + textNum(getK1()); 
}

//member function to fill signal with values
void Solhdeccic::fillSignal() 
{
	//solution signal
	Signal * secSignalPtr = modSigSol();
	
	secSignalPtr->setSamples(501);
	secSignalPtr->setInitialTime(gett0());
	
	double root1 = (-getA() + sqrt(pow(getA(),2) - 4 * getB())) / 2;
	double root2 = (-getA() - sqrt(pow(getA(),2) - 4 * getB())) / 2;
	
	//calculating max root
	double maxR;
	if (root1 > root2)
		maxR = root1;
	else if (root2 > root1)
		maxR = root2;
	else if (root2 == root1)
		maxR = root1;
	
	Signal secSignal(501,100/(1/fabs(maxR)),gett0());
	
	if (pow(getA(),2) > 4*getB())
	{	
		secSignalPtr->setFrequency(100/(1/fabs(maxR)));
		
		double c1 = ((getK0()*root2) - getK1()) / (root2 - root1);
		double c2 = ((getK0()*-1*root1) + getK1()) / (root2 - root1);
		
		secSignalPtr->fillSinExp(fabs(1/root1),c1);
		
		secSignal.fillSinExp(fabs(1/root2),c2);
		
		*secSignalPtr = *secSignalPtr + secSignal;
	}
	else if (pow(getA(),2) == 4*getB())
	{	
		secSignalPtr->setFrequency(100/(1/fabs(maxR)));
		
		double c1 = getK0();
		double c2 = getK1() + (getK0()*getA())/2;
		
		secSignalPtr->fillSinLinear(c2,c1);
		
		secSignal.fillSinExp(fabs(1/root1),1);
		
		*secSignalPtr = *secSignalPtr * secSignal;
	}
	else if (pow(getA(),2) < 4*getB())
	{
		double upperOmega = getA() / 2;
		double lowerOmega = (sqrt(4*getB() - pow(getA(),2))) / 2;
		
		secSignalPtr->setFrequency(100/(1/upperOmega));
		
		double c1 = getK0();
		double c2 = (getK1() - upperOmega*getK0()) / lowerOmega;
		
		Signal thirdSig(501,100/(1/upperOmega),gett0());
		thirdSig.fillSinExp(upperOmega,1);
		Signal fourthSig(501,100/(1/upperOmega),gett0());
		fourthSig.fillSinusoid(c1,lowerOmega/(2*3.14159),0);
		Signal fifthSig(501,100/(1/upperOmega),gett0());
		fifthSig.fillSinusoid(c2,lowerOmega/(2*3.14159),-3.14159/2);
		
		*secSignalPtr = thirdSig * (fourthSig + fifthSig);
		
	}
	
	secSignalPtr->roundSin();
}

//member virtual function to write header info to outfile
void Solhdeccic::virtHeader(std::ofstream &outfile) const
{
	outfile << "----------------------------------" << std::endl;
	outfile << "Second-Order Differential Equation" << std::endl;
	outfile << "----------------------------------" << std::endl;
	outfile << firstVirt() << std::endl << std::endl;
	outfile << "Initial Condition" << std::endl;
	outfile << "-----------------" << std::endl;
	outfile << getInitCond() << std::endl << std::endl; 
}
