#include <iostream>
#include "JMP.h"
using std::endl;
using std::cout;

int main()
{
    JMP my_number = "600";
    // 600
    cout<<my_number<<endl;

    // +700
    my_number = "+700";
    cout<<my_number<<endl;

    // -989
    string str = "-990";
    my_number = str;
    my_number++;
    cout<<my_number<<endl;

    // -1000
    my_number = "-999";
    my_number--;
    cout<<my_number<<endl;

    // -1
    my_number = "0";
    cout<<my_number--<<endl;

    // 1000
    my_number = "999";
    cout<<my_number++<<endl;

    return 0;
}