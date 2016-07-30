#include "Header.h"
#include "Classes.h"
using namespace std;

boost::scoped_ptr<BoostSingleton> BoostSingleton::_instance;
boost::mutex BoostSingleton::_mtx;
GoF_Fixed_Singleton* GoF_Fixed_Singleton::_instance = nullptr;
unique_ptr<CPP_0x_Singleton> CPP_0x_Singleton::_instance;
once_flag CPP_0x_Singleton::_once;

int main(int argc, char *argv[])
{
	double boost_time;
	double gof_time;
	double cpp0x_time;
	double cpp11_time;

	unsigned numCall = 0;
	numCall = atoi(argv[1]);
	boost::timer t;

	//Boost Singleton Test
	{
		t.restart();
		for (size_t i = 0; i < numCall; ++i) 
			BoostSingleton::instance();
		
		boost_time = t.elapsed();
		cout << setw(40) << left << "Time for Boost Singleton to complete: " << setiosflags(ios::fixed) << setprecision(6) << setw(10) << right << boost_time << " sec." << endl;
	}

	//GoF Fixed Singleton Test
	{
		Object& o = GoF_Fixed_Singleton::instance();
		stringstream ss;

		t.restart();
		for (size_t i = 0; i < numCall; ++i) 
			Object& o = GoF_Fixed_Singleton::instance();

		gof_time = t.elapsed();
		cout << setw(40) << left << "Time for Gof Fixed to complete: " << setiosflags(ios::fixed) << setprecision(6) << setw(10) << right << gof_time << " sec." << endl;
	}


	//C++ 0x (call once) Singleton Test
	{
		t.restart();
		for (size_t i = 0; i < numCall; ++i) 
			CPP_0x_Singleton::instance();

		cpp0x_time = t.elapsed();
		cout << setw(40) << left << "Time for C++ 0x to complete: " << setiosflags(ios::fixed) << setprecision(6) << setw(10) << right << cpp0x_time << " sec." << endl;
	}


	//C++ 11 (static) Singleton Test
	{
		t.restart();
		for (size_t i = 0; i < numCall; ++i)
			CPP_11_Singleton::instance();

		cpp11_time = t.elapsed();
		cout << setw(40) << left << "Time for C++ 11 to complete: " << setiosflags(ios::fixed) << setprecision(6) << setw(10) << right << cpp11_time << " sec." << endl;
	}


	//Holds a reference to the timing of the slowest singleton test
	double worstTime = std::max({ boost_time, cpp0x_time, cpp11_time, gof_time });

	///spacing for nice output
	cout << "\nCompared to the worst result("<< worstTime << " s)..." << "\n" << endl;
	
	//Vector will hold a pair
	//Each pair will hold a string representing the specific singleton test variation title
	//and will hold a double representing the percentage of that test compared to the slowest test
	std::vector <pair<string, double>> allSingletonTiming;

	//push the pairs into the vector
	allSingletonTiming.push_back(std::make_pair("Boost Singleton is faster by ", 100 - (boost_time / worstTime) * 100));
	allSingletonTiming.push_back(std::make_pair("GoF Fixed is faster by ", 100 - (gof_time / worstTime) * 100));
	allSingletonTiming.push_back(std::make_pair("C++ 0x Singleton is faster by ", 100 - (cpp0x_time / worstTime) * 100));
	allSingletonTiming.push_back(std::make_pair("C++ 11 Singleton is faster by ", 100 - (cpp11_time / worstTime) * 100));

	//sort the vector based on the elapsed time.
	//Display fastest to slowest
	std::sort(allSingletonTiming.begin(), allSingletonTiming.end(),
		boost::bind(&std::pair<string, double>::second, _1) >
		boost::bind(&std::pair<string, double>::second, _2));

	//iterate through pair and format the output
	for (vector<pair<string,double>>::const_iterator it = allSingletonTiming.begin(); it < allSingletonTiming.end(); it++)
		cout << setw(40) << left << it->first << setiosflags(ios::fixed) << setprecision(3) << setw(9) << right << it->second << "%" << endl;
	
}