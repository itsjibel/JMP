#include <vector>
#include <string>
using std::string;
using std::vector;

class JMP
{
    private:
        void string_2_vectorint(const string &str, vector<int_fast64_t> &vec)
        {
            vec.clear();
            string part;
            for (char ch : str)
            {
                part += ch;
                if (part.size() == 9)
                {
                    vec.push_back(stoi(part));
                    part.clear();
                }
            }
            if (part.size() > 0)
                vec.push_back(stoi(part));
        }

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

        bool which_is_bigger(const vector<int_fast64_t> &num1, const vector<int_fast64_t> &num2) const
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
        int float_point_index = 0;
        vector<int_fast64_t> number;

        /// Constructors
        JMP()
        {
            number.push_back(0);
        }

        JMP (const string &num)
        {
            // Check the validity of the number, if the number is invalid, so equal it to zero
            if (validation(num))
                string_2_vectorint(num, number);
            else {
                number.clear();
                number.push_back(0);
            }
        }

        JMP (const char* num)
        {
            // Check the validity of the number, if the number is invalid, so equal it to zero
            if (validation(num))
                string_2_vectorint(num, number);
            else {
                number.clear();
                number.push_back(0);
            }
        }

        JMP (const JMP &j)
        {
            number = j.number;
            float_point_index = j.float_point_index;
        }

        /// Destructor
        virtual ~JMP() {}

        /// Stream operators
        friend std::ostream &operator<<(std::ostream &k, JMP &j)
        {
            // Print the JMP object
            for (int_fast64_t i : j.number)
                k<<i;
            return k;
        }

        friend std::istream &operator>>(std::istream &k, JMP &j)
        {
            // Get the JMP object
            string num_str;
            k>>num_str;
            j.string_2_vectorint(num_str, j.number);
            return k;
        }

        /// Assignment operator
        JMP operator=(const string &num)
        {
            float_point_index = 0;
            // Check the validity of the number, if the number is invalid, so equal it to zero
            if (validation(num))
                string_2_vectorint(num, number);
            else {
                number.clear();
                number.push_back(0);
            }
            return *this;
        }

        JMP operator=(const char* num)
        {
            float_point_index = 0;
            // Check the validity of the number, if the number is invalid, so equal it to zero
            if (validation(num))
                string_2_vectorint(num, number);
            else {
                number.clear();
                number.push_back(0);
            }
            return *this;
        }
};