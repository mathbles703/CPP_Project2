#include "Header.h"
using namespace std;


class CPP_0x_Singleton :public Object {
	static unique_ptr<CPP_0x_Singleton>	_instance;
	static once_flag				_once;
public:
	static Object& instance() {
		call_once(_once, []() {_instance.reset(new CPP_0x_Singleton); });
		return *_instance;
	}
};
