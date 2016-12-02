// environment.h -- interface specification for the semantic environment

// Author: Douglas W. Jones
// Date 10/13/2016 -- framework established
//
// Note, the user must include something before including this file

// Environments are collections of identifier, attribute bindings.
// Bindings may be added to environments.
// The environment permits identifiers to be looked up to find their binding
#ifndef environment_h
#define environment_h


#include <climits>




#ifndef EXTERN
	#define EXTERN extern
#endif

class Environment {
public:
	// =BUG= nothing lives here yet
	Environment* parent = NULL;
	//std::shared_ptr<Environment> parent = NULL;
	string_handle name;
	int value;

	//int will be our only type for now
	int lookup(string_handle varHandle){
		if(varHandle == this->name) return value;
		if(this->parent == NULL) return INT_MAX;
		return this->parent->lookup(varHandle);
	}

	Environment * add(string_handle new_name, int new_value){
		//std::shared_ptr<Environment> newEnv = new Environment();
		Environment* newEnv = new Environment();
		newEnv->name = new_name;
		newEnv->value = new_value;
		newEnv->parent = this;
		return newEnv;
	}

	void print(){
		std::cout << "name (handle) is: " << name << std::endl;
		std::cout << "value (int only for now) is:" << value << std::endl;
	}
	
	void printAll() {
		if (this -> parent == NULL) {
			std::cout << "parent is null" << std::endl;
		}

		if (this == NULL) {
			std::cout << "this is null" << std::endl;
		}

		this -> print();
		while (this -> parent != NULL) {
			this -> print();
			parent -> printAll();
		}
	}

private:

  //=BUG= nothing lives here yet

};

#undef EXTERN


#endif
