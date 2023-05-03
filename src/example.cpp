#include <iostream>
#include "JMP.hpp"
using std::endl;
using std::cout;
using std::cin;

int main()
{
    // Put const char* into a JMP object with constructor
    JMP my_number = "123456841561561515616511165165165156116515615156167890";
    cout<<my_number<<endl;

    // cin the JMP object
    /*cin>>my_number;
    cout<<my_number<<endl;*/

    // Put JMP object into a JMP object
    JMP my_2nd_number = "1234568415615615156";
    my_number = my_2nd_number;

    // Valuing the JMP object with JMP object in constructor
    JMP my_3nd_number = my_2nd_number;
    cout<<my_3nd_number<<endl;

    return 0;
}