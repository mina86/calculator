/** \file
 * User Function class definition.
 * $Id: user-function.cpp,v 1.4 2008/04/21 08:29:30 mina86 Exp $
 */

#include "config.hpp"

#include <iterator>

#include "user-function.hpp"
#include "expression.hpp"
#include "environment.hpp"


namespace calc {

UserFunction::~UserFunction() {
	delete expr;
}

bool UserFunction::argumentsCountOK(unsigned count) const {
	return count == names.size();
}

void UserFunction::free() {
	delete this;
}


struct pair_iterator {
	typedef UserFunction::Names::const_iterator        names_iterator;
	typedef Function::Arguments::const_iterator        args_iterator;

	typedef std::input_iterator_tag                    iterator_category;
	typedef const std::pair<std::string, real>         value_type;
	typedef Environment::Variables::difference_type    difference_type;
	typedef value_type*                                pointer;
	typedef value_type&                                reference;

	pair_iterator(const names_iterator &n, const args_iterator &a)
		: name_iter(n), arg_iter(a) { }

	pair_iterator &operator++() {
		++name_iter; ++arg_iter;
		return *this;
	}

	pair_iterator operator++(int) {
		pair_iterator tmp(*this);
		++*this;
		return tmp;
	}

	value_type operator*() const {
		return value_type(*name_iter, *arg_iter);
	}
	/* operator-> is missing but apperently it works anyway. */

	bool operator==(const pair_iterator &pi) const {
		return name_iter == pi.name_iter;
	}

	bool operator!=(const pair_iterator &pi) const {
		return name_iter != pi.name_iter;
	}

private:
	names_iterator name_iter;
	args_iterator  arg_iter;
};


real UserFunction::execute(Environment &env, const Arguments &args) const {
	throwIfArgumentsCountNotOK(args.size());

	Environment::Variables *vars =
		new Environment::Variables(pair_iterator(names.begin(), args.begin()),
		                           pair_iterator(names.end(), args.end()));
	return env.executeInNewScope(expr, vars);
}


}
