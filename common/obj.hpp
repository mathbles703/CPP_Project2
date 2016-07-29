#if !defined(OBJECT_HPP)
#define OBJECT_HPP

#include <iostream>


class Object {
	Object(Object const&) = delete;
	Object& operator=(Object const&) = delete;
protected:
	Object() { std::cout << "Object::ctor" << std::endl; }
	virtual ~Object() { std::cout << "Object::dtor" << std::endl; }
public:
	void msg(int id = 0) {
		std::cout << "Object::msg";
		if (id > 0)
			std::cout << ": " << id;
		std::cout << std::endl;
	}
};


class PODObject {
	PODObject(PODObject const&) = delete;
	PODObject& operator=(PODObject const&) = delete;
public:
	PODObject() { std::cout << "PODObject::ctor" << std::endl; }
	virtual ~PODObject() { std::cout << "PODObject::dtor" << std::endl; }
	void msg(int id = 0) {
		std::cout << "PODObject::msg";
		if (id > 0)
			std::cout << ": " << id;
		std::cout << std::endl;
	}
};



#endif // OBJECT_HPP