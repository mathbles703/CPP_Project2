#include "Header.h"
using namespace std;

class BoostSingleton :public Object {
	static boost::scoped_ptr<BoostSingleton> _instance;
	static boost::mutex					_mtx;
public:
	static Object& instance() {
		if (!_instance) {
			boost::lock_guard<boost::mutex> lck(_mtx);
			if (!_instance) {
				_instance.reset(new BoostSingleton);
			}
		}
		return *_instance;
	}
};