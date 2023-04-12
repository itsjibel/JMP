#include <iostream>
#include "JMP.h"
using std::endl;
using std::cout;

int main()
{
    JMP my_number = "1000";
    cout<<my_number<<endl;

    my_number = "+80090";
    cout<<my_number<<endl;

    string str = "-990";
    my_number = str;
    my_number++;
    cout<<my_number<<endl;

    my_number = "+999";
    cout<<my_number++;

    return 0;
}