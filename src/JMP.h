#include <vector>
#include <string.h>
#include <algorithm>
using std::string;
using std::ostream;

class JMP
{
    public:
        string number;
        // Constructors
        JMP(string num) { number = num; }
        JMP() {}

        friend ostream & operator << (ostream &k, JMP &j)
        {
            k << j.number;
            return (k);
        }
};