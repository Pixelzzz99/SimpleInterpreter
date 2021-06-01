#pragma once
#include "Interpreter.hpp"
#include "Token.hpp"

namespace Interpreter
{
    namespace Parser
    {
        inline int PrecendenceOf(Operator op)
        {
            return (op == Operator::Multiply || op == Operator::Divide) ? 1 : 0;
        }

        namespace Detail
        {
            class ShuntingYardParser
            {
            private:
                Tokens::const_iterator m_current;
                Tokens::const_iterator m_end;
                Tokens m_output;
                Tokens m_stack;

                void ParseCurrentToken();
                void ParseOperator();

                void PushCurrentOperatorToStack();

                template <class T>
                void PopToOutputUntil(T whenToEnd);

                bool LeftParenOnTop() const;

                void PopLeftNoParen();

                bool OperatorWithLessPrecedenceOnTop() const;

                void ParseNumber();

                static bool StackIsEmpty() { return false; }

                bool StackHasNoOperators() const;

            public:
                ShuntingYardParser(const Tokens& tokens);
                void Parse();
                const Tokens& Result() const;
            };
        }

        inline Tokens Parse(const Tokens& tokens)
        {
            Detail::ShuntingYardParser parser(tokens);
            parser.Parse();
            return parser.Result();
        }

    }
}