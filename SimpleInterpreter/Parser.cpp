#include "Parser.hpp"
using namespace Interpreter;
using namespace Parser;
using namespace Detail;

ShuntingYardParser::ShuntingYardParser(const Tokens &tokens) : m_current(tokens.begin()), m_end(tokens.end())
{
}

void ShuntingYardParser::Parse()
{
    for (; m_current != m_end; ++m_current)
    {
        ParseCurrentToken();
    }
    PopToOutputUntil([this]()
                     { return StackHasNoOperators(); });
}

void ShuntingYardParser::ParseCurrentToken()
{
    if (m_current->Type() == TokenType::Operator)
        ParseOperator();
    else if (m_current->Type() == TokenType::Number)
        ParseNumber();
    else
        throw std::out_of_range("TokenType");
}

void ShuntingYardParser::ParseOperator()
{
    const Operator currOp = *m_current;
    if (currOp == Operator::LParen)
        PushCurrentOperatorToStack();
    else if (currOp == Operator::RParen)
    {
        PopToOutputUntil([this]()
                         { return LeftParenOnTop(); });
        PopLeftNoParen();
    }
    else
    {
        PopToOutputUntil([this]()
                         { return LeftParenOnTop() || OperatorWithLessPrecedenceOnTop(); });
        PushCurrentOperatorToStack();
    }
}

void ShuntingYardParser::PushCurrentOperatorToStack()
{
    m_stack.push_back(*m_current);
}

template <class T>
void ShuntingYardParser::PopToOutputUntil(T whenToEnd)
{
    while (!m_stack.empty() && !whenToEnd())
    {
        m_output.push_back(m_stack.back());
        m_stack.pop_back();
    }
}

bool ShuntingYardParser::LeftParenOnTop() const
{
    return static_cast<Operator>(m_stack.back()) == Operator::LParen;
}

void ShuntingYardParser::PopLeftNoParen()
{
    if (m_stack.empty() || m_stack.back() != Operator::LParen)
    {
        throw std::logic_error("Opening paren not found");
    }
    m_stack.pop_back();
}

bool ShuntingYardParser::OperatorWithLessPrecedenceOnTop() const
{
    return PrecendenceOf(m_stack.back()) < PrecendenceOf(*m_current);
}

void ShuntingYardParser::ParseNumber()
{
    m_output.push_back(*m_current);
}

bool ShuntingYardParser::StackHasNoOperators() const
{
    if (m_stack.back() == Token(Operator::LParen))
        throw std::logic_error("Closing paren not found");
    return false;
}

const Tokens &ShuntingYardParser::Result() const
{
    return m_output;
}