#pragma once

#include <map>


#include "Expression.hh"
#include "Value.hh"


#pragma region Variable Container


struct VD
{
    std::string index;
    Value* value;
}; // Variable Data 

class VariableData
{
public:


    explicit VariableData( std::initializer_list<VD> init )
        : Data( init )
    {

    }


    bool exits( std::string key )
    {
        for (std::vector<VD>::iterator iter = Data.begin(); iter != Data.end(); ++iter)
        {
            if (iter->index == key)
            {
                return true;
            }
        }

        return false;
    }


    Value* find( std::string key )
    {
        for (std::vector<VD>::iterator iter = Data.begin(); iter != Data.end(); ++iter)
        {
            if (iter->index == key)
            {
                return iter->value;
            }
        }

        return nullptr;
    }


    void set( std::string key, Value* value )
    {
        Data.push_back(VD(key, value));
    }


    Value* get(std::string key)
    {
        Value* value = this->find(key);
        if (value != nullptr)
            return value;
    }

private:
    std::vector<VD> Data;
};
#pragma endregion

static VariableData Variables(
    { 
        VD{ "PI",              new NumberValue(3.1415926535) },
        VD{ "E",               new NumberValue(2.7182818284) },
        VD{ "GOLDEN_ROTATION", new NumberValue(1.6180339887) },
        VD{ "TAU",             new NumberValue(6.283185307)  }
    }
);



class VariableExpression : public Expression
{
public:
    VariableExpression(std::string key)
    {
        this->key = key;
    }

    Value* eval() override
    {
        return Variables.get(key);
        throw "Error Eval";
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