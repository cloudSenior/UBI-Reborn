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
        if (typeid(expression1) == typeid(StringValue)) 
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
        std::string StrValue = expression1->eval()->asString(), 
                    StrValue2 = expression2->eval()->asString();
        double NumValue = expression2->eval()->asDouble();

        switch (operation) 
        {
            case '*': 
            {
                std::string buffer;
                for (std::size_t iter = 0; iter <= NumValue; ++iter) { 
                    buffer += StrValue;
                }
                return new StringValue(buffer);
            }

            case '+':
                default:
                    return new StringValue(StrValue + StrValue2);
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