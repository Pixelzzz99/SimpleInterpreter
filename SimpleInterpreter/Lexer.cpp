#include "Lexer.hpp"
using namespace Interpreter;
using namespace Lexer;
using namespace Detail;

Tokenizer::Tokenizer(const std::wstring &expr) : m_current(expr.c_str())
{
}

void Tokenizer::Tokenize()
{
    while (!EndOfExpression())
    {
        if (IsNumber())
        {
            ScanNumber();
        }
        else if (IsOperator())
        {
            ScanOperator();
        }
        else
            MoveNext();
    }
}

bool Tokenizer::EndOfExpression() const
{
    return *m_current == L'\0';
}

bool Tokenizer::IsNumber() const
{
    return iswdigit(*m_current) != 0;
}

void Tokenizer::ScanNumber()
{
    wchar_t *end = nullptr;
    m_result.push_back(wcstod(m_current, &end));
    m_current = end;
}

bool Tokenizer::IsOperator() const
{
    auto allOperators = {
        Operator::Plus,
        Operator::Minus,
        Operator::Multiply,
        Operator::Divide,
        Operator::LParen,
        Operator::RParen,
        Operator::LBraces,
        Operator::RBraces,
        Operator::LSquareBracket,
        Operator::RSquareBracket,

    };
    return std::any_of(allOperators.begin(), allOperators.end(), [this](Operator o)
                       { return *m_current == static_cast<wchar_t>(o); });
}

void Tokenizer::ScanOperator()
{
    m_result.push_back(static_cast<Operator>(*m_current));
    MoveNext();
}

void Tokenizer::MoveNext()
{
    ++m_current;
}

const Tokens &Tokenizer::Result() const
{
    return m_result;
}
