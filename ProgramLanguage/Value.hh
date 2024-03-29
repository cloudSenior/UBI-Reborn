#pragma once
#include <string>

#include "Debugger.hh"


__interface Value
{
   double asDouble();
   std::string asString();
};


class NumberValue : public Value
{
public:

	NumberValue( double value )
	{
        this->value = value;
	}

	double asDouble() override
	{
        return value;
	}

    std::string asString() override
    {
        try 
		{
            return std::to_string(value);
        }
		catch (std::exception& err)
		{
            Debugger.warning("No casting number to string");
		}
    }

private: 
	double value;
};


class StringValue : public Value
{
public:

	StringValue( std::string value )
	{
        this->value = value;
	}

	double asDouble() override
	{
        return std::stold(value);
	}

    std::string asString() override
    {
        return value;
    }

private: 
	std::string value;
};