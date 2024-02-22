#pragma once

#include "Statement.hh"
#include "Expression.hh"

class MatchStatement : public Statement
{
public:
    
    MatchStatement( Expression* expression, Statement* MatchStatment, Statement* elseStatement )
    {
        this->expression      = expression;
        this->MatchStatment   = std::move(MatchStatment);
        this->elseStatement   = std::move(elseStatement);
    }

    void execute() override 
    {
        if (expression->eval()->asDouble() == true) MatchStatment->execute();
        else if (elseStatement != nullptr) elseStatement->execute();
    }

private: 
    Expression* expression;
    Statement* MatchStatment;
    Statement* elseStatement;

};

/*        
  About the author (the beginning of development on 02/21/2024) 
                                
  @Project UBI language                           
  @Author MaredHat                                
  @GitHub https://github.com/cloudSenior          

  @Discord .maredhat                              
  @Discord Channel https://discord.gg/fAAkPncYfa  
*/