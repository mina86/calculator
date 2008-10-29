/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison LALR(1) parsers in C++

   Copyright (C) 2002, 2003, 2004, 2005, 2006 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */


#include "parser.hpp"

/* User implementation prologue.  */
#line 57 "parser.y"

#include "math.hpp"
#include "exceptions.hpp"
#include "environment.hpp"
#include "lexer.hpp"

static const std::string string_e("e");

int yylex(yy::Parser::semantic_type *yylval,
          yy::Parser::location_type *yylloc,
          calc::Lexer &lexer);


/* Line 317 of lalr1.cc.  */
#line 55 "parser.cpp"

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* FIXME: INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#define YYUSE(e) ((void) (e))

/* A pseudo ostream that takes yydebug_ into account.  */
# define YYCDEBUG							\
  for (bool yydebugcond_ = yydebug_; yydebugcond_; yydebugcond_ = false)	\
    (*yycdebug_)

/* Enable debugging if requested.  */
#if YYDEBUG

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)	\
do {							\
  if (yydebug_)						\
    {							\
      *yycdebug_ << Title << ' ';			\
      yy_symbol_print_ ((Type), (Value), (Location));	\
      *yycdebug_ << std::endl;				\
    }							\
} while (false)

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug_)				\
    yy_reduce_print_ (Rule);		\
} while (false)

# define YY_STACK_PRINT()		\
do {					\
  if (yydebug_)				\
    yystack_print_ ();			\
} while (false)

#else /* !YYDEBUG */

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_REDUCE_PRINT(Rule)
# define YY_STACK_PRINT()

#endif /* !YYDEBUG */

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab

namespace yy
{
#if YYERROR_VERBOSE

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  Parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr = "";
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              /* Fall through.  */
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }

#endif

  /// Build a parser object.
  Parser::Parser (calc::Lexer       &lexer_yyarg, calc::Environment &env_yyarg)
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
      lexer (lexer_yyarg),
      env (env_yyarg)
  {
  }

  Parser::~Parser ()
  {
  }

#if YYDEBUG
  /*--------------------------------.
  | Print this symbol on YYOUTPUT.  |
  `--------------------------------*/

  inline void
  Parser::yy_symbol_value_print_ (int yytype,
			   const semantic_type* yyvaluep, const location_type* yylocationp)
  {
    YYUSE (yylocationp);
    YYUSE (yyvaluep);
    switch (yytype)
      {
         default:
	  break;
      }
  }


  void
  Parser::yy_symbol_print_ (int yytype,
			   const semantic_type* yyvaluep, const location_type* yylocationp)
  {
    *yycdebug_ << (yytype < yyntokens_ ? "token" : "nterm")
	       << ' ' << yytname_[yytype] << " ("
	       << *yylocationp << ": ";
    yy_symbol_value_print_ (yytype, yyvaluep, yylocationp);
    *yycdebug_ << ')';
  }
#endif /* ! YYDEBUG */

  void
  Parser::yydestruct_ (const char* yymsg,
			   int yytype, semantic_type* yyvaluep, location_type* yylocationp)
  {
    YYUSE (yylocationp);
    YYUSE (yymsg);
    YYUSE (yyvaluep);

    YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

    switch (yytype)
      {
        case 3: /* "ID" */
#line 88 "parser.y"
	{ delete (yyvaluep->var.name); };
#line 216 "parser.cpp"
	break;
      case 34: /* "formal_arguments" */
#line 93 "parser.y"
	{ delete (yyvaluep->params); };
#line 221 "parser.cpp"
	break;
      case 35: /* "non_empty_formal_arguments" */
#line 93 "parser.y"
	{ delete (yyvaluep->params); };
#line 226 "parser.cpp"
	break;
      case 36: /* "expression" */
#line 88 "parser.y"
	{ delete (yyvaluep->expr); };
#line 231 "parser.cpp"
	break;
      case 37: /* "assignment_expr" */
#line 89 "parser.y"
	{ delete (yyvaluep->expr); };
#line 236 "parser.cpp"
	break;
      case 38: /* "repeat_expr" */
#line 88 "parser.y"
	{ delete (yyvaluep->expr); };
#line 241 "parser.cpp"
	break;
      case 39: /* "logic_or_expr" */
#line 91 "parser.y"
	{ delete (yyvaluep->expr); };
#line 246 "parser.cpp"
	break;
      case 40: /* "logic_xor_expr" */
#line 91 "parser.y"
	{ delete (yyvaluep->expr); };
#line 251 "parser.cpp"
	break;
      case 41: /* "logic_and_expr" */
#line 91 "parser.y"
	{ delete (yyvaluep->expr); };
#line 256 "parser.cpp"
	break;
      case 42: /* "cmp_expr" */
#line 88 "parser.y"
	{ delete (yyvaluep->expr); };
#line 261 "parser.cpp"
	break;
      case 43: /* "rel_expr" */
#line 88 "parser.y"
	{ delete (yyvaluep->expr); };
#line 266 "parser.cpp"
	break;
      case 44: /* "additive_expr" */
#line 89 "parser.y"
	{ delete (yyvaluep->expr); };
#line 271 "parser.cpp"
	break;
      case 45: /* "multiplicative_expr" */
#line 90 "parser.y"
	{ delete (yyvaluep->expr); };
#line 276 "parser.cpp"
	break;
      case 46: /* "pow_expr" */
#line 90 "parser.y"
	{ delete (yyvaluep->expr); };
#line 281 "parser.cpp"
	break;
      case 47: /* "prefix_expr" */
#line 90 "parser.y"
	{ delete (yyvaluep->expr); };
#line 286 "parser.cpp"
	break;
      case 48: /* "simple_expr" */
#line 89 "parser.y"
	{ delete (yyvaluep->expr); };
#line 291 "parser.cpp"
	break;
      case 49: /* "var" */
#line 92 "parser.y"
	{ delete (yyvaluep->var).name; };
#line 296 "parser.cpp"
	break;

	default:
	  break;
      }
  }

  void
  Parser::yypop_ (unsigned int n)
  {
    yystate_stack_.pop (n);
    yysemantic_stack_.pop (n);
    yylocation_stack_.pop (n);
  }

  std::ostream&
  Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  Parser::debug_level_type
  Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }


  int
  Parser::parse ()
  {
    /// Look-ahead and look-ahead in internal form.
    int yychar = yyempty_;
    int yytoken = 0;

    /* State.  */
    int yyn;
    int yylen = 0;
    int yystate = 0;

    /* Error handling.  */
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// Semantic value of the look-ahead.
    semantic_type yylval;
    /// Location of the look-ahead.
    location_type yylloc;
    /// The locations where the error started and ended.
    location yyerror_range[2];

    /// $$.
    semantic_type yyval;
    /// @$.
    location_type yyloc;

    int yyresult;

    YYCDEBUG << "Starting parse" << std::endl;


    /* Initialize the stacks.  The initial state will be pushed in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystate_stack_ = state_stack_type (0);
    yysemantic_stack_ = semantic_stack_type (0);
    yylocation_stack_ = location_stack_type (0);
    yysemantic_stack_.push (yylval);
    yylocation_stack_.push (yylloc);

    /* New state.  */
  yynewstate:
    yystate_stack_.push (yystate);
    YYCDEBUG << "Entering state " << yystate << std::endl;
    goto yybackup;

    /* Backup.  */
  yybackup:

    /* Try to take a decision without look-ahead.  */
    yyn = yypact_[yystate];
    if (yyn == yypact_ninf_)
      goto yydefault;

    /* Read a look-ahead token.  */
    if (yychar == yyempty_)
      {
	YYCDEBUG << "Reading a token: ";
	yychar = yylex (&yylval, &yylloc, lexer);
      }


    /* Convert token to internal form.  */
    if (yychar <= yyeof_)
      {
	yychar = yytoken = yyeof_;
	YYCDEBUG << "Now at end of input." << std::endl;
      }
    else
      {
	yytoken = yytranslate_ (yychar);
	YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
      }

    /* If the proper action on seeing token YYTOKEN is to reduce or to
       detect an error, take that action.  */
    yyn += yytoken;
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yytoken)
      goto yydefault;

    /* Reduce or error.  */
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
	if (yyn == 0 || yyn == yytable_ninf_)
	goto yyerrlab;
	yyn = -yyn;
	goto yyreduce;
      }

    /* Accept?  */
    if (yyn == yyfinal_)
      goto yyacceptlab;

    /* Shift the look-ahead token.  */
    YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

    /* Discard the token being shifted unless it is eof.  */
    if (yychar != yyeof_)
      yychar = yyempty_;

    yysemantic_stack_.push (yylval);
    yylocation_stack_.push (yylloc);

    /* Count tokens shifted since error; after three, turn off error
       status.  */
    if (yyerrstatus_)
      --yyerrstatus_;

    yystate = yyn;
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystate];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    /* If YYLEN is nonzero, implement the default value of the action:
       `$$ = $1'.  Otherwise, use the top of the stack.

       Otherwise, the following line sets YYVAL to garbage.
       This behavior is undocumented and Bison
       users should not rely upon it.  */
    if (yylen)
      yyval = yysemantic_stack_[yylen - 1];
    else
      yyval = yysemantic_stack_[0];

    {
      slice<location_type, location_stack_type> slice (yylocation_stack_, yylen);
      YYLLOC_DEFAULT (yyloc, slice, yylen);
    }
    YY_REDUCE_PRINT (yyn);
    switch (yyn)
      {
	  case 6:
#line 103 "parser.y"
    { env.execute((yysemantic_stack_[(2) - (1)].expr), false); ;}
    break;

  case 7:
#line 104 "parser.y"
    { env.execute((yysemantic_stack_[(2) - (1)].expr), true); ;}
    break;

  case 12:
#line 112 "parser.y"
    {
		env.addUserFunction(*(yysemantic_stack_[(6) - (1)].var.name), new calc::UserFunction((yysemantic_stack_[(6) - (6)].expr), *(yysemantic_stack_[(6) - (3)].params)));
		(yysemantic_stack_[(6) - (6)].expr) = 0;
	;}
    break;

  case 13:
#line 119 "parser.y"
    { (yyval.params) = new calc::UserFunction::Names() ;}
    break;

  case 14:
#line 120 "parser.y"
    { (yyval.params) = (yysemantic_stack_[(1) - (1)].params); (yysemantic_stack_[(1) - (1)].params) = 0; ;}
    break;

  case 15:
#line 124 "parser.y"
    {
		(yyval.params) = new calc::UserFunction::Names();
		(yyval.params)->push_back(*(yysemantic_stack_[(1) - (1)].var.name));
	;}
    break;

  case 16:
#line 128 "parser.y"
    {
		(yyval.params) = (yysemantic_stack_[(3) - (1)].params);
		(yyval.params)->push_back(*(yysemantic_stack_[(3) - (3)].var.name));
		(yysemantic_stack_[(3) - (1)].params) = 0;
	;}
    break;

  case 17:
#line 136 "parser.y"
    { (yyval.expr) = (yysemantic_stack_[(1) - (1)].expr); (yysemantic_stack_[(1) - (1)].expr) = 0; ;}
    break;

  case 18:
#line 137 "parser.y"
    {
		(yyval.expr) = (yysemantic_stack_[(3) - (1)].expr)->commaExpression();
		static_cast<calc::CommaExpression*>((yyval.expr))->push((yysemantic_stack_[(3) - (3)].expr));
		(yysemantic_stack_[(3) - (1)].expr) = (yysemantic_stack_[(3) - (3)].expr) = 0;
	;}
    break;

  case 19:
#line 145 "parser.y"
    {
		(yyval.expr) = (yysemantic_stack_[(3) - (1)].var).setExpression((yysemantic_stack_[(3) - (3)].expr));
		(yysemantic_stack_[(3) - (3)].expr) = 0;
	;}
    break;

  case 20:
#line 149 "parser.y"
    {
		calc::Expression *expr = (yysemantic_stack_[(3) - (1)].var).getExpression();
		switch ((yysemantic_stack_[(3) - (2)].setop)) {
		case semantic_type::SET_ADD:
			expr = new calc::AddExpression(expr, (yysemantic_stack_[(3) - (3)].expr)); break;
		case semantic_type::SET_SUB:
			expr = new calc::SubExpression(expr, (yysemantic_stack_[(3) - (3)].expr)); break;
		case semantic_type::SET_MUL:
			expr = new calc::MulExpression(expr, (yysemantic_stack_[(3) - (3)].expr)); break;
		case semantic_type::SET_DIV:
			expr = new calc::DivExpression(expr, (yysemantic_stack_[(3) - (3)].expr)); break;
		case semantic_type::SET_POW:
			expr = new calc::PowExpression(expr, (yysemantic_stack_[(3) - (3)].expr)); break;
		}
		(yyval.expr) = (yysemantic_stack_[(3) - (1)].var).setExpression(expr);
		(yysemantic_stack_[(3) - (3)].expr) = 0;
	;}
    break;

  case 21:
#line 166 "parser.y"
    { (yyval.expr) = (yysemantic_stack_[(1) - (1)].expr); (yysemantic_stack_[(1) - (1)].expr) = 0; ;}
    break;

  case 22:
#line 170 "parser.y"
    { (yyval.expr) = (yysemantic_stack_[(1) - (1)].expr); (yysemantic_stack_[(1) - (1)].expr) = 0;;}
    break;

  case 23:
#line 171 "parser.y"
    {
		(yyval.expr) = new calc::TimesExpression((yysemantic_stack_[(5) - (1)].expr), (yysemantic_stack_[(5) - (3)].expr), (yysemantic_stack_[(5) - (5)].expr));
		(yysemantic_stack_[(5) - (1)].expr) = (yysemantic_stack_[(5) - (3)].expr) = (yysemantic_stack_[(5) - (5)].expr) = 0;
	;}
    break;

  case 24:
#line 175 "parser.y"
    {
		(yyval.expr) = new calc::WhileExpression((yysemantic_stack_[(5) - (1)].expr), (yysemantic_stack_[(5) - (3)].expr), (yysemantic_stack_[(5) - (5)].expr));
		(yysemantic_stack_[(5) - (1)].expr) = (yysemantic_stack_[(5) - (3)].expr) = (yysemantic_stack_[(5) - (5)].expr) = 0;
	;}
    break;

  case 25:
#line 179 "parser.y"
    {
		(yyval.expr) = new calc::IfExpression((yysemantic_stack_[(5) - (1)].expr), (yysemantic_stack_[(5) - (3)].expr), (yysemantic_stack_[(5) - (5)].expr));
		(yysemantic_stack_[(5) - (1)].expr) = (yysemantic_stack_[(5) - (3)].expr) = (yysemantic_stack_[(5) - (5)].expr) = 0;
	;}
    break;

  case 26:
#line 186 "parser.y"
    { (yyval.expr) = (yysemantic_stack_[(1) - (1)].expr); (yysemantic_stack_[(1) - (1)].expr) = 0; ;}
    break;

  case 27:
#line 187 "parser.y"
    {
		(yyval.expr) = new calc::LogicalOrExpression((yysemantic_stack_[(3) - (1)].expr), (yysemantic_stack_[(3) - (3)].expr));
		(yysemantic_stack_[(3) - (1)].expr) = (yysemantic_stack_[(3) - (3)].expr) = 0;
	;}
    break;

  case 28:
#line 194 "parser.y"
    { (yyval.expr) = (yysemantic_stack_[(1) - (1)].expr); (yysemantic_stack_[(1) - (1)].expr) = 0; ;}
    break;

  case 29:
#line 195 "parser.y"
    {
		(yyval.expr) = new calc::LogicalXorExpression((yysemantic_stack_[(3) - (1)].expr), (yysemantic_stack_[(3) - (3)].expr));
		(yysemantic_stack_[(3) - (1)].expr) = (yysemantic_stack_[(3) - (3)].expr) = 0;
	;}
    break;

  case 30:
#line 202 "parser.y"
    { (yyval.expr) = (yysemantic_stack_[(1) - (1)].expr); (yysemantic_stack_[(1) - (1)].expr) = 0; ;}
    break;

  case 31:
#line 203 "parser.y"
    {
		(yyval.expr) = new calc::LogicalAndExpression((yysemantic_stack_[(3) - (1)].expr), (yysemantic_stack_[(3) - (3)].expr));
		(yysemantic_stack_[(3) - (1)].expr) = (yysemantic_stack_[(3) - (3)].expr) = 0;
	;}
    break;

  case 32:
#line 209 "parser.y"
    { (yyval.expr) = (yysemantic_stack_[(1) - (1)].expr); (yysemantic_stack_[(1) - (1)].expr) = 0; ;}
    break;

  case 33:
#line 210 "parser.y"
    {
		(yyval.expr) = new calc::EqualExpression((yysemantic_stack_[(3) - (1)].expr), (yysemantic_stack_[(3) - (3)].expr), !((yysemantic_stack_[(3) - (2)].flags) & CMP_NOT),
		                               env.precision((yysemantic_stack_[(3) - (2)].flags) & CMP_FUZZY));
		(yysemantic_stack_[(3) - (1)].expr) = (yysemantic_stack_[(3) - (3)].expr) = 0;
	;}
    break;

  case 34:
#line 217 "parser.y"
    { (yyval.expr) = (yysemantic_stack_[(1) - (1)].expr); (yysemantic_stack_[(1) - (1)].expr) = 0; ;}
    break;

  case 35:
#line 218 "parser.y"
    {
		(yyval.expr) = new calc::GreaterExpression((yysemantic_stack_[(3) - (1)].expr), (yysemantic_stack_[(3) - (3)].expr), (yysemantic_stack_[(3) - (2)].flags) & REL_SWITCH,
		                                 !((yysemantic_stack_[(3) - (2)].flags) & REL_NOT),
		                                 env.precision((yysemantic_stack_[(3) - (2)].flags)&REL_FUZZY));
		(yysemantic_stack_[(3) - (1)].expr) = (yysemantic_stack_[(3) - (3)].expr) = 0;
	;}
    break;

  case 36:
#line 227 "parser.y"
    {
		(yyval.expr) = new calc::AddExpression((yysemantic_stack_[(3) - (1)].expr), (yysemantic_stack_[(3) - (3)].expr));
		(yysemantic_stack_[(3) - (1)].expr) = (yysemantic_stack_[(3) - (3)].expr) = 0;
	;}
    break;

  case 37:
#line 231 "parser.y"
    {
		(yyval.expr) = new calc::SubExpression((yysemantic_stack_[(3) - (1)].expr), (yysemantic_stack_[(3) - (3)].expr));
		(yysemantic_stack_[(3) - (1)].expr) = (yysemantic_stack_[(3) - (3)].expr) = 0;
	;}
    break;

  case 38:
#line 235 "parser.y"
    { (yyval.expr) = (yysemantic_stack_[(1) - (1)].expr); (yysemantic_stack_[(1) - (1)].expr) = 0; ;}
    break;

  case 39:
#line 239 "parser.y"
    {
		(yyval.expr) = new calc::MulExpression((yysemantic_stack_[(3) - (1)].expr), (yysemantic_stack_[(3) - (3)].expr));
		(yysemantic_stack_[(3) - (1)].expr) = (yysemantic_stack_[(3) - (3)].expr) = 0;
	;}
    break;

  case 40:
#line 243 "parser.y"
    {
		(yyval.expr) = new calc::DivExpression((yysemantic_stack_[(3) - (1)].expr), (yysemantic_stack_[(3) - (3)].expr));
		(yysemantic_stack_[(3) - (1)].expr) = (yysemantic_stack_[(3) - (3)].expr) = 0;
	;}
    break;

  case 41:
#line 247 "parser.y"
    {
		(yyval.expr) = new calc::ModExpression((yysemantic_stack_[(3) - (1)].expr), (yysemantic_stack_[(3) - (3)].expr));
		(yysemantic_stack_[(3) - (1)].expr) = (yysemantic_stack_[(3) - (3)].expr) = 0;
	;}
    break;

  case 42:
#line 251 "parser.y"
    { (yyval.expr) = (yysemantic_stack_[(1) - (1)].expr); (yysemantic_stack_[(1) - (1)].expr) = 0; ;}
    break;

  case 43:
#line 254 "parser.y"
    {
		(yyval.expr) = new calc::PowExpression((yysemantic_stack_[(3) - (1)].expr), (yysemantic_stack_[(3) - (3)].expr));
		(yysemantic_stack_[(3) - (1)].expr) = (yysemantic_stack_[(3) - (3)].expr) = 0;
	;}
    break;

  case 44:
#line 258 "parser.y"
    { (yyval.expr) = (yysemantic_stack_[(1) - (1)].expr); (yysemantic_stack_[(1) - (1)].expr) = 0; ;}
    break;

  case 45:
#line 262 "parser.y"
    { (yyval.expr) = (yysemantic_stack_[(2) - (2)].expr); (yysemantic_stack_[(2) - (2)].expr) = 0; ;}
    break;

  case 46:
#line 263 "parser.y"
    {
		(yyval.expr) = new calc::NegExpression((yysemantic_stack_[(2) - (2)].expr));
		(yysemantic_stack_[(2) - (2)].expr) = 0;
	;}
    break;

  case 47:
#line 267 "parser.y"
    {
		calc::BooleanExpression *expr = (yysemantic_stack_[(2) - (2)].expr)->booleanExpression();
		expr->neg();
		(yyval.expr) = expr;
		(yysemantic_stack_[(2) - (2)].expr) = 0;
	;}
    break;

  case 48:
#line 273 "parser.y"
    { (yyval.expr) = (yysemantic_stack_[(1) - (1)].expr); (yysemantic_stack_[(1) - (1)].expr) = 0; ;}
    break;

  case 49:
#line 277 "parser.y"
    {
		(yyval.expr) = new calc::NumberExpression((yysemantic_stack_[(1) - (1)].num));
	;}
    break;

  case 50:
#line 280 "parser.y"
    { (yyval.expr) = (yysemantic_stack_[(3) - (2)].expr); (yysemantic_stack_[(3) - (2)].expr) = 0; ;}
    break;

  case 51:
#line 281 "parser.y"
    {
		(yyval.expr) = (yysemantic_stack_[(1) - (1)].var).getExpression();
	;}
    break;

  case 52:
#line 284 "parser.y"
    {
		(yyval.expr) = new calc::FunctionExpression(*(yysemantic_stack_[(3) - (1)].var.name));
	;}
    break;

  case 53:
#line 287 "parser.y"
    {
		(yyval.expr) = new calc::FunctionExpression(*(yysemantic_stack_[(4) - (1)].var.name), (yysemantic_stack_[(4) - (3)].expr)->commaExpression());
		(yysemantic_stack_[(4) - (3)].expr) = 0;
	;}
    break;

  case 54:
#line 293 "parser.y"
    {
		(yyval.var).name = (yysemantic_stack_[(1) - (1)].var.name); (yyval.var).scope = ' '; (yysemantic_stack_[(1) - (1)].var.name) = 0;
	;}
    break;

  case 55:
#line 296 "parser.y"
    {
		(yyval.var).name = (yysemantic_stack_[(2) - (2)].var.name); (yyval.var).scope = '$'; (yysemantic_stack_[(2) - (2)].var.name) = 0;
	;}
    break;

  case 56:
#line 299 "parser.y"
    {
		(yyval.var).name = (yysemantic_stack_[(2) - (2)].var.name); (yyval.var).scope = '#'; (yysemantic_stack_[(2) - (2)].var.name) = 0;
	;}
    break;


    /* Line 675 of lalr1.cc.  */
#line 823 "parser.cpp"
	default: break;
      }
    YY_SYMBOL_PRINT ("-> $$ =", yyr1_[yyn], &yyval, &yyloc);

    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();

    yysemantic_stack_.push (yyval);
    yylocation_stack_.push (yyloc);

    /* Shift the result of the reduction.  */
    yyn = yyr1_[yyn];
    yystate = yypgoto_[yyn - yyntokens_] + yystate_stack_[0];
    if (0 <= yystate && yystate <= yylast_
	&& yycheck_[yystate] == yystate_stack_[0])
      yystate = yytable_[yystate];
    else
      yystate = yydefgoto_[yyn - yyntokens_];
    goto yynewstate;

  /*------------------------------------.
  | yyerrlab -- here on detecting error |
  `------------------------------------*/
  yyerrlab:
    /* If not already recovering from an error, report this error.  */
    if (!yyerrstatus_)
      {
	++yynerrs_;
	error (yylloc, yysyntax_error_ (yystate, yytoken));
      }

    yyerror_range[0] = yylloc;
    if (yyerrstatus_ == 3)
      {
	/* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

	if (yychar <= yyeof_)
	  {
	  /* Return failure if at end of input.  */
	  if (yychar == yyeof_)
	    YYABORT;
	  }
	else
	  {
	    yydestruct_ ("Error: discarding", yytoken, &yylval, &yylloc);
	    yychar = yyempty_;
	  }
      }

    /* Else will try to reuse look-ahead token after shifting the error
       token.  */
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;

    yyerror_range[0] = yylocation_stack_[yylen - 1];
    /* Do not reclaim the symbols of the rule which action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    yystate = yystate_stack_[0];
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;	/* Each real token shifted decrements this.  */

    for (;;)
      {
	yyn = yypact_[yystate];
	if (yyn != yypact_ninf_)
	{
	  yyn += yyterror_;
	  if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
	    {
	      yyn = yytable_[yyn];
	      if (0 < yyn)
		break;
	    }
	}

	/* Pop the current state because it cannot handle the error token.  */
	if (yystate_stack_.height () == 1)
	YYABORT;

	yyerror_range[0] = yylocation_stack_[0];
	yydestruct_ ("Error: popping",
		     yystos_[yystate],
		     &yysemantic_stack_[0], &yylocation_stack_[0]);
	yypop_ ();
	yystate = yystate_stack_[0];
	YY_STACK_PRINT ();
      }

    if (yyn == yyfinal_)
      goto yyacceptlab;

    yyerror_range[1] = yylloc;
    // Using YYLLOC is tempting, but would change the location of
    // the look-ahead.  YYLOC is available though.
    YYLLOC_DEFAULT (yyloc, (yyerror_range - 1), 2);
    yysemantic_stack_.push (yylval);
    yylocation_stack_.push (yyloc);

    /* Shift the error token.  */
    YY_SYMBOL_PRINT ("Shifting", yystos_[yyn],
		   &yysemantic_stack_[0], &yylocation_stack_[0]);

    yystate = yyn;
    goto yynewstate;

    /* Accept.  */
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    /* Abort.  */
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (yychar != yyeof_ && yychar != yyempty_)
      yydestruct_ ("Cleanup: discarding lookahead", yytoken, &yylval, &yylloc);

    /* Do not reclaim the symbols of the rule which action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (yystate_stack_.height () != 1)
      {
	yydestruct_ ("Cleanup: popping",
		   yystos_[yystate_stack_[0]],
		   &yysemantic_stack_[0],
		   &yylocation_stack_[0]);
	yypop_ ();
      }

    return yyresult;
  }

  // Generate an error message.
  std::string
  Parser::yysyntax_error_ (int yystate, int tok)
  {
    std::string res;
    YYUSE (yystate);
#if YYERROR_VERBOSE
    int yyn = yypact_[yystate];
    if (yypact_ninf_ < yyn && yyn <= yylast_)
      {
	/* Start YYX at -YYN if negative to avoid negative indexes in
	   YYCHECK.  */
	int yyxbegin = yyn < 0 ? -yyn : 0;

	/* Stay within bounds of both yycheck and yytname.  */
	int yychecklim = yylast_ - yyn + 1;
	int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
	int count = 0;
	for (int x = yyxbegin; x < yyxend; ++x)
	  if (yycheck_[x + yyn] == x && x != yyterror_)
	    ++count;

	// FIXME: This method of building the message is not compatible
	// with internationalization.  It should work like yacc.c does it.
	// That is, first build a string that looks like this:
	// "syntax error, unexpected %s or %s or %s"
	// Then, invoke YY_ on this string.
	// Finally, use the string as a format to output
	// yytname_[tok], etc.
	// Until this gets fixed, this message appears in English only.
	res = "syntax error, unexpected ";
	res += yytnamerr_ (yytname_[tok]);
	if (count < 5)
	  {
	    count = 0;
	    for (int x = yyxbegin; x < yyxend; ++x)
	      if (yycheck_[x + yyn] == x && x != yyterror_)
		{
		  res += (!count++) ? ", expecting " : " or ";
		  res += yytnamerr_ (yytname_[x]);
		}
	  }
      }
    else
#endif
      res = YY_("syntax error");
    return res;
  }


  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
  const signed char Parser::yypact_ninf_ = -41;
  const signed char
  Parser::yypact_[] =
  {
       -41,    48,   -41,    -3,    36,    10,   -41,   -41,   -41,    51,
      38,    51,    51,    51,    69,   -41,    -6,   -41,   -41,    12,
      64,    68,    82,    89,    41,     1,   -41,    71,   -41,    -4,
     -41,   -41,     0,    83,     4,    27,   -41,   -41,   -41,   -41,
     -41,   -41,   -41,   -41,    51,    51,    51,    51,    51,    51,
      51,    51,    51,    51,    51,    51,    51,    51,    51,    51,
      51,   -41,    40,    96,   -41,   -41,   -41,   -41,    64,    70,
      74,    75,    68,    82,    89,    41,     1,     1,   -41,   -41,
     -41,   -41,   -41,   -41,   -41,   -41,    85,    84,    51,    51,
      51,    86,   100,   -41,   -41,   -41,    51,   -41,    87
  };

  /* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
     doesn't specify something else to do.  Zero means the default is an
     error.  */
  const unsigned char
  Parser::yydefact_[] =
  {
         3,     0,     1,     0,    54,     0,    49,     8,     9,     0,
       0,     0,     0,     0,     0,     2,     0,    17,    21,    22,
      26,    28,    30,    32,    34,    38,    42,    44,    48,    51,
      10,    11,     0,     0,     0,     0,    56,    45,    51,    46,
      47,    55,     6,     7,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    52,     0,    13,     4,     5,    50,    18,    27,     0,
       0,     0,    29,    31,    33,    35,    36,    37,    39,    40,
      41,    43,    20,    19,    53,    15,     0,    14,     0,     0,
       0,     0,     0,    23,    24,    25,     0,    16,    12
  };

  /* YYPGOTO[NTERM-NUM].  */
  const signed char
  Parser::yypgoto_[] =
  {
       -41,   -41,   -41,   -41,   -41,   -41,    -8,   -40,    -7,   -41,
      60,    57,    58,    56,    59,    14,   -21,    73,   -41,    -1
  };

  /* YYDEFGOTO[NTERM-NUM].  */
  const signed char
  Parser::yydefgoto_[] =
  {
        -1,     1,    15,    34,    86,    87,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    38
  };

  /* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule which
     number is the opposite.  If zero, do what YYDEFACT says.  */
  const signed char Parser::yytable_ninf_ = -1;
  const unsigned char
  Parser::yytable_[] =
  {
        29,    35,    59,     4,    67,     6,    42,    43,    29,    30,
      31,    44,    60,    33,     9,    61,    64,    65,    10,    82,
      83,    45,    11,    12,    62,    55,    56,    57,    13,    14,
      46,    29,    47,    48,    78,    79,    80,    81,    69,    70,
      71,    36,    66,    29,    44,    29,    29,    29,     2,     3,
      32,     4,     5,     6,     4,    84,     6,    44,    29,    29,
       7,     8,     9,    53,    54,     9,    10,    76,    77,    10,
      11,    12,    41,    11,    12,    49,    13,    14,    50,    13,
      14,    93,    94,    95,    37,    39,    40,    44,    98,    88,
      51,    44,    44,    89,    90,    29,    52,    63,    58,    85,
      91,    92,    96,    97,    44,    68,    72,    74,    73,     0,
       0,    75
  };

  /* YYCHECK.  */
  const signed char
  Parser::yycheck_[] =
  {
         1,     9,     6,     3,    44,     5,    12,    13,     9,    12,
      13,    17,    16,     3,    14,    15,    12,    13,    18,    59,
      60,     9,    22,    23,    32,    24,    25,    26,    28,    29,
      18,    32,    20,    21,    55,    56,    57,    58,    46,    47,
      48,     3,    15,    44,    17,    46,    47,    48,     0,     1,
      14,     3,     4,     5,     3,    15,     5,    17,    59,    60,
      12,    13,    14,    22,    23,    14,    18,    53,    54,    18,
      22,    23,     3,    22,    23,    11,    28,    29,    10,    28,
      29,    88,    89,    90,    11,    12,    13,    17,    96,    19,
       8,    17,    17,    19,    19,    96,     7,    14,    27,     3,
      15,    17,    16,     3,    17,    45,    49,    51,    50,    -1,
      -1,    52
  };

  /* STOS_[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
  const unsigned char
  Parser::yystos_[] =
  {
         0,    31,     0,     1,     3,     4,     5,    12,    13,    14,
      18,    22,    23,    28,    29,    32,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      12,    13,    14,     3,    33,    36,     3,    47,    49,    47,
      47,     3,    12,    13,    17,     9,    18,    20,    21,    11,
      10,     8,     7,    22,    23,    24,    25,    26,    27,     6,
      16,    15,    36,    14,    12,    13,    15,    37,    40,    36,
      36,    36,    41,    42,    43,    44,    45,    45,    46,    46,
      46,    46,    37,    37,    15,     3,    34,    35,    19,    19,
      19,    15,    17,    38,    38,    38,    16,     3,    36
  };

#if YYDEBUG
  /* TOKEN_NUMBER_[YYLEX-NUM] -- Internal symbol number corresponding
     to YYLEX-NUM.  */
  const unsigned short int
  Parser::yytoken_number_[] =
  {
         0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,    59,    10,    40,    41,    61,    44,    35,    58,
      64,    63,    43,    45,    42,    47,    37,    94,    33,    36
  };
#endif

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
  const unsigned char
  Parser::yyr1_[] =
  {
         0,    30,    31,    31,    32,    32,    32,    32,    32,    32,
      32,    32,    33,    34,    34,    35,    35,    36,    36,    37,
      37,    37,    38,    38,    38,    38,    39,    39,    40,    40,
      41,    41,    42,    42,    43,    43,    44,    44,    44,    45,
      45,    45,    45,    46,    46,    47,    47,    47,    47,    48,
      48,    48,    48,    48,    49,    49,    49
  };

  /* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
  const unsigned char
  Parser::yyr2_[] =
  {
         0,     2,     2,     0,     3,     3,     2,     2,     1,     1,
       2,     2,     6,     0,     1,     1,     3,     1,     3,     3,
       3,     1,     1,     5,     5,     5,     1,     3,     1,     3,
       1,     3,     1,     3,     1,     3,     3,     3,     1,     3,
       3,     3,     1,     3,     1,     2,     2,     2,     1,     1,
       3,     1,     3,     4,     1,     2,     2
  };

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
  /* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
     First, the terminals, then, starting at \a yyntokens_, nonterminals.  */
  const char*
  const Parser::yytname_[] =
  {
    "$end", "error", "$undefined", "ID", "\"define\"", "NUMBER", "\"#=\"",
  "REL_OP", "CMP_OP", "\"||\"", "\"&&\"", "\"^^\"", "';'", "'\\n'", "'('",
  "')'", "'='", "','", "'#'", "':'", "'@'", "'?'", "'+'", "'-'", "'*'",
  "'/'", "'%'", "'^'", "'!'", "'$'", "$accept", "start", "instruction",
  "define_instruction", "formal_arguments", "non_empty_formal_arguments",
  "expression", "assignment_expr", "repeat_expr", "logic_or_expr",
  "logic_xor_expr", "logic_and_expr", "cmp_expr", "rel_expr",
  "additive_expr", "multiplicative_expr", "pow_expr", "prefix_expr",
  "simple_expr", "var", 0
  };
#endif

#if YYDEBUG
  /* YYRHS -- A `-1'-separated list of the rules' RHS.  */
  const Parser::rhs_number_type
  Parser::yyrhs_[] =
  {
        31,     0,    -1,    31,    32,    -1,    -1,     4,    33,    12,
      -1,     4,    33,    13,    -1,    36,    12,    -1,    36,    13,
      -1,    12,    -1,    13,    -1,     1,    12,    -1,     1,    13,
      -1,     3,    14,    34,    15,    16,    36,    -1,    -1,    35,
      -1,     3,    -1,    35,    17,     3,    -1,    37,    -1,    36,
      17,    37,    -1,    49,    16,    37,    -1,    49,     6,    37,
      -1,    38,    -1,    39,    -1,    39,    18,    36,    19,    38,
      -1,    39,    20,    36,    19,    38,    -1,    39,    21,    36,
      19,    38,    -1,    40,    -1,    39,     9,    40,    -1,    41,
      -1,    40,    11,    41,    -1,    42,    -1,    41,    10,    42,
      -1,    43,    -1,    42,     8,    43,    -1,    44,    -1,    43,
       7,    44,    -1,    44,    22,    45,    -1,    44,    23,    45,
      -1,    45,    -1,    45,    24,    46,    -1,    45,    25,    46,
      -1,    45,    26,    46,    -1,    46,    -1,    47,    27,    46,
      -1,    47,    -1,    22,    47,    -1,    23,    47,    -1,    28,
      47,    -1,    48,    -1,     5,    -1,    14,    36,    15,    -1,
      49,    -1,     3,    14,    15,    -1,     3,    14,    36,    15,
      -1,     3,    -1,    29,     3,    -1,    18,     3,    -1
  };

  /* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
     YYRHS.  */
  const unsigned char
  Parser::yyprhs_[] =
  {
         0,     0,     3,     6,     7,    11,    15,    18,    21,    23,
      25,    28,    31,    38,    39,    41,    43,    47,    49,    53,
      57,    61,    63,    65,    71,    77,    83,    85,    89,    91,
      95,    97,   101,   103,   107,   109,   113,   117,   121,   123,
     127,   131,   135,   137,   141,   143,   146,   149,   152,   154,
     156,   160,   162,   166,   171,   173,   176
  };

  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
  const unsigned short int
  Parser::yyrline_[] =
  {
         0,    96,    96,    97,   101,   102,   103,   104,   105,   106,
     107,   108,   112,   119,   120,   124,   128,   136,   137,   145,
     149,   166,   170,   171,   175,   179,   186,   187,   194,   195,
     202,   203,   209,   210,   217,   218,   227,   231,   235,   239,
     243,   247,   251,   254,   258,   262,   263,   267,   273,   277,
     280,   281,   284,   287,   293,   296,   299
  };

  // Print the state stack on the debug stream.
  void
  Parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (state_stack_type::const_iterator i = yystate_stack_.begin ();
	 i != yystate_stack_.end (); ++i)
      *yycdebug_ << ' ' << *i;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  Parser::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    /* Print the symbols being reduced, and their result.  */
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
	       << " (line " << yylno << "), ";
    /* The symbols being reduced.  */
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
		       yyrhs_[yyprhs_[yyrule] + yyi],
		       &(yysemantic_stack_[(yynrhs) - (yyi + 1)]),
		       &(yylocation_stack_[(yynrhs) - (yyi + 1)]));
  }
#endif // YYDEBUG

  /* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
  Parser::token_number_type
  Parser::yytranslate_ (int t)
  {
    static
    const token_number_type
    translate_table[] =
    {
           0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      13,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    28,     2,    18,    29,    26,     2,     2,
      14,    15,    24,    22,    17,    23,     2,    25,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    19,    12,
       2,    16,     2,    21,    20,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    27,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11
    };
    if ((unsigned int) t <= yyuser_token_number_max_)
      return translate_table[t];
    else
      return yyundef_token_;
  }

  const int Parser::yyeof_ = 0;
  const int Parser::yylast_ = 111;
  const int Parser::yynnts_ = 20;
  const int Parser::yyempty_ = -2;
  const int Parser::yyfinal_ = 2;
  const int Parser::yyterror_ = 1;
  const int Parser::yyerrcode_ = 256;
  const int Parser::yyntokens_ = 30;

  const unsigned int Parser::yyuser_token_number_max_ = 266;
  const Parser::token_number_type Parser::yyundef_token_ = 2;

} // namespace yy

#line 304 "parser.y"

void yy::Parser::error(const location_type &location,
                       const std::string &m) {
	env.error(location.begin, m);
}

int yylex(yy::Parser::semantic_type *yylval,
          yy::Parser::location_type *yylloc,
          calc::Lexer &lexer) {
	return lexer.nextToken(*yylval, *yylloc);
}

