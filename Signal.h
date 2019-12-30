#ifndef SIGNAL_H
#define SIGNAL_H
#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <mgl2/mgl.h>

//class defintion
class Signal
{
	private:
		unsigned int samples;  //variables
		double frequency;
		double initialTime;
		
		std::string label;    //labels, files, etc
		std::string filename;
		std::string mathExpression;
		
		std::vector<double> signal;   //vectors
		std::vector<double> time;
	public:
		Signal(unsigned int, double, double);  //constructor
		Signal();
		
		void setSamples(unsigned int);   //mutators
		void setFrequency(double);
		void setInitialTime(double);
		void setLabel(std::string);
		void setMath(std::string);
		
		unsigned int returnSamples() const;   //accessors
		double returnFrequency() const;
		double returnInitialTime() const;
		std::string returnLabel() const;
		std::string returnFile() const;
		std::string returnMath() const;
		std::vector<double> returnSignal() const;
		std::vector<double> returnTime() const;
		double returnSignal(unsigned int) const;
		double returnTime(unsigned int) const;
		
		void writer() const;   //writes to output file
		void fillTimeVector(); //fills vector with values
		void initializer(); //initializes vectors to zero
		void createKSignal(double); //creates constant signal
		std::string textNum(double) const; // function from CourseWeb
		const Signal operator=(const Signal &);  //overloaded equal function
		Signal operator+(const Signal &);  //overloaded + function
		Signal operator*(const Signal &);  //overloaded * function
		void fillSinusoid(double, double, double); // function that fills sinusoid
		void fillSinExp(double, double);
		void fillSinLinear(double,double);
		void roundSin(); //function that rounds sinwave
		void createPicture() const;	//function that uses MathGL to plot
};
#endif
