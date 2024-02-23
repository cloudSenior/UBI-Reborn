#pragma once
#include <typeinfo>

#include "Expression.hh"

class ConditionalExpression : public Expression {
public:
    ConditionalExpression( TokenType operation, Expression* expr1, Expression* expr2 )
    {
        this->operation = operation;

        this->expr1 = expr1;
        this->expr2 = expr2;
    }

    Value* eval() override
    {
        Value* value1 = expr1->eval();
        Value* value2 = expr2->eval();
        double num1 = value1->asDouble(), num2 {0};
        bool result;

        if (typeid(value1) == typeid(StringValue))
        {
            num1 = value1->asString().compare(value2->asString());
            num2 = 0;
        }
        else
        {
            num1 = value1->asDouble();
            num2 = value2->asDouble();
        }

        
        
        switch (operation) 
        {
        case TokenType::LT:
            result = num1 < num2;
            break;

        case TokenType::GT:
           result = num1 > num2;
            break;

        case TokenType::GTEQ:
            result = num1 >= num2;
            break;

        case TokenType::LTEQ:
            result = num1 <= num2;
            break;

        case TokenType::EXCLEQ:
            result = num1 != num2;
            break;

        case TokenType::AMPAMP:
            result = num1 && num2;
            break;

        case TokenType::BARBAR:
            result = num1 || num2;
            break;

        case TokenType::EQEQ:
        default:
            result = num1 == num2;
            break;
        }

        return new NumberValue(result);
    }

private:
    Value* StringCondition()
    {


        std::size_t num1 { 0 }, num2 { 0 };
        bool result;


    }
    

    Value* NumberCondition()
    {
        Value* value1 = expr1->eval();
        Value* value2 = expr2->eval();
        double num1 = value1->asDouble(), num2 = value2->asDouble();
        
        bool result;
        switch (operation) 
        {
        case TokenType::LT:
            result = num1 < num2;
            break;
        case TokenType::GT:
           result = num1 > num2;
            break;

        case TokenType::EQEQ:
        default:
            result = num1 == num2;
            break;
        }

        return new NumberValue(result);
    }

private:
    Expression* expr1;
    Expression* expr2;

    TokenType operation;
};