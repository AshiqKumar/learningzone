
/*
The Interpreter design pattern is a behavioral design pattern used to define a language's grammar and provide an interpreter to process statements in that language. It is particularly useful for parsing and executing expressions or commands in a system.
Key Components:
- AbstractExpression – Defines an interface for all concrete expressions.
- TerminalExpression – Represents basic building blocks of the grammar.
- NonterminalExpression – Handles composite expressions made up of multiple sub-expressions.
- Context – Maintains global information during interpretation.
When to Use:
- When you need to interpret expressions in a structured language.
- Useful in SQL parsing, math
ematical expression evaluation, or any domain-specific language (DSL).
// Example: A simple interpreter that processes a script of commands to print "Hello world!".
*/

#include <string>
#include <iostream>
#include <stdexcept>

class Interpreter
{
public:
        template<typename It>
        void run(It from, It to)
        {
                for(It i=from; i!=to; ++i)
                {
                        switch(*i)
                        {
                        case 'h': std::cout << "Hello";         break;
                        case ' ': std::cout << ' ';                     break;
                        case 'w': std::cout << "world";         break;
                        case '!': std::cout << '!';                     break;
                        case 'n': std::cout << std::endl;       break;
                        default:  throw std::runtime_error("Unknown command");
                        }
                }
        }
};

void hello_world(const std::string & script)
{
        Interpreter().run(script.begin(), script.end());
}

int main()
{
        hello_world("h w!n");
        return 0;
}

/*
How is the example works (interpreter.cpp):
Interpreter class:
Has a run method that takes a range of characters (an input script) and interprets each character as a command.
Grammar:
'h' → prints "Hello"
'w' → prints "world"
'!' → prints '!'
' ' → prints a space
'n' → prints a newline
hello_world function:
Calls the interpreter with a script string.
main:
Runs the interpreter on "h w!n", which prints Hello world! followed by a newline.
-----------------------------------------------------------------------------------------

Summary:
The Interpreter pattern lets you define a grammar and interpret sentences in that grammar.
In this example, each character in the script is a command, and the interpreter executes the corresponding action.
This pattern is useful for implementing scripting languages, command interpreters, or expression evaluators.

*/