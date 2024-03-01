#pragma once
#include "Statement.hh"
#include "Expression.hh"

#include "BreakStatement.hh"
#include "ContinueStatement.hh"

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
            try
            {
                statement->execute();
            } 
            catch (BreakStatement& bs)
            {
                break;
            }
            catch (ContinueStatement& cs)
            {
                continue;
            }
        }

    }

private:
    Expression* condition;
    Statement* statement;
};