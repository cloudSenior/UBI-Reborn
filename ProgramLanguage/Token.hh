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
	FOR,
	WHILE,

	// Other
    LPAREN,   // (
	RPAREN,  // )
    LT,     // <
    GT,    // >
	EQUAL, // =
	WORD,
    TEXT,
	ECHO,
	MOD, // %
    NONE, // nil
    EXCL, // !
    AMP, // &
    BAR, // |
    EQEQ, // ==
    EXCLEQ, // !=
    LTEQ, // <=
    GTEQ, // >=
    AMPAMP, // &&
    BARBAR, // ||
	LBRACE, // {
	RBRACE, // }
    COMMA, // ,
	DO, // DO
	CONTINUE, 
	BREAK,
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


class TokenContainer
{

public:
	struct ContainerContent
	{
        std::string index;
        TokenType token;
	};


	TokenContainer(std::initializer_list<ContainerContent> init)
            : Data(init)
	{

	}


	TokenType operator[]( std::string index )
	{
        for (std::vector<ContainerContent>::iterator it = Data.begin(); it != Data.end(); ++it)
            if (it->index == index)
                return it->token;
	}


	bool valid( std::string index )
	{
        for (std::vector<ContainerContent>::iterator it = Data.begin(); it != Data.end(); ++it)
            if (it->index == index)
                return true;
        return false;
	}

	bool valid( char index )
	{
        for (std::vector<ContainerContent>::iterator it = Data.begin(); it != Data.end(); ++it)
            if (it->index == std::to_string(index))
                return true;
        return false;
	}

	std::vector<ContainerContent> operator&(TokenContainer D)
	{
        return D.Data;
	}

private:
    std::vector<ContainerContent> Data;
};


/*        
  About the author (the beginning of development on 02/21/2024) 
                                
  @Project UBI language                           
  @Author MaredHat                                
  @GitHub https://github.com/cloudSenior          

  @Discord .maredhat                              
  @Discord Channel https://discord.gg/fAAkPncYfa  
*/