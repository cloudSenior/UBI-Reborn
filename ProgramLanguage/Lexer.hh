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

            if (std::isdigit(Current)) tokenizateNumber();
            else if (std::isalpha(Current)) tokenizateWord();
            else if (OPERATION.find(Current) != -1) tokenizateOperation();
            else if (Current == '"' || Current == '\'') tokenizeText();
            else next();
            
        }
        return Tokens;
    }


    void tokenizeText()
    {
        next(); 
        str buffer;
        char current = peek(0);

        while (true) 
        {
            if (current == '\\')
            {
                current = next();
                switch (current) 
                {
                case '"':
                    current = next();
                    buffer.append("\"");
                    continue;

                case '\'':
                    current = next();
                    buffer.append("'");
                    continue;

                 case 'n':
                    current = next();
                    buffer.append("\n");
                    continue;

                 case 't':
                    current = next();
                    buffer.append("\t");
                    continue;
                }

                buffer += "\\";
                continue;
            }

            if (current == '"' || current == '\'') break;
        
            buffer += current;
            current = next();
        }

        next();

        addToken(TokenType::TEXT, buffer);
    }

    void tokenizateWord()
    {
        std::string buffer;
        char current = peek(0);

        while (true) 
        {
            if (!(std::isdigit(current) || std::isalpha(current)) && (current != '_') && (current != '$')) break;

            buffer += current;
            current = next();
        }

        if (buffer == "echo")       addToken(TokenType::ECHO);
        else if (buffer == "match") addToken(TokenType::IF);
        else if (buffer == "else")  addToken(TokenType::ELSE);
        else addToken(TokenType::WORD, buffer);
    }


    void tokenizateNumber()
    {
        char Current = peek();
        std::string Buffer { };
                
        while( true ) 
        {
            if (Current == '.') 
            {
                if (Buffer.find('.') != -1) 
                { 
                
                }
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