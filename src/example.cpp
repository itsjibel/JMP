#include "jmp.hpp"
#include <iostream>
using std::endl;
using std::cout;

int main()
{
    jmp my_number = "600";
    // Put const char* into a jmp object with constructor -> 600
    cout<<my_number<<endl;

    // Put const char* into a jmp object -> +700
    my_number = "+700";
    cout<<my_number<<endl;

    // Put the string into a jmp object -> -989
    string str = "-990";
    my_number = str;
    cout<<my_number<<endl;

    // ++ the jmp number
    my_number = "-999";
    my_number++;
    cout<<my_number<<endl;

    // -- the jmp number
    my_number = "0";
    cout<<--my_number<<endl;

    // Cout when ++ the jmp object
    my_number = "999999999999999999999999999999999999998";
    cout<<++my_number<<endl;

    // Put the string into a jmp object
    string sec_str = "9999999999999999999";
    jmp second_number = sec_str;

    // Print ++ed jmp number
    cout<<++second_number<<endl;

    // Cout the sum of the two positive jmp numbers
    cout<<second_number + my_number<<endl;

    // Cout the sum of the two negative jmp numbers
    second_number = "-99999999";
    my_number = "-9999999";
    cout<<my_number + second_number<<endl;


    // Cout sum of the positive and negative jmp numbers
    second_number = "-99999999";
    my_number = "100000000";
    cout<<my_number + second_number<<endl;

    // Cout sum of the jmp number and int
    int a = -98;
    cout<<my_number + a<<endl;

    // Cout, then -- the jmp number
    jmp c = "-542.21442";
    cout<<c--<<endl;

    // Cout the --ed jmp number
    cout<<--c<<endl;

    // Cout the sum of two float jmp numbers
    jmp e = -24.8653;
    cout<<"Result one: "<<c + e<<endl;
    cout<<"Result two: "<<c + -24.8653<<endl;

    // Put jmp number into a integer variable
    long long int my_int = c.to_int();
    cout<<"Int number: "<<my_int<<endl;

    // Put jmp number into a float variable
    long double my_double = c.to_double();
    cout<<"Double number: "<<my_double<<endl;

    // Convert the jmp number from decimal to integer
    c.internal_conversion_to_int();
    cout<<c<<endl;

    // Append number to the jmp number
    c.append("12345454");
    cout<<c<<endl;

    // Print is jmp number integer?
    cout<<(c.is_integer() ? "Yes\n" : "No\n");

    // Print is jmp number decimal?
    cout<<(c.is_decimal() ? "Yes\n" : "No\n");

    // Clear the jmp number data and print the is_empty function
    c.clear();
    cout<<(c.is_empty() ? "Yes\n" : "No\n");

    // Sumition this time the first number is an double
    c = "123221398173981738917382130812931037999.5699511455515322";
    cout<<465512 + c<<endl;

    // += the jmp number with an double number
    c += 120.454;
    cout<<c<<endl;

    // Add string to jmp number
    string string_number = "+210.6";
    c = "-400.4";
    cout<<c + string_number<<endl;
    cout<<string_number + c<<endl;

    // Add const char* to jmp number
    cout<<c + "-120"<<endl;
    cout<<"-120" + c<<endl;

    // Multiply two jmp numbers
    jmp mul1 = "195164524524524515.65156", mul2 = "9999443453452459534.3516515";
    cout<<mul1 * mul2<<endl;

    // Multiply jmp number with double
    cout<<mul1 * -10000<<endl;
    cout<<0.0001 * mul1<<endl;
    mul1 *= "-9999443453452459534.3516515";
    cout<<mul1<<endl;

    // Subtract two jmp numbers
    jmp sub1 = "-1234", sub2 = "-1235";
    cout<<sub2 - sub1<<endl;

    // Conditional checking
    jmp cond1 = "-1013.65";
    if (cond1 == -1013.65 && -1013.65 == cond1)
        cout<<"Yes\n";

    jmp cond2 = "-1013.65";
    if (cond1 == cond2)
        cout<<"Yes cond1 == cond2, "<<cond1<<" == "<<cond2<<endl;

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

    return 0;
}