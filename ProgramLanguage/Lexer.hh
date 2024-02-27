#pragma once

#include "Token.hh"

class Lexer {
public:
    using TokenNode     = vec< Token >;
    using TokenTypeNode = vec< TokenType >;

public:
    explicit Lexer(std::string Input_Code)
    {
        this->Input  = Input_Code;
        this->Length = Input.length();
        this->Position = 0;
    }

    TokenNode run()
    {
        while (Position <= Length) {
            char Current = peek(0);

            if (std::isdigit(Current))
                tokenizateNumber();
            else if (std::isalpha(Current))
                tokenizateWord();
            else if (Operations.find(Current) != -1)
                tokenizateOperation();
            else if (Current == '"' || Current == '\'')
                tokenizeText();
            else
                next();
        }
        return Tokens;
    }

    void tokenizeText()
    {
        next();
        str buffer;
        char current = peek(0);

        while (true) {
            if (current == '\\') {
                current = next();
                switch (current) {
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

            if (current == '"' || current == '\'')
                break;

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

        while (true) {
            if (!(std::isdigit(current) || std::isalpha(current)) && (current != '_') && (current != '$'))
                break;

            buffer += current;
            current = next();
        }

        if (buffer == "echo")
            addToken(TokenType::ECHO);
        else if (buffer == "match")
            addToken(TokenType::IF);
        else if (buffer == "else")
            addToken(TokenType::ELSE);
        else if (buffer == "for")
            addToken(TokenType::FOR);
        else if (buffer == "while")
            addToken(TokenType::WHILE);
        else if (buffer == "do")
            addToken(TokenType::DO);
        else if (buffer == "continue")
            addToken(TokenType::CONTINUE);
        else if (buffer == "break")
            addToken(TokenType::BREAK);
        else
            addToken(TokenType::WORD, buffer);
    }

    void tokenizateNumber()
    {
        char Current = peek();
        std::string Buffer {};

        while (true) {
            if (Current == '.') {
                if (Buffer.find('.') != -1) {
                }
            } else if (!std::isdigit(Current)) {
                break;
            }

            Buffer = Buffer + Current;
            Current = next();
        }

        addToken(TokenType::NUMBER, Buffer);
    }

    void tokenizateOperation()
    {
        char Current = peek();
        std::string Buffer {};

        if (Current == '/') 
        {
            switch (peek(1)) 
            {
            case '/': 
                next();
                tokenizateComment();
                return;

            case '*':
                next();
                tokenizateMultiComment();
                return;
            }
        }

        while (true)
        {
            std::string Temp { Buffer };

            if (!OPERATION.valid( Temp + Current ) && !Temp.empty())
            {
                addToken(OPERATION[Temp]);
                return;
            }
            
            Buffer = Buffer + Current;
            Current = next();
        }
    }

    void tokenizateComment()
    {
        char Current = peek(1);
        
        while ((Current != '\n') && (Current != '\0') && (Current != '\t')) 
        {
            Current = next();
        }
    }

    void tokenizateMultiComment()
    {
        char Current = peek(0);
        
        while (true)
        {
            if (Current == '\0')
                throw std::runtime_error("Missing Close MultiComment");

            if (Current == '*' && peek(1) == '/')
                break;
            Current = next();
        } 
        next(); 
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

    /*
        Need Fixe Operation Processing and Fixe operation on Lexer::run()
    */

    TokenContainer OPERATION  {  
        TokenContainer::ContainerContent{ "+", TokenType::PLUS },
        TokenContainer::ContainerContent{ "-", TokenType::MINUS },
        TokenContainer::ContainerContent{ "/", TokenType::DIVISION },
        TokenContainer::ContainerContent{ "*", TokenType::MULTIPLICATION },

        TokenContainer::ContainerContent{ "(", TokenType::LPAREN },
        TokenContainer::ContainerContent{ ")", TokenType::RPAREN },

        TokenContainer::ContainerContent{ ",", TokenType::COMMA },
        TokenContainer::ContainerContent{ "<", TokenType::LT },
        TokenContainer::ContainerContent{ ">", TokenType::GT },


        TokenContainer::ContainerContent{ "=", TokenType::EQUAL },
        TokenContainer::ContainerContent{ ">=", TokenType::GTEQ },
        TokenContainer::ContainerContent{ "<=", TokenType::LTEQ },
        TokenContainer::ContainerContent{ "!=", TokenType::EXCLEQ },
        TokenContainer::ContainerContent{ "==", TokenType::EQEQ },


        TokenContainer::ContainerContent{ "&", TokenType::AMP },
        TokenContainer::ContainerContent{ "&&", TokenType::AMPAMP },

        TokenContainer::ContainerContent{ "|", TokenType::BAR },
        TokenContainer::ContainerContent{ "||", TokenType::BARBAR },

        TokenContainer::ContainerContent{ "!", TokenType::EXCL },
        TokenContainer::ContainerContent{ "{", TokenType::LBRACE },
        TokenContainer::ContainerContent{ "}", TokenType::RBRACE },

        TokenContainer::ContainerContent{ "%", TokenType::MOD }
    };

	std::string Input { "\0" };
    std::string Operations { "+-/*()><=&|!{}%," };
    std::size_t Position { NULL }, Length { NULL };

	TokenNode Tokens = TokenNode {};

    

};

/*        
  About the author (the beginning of development on 02/21/2024) 
                                
  @Project UBI language                           
  @Author MaredHat                                
  @GitHub https://github.com/cloudSenior          

  @Discord .maredhat                              
  @Discord Channel https://discord.gg/fAAkPncYfa  
*/