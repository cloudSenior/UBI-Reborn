#pragma once
#include "defs.hh"


const enum class TokenType
{
	// Data types
	NUMBER, STRING,
	
	// Math operation
    PLUS,              // +
    MINUS,            // -
	DIVISION,        // / 
	MULTIPLICATION, // *

	// Keywords
	IF, 
	ELSE,
	LET,

	// Other
    LPAREN,   // (
	RPAREN,  // )
    LT,     // <
    RT,    // >
	EQUAL, // =
	WORD,
    TEXT,
	ECHO,
	CODEEXIT
};


class Token
{
public:

	Token(TokenType type, str content)
    {

		this->type = type;
        this->content = content;

    }

	TokenType getType() const
	{
		
        return this->type;

	}

	str getText()
	{

        return this->content;

	}

	void setType(TokenType type)
	{

        this->type = type;

	}

	void setText(str type)
    {

        this->content = type;

    }


private:

    TokenType type;
    str content;
};

/*        
  About the author (the beginning of development on 02/21/2024) 
                                
  @Project UBI language                           
  @Author MaredHat                                
  @GitHub https://github.com/cloudSenior          

  @Discord .maredhat                              
  @Discord Channel https://discord.gg/fAAkPncYfa  
*/