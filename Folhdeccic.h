#ifndef FOLHDECCIC_H
#define FOLHDECCIC_H
#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include "Lhdeccic.h"

//DC current source - derived from component class
class Folhdeccic : public Lhdeccic
{
	private:
	public:
		Folhdeccic();	//constructor
		Folhdeccic(double,double,double);
		
		virtual std::string firstVirt() const;	//virtual functions
		virtual void virtHeader(std::ofstream &) const;
		virtual std::string getInitCond() const;
		virtual void fillSignal();
		
		virtual void setb(double);	//virtual mutators
		virtual void setk(double);
		virtual void sett(double);
};
#endif
