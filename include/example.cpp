#include "jmp.hpp"
#include <iostream>

int main()
{
    // Summation
    jmp a("93893457857857857585875790.234534535434548486348"), b("674054345345345242443453453843.13554343452457994967");
    std::cout<<a + b<<std::endl;

    // Subtraction
    std::cout<<a - b<<std::endl;

    // Multiplication
    std::cout<<a * b<<std::endl;

    // Division
    a.set_division_precision(20);
    std::cout<<a / b<<std::endl;

    // Divisibility
    std::cout<<a % b<<std::endl;

    // Calculate Greatest Common Denominator
    // For now have some bugs in JMP::GCD function...

    // Put the jmp number into the string
    std::string jmp_string = a;
    std::cout<<jmp_string<<std::endl;

    // Get values from jmp array
    jmp jarr[5] {"18", "Hello", "9", "World", "9"};
    for (std::string itr : jarr)
        std::cout<<itr<<"\t";
    std::cout<<std::endl;
    // or ...
    for (auto i{0}; i<5; i++)
        std::cout<<jarr[i]<<"\t";
    std::cout<<std::endl;

    return 0;
}