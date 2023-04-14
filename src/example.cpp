#include <iostream>
#include "JMP.h"
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

    // Cout the sum of the two numbers -> 1000000000000000000009999999999999999998
    cout<<second_number + my_number<<endl;

    return 0;
}