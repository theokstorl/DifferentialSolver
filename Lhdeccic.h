#ifndef LHDECCIC_H
#define LHDECCIC_H
#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>

//class defintion
class Lhdeccic
{
	private:
		double b, t0, K0;
		std::string diffSolution;
		Signal solution;
	public:
		Lhdeccic();				//constructors
		Lhdeccic(double,double,double);
	
		double getB() const;	//accessors
		double gett0() const;
		double getK0() const;
		std::string getDiffSol() const;
		
		virtual void setB(double);		//mutators
		virtual void sett0(double);
		virtual void setK0(double);
		void setDiffSol(std::string);
		
		std::string textNum(double) const; // function from CourseWeb
		
		virtual std::string firstVirt() const = 0;	//virtual functions
		virtual void virtHeader(std::ofstream &) const = 0;
		virtual std::string getInitCond() const = 0;
		virtual void fillSignal()=0;
		
		Signal * modSigSol();	//function that derived class uses to access modified signal
		std::string getTextRep() const; //returns text representation
		
		virtual void baseWriter(std::ofstream &) const;
};
#endif
