#pragma once

#include "Expression.hh"

#include "ValueExpression.hh"
#include "UnaryExpression.hh"
#include "BinaryExpression.hh"

#include "Lexer.hh"


class Interpreter
{
public:


    Interpreter( TokenNode Tokens )
    {
        StatementList = std::move(Tokens);
        Size = StatementList.size();
        Position = NULL;
    }

    vec<Expression*> run()
    {
        vec<Expression*> result;

        while (!match( TokenType::CODEEXIT ))
        {
            result.push_back(std::move(expression()));
        }
        return result;
    }


/// 
/// Main Method's
/// 
private:
    
    Expression* expression()
    {
        return addtive();
    }


    Expression* addtive()
    {
        Expression* Addtive = multi();

        while (true) 
        {
            if (match(TokenType::PLUS)) 
            {
                Addtive = new BinaryExpression('+', std::move(Addtive), multi());
                continue;
            }
            if (match(TokenType::MINUS)) 
            {
                Addtive = new BinaryExpression('-', std::move(Addtive), multi());
                continue;
            }
            break;
        }

        return Addtive;
    }

    Expression* multi()
    {
        Expression* Unary = unary();

        while (true) 
        {
            if (match(TokenType::MULTIPLICATION)) 
            {
                Unary = new BinaryExpression('*', std::move(Unary), unary());
                continue;
            }
            if (match(TokenType::DIVISION)) 
            {
                Unary = new BinaryExpression('/', std::move(Unary), unary());
                continue;
            }
            break;
        }

        return Unary;
    }

    Expression* unary()
    {
        if (match(TokenType::MINUS)) return new UnaryExpression('-', std::move(primary()));
        return primary();
    }

    Expression* primary()
    {
        Token current = get(0);
        if (match(TokenType::NUMBER)) return new ValueExpression(std::stod(current.getText()));
        if (match(TokenType::LPAREN)) 
        {
            Expression* result = std::move(expression());
            match(TokenType::RPAREN);
            return result;
        }

    }


/// 
/// Supportive Method's
/// 
private:
Token consume(TokenType type)
{
    Token current = get(0);
    if (type != current.getType()) throw "Error";
    
    Position = Position + 1;

    return current;
}


bool match(TokenType type)
{
    Token current = get(0);
    if (type != current.getType()) return false;
    
    Position = Position + 1;
    
    return true;
}

Token get(uint32 realativePosition)
{
    size_t NowPosition = Position + realativePosition;
    if (NowPosition >= Size) return CodeExits;

    return StatementList.at(NowPosition);
}

private:
    TokenNode StatementList;
    size_t Size, Position;

    Token CodeExits = Token(TokenType::CODEEXIT, "");
};

/*        
  About the author (the beginning of development on 02/21/2024) 
                                
  @Project UBI language                           
  @Author MaredHat                                
  @GitHub https://github.com/cloudSenior          

  @Discord .maredhat                              
  @Discord Channel https://discord.gg/fAAkPncYfa  
*/