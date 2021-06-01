#pragma once
#include "Interpreter.hpp"
#include "Token.hpp"

namespace Interpreter
{
    namespace Evaluator
    {
        namespace Detail
        {
            class StackEvaluator
            {
            private:
                Tokens::const_iterator m_current;
                Tokens::const_iterator m_end;
                std::vector<double> m_stack;

                void EvaluateCurrentToken();
                void EvaluateOperator();
                void EvaluateNumber();
                double PopOperand();

                const std::function<double(double, double)> &BinaryFunctionFor(Operator op);

            public:
                StackEvaluator(const Tokens &tokens);
                void Evaluate();
                double Result() const;
            };
        }

        inline double Evaluate(const Tokens &tokens)
        {
            Detail::StackEvaluator evaluator(tokens);
            evaluator.Evaluate();
            return evaluator.Result();
        }
    }
}