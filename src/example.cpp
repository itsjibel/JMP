#include "JMP.hpp"
#include <iostream>
using std::endl;
using std::cout;

int main()
{
    JMP my_number = "600";
    // Put const char* into a JMP object with constructor -> 600
    cout<<my_number<<endl;

    // Put const char* into a JMP object -> +700
    my_number = "+700";
    cout<<my_number<<endl;

    // Put the string into a JMP object -> -989
    string str = "-990";
    my_number = str;
    cout<<my_number<<endl;

    // -- the -999 to get 4 digits -> -1000
    my_number = "-999";
    my_number--;
    cout<<my_number<<endl;

    // -- the zero to get negetive symbol -> -1
    my_number = "0";
    cout<<my_number--<<endl;

    // Cout when ++ the JMP object -> 999999999999999999999999999999999999999
    my_number = "999999999999999999999999999999999999998";
    cout<<my_number++<<endl;

    // Put the string into a JMP object with constructor -> 9999999999999999999
    string sec_str = "9999999999999999999";
    JMP second_number = sec_str;
    cout<<second_number<<endl;

    // Cout the sum of the two positive numbers -> 1000000000000000000009999999999999999998
    cout<<second_number + my_number<<endl;

    // Cout the sum of the two negative numbers -9999999 and -99999999 -> -109999998
    second_number = "-99999999";
    my_number = "-9999999";
    cout<<my_number + second_number<<endl;


    // Cout sum of the positive and negative numbers -99999999 and 100000000 -> 1
    second_number = "-99999999";
    my_number = "100000000";
    cout<<my_number + second_number<<endl;

    // Cout sum of the JMP variable and int variables 100000000 and 15 and -98 -> 99999917
    int a = -98;

    // ++ the float JMP variable 542.21442 -> 541.21442
    JMP c = "-542.21442";
    cout<<c--<<endl;

    // -- the float JMP variable -2.141592653589793238462643 -> -3.141592653589793238462643
    c = "-2.141592653589793238462643";
    cout<<c--<<endl;

    // Cout the sum of two float JMP variables -24.8653 + -3.141592653589793238462643 -> -28.006892653589793238462643
    JMP e = -24.8653;
    cout<<"Result one: "<<c + e<<endl;
    cout<<"Result two: "<<c + -24.8653<<endl;

    // Put number into a integer variable
    long long int my_int = c.to_int();
    cout<<"Int number: "<<my_int<<endl;

    // Put number into a float variable
    long double my_double = c.to_double();
    cout<<"Double number: "<<my_double<<endl;

    // Convert the 'c' number from decimal to integer
    c.internal_conversion_to_int();
    cout<<c<<endl;

    // Append number to the 'c' number
    c.append("12345454");
    cout<<c<<endl;

    // Print is 'c' number integer?
    cout<<(c.is_integer() ? "Yes\n" : "No\n");

    // Print is 'c' number decimal?
    cout<<(c.is_decimal() ? "Yes\n" : "No\n");

    // Clear the 'c' number data and print the is_empty function
    c.clear();
    cout<<(c.is_empty() ? "Yes\n" : "No\n");

    // Sumition this time the first number is an double
    c = "123221398173981738917382130812931037999.5699511455515322";
    cout<<465512 + c<<endl;

    // += the JMP object value with an integer number
    c += 120.454;
    cout<<c<<endl;

    // Add string to JMP object
    string string_number = "+210.6";
    c = "-400.4";
    cout<<c + string_number<<endl;
    cout<<string_number + c<<endl;

    // Add const char* to JMP object
    cout<<c + "-120"<<endl;
    cout<<"-120" + c<<endl;

    // Multiply two JMP numbers4
    JMP mul1 = "195164524524524515.65156", mul2 = "9999443453452459534.3516515";
    cout<<mul1 * mul2<<endl;
    return 0;
}