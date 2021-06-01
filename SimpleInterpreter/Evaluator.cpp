#include "Evaluator.hpp"
using namespace Interpreter;
using namespace Evaluator;
using namespace Detail;

StackEvaluator::StackEvaluator(const Tokens &tokens) : m_current(tokens.cbegin()), m_end(tokens.cend())
{
}

void StackEvaluator::Evaluate()
{
    for (; m_current != m_end; ++m_current)
    {
        EvaluateCurrentToken();
    }
}

double StackEvaluator::Result() const
{
    return m_stack.empty() ? 0 : m_stack.back();
}

void StackEvaluator::EvaluateCurrentToken()
{
    if (m_current->Type() == TokenType::Operator)
        EvaluateOperator();
    else if (m_current->Type() == TokenType::Number)
        EvaluateNumber();
    else
        throw std::out_of_range("TokenType");
}

void StackEvaluator::EvaluateOperator()
{
    double second = PopOperand();
    double first = PopOperand();
    m_stack.push_back(BinaryFunctionFor(*m_current)(first, second));
}

void StackEvaluator::EvaluateNumber()
{
    m_stack.push_back(*m_current);
}

double StackEvaluator::PopOperand()
{
    double back = m_stack.back();
    m_stack.pop_back();
    return back;
}

const std::function<double(double, double)> &StackEvaluator::BinaryFunctionFor(Operator op)
{
    static const std::map<Operator, std::function<double(double, double)>> functions{
        {Operator::Plus, std::plus<double>()},
        {Operator::Minus, std::minus<double>()},
        {Operator::Multiply, std::multiplies<double>()},
        {Operator::Divide, std::divides<double>()},
    };
    auto found = functions.find(op);
    if (found == functions.cend())
    {
        throw std::logic_error("Operator not found");
    }
    return found->second;
}