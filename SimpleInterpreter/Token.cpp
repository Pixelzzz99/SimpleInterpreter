#include "Token.hpp"
using namespace Interpreter;

Token::Token(Operator op) : m_type(TokenType::Operator), m_operator(op)
{
}

Token::Token(double num) : m_type(TokenType::Number), m_number(num)
{
}

TokenType Token::Type() const
{
    return m_type;
}