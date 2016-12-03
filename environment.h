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

//this is a hashmap
#include <iostream>
#include <unordered_map>




#ifndef EXTERN
	#define EXTERN extern
#endif

class Environment {
public:
	Environment* parent = NULL;

	//For now values only of type int

	typedef int32_t string_handle;
	typedef std::unordered_map<string_handle , int> MapType;
	MapType scope;


    Environment (Environment * parentEnv) {
		this->parent = parentEnv;
	}

	//int will be our only type for now
	int lookup(string_handle varHandle){
	//Try to find var in this environment's scope, if its not there, then try the parent scope
		if(this->scope.count(varHandle) < 1) {
			if(this->parent != NULL) {
				return this->parent->lookup(varHandle);
			}
			else {
				//didn't find the thing
				return INT_MAX; //Hack shouldn't do this probly
			}
		}
		else {
			// It's in this scope, so return
			return this->scope.find(varHandle)->second;
		}

	}

	void addElement(string_handle new_name, int new_value) {
		bool isThere = this->scope.count(new_name);
		if (isThere) {
			this->scope.erase(new_name);
		}
		this->scope.emplace(new_name, new_value);
	}

	void print(){
		//print out the entire scope
		MapType::const_iterator iter = this->scope.begin();
		while(iter != this->scope.end() ){
			std::cout << "name (handle) is: " << iter->first << std::endl;
			std::cout << "value (int only for now) is:" << iter->second << std::endl;
			iter++;
		}
	}
	
	void printAll() {
		if (this == NULL) {
			std::cout << "this is null WTF!! WTF!!!" << std::endl;
		}
		this -> print();
		if (this -> parent == NULL) {
			std::cout << "parent is null" << std::endl;
			return;
		}
		this -> print();
		parent -> printAll();
	}

private:

  //=BUG= nothing lives here yet

};

#undef EXTERN


#endif
