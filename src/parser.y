   /*  Make EMACS happy: -*- Mode: C++; tab-width: 8; c-basic-offset: 8 -*- */
%skeleton "lalr1.cc"
%require "2.1a"
%defines
%define "parser_class_name" "Parser"

%{
#include "config.hpp"

#include <string>

#include "expression.hpp"
#include "user-function.hpp"

namespace calc {
	struct Lexer;
	struct Environment;
}
%}

%union {
	/** A literal number. */
	calc::real                           num;
	/** A variable (name + scope). */
	calc::Variable                       var;
	/** An expression. */
	calc::Expression                    *expr;
	/** Function parameters */
	calc::UserFunction::Names           *params;
};

%parse-param { calc::Lexer       &lexer }
%parse-param { calc::Environment &env   }
%lex-param   { calc::Lexer       &lexer }


%debug
%error-verbose
%locations
%output = "parser.cpp"

%{
#include "math.hpp"
#include "exceptions.hpp"
#include "environment.hpp"
#include "lexer.hpp"

static const std::string string_e("e");

int yylex(yy::Parser::semantic_type *yylval,
          yy::Parser::location_type *yylloc,
          calc::Lexer &lexer);
%}


%token	<var.name>	ID
%token		DEFINE		"define"
%token	<num>	NUMBER
%token		ADD_EQ		"+="
%token		SUB_EQ		"-="
%token		MUL_EQ		"*="
%token		DIV_EQ		"/="
%token		POW_EQ		"^="
%token		GE		">="
%token		LE		"<="
%token		NE		"!="
%token		EQ		"=="
%token		OR		"||"
%token		AND		"&&"
%token		XOR		"^^"


%type	<expr>	assignment_expr additive_expr multiplicative_expr rel_expr
%type	<expr>	pow_expr prefix_expr simple_expr expression cond_expr
%type	<expr>	logic_or_expr logic_and_expr logic_xor_expr cmp_expr
%type	<var>	var
%type	<params> formal_arguments non_empty_formal_arguments

%destructor	{ delete $$; } ID expression rel_expr cond_expr cmp_expr
%destructor	{ delete $$; } assignment_expr additive_expr simple_expr
%destructor	{ delete $$; } multiplicative_expr pow_expr prefix_expr
%destructor	{ delete $$; } logic_or_expr logic_and_expr logic_xor_expr
%destructor	{ delete $$.name; } var
%destructor	{ delete $$; } formal_arguments non_empty_formal_arguments

%%
start	: start instruction
	| /* nothing */
	;

instruction
	: DEFINE define_instruction ';'
	| DEFINE define_instruction '\n'
	| expression ';'		{ env.execute($1, false); }
	| expression '\n'		{ env.execute($1, true); }
	| ';'
	| '\n'
	| error ';'
	| error '\n'
	;

define_instruction
	: ID '(' formal_arguments ')' '=' expression	{
		env.addUserFunction(*$1, new calc::UserFunction($6, *$3));
		$6 = 0;
	}
	;

formal_arguments
	: /* empty */ { $$ = new calc::UserFunction::Names() }
	| non_empty_formal_arguments { $$ = $1; $1 = 0; }
	;

non_empty_formal_arguments
	: ID	{
		$$ = new calc::UserFunction::Names();
		$$->push_back(*$1);
	}
	| non_empty_formal_arguments ',' ID {
		$$ = $1;
		$$->push_back(*$3);
		$1 = 0;
	}
	;

expression
	: assignment_expr		{ $$ = $1; $1 = 0; }
	| expression ',' assignment_expr {
		$$ = $1->commaExpression();
		static_cast<calc::CommaExpression*>($$)->push($3);
		$1 = $3 = 0;
	}
	;

assignment_expr
	: var '='  assignment_expr	{
		$$ = $1.setExpression($3);
		$3 = 0;
	}
	| var "+=" assignment_expr	{
		calc::Expression *expr;
		expr = new calc::AddExpression($1.getExpression(), $3);
		$$ = $1.setExpression(expr);
		$3 = 0;
	}
	| var "-=" assignment_expr	{
		calc::Expression *expr;
		expr = new calc::SubExpression($1.getExpression(), $3);
		$$ = $1.setExpression(expr);
		$3 = 0;
	}
	| var "*=" assignment_expr	{
		calc::Expression *expr;
		expr = new calc::MulExpression($1.getExpression(), $3);
		$$ = $1.setExpression(expr);
		$3 = 0;
	}
	| var "/=" assignment_expr	{
		calc::Expression *expr;
		expr = new calc::DivExpression($1.getExpression(), $3);
		$$ = $1.setExpression(expr);
		$3 = 0;
	}
	| var "^=" assignment_expr	{
		calc::Expression *expr;
		expr = new calc::PowExpression($1.getExpression(), $3);
		$$ = $1.setExpression(expr);
		$3 = 0;
	}
	| cond_expr			{ $$ = $1; $1 = 0; }
	;

cond_expr
	: logic_or_expr			{ $$ = $1; $1 = 0;}
	| logic_or_expr '?' expression ':' cond_expr {
		$$ = new calc::IfExpression($1, $3, $5);
		$1 = $3 = $5 = 0;
	}
	;

logic_or_expr
	: logic_xor_expr		{ $$ = $1; $1 = 0; }
	| logic_or_expr "||" logic_xor_expr {
		$$ = new calc::LogicalOrExpression($1, $3);
		$1 = $3 = 0;
	}
	;

logic_xor_expr
	: logic_and_expr		{ $$ = $1; $1 = 0; }
	| logic_xor_expr "^^" logic_and_expr {
		$$ = new calc::LogicalXorExpression($1, $3);
		$1 = $3 = 0;
	}
	;

logic_and_expr
	: cmp_expr			{ $$ = $1; $1 = 0; }
	| logic_and_expr "&&" cmp_expr {
		$$ = new calc::LogicalAndExpression($1, $3);
		$1 = $3 = 0;
	}
	;

cmp_expr: rel_expr			{ $$ = $1; $1 = 0; }
	| cmp_expr "==" rel_expr	{
		$$ = new calc::EqualExpression($1, $3, env.precision());
		$1 = $3 = 0;
	}
	| cmp_expr "!=" rel_expr	{
		$$ = new calc::EqualExpression($1, $3, false,env.precision());
		$1 = $3 = 0;
	}
	;

rel_expr: additive_expr			{ $$ = $1; $1 = 0; }
	| rel_expr '>'    additive_expr	{
		$$ = new calc::GreaterExpression($1, $3, env.precision());
		$1 = $3 = 0;
	}
	| rel_expr '<'    additive_expr	{
		$$ = new calc::GreaterExpression($3, $1, env.precision());
		$1 = $3 = 0;
	}
	| rel_expr "<="    additive_expr	{
		$$ = new calc::GreaterExpression($1, $3, false, env.precision());
		$1 = $3 = 0;
	}
	| rel_expr ">="    additive_expr	{
		$$ = new calc::GreaterExpression($3, $1, false, env.precision());
		$1 = $3 = 0;
	}
	;

additive_expr
	: additive_expr '+' multiplicative_expr	{
		$$ = new calc::AddExpression($1, $3);
		$1 = $3 = 0;
	}
	| additive_expr '-' multiplicative_expr	{
		$$ = new calc::SubExpression($1, $3);
		$1 = $3 = 0;
	}
	| multiplicative_expr		{ $$ = $1; $1 = 0; }
	;

multiplicative_expr
	: multiplicative_expr '*' pow_expr	{
		$$ = new calc::MulExpression($1, $3);
		$1 = $3 = 0;
	}
	| multiplicative_expr '/' pow_expr	{
		$$ = new calc::DivExpression($1, $3);
		$1 = $3 = 0;
	}
	| pow_expr			{ $$ = $1; $1 = 0; }
	;

pow_expr: prefix_expr '^' pow_expr	{
		$$ = new calc::PowExpression($1, $3);
		$1 = $3 = 0;
	}
	| prefix_expr			{ $$ = $1; $1 = 0; }
	;

prefix_expr
	: '+' prefix_expr		{ $$ = $2; $2 = 0; }
	| '-' prefix_expr		{
		$$ = new calc::NegExpression($2);
		$2 = 0;
	}
	| '!' prefix_expr		{
		calc::BooleanExpression *expr = $2->booleanExpression();
		expr->neg();
		$$ = expr;
		$2 = 0;
	}
	| simple_expr                   { $$ = $1; $1 = 0; }
	;

simple_expr
	: NUMBER			{
		$$ = new calc::NumberExpression($1);
	}
	| '(' expression ')'		{ $$ = $2; $2 = 0; }
	| var				{
		$$ = $1.getExpression();
	}
	| ID '(' ')' {
		$$ = new calc::FunctionExpression(*$1);
	}
	| ID '(' expression ')' {
		$$ = new calc::FunctionExpression(*$1, $3->commaExpression());
		$3 = 0;
	}
	;

var	: ID				{
		$$.name = $1; $$.scope = ' '; $1 = 0;
	}
	| '$' ID			{
		$$.name = $2; $$.scope = '$'; $2 = 0;
	}
	| '#' ID			{
		$$.name = $2; $$.scope = '#'; $2 = 0;
	}
	;

%%
void yy::Parser::error(const location_type &location,
                       const std::string &m) {
	env.error(location.begin, m);
}

int yylex(yy::Parser::semantic_type *yylval,
          yy::Parser::location_type *yylloc,
          calc::Lexer &lexer) {
	return lexer.nextToken(*yylval, *yylloc);
}
