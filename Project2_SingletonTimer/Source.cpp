#include "Header.h"
#include "Classes.h"
using namespace std;

boost::scoped_ptr<BoostSingleton> BoostSingleton::_instance;
boost::mutex BoostSingleton::_mtx;
GoF_Fixed_Singleton* GoF_Fixed_Singleton::_instance = nullptr;

int main()
{
	cout << "How many times would you like to loop? ";
	unsigned numCall = 0;
	cin >> numCall;

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

		cout << "Time for Boost Singleton to complete " << numCall << " times: ";
	}


	//GoF Fixed
	{
		Object& o = GoF_Fixed_Singleton::instance();

		boost::progress_timer t;
		for (size_t i = 0; i < numCall; ++i) {
			auto& p = GoF_Fixed_Singleton::instance();
		}

		cout << "Time for Gof Fixed to complete " << numCall << " times: ";
	}

}