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

    public:
        string number;
        /// Constructors
        JMP() {}

        JMP(const string &num)
        {
            this->number = num;
        }

        JMP(const char* num)
        {
            this->number = string(num);
        }

        /// Destructor
        virtual ~JMP() {}

        /// Stream operators
        friend ostream &operator<<(ostream &k, JMP &j)
        {
            k<<j.number;
            return (k);
        }

        /// Assignment operator
        JMP& operator=(const string &num)
        {
            number = num;
            return *this;
        }

        JMP& operator=(const char* num)
        {
            number = num;
            return *this;
        }

        /// Shortcut operators
        JMP& operator++(int)
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

        JMP& operator--(int)
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
};