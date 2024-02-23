#pragma once
#include "Statement.hh"
#include "Expression.hh"
class WhileStatement : public Statement
{
public:

    WhileStatement( Expression* condition, Statement* statement )
    {
        this->condition = condition;
        this->statement = statement;
    }

    void execute() override
    {
        while (condition->eval()->asDouble() != 0)
        {
            statement->execute();
        }
    }

private:
    Expression* condition;
    Statement* statement;
};