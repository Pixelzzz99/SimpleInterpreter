#pragma once
#include "Interpreter.hpp"

namespace Interpreter
{
    class Token
    {
    private:
        TokenType m_type;
        Operator m_operator;
        double m_number;

    public:
        Token(Operator op);
        operator Operator() const
        {
            if (m_type != TokenType::Operator)
                throw std::logic_error("Should be operator token");
            return m_operator;
        }

        Token(double num);

        operator double() const
        {
            if (m_type != TokenType::Number)
                throw std::logic_error("Should be number token");
            return m_number;
        }

        friend bool operator==(const Token &left, const Token &right)
        {
            if (left.m_type == right.m_type)
            {
                if (left.m_type == TokenType::Operator)
                    return left.m_operator == right.m_operator;
                if (left.m_type == TokenType::Number)
                    return left.m_number == right.m_number;
                throw std::out_of_range("TokenType");
            }
            return false;
        }

        TokenType Type() const;
    };

    inline std::wstring ToString(const Token& token)
    {
        if (token.Type() == TokenType::Number)
			return std::to_wstring(static_cast<double>(token));
		if (token.Type() == TokenType::Operator)
			return ToString(static_cast<Operator>(token));
		return L"Unknown token";
    }
}