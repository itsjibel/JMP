#include <string.h>
using std::string;
using std::ostream;

class JMP
{
    private:
        bool is_valid(const string &number) const
        {
            if (number.empty())
                return false;

            bool valid = true;
            for (int i=1; i<number.length(); i++)
            {
                if (number[i] < '0' || number[i] > '9')
                    valid = false;
            }

            if ((number[0]  < '0' || number[0]  > '9') &&
                (number[0] != '-' && number[0] != '+') ||
                number[0] == '0' || (number[1] == '0' && (number[0] == '-' || number[0] == '+')))
                valid = false;

            valid = number == "0" || number == "+0" || number == "-0" ? true : valid;

            return valid;
        }

        int8_t which_is_bigger(string num1, string num2)
        {
            if (num1.length() > num2.length())
                return 0;
            else if (num2.length() > num1.length())
                return 1;
            else if (num2.length() == num1.length())
                return 1;
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
            this->number = num;
        }

        JMP (const char* num)
        {
            this->number = string(num);
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

        /// Assignment operator
        JMP &operator=(const string &num)
        {
            number = num;
            return *this;
        }

        JMP &operator=(const char* num)
        {
            number = num;
            return *this;
        }

        /// Shortcut operators
        JMP &operator++(int)
        {
            // Check the validity of the number
            if (is_valid(number) == false)
            {
                number = "0";
                return *this;
            }

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
            if (number_has_minus_symbol == false)
            {
                // +1 for a positive number
                number[number.length() - 1]++;
                for (int i=number.length() - 1; i>=0; i--)
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
                // +1 for a negative number
                number[number.length() - 1]--;
                for (int i=number.length() - 1; i>=0; i--)
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

        JMP &operator--(int)
        {
            // Check the validity of the number
            if (is_valid(number) == false)
            {
                number = "0";
                return *this;
            }

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
            if (number_has_minus_symbol == false)
            {
                // -1 for a positive number
                number[number.length() - 1]--;
                for (int i=number.length() - 1; i>=0; i--)
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
                // -1 for a negative number
                number[number.length() - 1]++;
                for (int i=number.length() - 1; i>=0; i--)
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

        JMP &operator+(JMP &j)
        {
            JMP* sum_obj = new JMP;

            // Check the validity of the number and the passed number
            if (is_valid(number) == false)
            {
                number = "0";
                return *this;
            }
            if (is_valid(j.number) == false)
            {
                j.number = "0";
                return *this;
            }

            // Memorize the number and the passed number symbol
            bool number_has_minus_symbol = false, number_has_plus_symbol = false,
                 passed_number_has_minus_symbol = false, passed_number_has_plus_symbol = false;
            if (number[0] == '+')
            {
                number.erase(number.begin());
                number_has_plus_symbol = true;
            } else if (number[0] == '-') {
                number.erase(number.begin());
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
            int8_t which_number_is_bigger = which_is_bigger(j.number, number);
            bool number_is_bigger = false, passed_number_is_bigger = false;
            if (which_number_is_bigger == 0)
            {
                passed_number_is_bigger = true;
                sum_obj->number = j.number;
            } else {
                number_is_bigger = true;
                sum_obj->number = number;
            }

            if ((!number_has_minus_symbol && !passed_number_has_minus_symbol) ||
                (number_has_minus_symbol && passed_number_has_minus_symbol))
            {
                // Adding two positive numbers together or negative numbers together
                int range = passed_number_is_bigger ? j.number.length() : number.length();
                for (int i=range - 1; i>=0; i--)
                {
                    if (passed_number_is_bigger)
                    {
                        if (i >= j.number.length() - number.length())
                            sum_obj->number[i] += number[i - (j.number.length() - number.length())] - '0';
                    } else if (i >= number.length() - j.number.length())
                        sum_obj->number[i] += j.number[i - (number.length() - j.number.length())] - '0';

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
                    int number_index = number.size() - 1;
                    for (int i=sum_obj->number.size()-1; i>=0; i--)
                    {
                        if (number_index >= 0)
                            sum_obj->number[i] -= number[number_index] - '0';

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
};