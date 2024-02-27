#pragma once

#include "Statement.hh"
#include "Expression.hh"

#include "BreakStatement.hh"
#include "ContinueStatement.hh"


class ForStatement : public Statement
{
public:

    ForStatement( Expression* termination, Statement* statement, Statement* inizilation, Statement* incriment)
    {
        this->termination = termination;
        this->statement = statement;
        this->inizilation = inizilation;
        this->incriment = incriment;
    }

    void execute() override
    {
        for (inizilation->execute(); termination->eval()->asDouble() != 0; incriment->execute())
        {
            try
            {
                statement->execute();
            } catch (BreakStatement& bs)
            {
                break;
            }
            catch (ContinueStatement& cs)
            {
                
            }
        }
    }

private:
    Expression* termination;
    Statement* statement;
    Statement* inizilation;
    Statement* incriment;
};