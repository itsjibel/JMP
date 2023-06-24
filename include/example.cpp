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
    jmp c("2"), d("-10"), ten("10");
    std::cout<<"Exponentiation one: "<<c.powof(d)<<std::endl;
    d = JMP::abs(d * ten);
    std::cout<<"Exponentiation two: "<<c.powof(d)<<std::endl;

    // Calculate the cube of the jmp number
    std::cout<<"Cube: "<<JMP::cube(d)<<std::endl;

    // Calculate the square of the jmp number
    std::cout<<"Square: "<<JMP::sqr(d)<<std::endl;

    // Calculate the square root of the jmp number
    std::cout<<"Square root: "<<JMP::sqrt(ten)<<std::endl;

    return 0;
}