#include <iostream>
#include "JMP.h"
using std::endl;
using std::cout;

int main()
{
    JMP j = "1000";
    cout<<j<<endl;

    j = "+80090";
    cout<<j<<endl;

    string str="-990";
    j = str;
    j++;
    cout<<j<<endl;

    return 0;
}