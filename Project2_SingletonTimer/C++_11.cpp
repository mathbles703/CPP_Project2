#include "Header.h"
using namespace std;


class CPP_11_Singleton :public Object {
public:
	static Object& instance() {
		static unique_ptr<CPP_11_Singleton> _instance(new CPP_11_Singleton);
		return *_instance;
	}
};