   /*  Make EMACS happy: -*- Mode: C++; tab-width: 8; c-basic-offset: 8 -*- */
%skeleton "lalr1.cc"
%require "2.1a"
%defines
%define "parser_class_name" "Parser"

%{
#include "config.hpp"

#include <string>

#include "environment.hpp"

namespace calc {
	struct Lexer;
}
%}

%union {
	calc::real               dval;
	std::string             *sval;
	calc::FunctionArguments *vval;
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


%token	<sval>	ID
%token	<dval>	NUMBER
%token		ADD_EQ		"+="
%token		SUB_EQ		"-="
%token		MUL_EQ		"*="
%token		DIV_EQ		"/="
%token		POW_EQ		"^="

%type	<dval>	assignment_expr additive_expr multiplicative_expr
%type	<dval>	pow_expr prefix_expr simple_expr
%type	<vval>	arguments non_empty_arguments

%destructor	{ delete $$; } ID arguments non_empty_arguments

%printer	{ debug_stream() << *$$; } ID arguments non_empty_arguments
%printer	{ debug_stream() <<  $$; } assignment_expr additive_expr
%printer	{ debug_stream() <<  $$; } multiplicative_expr pow_expr
%printer	{ debug_stream() <<  $$; } prefix_expr simple_expr NUMBER

%%
start	: start instruction
	| /* nothing */
	;

instruction
	: assignment_expr ';'		{ env.commit(); }
	| assignment_expr '\n'		{ env.commit(); env.instruction($1); }
	| ';'
	| '\n'
	| error ';'			{ env.reject(); }
	| error '\n'			{ env.reject(); }
	;

assignment_expr
	: ID '='  assignment_expr	{ $$ = env.set(*$1, $3); }
	| ID "+=" assignment_expr	{ $$ = env.set(*$1, $3 + env.get(*$1)); }
	| ID "-=" assignment_expr	{ $$ = env.set(*$1, $3 - env.get(*$1)); }
	| ID "*=" assignment_expr	{ $$ = env.set(*$1, $3 * env.get(*$1)); }
	| ID "/=" assignment_expr	{ $$ = env.set(*$1, $3 / env.get(*$1)); }
	| ID "^=" assignment_expr	{ $$ = env.set(*$1, calc::m::pow($3, env.get(*$1))); }
	| additive_expr			{ $$ = $1; }
	;

additive_expr
	: additive_expr '+' multiplicative_expr	{ $$ = $1 + $3; }
	| additive_expr '-' multiplicative_expr	{ $$ = $1 - $3; }
	| multiplicative_expr		{ $$ = $1; }
	;

multiplicative_expr
	: multiplicative_expr '*' pow_expr	{ $$ = $1 * $3; }
	| multiplicative_expr '/' pow_expr	{ $$ = $1 / $3; }
	| pow_expr			{ $$ = $1; }
	;

pow_expr: prefix_expr '^' pow_expr	{ $$ = calc::m::pow($1, $3); }
	| prefix_expr				{ $$ = $1; }
	;

prefix_expr
	: '+' prefix_expr		{ $$ = $2; }
	| '-' prefix_expr		{ $$ = -$2; }
	| simple_expr
	;

simple_expr
	: NUMBER			{ $$ = $1; }
	| '(' assignment_expr ')'	{ $$ = $2; }
	| ID				{ $$ = env.get(*$1); }
	| '#' ID			{ $$ = env.getConst(*$2); }
	| ID '(' arguments ')'
	{
		try {
			$$ = env.run(*$1, *$3);
		}
		catch (const calc::FunctionException &e) {
			error(@$, *$1 + ": " + e.getMessage());
			YYERROR;
		}
	}
		;

arguments
	: /* empty */			{ $$ = new calc::FunctionArguments(); }
	| non_empty_arguments		{ $$ = $1; }
	;

non_empty_arguments
	: assignment_expr		{
		$$ = new calc::FunctionArguments();
		$$->push_back($1);
	}
	| non_empty_arguments ',' assignment_expr	{
		$$ = $1; $$->push_back($3);
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
