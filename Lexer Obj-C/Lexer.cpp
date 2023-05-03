using namespace std;
#include "Lexer.h"
#include "Token.h"

std::string keywords[] = { "auto",			"break",		"case",			"char",					"const",
						"continue",			"default",		"do",			"double",				"NSObject", 
						"property",			"weak",			"else",			"enum",					"extern", 
						"float",			"for",			"goto",			"if",					"int", 
						"protocol",			"NSInteger",	"nonatomic",	"unsafe_unretained",	"long", 
						"register",			"return",		"return",		"short",				"signed", 
						"sizeof",			"static",		"struct",		"interface",			"NSNumber", 
						"retain",			"readwrite",	"switch",		"typedef",				"union", 
						"unsigned",			"void",			"volatile",		"while",				"_Packed", 
						"implementation",	"CGFloat",		"strong",		"readonly"};

Lexer::Lexer(string path) {
	file.open(path);
	if (!file.is_open()) {
		cout << "Couldn't open file";
	}
}

Lexer::~Lexer() {
	file.close();
}

bool Lexer::is_number(char c) {
	return std::isalnum(static_cast<unsigned char>(c)) && !is_letter(c);
}

bool Lexer::is_letter(char c) {
	return std::isalpha(static_cast<unsigned char>(c));
}

bool Lexer::is_space(char c) {
	switch (c) {
	case ' ':
	case '\t':
	case '\r':
	case '\n':
		return true;
	default:
		return false;
	}
}

Token Lexer::identifier() {
	std::string str = "";
	str += file.get();
	while (is_letter(file.peek())) {
		str += file.get();
	}
	return Token(Token::Kind::Identifier, str);
}

Token Lexer::number() {
	std::string str = "";
	str += file.get();
	bool is_float = false;
	while (is_number(file.peek()) || file.peek() == '.') {
		if (is_float && file.peek() == '.') {
			return Token(Token::Kind::Unexpected, str);
		}
		if (file.peek() == '.') {
			is_float = true;

		}
		str += file.get();
	}
	return Token(Token::Kind::Number, str);
}

Token Lexer::next() {
	while (is_space(file.peek())) file.get();

	char c = file.peek();
	if (file.eof()) {
		return Token(Token::Kind::End, "");
	}
	else if (is_letter(c)) {
		Token token = identifier();
		int arr_length = sizeof(keywords) / sizeof(std::string);
		for (int i = 0; i < arr_length; i++) {
			if (token.get_str() == keywords[i]) {
				return Token(Token::Kind::Keyword, token.get_str());
			}
		}
		return token;
	}
	else if (is_number(c)) {
		return number();
	}
	else {
		file.get();
		switch (c)
		{
		case '>':
			if (file.peek() == '=') {
				file.get();
				return Token(Token::Kind::GreaterEquals, ">=");
			}
			else if (file.peek() == '>') {
				file.get();
				if (file.peek() == '=') {
					file.get();
					return Token(Token::Kind::RightShiftAssignment, ">>=");
				}
				else
				{
					return Token(Token::Kind::RightShift, ">>");
				}
			}
			else
			{
				return Token(Token::Kind::GreaterThan, ">");
			}
			break;
		case '<':
			if (file.peek() == '=') {
				file.get();
				return Token(Token::Kind::LessEquals, "<=");
			}
			else if (file.peek() == '<') {
				file.get();
				if (file.peek() == '=') {
					file.get();
					return Token(Token::Kind::LeftShiftAssignment, "<<=");
				}
				else
				{
					return Token(Token::Kind::LeftShift, "<<");
				}
			}
			else
			{
				return Token(Token::Kind::LessThan, "<");
			}
			break;
		case '=':
			if (file.peek() == '=') {
				file.get();
				return Token(Token::Kind::Equals, "==");
			}
			else
			{
				return Token(Token::Kind::Assignment, "=");
			}
			break;
		case '+':
			if (file.peek() == '=') {
				file.get();
				return Token(Token::Kind::AddAssignment, "+=");
			}
			else
			{
				return Token(Token::Kind::Addition, "+");
			}
			break;
		case '-':
			if (file.peek() == '=') {
				file.get();
				return Token(Token::Kind::MinusAssignment, "-=");
			}
			else
			{
				return Token(Token::Kind::Substraction, "-");
			}
			break;
		case '*':
			if (file.peek() == '=') {
				file.get();
				return Token(Token::Kind::MultiplicationAssignment, "*=");
			}
			else
			{
				return Token(Token::Kind::Multiplication, "*");
			}
			break;
		case '/':
			if (file.peek() == '/') {
				std::string str = "/";
				str += file.get();
				while (file.peek() != '\n' && !file.eof()) {
					str += file.get();
				}
				return Token(Token::Kind::Comment, str);
			}
			else if (file.peek() == '=') {
				file.get();
				return Token(Token::Kind::DivisionAssignment, "/=");
			}
			else if (file.peek() == '*') {
				std::string str = "/";
				str += file.get();
				while (file.peek() && !file.eof()) {
					if (file.peek() == '*') {
						str += file.get();
						if (file.peek() == '/') {
							str += file.get();
							return Token(Token::Kind::Multicomment, str);
						}
						continue;
					}
					str += file.get();
				}
				return Token(Token::Kind::Unexpected, "");
			}
			else
			{
				return Token(Token::Kind::Division, "/");
			}
			break;
		case '%':
			if (file.peek() == '=') {
				file.get();
				return Token(Token::Kind::ModulusAssignment, "%=");
			}
			else
			{
				return Token(Token::Kind::Modulus, "%");
			}
			break;
		case '!':
			if (file.peek() == '=') {
				file.get();
				return Token(Token::Kind::NotEquals, "!=");
			}
			else
			{
				return Token(Token::Kind::Not, "!");
			}
			break;
		case '(':
			return Token(Token::Kind::LeftParen, "(");
			break;
		case ')':
			return Token(Token::Kind::RightParen, ")");
			break;
		case '[':
			return Token(Token::Kind::LeftSquare, "[");
			break;
		case ']':
			return Token(Token::Kind::RightSquare, "]");
			break;
		case '{':
			return Token(Token::Kind::LeftCurly, "{");
			break;
		case '}':
			return Token(Token::Kind::RightCurly, "}");
			break;
		case ',':
			return Token(Token::Kind::Comma, ",");
			break;
		case ':':
			return Token(Token::Kind::Colon, ":");
			break;
		case ';':
			return Token(Token::Kind::Semicolon, ";");
			break;
		case '\'':
		{
			std::string str = "'";
			while (file.peek() && !file.eof()) {
				if (file.peek() == '\'') {
					str += file.get();
					return Token(Token::Kind::Char, str);
				}
				str += file.get();
			}
			return Token(Token::Kind::Unexpected, str);
			break;
		}
		case '"':
		{
			std::string str = "\"";
			while (file.peek() && !file.eof()) {
				if (file.peek() == '"') {
					str += file.get();
					return Token(Token::Kind::String, str);
				}
				str += file.get();
			}
			return Token(Token::Kind::Unexpected, str);
			break;
		}
		case '|':
			if (file.peek() == '|') {
				file.get();
				return Token(Token::Kind::LogicalOr, "||");
			}
			else if (file.peek() == '=') {
				file.get();
				return Token(Token::Kind::LogicalOrAssignment, "|=");
			}
			else
			{
				return Token(Token::Kind::BitOr, "|");
			}
			break;
		case '&':
			if (file.peek() == '&') {
				file.get();
				return Token(Token::Kind::LogicalAnd, "&&");
			}
			else if (file.peek() == '=') {
				file.get();
				return Token(Token::Kind::BitAndAssignment, "&=");
			}
			else
			{
				return Token(Token::Kind::BitAnd, "&");
			}
			break;
		case '^':
			if (file.peek() == '=') {
				file.get();
				return Token(Token::Kind::BitXORAssignment, "^=");
			}
			else
			{
				return Token(Token::Kind::BitXOR, "^");
			}
			break;
		case '~':
			return Token(Token::Kind::BitNOT, "~");
			break;
		case '.':
			return Token(Token::Kind::Dot, ".");
			break;
		default:
			break;
		}
	}
}
