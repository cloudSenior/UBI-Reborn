#pragma once

#include <map>

#include "Expression.hh"
#include "Value.hh"


static std::map<std::string, Value*> Variables {
    { "PI",              new NumberValue(3.1415926535) },
    { "E",               new NumberValue(2.7182818284) },
    { "GOLDEN_ROTATION", new NumberValue(1.6180339887) },
    { "TAU",             new NumberValue(6.283185307) }
};




class VariableExpression : public Expression
{
public:
    VariableExpression( std::string key )
    {
        this->key;
    }

    Value* eval() override
    {
        if (IVC.isExists(key))
            return IVC.get(key);

        throw "Error Eval";
    }

private:
    std::string key;
};


class VariableController
{
public:

	bool isExists(std::string key)
    {
        if (Variables.find(key) != Variables.end())
            return true;
        return false;
    }

    Value* get(std::string key)
    {
        if (!isExists(key)) 
            throw "Variable not on regidit";
        else 
            return Variables.at(key);
    }

    void set(std::string name, Value* value)
    {
        Variables[name] = value;
    }

} IVC; // InstanceVariableController