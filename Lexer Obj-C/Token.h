#include <string>
#include <iostream>
#pragma once
#ifndef TOKEN
#define TOKEN


class Token {
public:
    enum class Kind {
        Number,                     // 0-9
        Identifier,                 // example: "num"
        LeftParen,                  // (            
        RightParen,                 // )            
        LeftSquare,                 // [            
        RightSquare,                // ]            
        LeftCurly,                  // {            
        RightCurly,                 // }            
        LessThan,                   // <
        LessEquals,                 // <=
        GreaterThan,                // >
        GreaterEquals,              // >=
        Equals,                     // =
        Not,                        // !
        NotEquals,                  // !=
        Assignment,                 // ==
        AddAssignment,              // +=
        Addition,                   // +
        MinusAssignment,            // -=
        Substraction,               // -
        Multiplication,             // *
        MultiplicationAssignment,   // *=
        Division,                   // /
        DivisionAssignment,         // /=
        Modulus,                    // %
        ModulusAssignment,          // %=
        Dot,                        // .            
        Comma,                      // ,            
        Colon,                      // :            
        Semicolon,                  // ;            
        Char,                       // '            
        String,                     // "            
        Comment,                    // //
        Multicomment,               // /*---*/
        BitOr,                      // |            
        LogicalOr,                  // ||
        LogicalOrAssignment,        // |=
        BitAnd,                     // &
        LogicalAnd,                 // &&
        BitAndAssignment,           // &=
        BitXOR,                     // ^
        BitXORAssignment,           // ^=
        BitNOT,                     // ~
        End,                        //
        LeftShift,                  // <<
        LeftShiftAssignment,        // <<=
        RightShift,                 // >>
        RightShiftAssignment,       // >>=
        Unexpected,                 // 
        Keyword,                    // example: "auto"
        Preprocessor,               // #define
    };

    

    Token(Token::Kind kind, std::string str) {
        this->m_kind = kind;
        this->str = str;
    };

    std::string get_str() {
        return this->str;
    }
    
    Kind get_kind() {
        return this->m_kind;
    }

    bool is(Kind kind) const noexcept { return m_kind == kind; }

    bool is_not(Kind kind) {
        return m_kind != kind;
    };

    bool is_one_of(Kind k1, Kind k2) const noexcept { return is(k1) || is(k2); }

    template <typename... Ts>
    bool is_one_of(Kind k1, Kind k2, Ts... ks) const noexcept {
        return is(k1) || is_one_of(k2, ks...);
    }
private:
    Kind m_kind;
    std::string str;
};


#endif // !Token
