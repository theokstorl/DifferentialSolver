#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <iomanip>
#include "Signal.h"

//default constructor
Signal::Signal()
{
	setSamples(101);
	setFrequency(100);
	setInitialTime(0);
	setLabel("x");
	setMath(textNum(0));
}

//constructor to assign initial values
Signal::Signal(unsigned int s, double f, double t)
{
	setSamples(s);
	setFrequency(f);
	setInitialTime(t);
	setLabel("x");
	setMath(textNum(0));
}

//member function to initialize vectors to zero
void Signal::initializer()
{
	for(unsigned int d=0;d<returnSamples();d++)
	{
		time.push_back(0.0);
		signal.push_back(0.0);
	}
}

//member function to set number of samples
void Signal::setSamples(unsigned int n)
{
	samples = n;
	time.resize(n);
	signal.resize(n);
	fillTimeVector();
}

//member function to set frequency
void Signal::setFrequency(double Hz)
{
	frequency = Hz;
	fillTimeVector();
}

//member function to set initial time
void Signal::setInitialTime(double t)
{
	initialTime = t;
	fillTimeVector();
}

//member function to return number of samples
unsigned int Signal::returnSamples() const
{
	return samples;
}

//member function to return frequency
double Signal::returnFrequency() const
{
	return frequency;
}

//member function to return initial time
double Signal::returnInitialTime() const
{
	return initialTime;
}

//member function to set the Label
void Signal::setLabel(std::string newLabel)
{
	label = newLabel;
	filename = "diff_eqn_soln_" + label;
}

//member accesor function for label
std::string Signal::returnLabel() const
{
	return label;
}

//member accesor function to return filename
std::string Signal::returnFile() const
{
	return filename;
}

//member accessor function for math expression
std::string Signal::returnMath() const
{
	return mathExpression;
}

//member mutator function for math expression
void Signal::setMath(std::string math)
{
	mathExpression = math;
}

//member accessor function for Signal vector
std::vector<double> Signal::returnSignal() const
{
	return signal;
}

//member accessor function for Time vector
std::vector<double> Signal::returnTime() const
{
	return time;
}

//overloaded accessor function for Signal vector
double Signal::returnSignal(unsigned int y_pos) const
{
	return signal[y_pos];
}

//overloaded accessor function for Time vector
double Signal::returnTime(unsigned int x_pos) const
{
	return signal[x_pos];
}

//member function to fill time vector with values
void Signal::fillTimeVector()
{
	time.clear();
	for(unsigned int a=0;a<returnSamples();a++)
	{
		time.push_back(returnInitialTime() + (a / returnFrequency()));
	}
}

//member function to create a constant signal
void Signal::createKSignal(double holderK)
{
	signal.clear();
	for (unsigned int f=0;f<returnSamples();f++)
	{
		signal.push_back(holderK);
	}
	
	//setting math expression to constant
	setMath(textNum(holderK));
}

//member function copied and pasted from CourseWeb 
std::string Signal::textNum(double x) const	// Convert num->string for title
{
	if (x >= 100)
		return std::to_string(int(x));		// Large nums trunc. as int
	else
	{
		std::string x_exp = std::to_string(x);	// Small nums get 3 digits
		return x_exp.substr(0, 4 + (x<0));
	}
}	

//member function to overload equal operator
const Signal Signal::operator=(const Signal &right)
{
	if (this != &right)
	{
		samples = right.samples;
		frequency = right.frequency;
		initialTime = right.initialTime;
		mathExpression = right.mathExpression;
		signal = right.signal;
		time = right.time;
	}
	return *this;
}

//overloaded +
Signal Signal::operator+(const Signal &right)
{
	Signal temp(samples, frequency, initialTime);
	temp.signal.clear();
	temp.time.clear();
	if ((this->samples == right.samples) && (this->frequency == right.frequency) && (this->initialTime == right.initialTime))
	{
		for(unsigned int v=0;v<samples;v++)
		{
			temp.signal.push_back(this->returnSignal()[v] + right.signal[v]);
			temp.time.push_back(this->time[v]);
		}
		if (right.mathExpression.front() == '-')
		{
			std::string temps = right.mathExpression;
			temps.front() = ' ';
			temp.mathExpression = this->mathExpression + " -" + temps;
		}
		else
			temp.mathExpression = this->mathExpression + " + " + right.mathExpression;
		
		return temp;
	}
	else
	{
		std::cout << "Error! Attempt to add incompatible signals." << std::endl;
		exit(-1);
	}
}

//overloaded *
Signal Signal::operator*(const Signal &right)
{
	if ((this->samples == right.samples) && (this->frequency == right.frequency) && (this->initialTime == right.initialTime))
	{
		Signal temp(samples, frequency, initialTime);
		temp.signal.clear();
		temp.time.clear();
		for(unsigned int v=0;v<samples;v++)
		{
			temp.signal.push_back(this->returnSignal()[v] * right.signal[v]);
			temp.time.push_back(this->time[v]);
		}
		
		temp.mathExpression = "(" + this->mathExpression + ")" + "(" + right.mathExpression + ")";
		
		return temp;
	}
	else
	{
		std::cout << "Error! Attempt to mulitply incompatible signals." << std::endl;
		exit(-1);
	}
}

//member function to fill sinusoid with sin values
void Signal::fillSinusoid(double amplitude, double frequency1, double phase)
{
	for (unsigned int h=0;h<samples;h++)
	{
		signal[h] = amplitude * cos((2 * 3.14159 * frequency1 * (time[h]-time[0])) + phase);	
	}
	
	if (phase >= 0)
		setMath(textNum(amplitude) + " cos( " + textNum(6.28 * frequency1) + " (t + " + textNum(-1*time[0]) + ") " + " )");
	else
		setMath(textNum(amplitude) + " cos( " + textNum(6.28 * frequency1) + " (t + " + textNum(-1*time[0]) + ") - " + textNum(fabs(phase)) + " )");
}

//member function to fill sinusoid with exponential values
void Signal::fillSinExp(double tau, double A0)
{
	for (unsigned int h=0;h<samples;h++)
	{
		signal[h] = A0 * exp(-(time[h] - time[0]) / tau);	
	}
	if(time[0] == 0 && tau == 1)
		setMath(textNum(A0) + " exp( -t  )");
	else if (time[0] == 0 && tau != 1)
		setMath(textNum(A0) + " exp( -t / " + textNum(tau) + " )");
	else if (time[0] >= 0)
		setMath(textNum(A0) + " exp( -(t - " + textNum(time[0]) + ") / " + textNum(tau) + " )");
	else if(time[0] < 0 && tau == 1)
		setMath(textNum(A0) + " exp( -(t + " + textNum(-1*time[0]) + ") " + ")");
	else if(time[0] < 0)
		setMath(textNum(A0) + " exp( -(t + " + textNum(-1*time[0]) + ") / " + textNum(tau) + " )");
}

//member function that fills sinusoid with linear values
void Signal::fillSinLinear(double m,double b)
{
	for (unsigned int u=0;u<samples;u++)
	{
		signal[u] = m*(time[u] - time[0]) + b;
	}
	
	if (time[0] == 0 && b < 0)
		setMath(textNum(m) + " t - " + textNum(-1*b)); 
	else if (time[0] >= 0 && b < 0)
		setMath(textNum(m) + " (t - " + textNum(time[0]) + ") - " + textNum(-1*b)); 
	else if(time[0]<0 && b < 0)
		setMath(textNum(m) + " (t + " + textNum(-1*time[0]) + ") - " + textNum(-1*b));
	else 
		setMath(textNum(m) + " (t - " + textNum(time[0]) + ") + " + textNum(b)); 
}

//member function to round sin wave
void Signal::roundSin()
{
	for (unsigned int o=0;o<samples;o++)
	{
		signal[o] = round(signal[o]);
	}
}

//member function to plot sinusoid and make picture
void Signal::createPicture() const
{
	// MathGL objects from the mglData class for plotting
	mglData time1(samples), signal1(samples);
	
	time1.Set(time);
	signal1.Set(signal);

	// Create mglGraph object
	mglGraph graph;
	graph.Title((label+"(t)").c_str());
	
	
	double timestart = time[0];
	double timeend = time[samples - 1];
	//finding absolute max value
	double max = abs(signal[0]);
	for(unsigned int f=1;f<samples;f++)
	{
		if (abs(signal[f]) > max)
		{
			max = abs(signal[f]);
		}
	}
	
	// Set axis ranges as (x start, x end, y start, y end)
	graph.SetRanges(timestart, timeend, -max, max);
	// Set the origin of the graph
	graph.SetOrigin(0, 0);
	// Create axis
	graph.Axis();
	
	// Plot the function in x_mgl versus t_mgl.
	graph.Plot(time1, signal1);
	// Write the plot to eps & png files
	graph.WriteEPS((filename+".eps").c_str());
	graph.WritePNG((filename+".png").c_str());
}
	
//member function to write data to output file
void Signal::writer() const
{
	std::ofstream outfile;
	outfile.open(returnFile() + ".txt");
	
	outfile << "Time-Domain Signal Samples" << std::endl;
	outfile << "N = " << returnSamples() << std::endl;
	outfile << "fs = " << returnFrequency() << std::endl;
	outfile << "t0 = " << returnInitialTime() << std::endl;
	outfile << "Signal label: " << returnLabel() << std::endl;
	outfile << "Mathematical expression" << std::endl;
	outfile << returnLabel() << "(t) = " << returnMath() << std::endl;
	outfile << "Time and signal samples in .csv format" << std::endl;
	outfile << "t, " << returnLabel() << "(t)" << std::endl;
	outfile << "-------" << std::endl;
	
	//writing data to file
	for (unsigned int c=0;c<returnSamples();c++)
	{
		outfile << time[c] << ", " << signal[c] << std::endl;		 
	}
	
	//closing outfile
	outfile.close();
}
