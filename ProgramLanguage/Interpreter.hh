#pragma once

#pragma region Expression libs

#include "Expression.hh"

#include "ValueExpression.hh"

#include "UnaryExpression.hh"

#include "BinaryExpression.hh"

#include "ConditionExpression.hh"

#pragma endregion

#pragma region Statement libs
#include "Statement.hh"

#include "Assigment.hh"

#include "PrintAssigment.hh"

#include "MatchAssigment.hh"

#include "BlockStatement.hh";

#include "WhileStatement.hh" 

#include "ForStatement.hh"

#include "BreakStatement.hh"

#pragma endregion 

#include "Variable.hh"




class Interpreter
{
public:
    using TokenNode = Lexer::TokenNode;

    Interpreter( TokenNode Tokens )
    {
        StatementList = std::move(Tokens);
        Size = StatementList.size();
        Position = NULL;
    }

    Statement* run()
    {
        BlockStatement* result = new BlockStatement;

        while (!match( TokenType::CODEEXIT ))
        {
            result->add(statement());
        }        
        return result;
    }


/// 
/// Main Method's
/// 
private:
    
    Statement* Block()
    {
        BlockStatement* block = new BlockStatement;
        
        consume(TokenType::LBRACE);
        while (!match( TokenType::RBRACE ))
        {
            block->add(std::move(statement()));
        }

        return std::move(block);
    }
    
    Statement* statement()
    {
        if (match(TokenType::ECHO))
        {
            return new PrintStatement(std::move(expression()));
        } 

        else if (match(TokenType::IF))
        {
            return MatchElse();
        }
        
        else if (match(TokenType::WHILE))
        {
            return WhileState();
        }

        else if (match( TokenType::BREAK ))
        {
            return new BreakStatement();
        }

        else if (match( TokenType::CONTINUE ))
        {
            return new ContinueStatement();
        }

        else if (match( TokenType::FOR ))
        {
            return ForState();
        }


    
        return assigmentStatement();
    }

    Statement* assigmentStatement()
    {
        Token current = get(0);

        if (match(TokenType::WORD) && get().getType() == TokenType::EQUAL)
        {
            std::string variable = current.getText();
            consume(TokenType::EQUAL);
            return new Assigment(variable, expression());
        }

    }


    Statement* StatementOrBlock() 
    {
        if (get().getType() == TokenType::LBRACE) {
            return Block();
        }
        return statement();
    }

    Statement* WhileState()
    {
        Expression* condition = expression();
        Statement* statement = StatementOrBlock();
        return new WhileStatement(condition, statement);
    }

    Statement* ForState()
    {
        Statement* inizilation = assigmentStatement();
        consume(TokenType::COMMA);
        Expression* termination = expression();
        consume(TokenType::COMMA);
        Statement* increment = assigmentStatement();
        Statement* statement = StatementOrBlock();

        return new ForStatement(termination, statement, inizilation, increment);
    }

    Statement* MatchElse()
    {
        Expression* condition = std::move(expression());
        Statement* ifStatment = std::move(StatementOrBlock());
        Statement* elseStatment = nullptr;

        if (match(TokenType::ELSE)) 
        {
            elseStatment = StatementOrBlock();
        } 
        else 
        {
            elseStatment = nullptr;
        }

        return new MatchStatement(condition, ifStatment, elseStatment);
    }

    

    Expression* expression()
    {
        return LogicalOr();
    }


    Expression* LogicalOr()
    {
        Expression* result = LogicalAnd();

        while (true) 
        {
            if (match(TokenType::BARBAR)) 
            {
                result = new ConditionalExpression(TokenType::BARBAR, std::move(result), LogicalAnd());
                continue;
            }
            break;
        }
        
        return result;
    }

    Expression* LogicalAnd()
    {
        Expression* result = LogicalEqualed();

        while (true) 
        {
            if (match( TokenType::AMPAMP ))
            {
                result = new ConditionalExpression(TokenType::AMPAMP, std::move(result), LogicalEqualed());
                continue;
            }
            break;
        }
        
        return result;
    }

    Expression* LogicalEqualed()
    {
        Expression* result = conditional();

        if (match(TokenType::EQEQ)) 
        {
            result = new ConditionalExpression(TokenType::EQEQ, std::move(result), conditional());
        }
        if (match(TokenType::EXCLEQ)) 
        {
            result = new ConditionalExpression(TokenType::EXCLEQ, std::move(result), conditional());
        }
        return result;
    }

    Expression* conditional()
    {
        Expression* Add = std::move(addtive());
        while (true) 
        {
            if (match(TokenType::LTEQ)) 
            {
                Add = new ConditionalExpression(TokenType::LTEQ, std::move(Add), addtive());
                continue;
            }
            if (match(TokenType::LT)) 
            {
                Add = new ConditionalExpression(TokenType::LT, std::move(Add), addtive());
                continue;
            }
            if (match(TokenType::GTEQ)) 
            {
                Add = new ConditionalExpression(TokenType::GTEQ, std::move(Add), addtive());
                continue;
            }
            if (match(TokenType::GT)) 
            {
                Add = new ConditionalExpression(TokenType::GT, std::move(Add), addtive());
                continue;
            }

            break;
        }

        return Add;
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
            if (match(TokenType::MOD)) 
            {
                Unary = new BinaryExpression('%', std::move(Unary), unary());
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


        if (match(TokenType::TEXT)) return new ValueExpression(current.getText());

        if (match(TokenType::WORD)) 
        {
            return new VariableExpression(current.getText());
        }
    }

/// 
/// Supportive Method's
/// 
private:
Token consume(TokenType type)
{
    Token current = get(0);
    if (type != current.getType()) throw std::runtime_error("Error consume keyword");
    
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

Token get(uint32 realativePosition = 0)
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