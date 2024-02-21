#pragma once

#include "Expression.hh"
#include "Value.hh"



class ValueExpression : public Expression
{
public:
	ValueExpression(double value)
	{
        this->value = new NumberValue(value);
	}

    ValueExpression(std::string value)
	{
        this->value = new StringValue(value);
	}

	Value* eval()
	{
        return value;
	}
private:
    Value* value;
};

/*        
  About the author (the beginning of development on 02/21/2024) 
                                
  @Project UBI language                           
  @Author MaredHat                                
  @GitHub https://github.com/cloudSenior          

  @Discord .maredhat                              
  @Discord Channel https://discord.gg/fAAkPncYfa  
*/