#pragma once

#include "Statement.hh"
#include "Expression.hh"

#include <exception>


class BreakStatement : public Statement
{

public:

	void execute() override
	{
        throw std::runtime_error("Break");
	}
};