#pragma once

#include <typeinfo>

#include "ValueExpression.hh"



class BinaryExpression : public Expression
{
public:
    BinaryExpression(char operation, Expression * expression1, Expression* expression2)
    {
        this->expression1 = expression1;
        this->expression2 = expression2;

        this->operation = operation;
    }

    Value* eval() override
    {
        if (typeid(expression1->eval()).name()  == typeid(StringValue).name()) 
        {
            return stringEval();
        } 
        else 
        {
            return numberEval();
        }
    }

private:

    Value* numberEval()
    {
        Value* Value1 = expression1->eval();
        Value* Value2 = expression2->eval();
        switch (operation) 
        {
            case '-': return new NumberValue(Value1->asDouble() - Value2->asDouble());
            case '/': return new NumberValue(Value1->asDouble() / Value2->asDouble());
            case '*': return new NumberValue(Value1->asDouble() * Value2->asDouble());
            case '%': return new NumberValue(std::fmod(Value1->asDouble(), Value2->asDouble()));
            case '+': 
                default:
                    return new NumberValue(Value1->asDouble() + Value2->asDouble());
        }
    }


    Value* stringEval()
    {
        Value* Expr1 { expression1->eval() };
        Value* Expr2 { expression2->eval() };

        switch (operation) 
        {
            case '*': 
            {
                double NumValue = Expr2->asDouble();
                
                std::string buffer;
                std::string data = Expr1->asString();
                
                for (std::size_t iter = 0; iter <= NumValue; ++iter) 
                    buffer += data;
                
                return new StringValue(buffer);
            }

            case '+':
                default:
                    return new StringValue(Expr1->asString() + Expr2->asString());
        }
    }


private:
    Expression* expression1 = nullptr;
    Expression* expression2 = nullptr;
    
    char operation = '\0';
};

/*        
  About the author (the beginning of development on 02/21/2024) 
                                
  @Project UBI language                           
  @Author MaredHat                                
  @GitHub https://github.com/cloudSenior          

  @Discord .maredhat                              
  @Discord Channel https://discord.gg/fAAkPncYfa  
*/