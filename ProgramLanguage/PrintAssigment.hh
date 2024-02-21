#pragma once
#include <iostream>

#include "Expression.hh"

#include "Statement.hh"



class PrintAssigment : public Statement
{
public:

	PrintAssigment( Expression* expression )
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