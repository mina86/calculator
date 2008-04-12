/** \file
 * Expression declarations.
 * $Id: expression.hpp,v 1.1 2008/04/12 02:13:31 mina86 Exp $
 */
#ifndef H_EXPRESSION_HPP
#define H_EXPRESSION_HPP

#include "config.hpp"

#include <string>

#include "environment.hpp"


namespace calc {


struct Expression {
	virtual real execute(Environment &env) const = 0;
	virtual ~Expression();

	Expression() { }

private:
	/** No copy constructor. */
	Expression(const Expression &expr) { (void)expr; }
};


struct Variable {
	std::string *name;
	char scope;

	inline operator Expression*() const;
};


struct NumberExpression : public Expression {
	NumberExpression(real v) : val(v) { }
	virtual real execute(Environment &env) const;
private:
	real val;
};


struct NegExpression : public Expression {
	NegExpression(Expression *e) : expr(e) { }
	~NegExpression();
	virtual real execute(Environment &env) const;
private:
	Expression *expr;
};



struct NameExpression : public Expression {
	~NameExpression();
protected:
	std::string *name;
	NameExpression(std::string *n) : name(n) { }
};


struct GetExpression : public NameExpression {
	static inline GetExpression *create(const Variable &v);
protected:
	GetExpression(std::string *n) : NameExpression(n) { }
};


struct GetLocalExpression : public GetExpression {
	GetLocalExpression(std::string *n) : GetExpression(n) { }
	virtual real execute(Environment &env) const;
};

struct GetGlobalExpression : public GetExpression {
	GetGlobalExpression(std::string *n) : GetExpression(n) { }
	virtual real execute(Environment &env) const;

};

struct GetConstExpression : public GetExpression {
	GetConstExpression(std::string *n) : GetExpression(n) { }
	virtual real execute(Environment &env) const;
};


inline GetExpression *GetExpression::create(const Variable &var) {
	if (var.scope == '$') {
		return new GetGlobalExpression(var.name);
	} else if (var.scope == '#') {
		return new GetConstExpression(var.name);
	} else {
		return new GetLocalExpression(var.name);
	}
}


inline Variable::operator Expression*() const {
	return GetExpression::create(*this);
}



struct SetExpression : public NameExpression {
	static inline SetExpression *create(const Variable &var, Expression *e);
	~SetExpression();
protected:
	Expression *expr;
	SetExpression(std::string *n, Expression *e)
		: NameExpression(n), expr(e) { }
};


struct SetLocalExpression : public SetExpression {
	SetLocalExpression(std::string *n, Expression *e) : SetExpression(n, e) {}
	virtual real execute(Environment &env) const;
};

struct SetGlobalExpression : public SetExpression {
	SetGlobalExpression(std::string *n, Expression *e) : SetExpression(n, e){}
	virtual real execute(Environment &env) const;
};


inline SetExpression *SetExpression::create(const Variable &var,
                                            Expression *e) {
	if (var.scope == '$') {
		return new SetGlobalExpression(var.name, e);
	} else {
		return new SetLocalExpression(var.name, e);
	}
}




struct AtLeast2ArgExpression : public Expression {
	~AtLeast2ArgExpression();
protected:
	Expression *expr1;
	Expression *expr2;
	AtLeast2ArgExpression(Expression *e1, Expression *e2)
		: expr1(e1), expr2(e2) { }
};


struct AddExpression : public AtLeast2ArgExpression {
	AddExpression(Expression *e1, Expression *e2)
		: AtLeast2ArgExpression(e1, e2) { }
	virtual real execute(Environment &env) const;
};

struct SubExpression : public AtLeast2ArgExpression {
	SubExpression(Expression *e1, Expression *e2)
		: AtLeast2ArgExpression(e1, e2) { }
	virtual real execute(Environment &env) const;
};

struct MulExpression : public AtLeast2ArgExpression {
	MulExpression(Expression *e1, Expression *e2)
		: AtLeast2ArgExpression(e1, e2) { }
	virtual real execute(Environment &env) const;
};

struct DivExpression : public AtLeast2ArgExpression {
	DivExpression(Expression *e1, Expression *e2)
		: AtLeast2ArgExpression(e1, e2) { }
	virtual real execute(Environment &env) const;
};

struct PowExpression : public AtLeast2ArgExpression {
	PowExpression(Expression *e1, Expression *e2)
		: AtLeast2ArgExpression(e1, e2) { }
	virtual real execute(Environment &env) const;
};




struct FunctionExpression : public NameExpression {
	typedef std::vector<Expression*> Arguments;

	FunctionExpression(std::string *n, Arguments *a)
		: NameExpression(n), args(a) { }

	~FunctionExpression();

	virtual real execute(Environment &env) const;

private:
	Arguments *args;
};


}

#endif
