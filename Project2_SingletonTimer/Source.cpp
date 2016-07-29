#include "Header.h"
#include "Classes.h"
#include <sstream>
#include <iomanip>
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

	//Boost
	{
		t.restart();
		for (size_t i = 0; i < numCall; ++i) {
			BoostSingleton::instance();
		}

		boost_time = t.elapsed();
		cout << setw(40) << left << "Time for Boost Singleton to complete: " << setiosflags(ios::fixed) << setprecision(6) << setw(8) << right << boost_time << endl;

	}

	//cout << "Time with more precision for Boost is: " << setiosflags(ios::fixed) << setprecision(6) << boost_time;
	//GoF Fixed
	{
		Object& o = GoF_Fixed_Singleton::instance();
		stringstream ss;

		t.restart();
		for (size_t i = 0; i < numCall; ++i) {
			Object& o = GoF_Fixed_Singleton::instance();
		}
		

		gof_time = t.elapsed();
		cout << setw(40) << left << "Time for Gof Fixed to complete: " << setiosflags(ios::fixed) << setprecision(6) << setw(8) << right << gof_time << endl;

	}


	//C++ 0x
	{
		t.restart();
		for (size_t i = 0; i < numCall; ++i) {
			CPP_0x_Singleton::instance();
		}

		cpp0x_time = t.elapsed();
		cout << setw(40) << left << "Time for C++ 0x to complete: " << setiosflags(ios::fixed) << setprecision(6) << setw(8) << right << cpp0x_time << endl;

	}


	//C++ 11
	{
		t.restart();
		for (size_t i = 0; i < numCall; ++i)
			CPP_11_Singleton::instance();

		cpp11_time = t.elapsed();
		cout << setw(40) << left << "Time for C++ 11 to complete: " << setiosflags(ios::fixed) << setprecision(6) << setw(8) << right << cpp11_time << endl;

	}


	//Percentages
	double worstTime = std::max({ boost_time, cpp0x_time, cpp11_time, gof_time });
	cout << "\nWorst time : " << worstTime << " s\n" << endl;


	cout << setw(40) << left << "Boost Singleton is faster by" << setw(10) << right << 100-(boost_time / worstTime)*100 << "%" << endl;
	cout << setw(40) << left << "GoF Fixed is " << setw(10) << right << 100 - (gof_time / worstTime) * 100 << "%" << endl;
	cout << setw(40) << left << "C++ 0x Singleton is " << setw(10) << right << 100 - (cpp0x_time / worstTime) * 100 << "%" << endl;
	cout << setw(40) << left << "C++ 11 Singleton is " << setw(10) << right << 100 - (cpp11_time / worstTime) * 100 << "%" << endl;
}