#include <string>
#include <iostream>
#include <fstream>
#include "Token.h"

#pragma once
#ifndef LEXER_H
#define LEXER_H


class Lexer
{
private:
	ifstream file;
public:

	Lexer(string);
	~Lexer();
	bool is_number(char);
	bool is_letter(char);
	bool is_space(char c);
	Token identifier();
	Token number();
	Token preprocessor();
	char esc_sequence();
	Token string();
	Token charecter();
	Token next();
	
};

#endif
