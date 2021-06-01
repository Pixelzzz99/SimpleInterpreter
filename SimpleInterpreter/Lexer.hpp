#pragma once
#include "Interpreter.hpp"
#include "Token.hpp"

namespace Interpreter
{
	namespace Lexer
	{
		namespace Detail
		{
			class Tokenizer
			{
			private:
				const wchar_t *m_current;
				Tokens m_result;
				bool EndOfExpression() const;
				bool IsNumber() const;
				void ScanNumber();
				bool IsOperator() const;
				void ScanOperator();
				void MoveNext();

			public:
				Tokenizer(const std::wstring &expr);
				void Tokenize();
				const Tokens &Result() const;
			};
		}

		inline Tokens Tokenize(const std::wstring &expr)
		{
			Detail::Tokenizer tokenizer(expr);
			tokenizer.Tokenize();
			return tokenizer.Result();
		}
	}
}