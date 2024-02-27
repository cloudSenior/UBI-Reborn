#pragma once

#include "Statement.hh"
#include "Expression.hh"

#include <stdexcept>


class ContinueStatement : public Statement
{

public:

	void execute() override
	{
        throw std::runtime_error("Break");
	}
};