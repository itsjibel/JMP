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
            if (num1.length() > num2.length())
                return 0;
            else if (num2.length() > num1.length())
                return 1;
            else if (num2.length() == num1.length())
                return 0;
            else
            {
                int counter = num1.length();
                while (num1[counter] == num2[counter])
                    counter--;
                if (num1[counter] > num2[counter])
                    return 0;
                else if (num2[counter] > num2[counter])
                    return 1;
            }

            return 0;
        }

    public:
        string number;
        /// Constructors
        JMP() {}

        JMP (const string &num)
        {
            // Check the validity of the number
            if (is_valid(num))
                this->number = num;
            else
                this->number = "0";
        }

        JMP (const char* num)
        {
            // Check the validity of the number
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
            k<<j.number;
            return (k);
        }

        friend istream &operator>>(istream &k, JMP &j)
        {
            k>>j.number;
            return (k);
        }

        /// Assignment operator
        JMP &operator=(const string &num)
        {
            // Check the validity of the number
            if (is_valid(num))
                this->number = num;
            else
                this->number = "0";
            return *this;
        }

        JMP &operator=(const char* num)
        {
            // Check the validity of the number
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

    // Memorize the number and the passed number symbol
    bool number_has_minus_symbol = false, number_has_plus_symbol = false,
            passed_number_has_minus_symbol = false, passed_number_has_plus_symbol = false;
    if (this->number[0] == '+')
    {
        this->number.erase(number.begin());
        number_has_plus_symbol = true;
    } else if (this->number[0] == '-') {
        this->number.erase(this->number.begin());
        number_has_minus_symbol = true;
    }

    if (j.number[0] == '+')
    {
        j.number.erase(j.number.begin());
        passed_number_has_plus_symbol = true;
    } else if (j.number[0] == '-') {
        j.number.erase(j.number.begin());
        passed_number_has_minus_symbol = true;
    }

    // Check the bigger number with the length
    int8_t which_number_is_bigger = which_is_bigger(j.number, this->number);
    bool number_is_bigger = false, passed_number_is_bigger = false;
    if (which_number_is_bigger == 0)
    {
        passed_number_is_bigger = true;
        sum_obj->number = j.number;
    } else {
        number_is_bigger = true;
        sum_obj->number = this->number;
    }

    if ((!number_has_minus_symbol && !passed_number_has_minus_symbol) ||
        (number_has_minus_symbol && passed_number_has_minus_symbol))
    {
        // Adding two positive numbers together or negative numbers together
        int range = passed_number_is_bigger ? j.number.length() : this->number.length();
        for (int i=range - 1; i>=0; i--)
        {
            if (passed_number_is_bigger)
            {
                if (i >= j.number.length() - this->number.length())
                {
                    sum_obj->number[i] += this->number[i - (j.number.length() - this->number.length())] - '0';
                }
            } else if (i >= number.length() - j.number.length()) {
                sum_obj->number[i] += j.number[i - (this->number.length() - j.number.length())] - '0';
            }

            if (sum_obj->number[i] > '9')
            {
                if (i != 0)
                {
                    sum_obj->number[i - 1] += (sum_obj->number[i] - '0') / 10;
                    sum_obj->number[i] = '0' + (sum_obj->number[i] - '0') % 10;
                } else {
                    sum_obj->number.insert(sum_obj->number.begin(), '0');
                    sum_obj->number[0] += (sum_obj->number[1] - '0') / 10;
                    sum_obj->number[1] = '0' + (sum_obj->number[1] - '0') % 10;
                }
            }
        }

        if (number_has_minus_symbol && passed_number_has_minus_symbol)
            sum_obj->number.insert(sum_obj->number.begin(), '-');
    } else {
        // Adding two positive and negative numbers together
        if (number_is_bigger)
        {
            sum_obj->number = this->number;
            int passed_number_index = j.number.size() - 1;
            for (int i=sum_obj->number.size()-1; i>=0; i--)
            {
                if (passed_number_index >= 0)
                    sum_obj->number[i] -= j.number[passed_number_index] - '0';

                if (sum_obj->number[i] < '0')
                {
                    sum_obj->number[i] += 10;
                    sum_obj->number[i - 1] -= 1;
                }

                passed_number_index--;
            }
        } else if (passed_number_is_bigger) {
            sum_obj->number = j.number;
            int number_index = this->number.size() - 1;
            for (int i=sum_obj->number.size()-1; i>=0; i--)
            {
                if (number_index >= 0)
                    sum_obj->number[i] -= this->number[number_index] - '0';

                if (sum_obj->number[i] < '0')
                {
                    sum_obj->number[i] += 10;
                    sum_obj->number[i - 1] -= 1;
                }

                number_index--;
            }
        }

        while (sum_obj->number[0] == '0' && sum_obj->number.size() != 1)
            sum_obj->number.erase(sum_obj->number.begin());

        if (((number_has_minus_symbol && number_is_bigger) ||
            (passed_number_has_minus_symbol && passed_number_is_bigger)) &&
            !(sum_obj->number.size() == 1 && sum_obj->number[0] == '0'))
            sum_obj->number.insert(sum_obj->number.begin(), '-');
    }

    return *sum_obj;
}

JMP &JMP::operator+(const long long int &j)
{
    string second_number = to_string(j);
    JMP* sum_obj = new JMP("0");

    // Memorize the number and the passed number symbol
    bool number_has_minus_symbol = false, number_has_plus_symbol = false,
            passed_number_has_minus_symbol = false, passed_number_has_plus_symbol = false;
    if (this->number[0] == '+')
    {
        this->number.erase(number.begin());
        number_has_plus_symbol = true;
    } else if (this->number[0] == '-') {
        this->number.erase(this->number.begin());
        number_has_minus_symbol = true;
    }

    if (second_number[0] == '+')
    {
        second_number.erase(second_number.begin());
        passed_number_has_plus_symbol = true;
    } else if (second_number[0] == '-') {
        second_number.erase(second_number.begin());
        passed_number_has_minus_symbol = true;
    }

    // Check the bigger number with the length
    int8_t which_number_is_bigger = which_is_bigger(second_number, this->number);
    bool number_is_bigger = false, passed_number_is_bigger = false;
    if (which_number_is_bigger == 0)
    {
        passed_number_is_bigger = true;
        sum_obj->number = second_number;
    } else {
        number_is_bigger = true;
        sum_obj->number = this->number;
    }

    if ((!number_has_minus_symbol && !passed_number_has_minus_symbol) ||
        (number_has_minus_symbol && passed_number_has_minus_symbol))
    {
        // Adding two positive numbers together or negative numbers together
        int range = passed_number_is_bigger ? second_number.length() : this->number.length();
        for (int i=range - 1; i>=0; i--)
        {
            if (passed_number_is_bigger)
            {
                if (i >= second_number.length() - this->number.length())
                {
                    sum_obj->number[i] += this->number[i - (second_number.length() - this->number.length())] - '0';
                }
            } else if (i >= number.length() - second_number.length()) {
                sum_obj->number[i] += second_number[i - (this->number.length() - second_number.length())] - '0';
            }

            if (sum_obj->number[i] > '9')
            {
                if (i != 0)
                {
                    sum_obj->number[i - 1] += (sum_obj->number[i] - '0') / 10;
                    sum_obj->number[i] = '0' + (sum_obj->number[i] - '0') % 10;
                } else {
                    sum_obj->number.insert(sum_obj->number.begin(), '0');
                    sum_obj->number[0] += (sum_obj->number[1] - '0') / 10;
                    sum_obj->number[1] = '0' + (sum_obj->number[1] - '0') % 10;
                }
            }
        }

        if (number_has_minus_symbol && passed_number_has_minus_symbol)
            sum_obj->number.insert(sum_obj->number.begin(), '-');
    } else {
        // Adding two positive and negative numbers together
        if (number_is_bigger)
        {
            sum_obj->number = this->number;
            int passed_number_index = second_number.size() - 1;
            for (int i=sum_obj->number.size()-1; i>=0; i--)
            {
                if (passed_number_index >= 0)
                    sum_obj->number[i] -= second_number[passed_number_index] - '0';

                if (sum_obj->number[i] < '0')
                {
                    sum_obj->number[i] += 10;
                    sum_obj->number[i - 1] -= 1;
                }

                passed_number_index--;
            }
        } else if (passed_number_is_bigger) {
            sum_obj->number = second_number;
            int number_index = this->number.size() - 1;
            for (int i=sum_obj->number.size()-1; i>=0; i--)
            {
                if (number_index >= 0)
                    sum_obj->number[i] -= this->number[number_index] - '0';

                if (sum_obj->number[i] < '0')
                {
                    sum_obj->number[i] += 10;
                    sum_obj->number[i - 1] -= 1;
                }

                number_index--;
            }
        }

        while (sum_obj->number[0] == '0' && sum_obj->number.size() != 1)
            sum_obj->number.erase(sum_obj->number.begin());

        if (((number_has_minus_symbol && number_is_bigger) ||
            (passed_number_has_minus_symbol && passed_number_is_bigger)) &&
            !(sum_obj->number.size() == 1 && sum_obj->number[0] == '0'))
            sum_obj->number.insert(sum_obj->number.begin(), '-');
    }

    return *sum_obj;
}