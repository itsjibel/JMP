#include "jmp.hpp"
#include <iostream>

int main()
{
    jmp a("6740482482648246823472847207420748293748204954582345"), b("944245535324924623946267942976295348050835478392");

    // Summation
    std::cout<<"Summation: "<<a + b<<std::endl;

    // Subtraction
    std::cout<<"Subtraction: "<<a - b<<std::endl;

    // Multiplication
    std::cout<<"Multiplication: "<<a * b<<std::endl;

    // Division
    a.set_division_precision(20);
    std::cout<<"Division: "<<a / b<<std::endl;

    // Divisibility
    std::cout<<"Divisibility: "<<a % b<<std::endl;

    // Calculate Greatest Common Denominator
    std::cout<<"GCD: "<<JMP::gcd(a, b)<<std::endl;

    // Calculate exponentiation of two jmp numbers
    jmp c("2"), d("-3");
    std::cout<<"Exponentiation: "<<c.powof(d)<<std::endl;

    return 0;
}