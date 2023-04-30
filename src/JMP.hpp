#include <string.h>
#include <math.h>
using std::string;

class JMP
{
    protected:
        int float_point_index = 0;

    private:
        bool validation(const string &number)
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
                 (number[0] == '0' && !(number[1] == '.' && (number[2] >= '0' && number[2] <= '9'))) ||
                 (number[1] == '0'  && (number[0] == '-' || number[0] == '+')) ||
                (number.back() == '.' || number_of_dots > 1))
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
            if (num1.size() > num2.size())
                return 0;
            else if (num2.size() > num1.size())
                return 1;
            else
            {
                // If the two string numbers have the same length then we should check digit by digit to-
                // understand which number is bigger
                int counter = 0;
                while (counter < num1.size())
                {
                    if (num1[counter] > num2[counter])
                        return 0;
                    else if (num2[counter] > num1[counter])
                        return 1;
                    counter++;
                }
            }
            return 0;
        }

    public:
        string number;

        /// Constructors
        JMP()
        {
            number = "0";
        }

        JMP (const string &num)
        {
            // Check the validity of the number, if the number is invalid, so equal it to zero
            if (validation(num))
                number = num;
            else
                number = "0";
        }

        JMP (const char* num)
        {
            // Check the validity of the number, if the number is invalid, so equal it to zero
            if (validation(num))
                number = num;
            else
                number = "0";
        }

        JMP (const JMP &j)
        {
            this->number = j.number;
            float_point_index = j.float_point_index;
        }

        /// Destructor
        virtual ~JMP()
        {
            number.clear();
        }

        /// Stream operators
        friend std::ostream &operator<<(std::ostream &k, JMP &j)
        {
            // Print the JMP object
            k<<j.number;
            return (k);
        }

        friend std::istream &operator>>(std::istream &k, JMP &j)
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
            if (validation(num))
                number = num;
            else
                number = "0";
            return *this;
        }

        JMP &operator=(const char* num)
        {
            float_point_index = 0;
            // Check the validity of the number, if the number is invalid, so equal it to zero
            if (validation(num))
                number = num;
            else
                number = "0";
            return *this;
        }

        /// Optional functions
        long long int to_int()
        {
            return atoi(number.c_str());
        }

        long double to_double()
        {
            return std::stod(number);
        }

        void internal_conversion_to_int()
        {
            number = number.substr(0, number.find('.'));
        }

        /// Shortcut operators
        JMP &operator++(int);
        JMP &operator--(int);
        JMP &operator+(JMP &j);
        JMP &operator+(const long double &j);
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
    int last_integer_index = float_point_index != 0 ? float_point_index - 1: number.size();
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

    if (number[float_point_index - 1] != '.' && float_point_index != 0)
        number[float_point_index - 1] = '.';

    // Add the memorized symbol to the beginning of the number
    if (number_has_minus_symbol)
        number.insert(number.begin(), '-');
    else if (number_has_plus_symbol)
        number.insert(number.begin(), '+');
    return *this;
}

JMP &JMP::operator+(JMP &j)
{
    JMP *sum_obj = new JMP("0");

    // Check symbol of the number
    bool this_number_is_negative = false, second_number_is_negative = false,
         this_number_has_positive_symbol = false, second_number_has_positive_symbol = false;

    this_number_is_negative = number[0] == '-' ? true : false;
    second_number_is_negative = j.number[0] == '-' ? true : false;
    this_number_has_positive_symbol = number[0] == '+' ? true : false;
    second_number_has_positive_symbol = j.number[0] == '+' ? true : false;

    // Remove number symbol
    if (number[0] == '-' || number[0] == '+')
    {
        float_point_index = float_point_index > 0 ? float_point_index - 1 : 0;
        number.erase(number.begin());
    }
    if (j.number[0] == '-' || j.number[0] == '+')
    {
        j.float_point_index = j.float_point_index > 0 ? j.float_point_index - 1 : 0;
        j.number.erase(j.number.begin());
    }

    // We need to remove the float sign from the number so that we don't have a problem finding a specific index
    if (float_point_index != 0)
        number.erase(number.begin() + float_point_index);
    if (j.float_point_index != 0)
        j.number.erase(j.number.begin() + j.float_point_index);

    int temp_number_size = number.size(), temp_second_number_size = j.number.size();

    // If two numbers do not have the same decimals, we add '0' decimals to the end of that number that has lower decimals.
    if (j.float_point_index != 0 && float_point_index != 0 && (number.size() - float_point_index) > (j.number.size() - j.float_point_index))
    {
        // It means this object number has more decimals than second number
        // Now we need to know how many '0' decimals we should push back to the second number. (that number has lower decimals)
        int how_many_zeros = (number.size() - float_point_index) - (j.number.size() - j.float_point_index);
        for (int i=0; i<how_many_zeros; i++)
            j.number.push_back('0');
    } else if (j.float_point_index != 0 && float_point_index != 0 && (number.size() - float_point_index) < (j.number.size() - j.float_point_index)) {
        // It means second number has more decimals than this object number
        int how_many_zeros = (j.number.size() - j.float_point_index) - (number.size() - float_point_index);
        for (int i=0; i<how_many_zeros; i++)
            number.push_back('0');
    } else if (j.float_point_index != 0 && float_point_index == 0) {
        int how_many_zeros = j.number.size() - j.float_point_index;
        for (int i=0; i<how_many_zeros; i++)
            number.push_back('0');
    } else if (j.float_point_index == 0 && float_point_index != 0) {
        int how_many_zeros = number.size() - float_point_index;
        for (int i=0; i<how_many_zeros; i++)
            j.number.push_back('0');
    }

    // Check which number is bigger, and we equal the sum object number to the biggest number
    bool this_number_is_bigger = false, second_number_is_bigger = false;
    if (which_is_bigger(number, j.number) == 0)
    {
        sum_obj->number = number;

        if (float_point_index != 0)
            sum_obj->float_point_index = float_point_index;
        else if (float_point_index == 0 && j.float_point_index != 0)
            sum_obj->float_point_index = temp_number_size;
        else
            sum_obj->float_point_index = 0;
        this_number_is_bigger = true;
    } else {
        sum_obj->number = j.number;

        if (j.float_point_index != 0)
            sum_obj->float_point_index = j.float_point_index;
        else if (j.float_point_index == 0 && float_point_index != 0)
            sum_obj->float_point_index = temp_second_number_size;
        else
            sum_obj->float_point_index = 0;
        second_number_is_bigger = true;
    }


    // Now we ready to add two numbers together
    if (this_number_is_bigger && (this_number_is_negative == second_number_is_negative))
    {
        int difference_of_two_numbers = number.size() - j.number.size();
        for (int i=number.size() - 1; i>=0; i--)
        {
            if (i >= difference_of_two_numbers)
                sum_obj->number[i] += j.number[i - difference_of_two_numbers] - '0';
            if (i != 0 && sum_obj->number[i] > '9')
            {
                sum_obj->number[i - 1] += (sum_obj->number[i] - '0') / 10;
                sum_obj->number[i] -= (sum_obj->number[i] - '0') / 10 * 10;
            } else if (i == 0 && sum_obj->number[i] > '9') {
                sum_obj->number = '1' + sum_obj->number;
                sum_obj->number[1] -= (sum_obj->number[1] - '0') / 10 * 10;
                sum_obj->float_point_index = float_point_index != 0 ? float_point_index + 1 : 0;
            }
        }
    } else if (second_number_is_bigger && (this_number_is_negative == second_number_is_negative)) {
        int difference_of_two_numbers = j.number.size() - number.size();
        for (int i=j.number.size() - 1; i>=0; i--)
        {
            if (i >= difference_of_two_numbers)
                sum_obj->number[i] += number[i - (difference_of_two_numbers)] - '0';

            if (i != 0 && sum_obj->number[i] > '9')
            {
                sum_obj->number[i - 1] += (sum_obj->number[i] - '0') / 10;
                sum_obj->number[i] -= (sum_obj->number[i] - '0') / 10 * 10;
            } else if (i == 0 && sum_obj->number[i] > '9') {
                sum_obj->number = '1' + sum_obj->number;
                sum_obj->number[1] -= (sum_obj->number[1] - '0') / 10 * 10;
                sum_obj->float_point_index = float_point_index != 0 ? float_point_index + 1 : 0;
            }
        }
    } else if (this_number_is_bigger && (this_number_is_negative != second_number_is_negative)) {
        int difference_of_two_numbers = number.size() - j.number.size();
        for (int i=number.size() - 1; i>=0; i--)
        {
            if (i >= difference_of_two_numbers)
                sum_obj->number[i] -= j.number[i - difference_of_two_numbers] - '0';

            if (sum_obj->number[i] < '0')
            {
                sum_obj->number[i] += 10;
                sum_obj->number[i - 1]--;
            }
        }
    } else if (second_number_is_bigger && (this_number_is_negative != second_number_is_negative)) {
        int difference_of_two_numbers = j.number.size() - number.size();
        for (int i=j.number.size() - 1; i>=0; i--)
        {
            if (i >= difference_of_two_numbers)
                sum_obj->number[i] -= number[i - difference_of_two_numbers] - '0';

            if (sum_obj->number[i] < '0')
            {
                sum_obj->number[i] += 10;
                sum_obj->number[i - 1]--;
            }
        }
    }

    // Remove the beginning-unusable zeros
    while (sum_obj->number[0] == '0')
    {
        sum_obj->number.erase(sum_obj->number.begin());
        if (sum_obj->float_point_index > 0)
        {
            sum_obj->float_point_index--;
            if (sum_obj->float_point_index == 0)
            {
                sum_obj->float_point_index++;
                sum_obj->number = "0" + sum_obj->number;
                break;
            }
        }
    }

    // Remove the ending-unusable zeros
    while (sum_obj->number[sum_obj->number.size() - 1] == '0' && sum_obj->float_point_index != 0)
    {
        sum_obj->number.erase(sum_obj->number.begin() + sum_obj->number.size() - 1);
    }

    if (sum_obj->number.empty())
    {
        sum_obj->number = "0";
    } else {
        if ((this_number_is_bigger && this_number_is_negative) || (second_number_is_bigger && second_number_is_negative))
        {
            sum_obj->float_point_index = sum_obj->float_point_index > 0 ? sum_obj->float_point_index + 1 : 0;
            sum_obj->number.insert(sum_obj->number.begin(), '-');
        }

        if (sum_obj->float_point_index != 0)
            sum_obj->number.insert(sum_obj->number.begin() + sum_obj->float_point_index, '.');
    }

    if (sum_obj->float_point_index != 0 && sum_obj->float_point_index == sum_obj->number.size() - 1)
        sum_obj->number.append("0");

    /// Back the numbers to default

    // Removing the zeros that are added to add two decimal numbers
    if (number.size() != temp_number_size)
        number = number.substr(0, temp_number_size);
    if (j.number.size() != temp_second_number_size)
        j.number = j.number.substr(0, temp_second_number_size);

    // Add float point symbol to the number who had float point
    if (float_point_index != 0)
        number.insert(number.begin() + float_point_index, '.');
    if (j.float_point_index != 0)
        j.number.insert(j.number.begin() + j.float_point_index, '.');

    // Add number symbols to themselves
    if (this_number_is_negative)
    {
        number = '-' + number;
        float_point_index++;
    }

    if (second_number_is_negative)
    {
        j.number = '-' + j.number;
        j.float_point_index++;
    }
    
    if (this_number_has_positive_symbol)
    {
        number = '+' + number;
        float_point_index++;
    }

    if (second_number_has_positive_symbol)
    {
        j.number = '+' + j.number;
        j.float_point_index++;
    }

    return *sum_obj;
}

JMP &JMP::operator+(const long double &j)
{
    JMP *sum_obj = new JMP("0");
    double check;

    string num2_str = std::to_string(j);
    int num2_float_point_index = num2_str.find('.');
    if (modf(j, &check) == 0.0)
    {
        num2_str = num2_str.substr(0, num2_float_point_index);
        num2_float_point_index = 0;
    } else
        num2_str.erase(num2_str.begin() + num2_float_point_index);

    // Check symbol of the number
    bool this_number_is_negative = false, second_number_is_negative = false,
         this_number_has_positive_symbol = false;

    this_number_is_negative = number[0] == '-' ? true : false;
    second_number_is_negative = num2_str[0] == '-' ? true : false;
    this_number_has_positive_symbol = number[0] == '+' ? true : false;

    // Remove number symbol
    if (number[0] == '-' || number[0] == '+')
    {
        float_point_index = float_point_index > 0 ? float_point_index - 1 : 0;
        number.erase(number.begin());
    }
    if (num2_str[0] == '-' || num2_str[0] == '+')
    {
        num2_float_point_index = num2_float_point_index > 0 ? num2_float_point_index - 1 : 0;
        num2_str.erase(num2_str.begin());
    }

    // We need to remove the float sign from the number so that we don't have a problem finding a specific index
    if (float_point_index != 0)
        number.erase(number.begin() + float_point_index);

    int temp_number_size = number.size(), temp_second_number_size = num2_str.size();

    // If two numbers do not have the same decimals, we add '0' decimals to the end of that number that has lower decimals.
    if (num2_float_point_index != 0 && float_point_index != 0 && (number.size() - float_point_index) > (num2_str.size() - num2_float_point_index))
    {
        // It means this object number has more decimals than second number
        // Now we need to know how many '0' decimals we should push back to the second number. (that number has lower decimals)
        int how_many_zeros = (number.size() - float_point_index) - (num2_str.size() - num2_float_point_index);
        for (int i=0; i<how_many_zeros; i++)
            num2_str.push_back('0');
    } else if (num2_float_point_index != 0 && float_point_index != 0 && (number.size() - float_point_index) < (num2_str.size() - num2_float_point_index)) {
        // It means second number has more decimals than this object number
        int how_many_zeros = (num2_str.size() - num2_float_point_index) - (number.size() - float_point_index);
        for (int i=0; i<how_many_zeros; i++)
            number.push_back('0');
    } else if (num2_float_point_index != 0 && float_point_index == 0) {
        int how_many_zeros = num2_str.size() - num2_float_point_index;
        for (int i=0; i<how_many_zeros; i++)
            number.push_back('0');
    } else if (num2_float_point_index == 0 && float_point_index != 0) {
        int how_many_zeros = number.size() - float_point_index;
        for (int i=0; i<how_many_zeros; i++)
            num2_str.push_back('0');
    }

    // Check which number is bigger, and we equal the sum object number to the biggest number
    bool this_number_is_bigger = false, second_number_is_bigger = false;
    if (which_is_bigger(number, num2_str) == 0)
    {
        sum_obj->number = number;

        if (float_point_index != 0)
            sum_obj->float_point_index = float_point_index;
        else if (float_point_index == 0 && num2_float_point_index != 0)
            sum_obj->float_point_index = temp_number_size;
        else
            sum_obj->float_point_index = 0;
        this_number_is_bigger = true;
    } else {
        sum_obj->number = num2_str;

        if (num2_float_point_index != 0)
            sum_obj->float_point_index = num2_float_point_index;
        else if (num2_float_point_index == 0 && float_point_index != 0)
            sum_obj->float_point_index = temp_second_number_size;
        else
            sum_obj->float_point_index = 0;
        second_number_is_bigger = true;
    }


    // Now we ready to add two numbers together
    if (this_number_is_bigger && (this_number_is_negative == second_number_is_negative))
    {
        int difference_of_two_numbers = number.size() - num2_str.size();
        for (int i=number.size() - 1; i>=0; i--)
        {
            if (i >= difference_of_two_numbers)
                sum_obj->number[i] += num2_str[i - difference_of_two_numbers] - '0';
            if (i != 0 && sum_obj->number[i] > '9')
            {
                sum_obj->number[i - 1] += (sum_obj->number[i] - '0') / 10;
                sum_obj->number[i] -= (sum_obj->number[i] - '0') / 10 * 10;
            } else if (i == 0 && sum_obj->number[i] > '9') {
                sum_obj->number = '1' + sum_obj->number;
                sum_obj->number[1] -= (sum_obj->number[1] - '0') / 10 * 10;
                sum_obj->float_point_index = float_point_index != 0 ? float_point_index + 1 : 0;
            }
        }
    } else if (second_number_is_bigger && (this_number_is_negative == second_number_is_negative)) {
        int difference_of_two_numbers = num2_str.size() - number.size();
        for (int i=num2_str.size() - 1; i>=0; i--)
        {
            if (i >= difference_of_two_numbers)
                sum_obj->number[i] += number[i - (difference_of_two_numbers)] - '0';

            if (i != 0 && sum_obj->number[i] > '9')
            {
                sum_obj->number[i - 1] += (sum_obj->number[i] - '0') / 10;
                sum_obj->number[i] -= (sum_obj->number[i] - '0') / 10 * 10;
            } else if (i == 0 && sum_obj->number[i] > '9') {
                sum_obj->number = '1' + sum_obj->number;
                sum_obj->number[1] -= (sum_obj->number[1] - '0') / 10 * 10;
                sum_obj->float_point_index = float_point_index != 0 ? float_point_index + 1 : 0;
            }
        }
    } else if (this_number_is_bigger && (this_number_is_negative != second_number_is_negative)) {
        int difference_of_two_numbers = number.size() - num2_str.size();
        for (int i=number.size() - 1; i>=0; i--)
        {
            if (i >= difference_of_two_numbers)
                sum_obj->number[i] -= num2_str[i - difference_of_two_numbers] - '0';

            if (sum_obj->number[i] < '0')
            {
                sum_obj->number[i] += 10;
                sum_obj->number[i - 1]--;
            }
        }
    } else if (second_number_is_bigger && (this_number_is_negative != second_number_is_negative)) {
        int difference_of_two_numbers = num2_str.size() - number.size();
        for (int i=num2_str.size() - 1; i>=0; i--)
        {
            if (i >= difference_of_two_numbers)
                sum_obj->number[i] -= number[i - difference_of_two_numbers] - '0';

            if (sum_obj->number[i] < '0')
            {
                sum_obj->number[i] += 10;
                sum_obj->number[i - 1]--;
            }
        }
    }

    // Remove the beginning-unusable zeros
    while (sum_obj->number[0] == '0')
    {
        sum_obj->number.erase(sum_obj->number.begin());
        if (sum_obj->float_point_index > 0)
        {
            sum_obj->float_point_index--;
            if (sum_obj->float_point_index == 0)
            {
                sum_obj->float_point_index++;
                sum_obj->number = "0" + sum_obj->number;
                break;
            }
        }
    }

    // Remove the ending-unusable zeros
    while (sum_obj->number[sum_obj->number.size() - 1] == '0' && sum_obj->float_point_index != 0)
    {
        sum_obj->number.erase(sum_obj->number.begin() + sum_obj->number.size() - 1);
    }

    if (sum_obj->number.empty())
    {
        sum_obj->number = "0";
    } else {
        if ((this_number_is_bigger && this_number_is_negative) || (second_number_is_bigger && second_number_is_negative))
        {
            sum_obj->float_point_index = sum_obj->float_point_index > 0 ? sum_obj->float_point_index + 1 : 0;
            sum_obj->number.insert(sum_obj->number.begin(), '-');
        }

        if (sum_obj->float_point_index != 0)
            sum_obj->number.insert(sum_obj->number.begin() + sum_obj->float_point_index, '.');
    }

    if (sum_obj->float_point_index != 0 && sum_obj->float_point_index == sum_obj->number.size() - 1)
        sum_obj->number.append("0");

    /// Back the number to default

    // Removing the zeros that are added to add two decimal numbers
    if (number.size() != temp_number_size)
        number = number.substr(0, temp_number_size);

    // Add float point symbol to the number who had float point
    if (float_point_index != 0)
        number.insert(number.begin() + float_point_index, '.');

    // Add number symbols to themselves
    if (this_number_is_negative)
    {
        number = '-' + number;
        float_point_index++;
    }

    if (this_number_has_positive_symbol)
    {
        number = '+' + number;
        float_point_index++;
    }

    return *sum_obj;
}