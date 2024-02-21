#pragma once
#include "Statement.hh"
#include "Expression.hh"

#include "Variable.hh"


class Assigment : public Statement
{
public:

    Assigment( std::string variable, Expression* expression )
    {
        this->variable = variable;
        this->expression = expression;
    }

    void execute() override 
    {
        IVC.set(variable, expression->eval());
    }

private:
    std::string variable;
    Expression* expression;
}; 