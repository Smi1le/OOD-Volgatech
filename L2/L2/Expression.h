#pragma once
#include "LongValue.h"


struct SExpression
{
	CLongValue firstArg;
	CLongValue secondArg;
	TypeOperand typeOperand;
	CLongValue result;
};