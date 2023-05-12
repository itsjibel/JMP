#include "jmp.hpp"
#include <iostream>

using std::endl;
using std::cout;

int main()
{
    // Creating a jmp object initialized with a const char* value "600"
    jmp my_number = "600";
    cout<<my_number<<endl;

    // Assigning a new value to the jmp object
    my_number = "+700";
    cout<<my_number<<endl;

    // Using a string to assign a value to the jmp object
    string str = "-990";
    my_number = str;
    cout<<my_number<<endl;

    // Incrementing the jmp object by one
    my_number = "-999";
    my_number++;
    cout<<my_number<<endl;

    // Decrementing the jmp object by one
    my_number = "0";
    cout<<--my_number<<endl;

    // Incrementing the jmp object by one and then printing it
    my_number = "999999999999999999999999999999999999998";
    cout<<++my_number<<endl;

    // Creating a new jmp object and incrementing it by one
    string sec_str = "9999999999999999999";
    jmp second_number = sec_str;
    cout<<++second_number<<endl;

    // Printing the sum of two positive jmp numbers
    cout<<second_number + my_number<<endl;

    // Printing the sum of two negative jmp numbers
    second_number = "-99999999";
    my_number = "-9999999";
    cout<<my_number + second_number<<endl;

    // Printing the sum of a positive and a negative jmp number
    second_number = "-99999999";
    my_number = "100000000";
    cout<<my_number + second_number<<endl;

    // Printing the sum of the jmp number and an integer
    int a {-98};
    cout<<my_number + a<<endl;

    // Printing the jmp number and then decrementing it
    jmp c = "-542.21442";
    cout<<c--<<endl;

    // Decrementing the jmp number and then printing it
    cout<<--c<<endl;

    // Printing the sum of two float jmp numbers
    jmp e = -24.8653;
    cout<<"Result one: "<<c + e<<endl;
    cout<<"Result two: "<<c + -24.8653<<endl;

    // Converting the jmp number to an integer and printing it
    long long int my_int = c.to_int();
    cout<<"Int number: "<<my_int<<endl;

    // Converting the jmp number to a float and printing it
    long double my_double = c.to_double();
    cout<<"Double number: "<<my_double<<endl;

    // Converting the jmp number from decimal to integer
    c.internal_conversion_to_int();
    cout<<c<<endl;

    // Appending a number to the jmp number
    c.append("12345454");
    cout<<c<<endl;

    // Checking if the jmp number is an integer
    cout<<(c.is_integer() ? "Yes\n" : "No\n");

    // Checking if the jmp number is a decimal
    cout<<(c.is_decimal() ? "Yes\n" : "No\n");

    // Clearing the jmp number data and checking if it is empty
    c.clear();
    cout<<(c.is_empty() ? "Yes\n" : "No\n");

    // Sumition this time the first number is a double
    c = "123221398173981738917382130812931037999.5699511455515322";
    cout<<465512 + c<<endl;

    // Adding a double number to the jmp number using +=
    c += 120.454;
    cout<<c<<endl;

    // Adding a string to the jmp number
    string string_number = "+210.6";
    c = "-400.4";
    cout<<c + string_number<<endl;
    cout<<string_number + c<<endl;

    // Adding a const char* to the jmp number
    cout<<c + "-120"<<endl;
    cout<<"-120" + c<<endl;

    // Multiplying two jmp numbers
    jmp mul1 = "195164524524524515.65156", mul2 = "9999443453452459534.3516515";
    cout<<mul1 * mul2<<endl;

    // Multiplying the jmp number with a double
    cout<<mul1 * -10000<<endl;
    cout<<0.0001 * mul1<<endl;
    mul1 *= "-9999443453452459534.3516515";
    cout<<mul1<<endl;

    // Subtracting two jmp numbers
    jmp sub1 = "-1234", sub2 = "-1235";
    cout<<sub2 - sub1<<endl;

    // Conditional checking
    jmp cond1 = "-1013.65";
    if (cond1 == -1013.65 && -1013 == cond1)
        cout<<"Yes\n";

    jmp cond2 = "-1013.65";
    if (cond1 == cond2)
        cout<<"Yes cond1 == cond2, "<< cond1<<" == "<<cond2<<endl;

    cond2--;
    if (cond2 < cond1)
        cout<<"Yes cond2 < cond1, "<<cond2<<" < "<<cond1<<endl;

    if (cond1 > cond2)
        cout<<"Yes cond1 > cond2, "<<cond1<<" > "<<cond2<<endl;

    if (cond2 != cond1)
        cout<<"Yes cond2 != cond1, "<<cond2<<" != "<<cond1<<endl;

    cond1--;
    if (cond2 <= cond1)
        cout<<"Yes cond2 <= cond1, "<<cond2<<" <= "<<cond1<<endl;

    if (cond2 >= cond1)
        cout<<"Yes cond2 >= cond1, "<<cond2<<" >= "<<cond1<<endl;

    jmp pow1 = "2", pow2 = "100";
    cout<<(pow1 ^ pow2)<<endl;
    cout<<(pow1 ^ 100)<<endl;
    cout<<(pow1 ^ "100")<<endl;
    string hundred = "100";
    cout<<(pow1 ^ hundred)<<endl;
    cout<<(2 ^ pow2)<<endl;
    cout<<("2" ^ pow2)<<endl;
    string two = "2";
    cout<<(two ^ pow2)<<endl;

    return 0;
}