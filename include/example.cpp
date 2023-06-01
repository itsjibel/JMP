#include "jmp.hpp"
#include <iostream>

int main()
{
    // Creating a jmp object initialized with a const char* value "600"
    jmp my_number = jmp("600");
    std::cout<<my_number<<std::endl;

    // Assigning a new value to the jmp object
    my_number = jmp("+700");
    std::cout<<my_number<<std::endl;

    // Using a std::string to assign a value to the jmp object
    std::string str = "-990";
    my_number = jmp(str);
    std::cout<<my_number<<std::endl;

    // Incrementing the jmp object by one
    my_number = jmp("-999");
    my_number++;
    std::cout<<my_number<<std::endl;

    // Decrementing the jmp object by one
    my_number = jmp("0");
    std::cout<<--my_number<<std::endl;

    // Incrementing the jmp object by one and then printing it
    my_number = jmp("999999999999999999999999999999999999998");
    std::cout<<++my_number<<std::endl;

    // Creating a new jmp object and incrementing it by one
    std::string sec_str = "9999999999999999999";
    jmp second_number = jmp(sec_str);
    std::cout<<++second_number<<std::endl;

    // Printing the sum of two positive jmp numbers
    std::cout<<second_number + my_number<<std::endl;

    // Printing the sum of two negative jmp numbers
    second_number = jmp("-99999999");
    my_number = jmp("-9999999");
    std::cout<<my_number + second_number<<std::endl;

    // Printing the sum of a positive and a negative jmp number
    second_number = jmp("-99999999");
    my_number = jmp("100000000");
    std::cout<<my_number + second_number<<std::endl;

    // Printing the sum of the jmp number and an integer
    jmp a(-98);
    std::cout<<my_number + a<<std::endl;

    // Printing the jmp number and then decrementing it
    jmp c = jmp("-542.21442");
    std::cout<<c--<<std::endl;

    // Decrementing the jmp number and then printing it
    std::cout<<--c<<std::endl;

    // Printing the sum of two float jmp numbers
    jmp e = jmp(-24.8653);
    std::cout<<c + e<<std::endl;

    // Converting the jmp number to an integer and printing it
    long long int my_int = JMP::to_int(c);
    std::cout<<"Int number: "<<my_int<<std::endl;

    // Converting the jmp number to a float and printing it
    long double my_double = JMP::to_double(c);
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

    // Sumition this time the first number is a double
    c = jmp("123221398173981738917382130812931037999.5699511455515322");
    std::cout<<465512 + c<<std::endl;

    // Adding a jmp number to the jmp number using +=
    jmp add_val(120.454);
    c += add_val;
    std::cout<<c<<std::endl;

    // Adding a std::string to the jmp number
    jmp string_number = jmp("+210.6");
    c = jmp("-400.4");
    std::cout<<c + string_number<<std::endl;
    std::cout<<string_number + c<<std::endl;

    // Multiplying two jmp numbers
    jmp mul1 = jmp("195164524524524515.65156"), mul2 = jmp("9999443453452459534.3516515");
    std::cout<<mul1 * mul2<<std::endl;

    // Subtracting two jmp numbers
    jmp sub1 = jmp("-1234"), sub2 = jmp("-1235");
    std::cout<<sub2 - sub1<<std::endl;

    // Conditional checking
    jmp cond1 = jmp("-1013.65"), check1(-1013.65), check2(-1013);
    if (cond1 == check1 && check2 == cond1)
        std::cout<<"Yes\n";

    jmp cond2 = jmp("-1013.65");
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

    jmp pow1 = jmp("2"), pow2 = jmp("100");
    std::cout<<pow1.powof(pow2)<<std::endl;
    std::cout<<pow1.powof(jmp(100))<<std::endl;
    std::cout<<pow1.powof(jmp("100"))<<std::endl;
    std::string hundred = "100";
    std::cout<<pow1.powof(jmp(hundred))<<std::endl;

    // Print the 'a1' absolute value of the jmp number
    jmp a1 = jmp(-9.65526);
    std::cout<<JMP::abs(a1)<<std::endl;

    // Set the 'a1' precision to 3
    a1.set_precision(4);
    std::cout<<a1<<std::endl;

    // Round the 'a1' form the precision 2
    a1.round_precision(2);
    std::cout<<a1<<std::endl;

    jmp fact1("10");
    std::cout<<JMP::fact(fact1)<<std::endl;

    jmp div1 = jmp("3.33"), div2 = jmp("1.5");
    div1.set_division_precision(100);
    std::cout<<div1/div2<<std::endl;

    jmp pow3("2");
    std::cout<<pow3.powof(jmp("-20"))<<std::endl;

    return 0;
}