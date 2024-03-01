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
        try 
        {
            for (auto statement : Statements) {
                statement->execute();
            }
        }
        catch (std::exception& err)
        {
            Debugger.error("BlockStatement err: error stold arguments");
        }
    }

private:
    std::vector<Statement*> Statements;

};