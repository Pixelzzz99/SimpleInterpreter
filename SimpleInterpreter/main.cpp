#include <iostream>
#include <conio.h>
#include "InterpreterExpr.h"

using namespace Interpreter;

int main()
{
	for (int i = 0;; ++i)
	{
		int key_press = _getch();
		if(key_press == 27)
		{
			break;
		}
		std::wstring expr;
		std::wcin >> expr;
		double result = InterpreterExpr::InterpreterExpr::InterpreterExpression(expr);

		std::cout << ">>>"<< result << std::endl;
	}
	
	return 0;
}