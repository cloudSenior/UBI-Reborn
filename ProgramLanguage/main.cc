#include <iostream>
#include <fstream>

#include "Lexer.hh"
#include "Interpreter.hh"


int main()
{
	using namespace std;

	string buffer;
    ifstream f("main.ubi");

    

    while (getline(f, buffer, '\n')) 
    {
        Lexer lexer(buffer);
        TokenNode node = lexer.run();

        Interpreter interpreter(node);

        for (auto& a : interpreter.run()) {
            a->execute();
        }
    }
    

    f.close();

	return EXIT_SUCCESS;
}


/*        
  About the author (the beginning of development on 02/21/2024) 
                                
  @Project UBI language                           
  @Author MaredHat                                
  @GitHub https://github.com/cloudSenior          

  @Discord .maredhat                              
  @Discord Channel https://discord.gg/fAAkPncYfa  
*/