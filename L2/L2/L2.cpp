// L2.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "LongValue.h"
#include "Calculator.h"

int main()
{
	/*CLongValue value("15630126455");
	CLongValue value2("11897654123");
	CLongValue res3 = value - value2;
	res3.Output();*/
	CCalculator calc;
	calc.AddExpression("6666666666 + 8963459789");
	calc.AddExpression("8963459789 * 6666666666");
	calc.AddExpression("15630126455 - 11897654123");
	calc.AddExpression("59756398587357693474 / 6666666666");
	calc.CountAll();
	calc.OutputResults();
    return 0;
}

