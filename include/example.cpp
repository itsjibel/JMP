#include "jmp.hpp"
#include <iostream>

int main()
{
    // Creating a jmp object initialized with a const char* value "600"
    jmp my_number = "600";
    std::cout<<my_number<<std::endl;

    // Assigning a new value to the jmp object
    my_number = "+700";
    std::cout<<my_number<<std::endl;

    // Using a std::string to assign a value to the jmp object
    std::string str = "-990";
    my_number = str;
    std::cout<<my_number<<std::endl;

    // Incrementing the jmp object by one
    my_number = "-999";
    my_number++;
    std::cout<<my_number<<std::endl;

    // Decrementing the jmp object by one
    my_number = "0";
    std::cout<<--my_number<<std::endl;

    // Incrementing the jmp object by one and then printing it
    my_number = "999999999999999999999999999999999999998";
    std::cout<<++my_number<<std::endl;

    // Creating a new jmp object and incrementing it by one
    std::string sec_str = "9999999999999999999";
    jmp second_number = sec_str;
    std::cout<<++second_number<<std::endl;

    // Printing the sum of two positive jmp numbers
    std::cout<<second_number + my_number<<std::endl;

    // Printing the sum of two negative jmp numbers
    second_number = "-99999999";
    my_number = "-9999999";
    std::cout<<my_number + second_number<<std::endl;

    // Printing the sum of a positive and a negative jmp number
    second_number = "-99999999";
    my_number = "100000000";
    std::cout<<my_number + second_number<<std::endl;

    // Printing the sum of the jmp number and an integer
    int a {-98};
    std::cout<<my_number + a<<std::endl;

    // Printing the jmp number and then decrementing it
    jmp c = "-542.21442";
    std::cout<<c--<<std::endl;

    // Decrementing the jmp number and then printing it
    std::cout<<--c<<std::endl;

    // Printing the sum of two float jmp numbers
    jmp e = -24.8653;
    std::cout<<"Result one: "<<c + e<<std::endl;
    std::cout<<"Result two: "<<c + -24.8653<<std::endl;

    // Converting the jmp number to an integer and printing it
    long long int my_int = c.to_int();
    std::cout<<"Int number: "<<my_int<<std::endl;

    // Converting the jmp number to a float and printing it
    long double my_double = c.to_double();
    std::cout<<"Double number: "<<my_double<<std::endl;

    // Converting the jmp number from decimal to integer
    c.internal_conversion_to_int();
    std::cout<<c<<std::endl;

    // Appending a number to the jmp number
    c.append("12345454");
    std::cout<<c<<std::endl;

    // Checking if the jmp number is an integer
    std::cout<<(c.is_integer() ? "Yes\n" : "No\n");

    // Checking if the jmp number is a decimal
    std::cout<<(c.is_decimal() ? "Yes\n" : "No\n");

    // Clearing the jmp number data and checking if it is empty
    c.clear();
    std::cout<<(c.is_empty() ? "Yes\n" : "No\n");

    // Sumition this time the first number is a double
    c = "123221398173981738917382130812931037999.5699511455515322";
    std::cout<<465512 + c<<std::endl;

    // Adding a double number to the jmp number using +=
    c += 120.454;
    std::cout<<c<<std::endl;

    // Adding a std::string to the jmp number
    std::string string_number = "+210.6";
    c = "-400.4";
    std::cout<<c + string_number<<std::endl;
    std::cout<<string_number + c<<std::endl;

    // Adding a const char* to the jmp number
    std::cout<<c + "-120"<<std::endl;
    std::cout<<"-120" + c<<std::endl;

    // Multiplying two jmp numbers
    jmp mul1 = "195164524524524515.65156", mul2 = "9999443453452459534.3516515";
    std::cout<<mul1 * mul2<<std::endl;

    // Multiplying the jmp number with a double
    std::cout<<mul1 * -10000<<std::endl;
    std::cout<<0.0001 * mul1<<std::endl;
    mul1 *= "-9999443453452459534.3516515";
    std::cout<<mul1<<std::endl;

    // Subtracting two jmp numbers
    jmp sub1 = "-1234", sub2 = "-1235";
    std::cout<<sub2 - sub1<<std::endl;

    // Conditional checking
    jmp cond1 = "-1013.65";
    if (cond1 == -1013.65 && -1013 == cond1)
        std::cout<<"Yes\n";

    jmp cond2 = "-1013.65";
    if (cond1 == cond2)
        std::cout<<"Yes cond1 == cond2, "<< cond1<<" == "<<cond2<<std::endl;

    cond2--;
    if (cond2 < cond1)
        std::cout<<"Yes cond2 < cond1, "<<cond2<<" < "<<cond1<<std::endl;

    if (cond1 > cond2)
        std::cout<<"Yes cond1 > cond2, "<<cond1<<" > "<<cond2<<std::endl;

    if (cond2 != cond1)
        std::cout<<"Yes cond2 != cond1, "<<cond2<<" != "<<cond1<<std::endl;

    cond1--;
    if (cond2 <= cond1)
        std::cout<<"Yes cond2 <= cond1, "<<cond2<<" <= "<<cond1<<std::endl;

    if (cond2 >= cond1)
        std::cout<<"Yes cond2 >= cond1, "<<cond2<<" >= "<<cond1<<std::endl;

    jmp pow1 = "2", pow2 = "100";
    std::cout<<pow1.powof(pow2)<<std::endl;
    std::cout<<pow1.powof(100)<<std::endl;
    std::cout<<pow1.powof("100")<<std::endl;
    std::string hundred = "100";
    std::cout<<pow1.powof(hundred)<<std::endl;

    jmp a1 = -5.35526;
    std::cout<<JMP::abs(a1)<<std::endl;

    return 0;
}