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
 * Lexer reading from FILE stream implementation.
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


int FILELexer::getChar() {
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

/** Returns \c true iff \a ch is an octal digit. */
static inline bool isodigit(int ch) {
	return ch != EOF && isdigit(ch) && ch != '8' && ch != '9';
}

char FILELexer::getDecodedChar() {
	int ch = getChar();
	switch (ch) {
	case EOF: return 0;

	case 'a': return '\a';
	case 'b': return '\b';
	case 'f': return '\f';
	case 'n': return '\n';
	case 'r': return '\r';
	case 't': return '\t';
	case 'v': return '\v';

	case 'c':
		ch = getChar();
		return ch != EOF ? ch & 0x1f : 0;

	case 'x': {
		char buf[3] = { 0, 0, 0 };
		unsigned i = 0;
		while (i < 2 && isxdigit(ch = getChar())) {
			buf[i++] = ch;
		}
		if (i != 2) {
			ungetChar(ch);
		}
		return i ? strtol(buf, 0, 16) : 0;
	}

	case '0': case '1': case '2': case '3':
	case '4': case '5': case '6': case '7': {
		char buf[4] = { 0, 0, 0, 0 };
		unsigned i = 0;
		while (i < 3 && isodigit(ch = getChar())) {
			buf[i++] = ch;
		}
		if (i != 3) {
			ungetChar(ch);
		}
		return i ? strtol(buf, 0, 8) & 0xff : 0;
	}


	default:
		return ch;
	}
}


void FILELexer::ungetChar(int ch) {
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
		while ((ch = getChar()) != EOF && ch != '\n' && isspace(ch)) /*nop*/;
		location.begin = previous;

		if (ch != '\\') break;
		ch = getChar();
		if (ch != '\n') {
			location.end = current;
			return ch;
		}
	}

	/* Identifier */
	if (isalpha(ch) || ch == '_') {
		std::string id;
		do {
			id += (char)ch;
		} while ((ch = getChar()) == '_' || isalpha(ch) || isdigit(ch));

		ungetChar(ch);
		location.end = current;

		if (id == "inf") {
			value.num = std::numeric_limits<calc::real>::infinity();
			return yy::Parser::token::NUMBER;
		} else if (id == "define") {
			return yy::Parser::token::DEFINE;
		} else {
			value.var.name = new std::string(id);
			return yy::Parser::token::ID;
		}
	}

	/* ^, ^= or ^^ */
	if (ch == '^') {
		switch (ch = getChar()) {
		case '=': /* ^= */
			value.setop = yy::Parser::semantic_type::SET_POW;
			return yy::Parser::token::SET_OP;
		case '^': /* ^^ */
			return yy::Parser::token::XOR;
		default:
			ungetChar(ch);
			return '^';
		}
	}

	/* >, <, >=, <=, >~ or <~ */
	if (ch == '>' || ch == '<') {
		int c = getChar();
		value.flags = ch == '<' ? yy::REL_SWITCH : 0;
		switch (c) {
		case '~': value.flags |= yy::REL_FUZZY; break;
		case '=': value.flags ^= yy::REL_SWITCH | yy::REL_NOT; break;
		default : ungetChar(c); break;
		}
		return yy::Parser::token::REL_OP;
	}

	/* =, !, ==, !=, =~ or !~ */
	if (ch == '=' || ch == '!') {
		int c = getChar();
		switch (c) {
		case '~': value.flags = yy::CMP_FUZZY; break;
		case '=': value.flags = 0; break;
		default : ungetChar(c); return ch;
		}
		if (ch == '!') {
			value.flags |= yy::CMP_NOT;
		}
		return yy::Parser::token::CMP_OP;
	}

	/* # or #= */
	if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%') {
		int c = getChar();
		if (c != '=') {
			ungetChar(c);
			return ch;
		}

		switch (ch) {
		case '+': value.setop = yy::Parser::semantic_type::SET_ADD; break;
		case '-': value.setop = yy::Parser::semantic_type::SET_SUB; break;
		case '*': value.setop = yy::Parser::semantic_type::SET_MUL; break;
		case '/': value.setop = yy::Parser::semantic_type::SET_DIV; break;
		case '%': value.setop = yy::Parser::semantic_type::SET_MOD; break;
		default : assert(0);
		}
		return yy::Parser::token::SET_OP;
	}

	/* Logical operator? */
	if (ch == '&' || ch == '|') {
		int c = getChar();
		if (c != ch) {
			ungetChar(c);
			return ch;
		}
		switch (ch) {
		case '|': return yy::Parser::token::OR;
		case '&': return yy::Parser::token::AND;
		}
	}

	/* #, ## or #! */
	if (ch == '#') {
		int c = getChar();
		switch (c) {
		case '#': return yy::Parser::token::IT;
		case '!': return yy::Parser::token::LAST;
		default : ungetChar(c); return ch;
		}
	}

	/* String */
	if (ch == '"' || ch == '\'') {
		int end = ch;
		std::string str;
		while ((ch = getChar()) != end && ch != EOF) {
			str += ch == '\\' ? getDecodedChar() : (char)ch;
		}

		value.var.name = new std::string(str);
		return yy::Parser::token::STRING;
	}

	/* Not a number */
	if (!isdigit(ch) && ch != '.') {
		location.end = current;
		if (ch == ',') {
			int c;
			while ((c = getChar()) != EOF && isspace(c)) /*nop*/;
			ungetChar(c);
		}
		return ch;
	}

	std::string str;
	if (ch == '.') {
		ch = getChar();
		ungetChar(ch);
		if (!isdigit(ch)) {
			return '.';
		}
		str += '0';
		ch = '.';
	} else {
		str += ch;
		for (ch = getChar(); isdigit(ch) || ch == '_'; ch = getChar()) {
			if (ch != '_') str += ch;
		}
	}

	/* Fractional part */
	if (ch == '.') {
		ch = getChar();
		if (isdigit(ch)) {
			str += '.';
			do {
				if (ch != '_') str += ch;
			} while(isdigit(ch = getChar()) || ch == '_');
		}
	}

	/* Exp */
	if (ch == 'e' || ch == 'E') {
		str += ch;
		do {
			ch = getChar();
		} while (ch == '_');

		if (ch == '+' || ch == '-') {
			str += ch;
			ch = getChar();
		}

		for (str += '0'; isdigit(ch) || ch == '_'; ch = getChar()) {
			if (ch != '_') str += ch;
		}
	}

	/* Return number */
	ungetChar(ch);
	location.end = current;
	value.num = calc::m::ator(str.c_str());
	return yy::Parser::token::NUMBER;
}


}
