#pragma once

#include <map>


#include "Expression.hh"
#include "Value.hh"


#pragma region Variable Container


static std::map<std::string, Value*> Variables {
    { "PI", new NumberValue(3.1415926535) },
    { "E", new NumberValue(2.7182818284) },
    { "GOLDEN_ROTATION", new NumberValue(1.6180339887) },
    { "TAU", new NumberValue(6.283185307) },
    { "@nil", new StringValue("@nil") }
};

class
{
public:

    bool exits( std::string key )
    {
        return Variables.contains( key );
    }


    Value* find( std::string key )
    {
        if (Variables.contains(key))
            return Variables.at(key);
        return nullptr;
    }


    void set( std::string key, Value* value )
    {
        Variables[key] = value;
    }


    Value* get(std::string key)
    {
        if (!Variables.contains(key))
            return __nil__value__;
        return Variables.at(key);
    }

private:
    StringValue* __nil__value__ = new StringValue("@nil"); 

} VariableData;
#pragma endregion






class VariableExpression : public Expression
{
public:
    VariableExpression(std::string key)
    {
        this->key = key;
    }

    Value* eval() override
    {
        return VariableData.get(key);
    }

private:
    std::string key;
};


/*        
  About the author (the beginning of development on 02/21/2024) 
                                
  @Project UBI language                           
  @Author MaredHat                                
  @GitHub https://github.com/cloudSenior          

  @Discord .maredhat                              
  @Discord Channel https://discord.gg/fAAkPncYfa  
*/