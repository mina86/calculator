/*
 * Copyright 2008-2009 by Michal Nazarewicz (mina86/AT/mina86.com)
 *                     by Jakub Ksiezniak
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses/>.
 */

/** \file
 * Function class virtual methods definitions.
 */
#include "function.hpp"
#include "expression.hpp"

namespace calc {


Function::~Function() { }

real Function::execute(Environment &env,
                       const std::vector<Expression*> &args) const {
	std::vector<Expression*>::const_iterator it(args.begin()),end(args.end());
	Arguments a(args.size());
	Arguments::iterator out = a.begin();
	for (; it != end; ++it, ++out) {
		*out = (*it)->execute(env);
	}
	return execute(env, a);
}


}
