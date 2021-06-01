#pragma once
#include <algorithm>
#include <functional>
#include <iterator>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

namespace Interpreter
{
	class Token;
   
	enum class Operator : wchar_t
    {
        Plus = L'+',
        Minus = L'-',
        Multiply = L'*',
        Divide = L'/',
        LParen = L'(',
        RParen = L')',
        LBraces = L'{',
        RBraces = L'}',
        LSquareBracket = L'[',
        RSquareBracket = L']',
    };

    inline std::wstring ToString(const Operator &token)
    {
        return {static_cast<wchar_t>(token)};
    }

    enum class TokenType
    {
        Operator,
        Number
    };

    inline std::wstring ToString(const TokenType &type)
    {
        if (type == TokenType::Operator)
            return L"Operator";
        if (type == TokenType::Number)
            return L"Number";
        throw std::out_of_range("TokenType");
    }

    typedef std::vector<Token> Tokens;
    
}