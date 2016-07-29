#include "Header.h"
#include "Classes.h"
#include <sstream>
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

	//Boost
	{
		boost::progress_timer t;
		
		for (size_t i = 0; i < numCall; ++i) {
			BoostSingleton::instance();
		}

		cout << "Time for Boost Singleton to complete " << numCall << " times: ";
		boost_time = t.elapsed();
	}


	//GoF Fixed
	{
		Object& o = GoF_Fixed_Singleton::instance();
		stringstream ss;

		boost::progress_timer t;
		for (size_t i = 0; i < numCall; ++i) {
			Object& o = GoF_Fixed_Singleton::instance();
		}
		

		cout << "Time for Gof Fixed to complete " << numCall << " times: ";
		gof_time = t.elapsed();
	}


	//C++ 0x
	{
		boost::progress_timer t;
		for (size_t i = 0; i < numCall; ++i) {
			CPP_0x_Singleton::instance();
		}

		cout << "Time for C++ 0x to complete " << numCall << " times: ";
		cpp0x_time = t.elapsed();
	}


	//C++ 11
	{
		boost::progress_timer t;
		for (size_t i = 0; i < numCall; ++i)
			CPP_11_Singleton::instance();

		cout << "Time for C++ 11 to complete " << numCall << " times: ";
		cpp11_time = t.elapsed();
	}


	//Percentages
	double worstTime = std::max({ boost_time, cpp0x_time, cpp11_time, gof_time });
	cout << "Worst time : " << worstTime << " s\n" << endl;


	cout << "Boost Singleton is " << 100-(boost_time / worstTime)*100 << "% faster than worst time." << endl;
	cout << "GoF Fixed is " << 100 - (gof_time / worstTime) * 100 << "% faster than worst time." << endl;
	cout << "C++ 0x Singleton is " << 100 - (cpp0x_time / worstTime) * 100 << "% faster than worst time." << endl;
	cout << "C++ 11 Singleton is " << 100 - (cpp11_time / worstTime) * 100 << "% faster than worst time." << endl;
}