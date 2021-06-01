#pragma once

#include "Interpreter.hpp"
#include "Evaluator.hpp"
#include "Lexer.hpp"
#include "Parser.hpp"

namespace Interpreter
{
	namespace InterpreterExpr
	{
		namespace InterpreterExpr
		{
			inline double InterpreterExpression(const std::wstring& expression)
			{
				return Evaluator::Evaluate(Parser::Parse(Lexer::Tokenize(expression)));
			}
		}
	}
}


