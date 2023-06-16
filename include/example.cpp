#include "jmp.hpp"
#include <iostream>

int main()
{
    // Summation
    jmp a("6740482482648246823472847207420748293748204954582345"), b("944245535324924623946267942976295348050835478392");
    std::cout<<"Summation: "<<a + b<<std::endl;

    // Subtraction
    std::cout<<"Subtraction: "<<a - b<<std::endl;

    // Multiplication
    std::cout<<"Multiplication: "<<a * b<<std::endl;

    // Division
    a.set_division_precision(15);
    std::cout<<"Division: "<<a / b<<std::endl;

    // Divisibility
    std::cout<<"Divisibility: "<<a % b<<std::endl;

    // Calculate Greatest Common Denominator
    //std::cout<<"GCD: "<<JMP::gcd(a, b)<<std::endl;

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