#if !defined(OBJECT_HPP)
#define OBJECT_HPP

#include <iostream>


class Object {
	Object(Object const&) = delete;
	Object& operator=(Object const&) = delete;
protected:
	Object() {  }
	virtual ~Object() { }
};




#endif // OBJECT_HPP