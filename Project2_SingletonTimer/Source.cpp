#include "Header.h"
#include "Classes.h"
#include <sstream>
using namespace std;

boost::scoped_ptr<BoostSingleton> BoostSingleton::_instance;
boost::mutex BoostSingleton::_mtx;
GoF_Fixed_Singleton* GoF_Fixed_Singleton::_instance = nullptr;
unique_ptr<CPP_0x_Singleton> CPP_0x_Singleton::_instance;
once_flag CPP_0x_Singleton::_once;

int main()
{
	double boost_time;
	double gof_time;
	double cpp0x_time;
	double cpp11_time;

	cout << "How many times would you like to loop? ";
	unsigned numCall = 0;
	cin >> numCall;
	cout << "--------------------------------------" << endl;
	//Boost
	{
		boost::progress_timer t;
		
		vector<boost::thread> threads;
		for (size_t i = 0; i < numCall; ++i) {
			threads.push_back(
				boost::thread(
					[](int id) { BoostSingleton::instance(); },
					i + 1
				)
			);
		}
		// wait for all threads to finish
		for (auto& t : threads)
			t.join();

		boost_time = t.elapsed();
		cout << "Time for Boost Singleton to complete " << numCall << " times: ";
	}


	//GoF Fixed
	{
		Object& o = GoF_Fixed_Singleton::instance();
		stringstream ss;

		boost::progress_timer t;
		for (size_t i = 0; i < numCall; ++i) {
			ss << "p" << i;
			auto& ss = GoF_Fixed_Singleton::instance();
		}
		
		gof_time = t.elapsed();
		cout << "Time for Gof Fixed to complete " << numCall << " times: ";
	}


	//C++ 0x
	{
		boost::progress_timer t;
		vector<thread> threads;
		for (size_t i = 0; i < numCall; ++i)
			threads.push_back(
				thread(
					[](int id) { CPP_0x_Singleton::instance(); },
					i + 1
				)
			);

		// wait for all threads to finish
		for (auto& t : threads)
			t.join();

		cpp0x_time = t.elapsed();
		cout << "Time for C++ 0x to complete " << numCall << " times: ";
	}


	//C++ 11
	{
		boost::progress_timer t;
		vector<thread> threads;
		for (size_t i = 0; i < numCall; ++i)
			threads.push_back(
				thread(
					[](int id) { CPP_11_Singleton::instance(); },
					i + 1
				)
			);
		
		// wait for all threads to finish
		for (auto& t : threads)
			t.join();

		cpp11_time = t.elapsed();
		cout << "Time for C++ 11 to complete " << numCall << " times: ";
	}


	//Percentages

}