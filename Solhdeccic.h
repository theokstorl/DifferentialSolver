#ifndef SOLHDECCIC_H
#define SOLHDECCIC_H
#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include "Lhdeccic.h"

//Second order diff equation derived class
class Solhdeccic : public Lhdeccic
{
	private:
		double a;
		double K1;
	public:
		Solhdeccic();
		Solhdeccic(double,double,double,double,double);
	
		void setA(double);		//mutators
		void setK1(double);
		
		double getA() const;	//accessors
		double getK1() const;
		
		virtual std::string firstVirt() const;		//virtual functions
		virtual std::string getInitCond() const;
		virtual void virtHeader(std::ofstream &) const;
		virtual void fillSignal();
};
#endif
