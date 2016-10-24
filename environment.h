// environment.h -- interface specification for the semantic environment

// Author: Douglas W. Jones
// Date 10/13/2016 -- framework established
//
// Note, the user must include something before including this file

// Environments are collections of identifier, attribute bindings.
// Bindings may be added to environments.
// The environment permits identifiers to be looked up to find their binding

#ifndef EXTERN
	#define EXTERN extern
#endif

class Environment {
public:
	// =BUG= nothing lives here yet
};

#undef EXTERN
