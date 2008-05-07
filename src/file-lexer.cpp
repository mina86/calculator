/** \file
 * Lexer reading from FILE stream implementation.
 * $Id: file-lexer.cpp,v 1.9 2008/05/07 17:30:27 mina86 Exp $
 */
#include "math.hpp"
#include "exceptions.hpp"
#include "file-lexer.hpp"

#include <limits>


namespace calc {

const std::string FILELexer::stdin_filename("<stdin>");

FILELexer::~FILELexer() {
	if (closeStream) {
		fclose(stream);
	}
}


FILE *FILELexer::openFile(const char *filename) {
	FILE *fd = fopen(filename, "r");
	if (!fd) {
		throw IOException(std::string(filename) + ": could not open file");
	}
	return fd;
}


int FILELexer::getchar() {
	int ch = ::getc(stream);
	previous.line = current.line;
	previous.column = current.column;
	if (ch == '\n') {
		++current.line;
		current.column = 1;
	} else {
		++current.column;
	}
	return ch;
}

void FILELexer::ungetchar(int ch) {
	if (ch != EOF) {
		current.line = previous.line;
		current.column = previous.column;
		ungetc(ch, stream);
	}
}


int FILELexer::nextToken(yy::Parser::semantic_type &value,
                         yy::location &location) {
	int ch;

	for(;;){
		while ((ch = getchar()) != EOF && ch != '\n' && isspace(ch)) /*nop*/;
		location.begin = previous;

		if (ch != '\\') break;
		ch = getchar();
		if (ch != '\n') {
			location.end = current;
			return ch;
		}
	}

	/* Identifier or 'e' */
	if (isalpha(ch) || ch == '_') {
		std::string id;
		do {
			id += (char)ch;
		} while ((ch = getchar()) == '_' || isalpha(ch) || isdigit(ch));

		ungetchar(ch);
		location.end = current;

		if (id == "inf") {
			value.num = std::numeric_limits<calc::real>::infinity();
			return yy::Parser::token::NUMBER;
		} else {
			value.var.name = new std::string(id);
			return yy::Parser::token::ID;
		}
	}

	/* ^, ^= or ^^ */
	if (ch == '^') {
		switch (ch = getchar()) {
		case '=': return yy::Parser::token::POW_EQ;
		case '^': return yy::Parser::token::XOR;
		default: ungetchar(ch); return '^';
		}
	}

	/* #= maybe? */
	if (ch == '+' || ch == '-' || ch == '*' || ch == '/' ||
	    ch == '>' || ch == '<' || ch == '=' || ch == '!') {
		int c = getchar();
		if (c != '=') {
			ungetchar(c);
			return ch;
		}
		switch (ch) {
		case '+': return yy::Parser::token::ADD_EQ;
		case '-': return yy::Parser::token::SUB_EQ;
		case '*': return yy::Parser::token::MUL_EQ;
		case '/': return yy::Parser::token::DIV_EQ;
		case '^':
		case '>': return yy::Parser::token::GE;
		case '<': return yy::Parser::token::LE;
		case '=': return yy::Parser::token::EQ;
		case '!': return yy::Parser::token::NE;
		}
	}

	/* Logical operator? */
	if (ch == '&' || ch == '|') {
		int c = getchar();
		if (c != ch) {
			ungetchar(c);
			return ch;
		}
		switch (ch) {
		case '|': return yy::Parser::token::OR;
		case '&': return yy::Parser::token::AND;
		}
	}

	/* Not a number */
	if (!isdigit(ch) && ch != '.') {
		location.end = current;
		if (ch == ',') {
			int c;
			while ((c = getchar()) != EOF && isspace(c)) /*nop*/;
			ungetchar(c);
		}
		return ch;
	}

	std::string str;
	if (ch == '.') {
		ch = getchar();
		ungetchar(ch);
		if (!isdigit(ch)) {
			return '.';
		}
		str += '0';
		ch = '.';
	} else {
		str += ch;
		for (ch = getchar(); isdigit(ch) || ch == '_'; ch = getchar()) {
			if (ch != '_') str += ch;
		}
	}

	/* Fractional part */
	if (ch == '.') {
		ch = getchar();
		if (isdigit(ch)) {
			str += '.';
			do {
				if (ch != '_') str += ch;
			} while(isdigit(ch = getchar()) || ch == '_');
		}
	}

	/* Exp */
	if (ch == 'e' || ch == 'E') {
		str += ch;
		do {
			ch = getchar();
		} while (ch == '_');

		if (ch == '+' || ch == '-') {
			str += ch;
			ch = getchar();
		}

		for (str += '0'; isdigit(ch) || ch == '_'; ch = getchar()) {
			if (ch != '_') str += ch;
		}
	}

	/* Return number */
	ungetchar(ch);
	location.end = current;
	value.num = calc::m::ator(str.c_str());
	return yy::Parser::token::NUMBER;
}


}
