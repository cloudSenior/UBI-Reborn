#pragma once
#include "Statement.hh"
#include <vector>

class BlockStatement : public Statement
{
public:

    void add( Statement* statement )
    {
        Statements.push_back(statement);
    }

    void execute() override
    {
        for (auto statement: Statements)
        {
            statement->execute();
        }
    }

private:
    std::vector<Statement*> Statements;

};