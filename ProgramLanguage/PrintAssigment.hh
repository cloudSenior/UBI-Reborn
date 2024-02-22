#pragma once
#include <iostream>

#include "Expression.hh"

#include "Statement.hh"



class PrintStatement : public Statement
{
public:

	PrintStatement( Expression* expression )
	{
		this->expression = expression;
	}

	void execute() override
	{
        std::cout << expression->eval()->asString();
	}

private:
	Expression* expression;
};