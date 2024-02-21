#pragma once
#include <typeinfo>

#include "Expression.hh"

class ConditionalExpression : public Expression {
public:
    ConditionalExpression( char operation, Expression* expr1, Expression* expr2 )
    {
        this->operation = operation;

        this->expr1 = expr1;
        this->expr2 = expr2;
    }

    Value* eval() override 
    {
        Value* value1 = expr1->eval();
        Value* value2 = expr2->eval();

        if (typeid(value1) == typeid(StringValue)) 
        {
            std::string string1 = value1->asString();
            std::string string2 = value2->asString();

            switch (operation) {
            case '>':
                return new NumberValue(string1.compare(string2) > 0);

            case '<':
                return new NumberValue(string1.compare(string2) < 0);

            case '=':
            default:
                return new NumberValue(string1._Equal(string2));
            }
        }

        double number1 = value1->asDouble(), number2 = value2->asDouble();

        switch (operation) {
        case '>':
            return new NumberValue(number1 < number2);

        case '<':
            return new NumberValue(number1 > number2);

        case '=':
        default:
            return new NumberValue(number1 == number2);
        }
    }

private:
    Expression* expr1;
    Expression* expr2;

    char operation;
};