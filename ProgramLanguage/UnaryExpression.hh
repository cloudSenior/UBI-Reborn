#pragma once

#include "Expression.hh"

class UnaryExpression : public Expression
{
public:
    UnaryExpression( char operation, Expression* expr )
    {
        this->operation = operation;
        this->expr = expr;
    }

    Value* eval() override
    {
        switch (operation) 
        {
            case '-': return new NumberValue(-expr->eval()->asDouble());
            case '+': 
                default:
                 return new NumberValue(expr->eval()->asDouble());
        }
    }
     
private:
    Expression* expr;
    char operation;
};

/*        
  About the author (the beginning of development on 02/21/2024) 
                                
  @Project UBI language                           
  @Author MaredHat                                
  @GitHub https://github.com/cloudSenior          

  @Discord .maredhat                              
  @Discord Channel https://discord.gg/fAAkPncYfa  
*/