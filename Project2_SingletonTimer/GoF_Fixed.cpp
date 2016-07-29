#include "Header.h"

class GoF_Fixed_Singleton :public Object {
	static GoF_Fixed_Singleton* _instance;
	static void cleanup() {
		delete _instance;
	}
public:
	static Object& instance() {		// Meyer uses this to block delete.
		if (_instance == nullptr) {
			_instance = new GoF_Fixed_Singleton;
			atexit(cleanup);
		}
		return *_instance;
	}
};
