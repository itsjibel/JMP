#include <string.h>
using std::string;
using std::ostream;
using std::istream;
using std::to_string;

class JMP
{
    protected:
        int float_point_index = 0;

    private:
        bool is_valid(const string &number)
        {
            // If number is empty so is not valid
            if (number.empty())
                return false;

            bool valid = true;
            int number_of_dots = 0;
            for (int i=1; i<number.length(); i++)
            {
                // If the number character is not in the range 0-9 and the number character is not '.'-
                // then this character is invalid
                if ((number[i] < '0' || number[i] > '9') && number[i] != '.')
                    valid = false;
                
                // If the number character is '.', so we add 1 to number_of_dots to know how many dots we have in-
                // the number characters, then update the float_point_index to know-
                // where is the point index in the number
                if (number[i] == '.')
                {
                    number_of_dots++;
                    this->float_point_index = i;
                }
            }

            // "If conditions" for falsing the validity of the number string
            if ((number[0]  < '0' ||  number[0]  > '9') && (number[0] != '-' && number[0] != '+')  ||
                 number[0] == '0' || (number[1] == '0'  && (number[0] == '-' || number[0] == '+')) ||
                (number.back() == '.' || number.front() == '.' || number_of_dots > 1))
                valid = false;
            
            // "If conditions" for truing the validity of the number string
            valid = number == "0" || number == "+0" || number == "-0" ? true : valid;

            // We set the float_point_index to zero when the number is invalid.
            // Because if the next value is an integer number, and we have a specific float_point_index, some-
            // calculations will fail and give wrong answers.
            float_point_index = valid ? float_point_index : 0;

            return valid;
        }

        int8_t which_is_bigger(const string &num1, const string &num2) const
        {
            // This function takes two strings that number and compares them in terms of size
            // First of all, we check the simple things make the number bigger than other
            // It's clear if the number string has a bigger length when is bigger than other
            if (num1.length() > num2.length())
                return 0;
            else if (num2.length() > num1.length())
                return 1;
            else
            {
                // If the two string numbers have the same length then we should check digit by digit to-
                // understand which number is bigger
                int counter = num1.length();
                while (num1[counter] == num2[counter])
                {
                    counter--;
                    if (num1[counter] > num2[counter])
                        return 0;
                    else if (num2[counter] > num2[counter])
                        return 1;
                }
            }

            return 0;
        }

    public:
        string number;
        /// Constructors
        JMP() {}

        JMP (const string &num)
        {
            // Check the validity of the number, if the number is invalid, so equal it to zero
            if (is_valid(num))
                this->number = num;
            else
                this->number = "0";
        }

        JMP (const char* num)
        {
            // Check the validity of the number, if the number is invalid, so equal it to zero
            if (is_valid(num))
                this->number = num;
            else
                this->number = "0";
        }

        /// Destructor
        virtual ~JMP()
        {
            number.clear();
        }

        /// Stream operators
        friend ostream &operator<<(ostream &k, JMP &j)
        {
            // Print the JMP object
            k<<j.number;
            return (k);
        }

        friend istream &operator>>(istream &k, JMP &j)
        {
            // Get the JMP object
            k>>j.number;
            return (k);
        }

        /// Assignment operator
        JMP &operator=(const string &num)
        {
            float_point_index = 0;
            // Check the validity of the number, if the number is invalid, so equal it to zero
            if (is_valid(num))
                this->number = num;
            else
                this->number = "0";
            return *this;
        }

        JMP &operator=(const char* num)
        {
            float_point_index = 0;
            // Check the validity of the number, if the number is invalid, so equal it to zero
            if (is_valid(num))
                this->number = num;
            else
                this->number = "0";
            return *this;
        }

        /// Shortcut operators
        JMP &operator++(int);
        JMP &operator--(int);
        JMP &operator+(JMP &j);
        JMP &operator+(const long long int &j);
};



JMP &JMP::operator++(int)
{
    // Memorize the number symbol
    bool number_has_minus_symbol = false, number_has_plus_symbol = false;
    if (number[0] == '+')
    {
        number.erase(number.begin());
        number_has_plus_symbol = true;
    } else if (number[0] == '-') {
        number.erase(number.begin());
        number_has_minus_symbol = true;
    }

    // +1 the number
    int last_integer_index = float_point_index != 0 ? float_point_index - 1 : number.length() - 1;
    if (number_has_minus_symbol == false)
    {
        // +1 for a positive number
        number[last_integer_index]++;
        for (int i=last_integer_index; i>=0; i--)
        {
            if (number[i] > '9' && i != 0)
            {
                number[i] = '0';
                number[i - 1]++;
            } else if (number[i] > '9' && i == 0) {
                number[i] = '0';
                number.insert(number.begin(), '1');
            }
        }
    } else {
        last_integer_index--;
        // +1 for a negative number
        number[last_integer_index]--;
        for (int i=last_integer_index; i>=0; i--)
        {
            if (number[i] < '0' && i != 0)
            {
                number[i] = '9';
                number[i - 1]--;
            } else if (number[i] < '0' && i == 0) {
                number.clear();
                number.push_back('1');
                number_has_minus_symbol = false;
                number_has_plus_symbol = true;
            } else if (number[i] == '0' && i == 0) {
                number.erase(number.begin());
            }
        }
    }

    // Add the memorized symbol to the beginning of the number
    if (number_has_minus_symbol)
        number.insert(number.begin(), '-');
    else if (number_has_plus_symbol)
        number.insert(number.begin(), '+');
    return *this;
}

JMP &JMP::operator--(int)
{
    // Memorize the number symbol
    bool number_has_minus_symbol = false, number_has_plus_symbol = false;
    if (number[0] == '+')
    {
        number.erase(number.begin());
        number_has_plus_symbol = true;
    } else if (number[0] == '-') {
        number.erase(number.begin());
        number_has_minus_symbol = true;
    }

    // -1 the number
    int last_integer_index = float_point_index != 0 ? float_point_index - 1 : number.length() - 1;
    if (number_has_minus_symbol == false)
    {
        // -1 for a positive number
        number[last_integer_index]--;
        for (int i=last_integer_index; i>=0; i--)
        {
            if (number[i] < '0' && i != 0)
            {
                number[i] = '9';
                number[i - 1]--;
            } else if (number[i] < '0' && i == 0) {
                number.clear();
                number.push_back('1');
                number_has_minus_symbol = true;
                number_has_plus_symbol = false;
            }
        }
    } else {
        last_integer_index--;
        // -1 for a negative number
        number[last_integer_index]++;
        for (int i=last_integer_index; i>=0; i--)
        {
            if (number[i] > '9' && i != 0)
            {
                number[i] = '0';
                number[i - 1]++;
            } else if (number[i] > '9' && i == 0) {
                number[i] = '0';
                number.insert(number.begin(), '1');
            }
        }
    }

    // Add the memorized symbol to the beginning of the number
    if (number_has_minus_symbol)
        number.insert(number.begin(), '-');
    else if (number_has_plus_symbol)
        number.insert(number.begin(), '+');
    return *this;
}

JMP &JMP::operator+(JMP &j)
{
    JMP* sum_obj = new JMP("0");

    // We need to remove the float sign from the number so that we don't have a problem finding a specific index
    if (float_point_index != 0)
        number.erase(number.begin() + float_point_index);
    if (j.float_point_index != 0)
        j.number.erase(j.number.begin() + j.float_point_index);

    // If two numbers do not have the same decimals, we add '0' decimals to the end of that number that has lower decimals.
    if (j.float_point_index != 0 && float_point_index != 0 && (this->number.size() - float_point_index) > (j.number.size() - j.float_point_index))
    {
        // It means this object number has more decimals than second number
        // Now we need to know how many '0' decimals we should push back to the second number. (that number has lower decimals)
        for (int i=0; i<(this->number.size() - float_point_index) - (j.number.size() - j.float_point_index); i++)
            j.number.push_back('0');
    } else if (j.float_point_index != 0 && float_point_index != 0 && (this->number.size() - float_point_index) < (j.number.size() - j.float_point_index)) {
        // It means second number has more decimals than this object number
        for (int i=0; i<(j.number.size() - j.float_point_index) - (this->number.size() - float_point_index); i++)
            j.number.push_back('0');
    } else if (j.float_point_index != 0 && float_point_index == 0) {
        for (int i=0; i<j.number.size() - j.float_point_index; i++)
            j.number.push_back('0');
    } else if (j.float_point_index == 0 && float_point_index != 0) {
        for (int i=0; i<this->number.size() - float_point_index; i++)
            j.number.push_back('0');
    }

    // Check which number is bigger, and we equal the sum object number to the biggest number
    bool this_number_is_bigger = false, second_number_is_bigger = false;
    if (which_is_bigger(this->number, j.number) == 0)
    {
        sum_obj->number = this->number;
        this_number_is_bigger = true;
    } else {
        sum_obj->number = j.number;
        second_number_is_bigger = true;
    }

    // Check symbol of the number
    bool this_number_is_negative = false, second_number_is_negative = false;
    if (this->number[0] == '-')
        this_number_is_negative = true;
    else if (j.number[0] == '-')
        second_number_is_negative = true;

    // Remove number symbol
    if (this->number[0] == '-' || this->number[0] == '+')
        this->number.erase(this->number.begin());
    if (j.number[0] == '-' || j.number[0] == '+')
        j.number.erase(j.number.begin());

    // Now we ready to add two numbers together
    if (this_number_is_bigger && (this_number_is_negative && second_number_is_negative))
    {
        for (int i=j.number.size() - 1; i>=0; i--)
        {
        }
    } else if (second_number_is_bigger && (this_number_is_negative == second_number_is_negative)) {
        for (int i=this->number.size() - 1; i>=0; i--)
        {
        }
    } else if (this_number_is_bigger && (this_number_is_negative != second_number_is_negative)) {
        for (int i=j.number.size() - 1; i>=0; i--)
        {
        }
    } else if (second_number_is_bigger && (this_number_is_negative != second_number_is_negative)) {
        for (int i=this->number.size() - 1; i>=0; i--)
        {
        }
    }

    return *sum_obj;
}