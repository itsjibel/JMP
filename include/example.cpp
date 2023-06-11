#include "jmp.hpp"
#include <iostream>

int main()
{
    // Summation
    jmp a("93893490.24848634"), b("67405843.137994968");
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

    return 0;
}