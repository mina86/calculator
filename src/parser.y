   /*  Make EMACS happy: -*- Mode: C++; tab-width: 8; c-basic-offset: 8 -*- */
%skeleton "lalr1.cc"
%require "2.1a"
%defines
%define "parser_class_name" "Parser"

%{
#include "config.hpp"

#include <string>

#include "expression.hpp"

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
	/** List of arguments for function call. */
	calc::FunctionExpression::Arguments *args;
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
#include "lexer.hpp"

static const std::string string_e("e");

int yylex(yy::Parser::semantic_type *yylval,
          yy::Parser::location_type *yylloc,
          calc::Lexer &lexer);
%}


%token	<var.name>	ID
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


%type	<expr>	assignment_expr additive_expr multiplicative_expr
%type	<expr>	pow_expr prefix_expr simple_expr
%type	<var>	var
%type	<args>	arguments non_empty_arguments

%destructor	{ delete $$; } ID arguments non_empty_arguments
%destructor	{ delete $$; } assignment_expr additive_expr simple_expr
%destructor	{ delete $$; } multiplicative_expr pow_expr prefix_expr
%destructor	{ delete $$.name; } var

%%
start	: start instruction
	| /* nothing */
	;

instruction
	: assignment_expr ';'		{ $1->execute(env) }
	| assignment_expr '\n'		{ env.instruction($1->execute(env)); }
	| ';'
	| '\n'
	| error ';'
	| error '\n'
	;

assignment_expr
	: var '='  assignment_expr	{
		$$ = calc::SetExpression::create($1, $3);
		$3 = 0;
	}
	| var "+=" assignment_expr	{
		calc::Expression *expr;
		expr = new calc::AddExpression($1, $3);
		$$ = calc::SetExpression::create($1, expr);
		$3 = 0;
	}
	| var "-=" assignment_expr	{
		calc::Expression *expr;
		expr = new calc::SubExpression($1, $3);
		$$ = calc::SetExpression::create($1, expr);
		$3 = 0;
	}
	| var "*=" assignment_expr	{
		calc::Expression *expr;
		expr = new calc::MulExpression($1, $3);
		$$ = calc::SetExpression::create($1, expr);
		$3 = 0;
	}
	| var "/=" assignment_expr	{
		calc::Expression *expr;
		expr = new calc::DivExpression($1, $3);
		$$ = calc::SetExpression::create($1, expr);
		$3 = 0;
	}
	| var "^=" assignment_expr	{
		calc::Expression *expr;
		expr = new calc::PowExpression($1, $3);
		$$ = calc::SetExpression::create($1, expr);
		$3 = 0;
	}
	| additive_expr			{ $$ = $1; $1 = 0; }
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
	| simple_expr                   { $$ = $1; $1 = 0; }
	;

simple_expr
	: NUMBER			{
		$$ = new calc::NumberExpression($1);
	}
	| '(' assignment_expr ')'	{ $$ = $2; $2 = 0; }
	| var				{
		$$ = calc::GetExpression::create($1);
	}
	| ID '(' arguments ')' {
		$$ = new calc::FunctionExpression(*$1, $3);
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

arguments
	: /* empty */			{
		$$ = new calc::FunctionExpression::Arguments();
	}
	| non_empty_arguments		{ $$ = $1; $1 = 0; }
	;

non_empty_arguments
	: assignment_expr		{
		$$ = new calc::FunctionExpression::Arguments();
		$$->push_back($1);
		$1 = 0;
	}
	| non_empty_arguments ',' assignment_expr	{
		$$ = $1; $$->push_back($3);
		$1 = 0; $3 = 0;
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
