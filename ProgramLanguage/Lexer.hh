#pragma once

#include "Token.hh"



using TokenNode     = vec< Token >;
using TokenTypeNode = vec< TokenType >;

class Lexer
{
public:

	explicit Lexer(std::string Input_Code)
	{
        this->Input = Input_Code;
        this->Length = Input.length();
        this->Position = 0;
	}

	TokenNode run() 
    { 
        while (Position < Length)
        {
            char Current = peek();

            if (isdigit(Current))  
                tokenizateNumber();
            else if (OPERATION.find(Current) != -1) 
                tokenizateOperation();
            else
                next();
           
        }
        return Tokens;
    }


    void tokenizateNumber()
    {
        char Current = peek();
        std::string Buffer { };
                
        while( true ) 
        {
            if (Current == '.') 
            {
                if (Buffer.find('.') != std::string::npos) { }
            }
            else if (!std::isdigit(Current))
            {
                break;
            }

            Buffer = Buffer + Current;
            Current = next();
        }

        addToken(TokenType::NUMBER, Buffer);
    }


    void tokenizateOperation()
    {
        addToken(TypeNode[OPERATION.find(peek())]);
        next();
    }

private:

	char peek(size_t RealativePosition = NULL)
    {
        size_t NowPosition = Position + RealativePosition;
        char Result = (NowPosition >= Length ? NULL : Input[NowPosition]); 
        return Result;
    }

	char next()
    {
        Position = Position + 1;
        return peek();
    }

    void addToken(TokenType type, std::string content = "")
    {
        Tokens.push_back(Token(type, content));
    }

private:
    const std::string OPERATION { "+-/*()=<>" };

	std::string Input { "\0" };
    std::size_t Position { NULL }, Length { NULL };

	TokenNode Tokens = TokenNode {};

    TokenTypeNode TypeNode {
		 TokenType::PLUS, 
		 TokenType::MINUS, 
		 TokenType::DIVISION, 
		 TokenType::MULTIPLICATION,
	 	 TokenType::LPAREN, 
		 TokenType::RPAREN, 
		 TokenType::EQUAL,
		 TokenType::LT, 
		 TokenType::RT
	 };

};

/*        
  About the author (the beginning of development on 02/21/2024) 
                                
  @Project UBI language                           
  @Author MaredHat                                
  @GitHub https://github.com/cloudSenior          

  @Discord .maredhat                              
  @Discord Channel https://discord.gg/fAAkPncYfa  
*/