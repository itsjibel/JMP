#include <algorithm>
#include <complex>
#include <memory>
#include <string.h>
using std::string;

string double_to_string(const long double &num)
{
    std::ostringstream strs;
    strs<<num;
    return strs.str();
}

class JMP
{
    private:
        typedef unsigned long long int ulli;
        void validation (const string &num);
        bool which_is_bigger(const string &num1, const string &num2) const;
        void equalizing_figures(JMP &j);
        void trim_the_number(JMP &j, bool bigger_number_is_negative);

        /// Arithmetic functions
        void FFT (std::complex<double>* a, ulli n, bool invert);
        void summation (JMP &sum_obj, const string &num1, const string &num2,
                        bool &first_number_is_bigger, bool &second_number_is_bigger,
                        bool &first_number_has_negative_sign, bool &second_number_has_negative_sign);
        string multiply(const string& num1, const string& num2);

    public:
        bool has_negative_sign = false, has_positive_sign = false;
        ulli float_point_index = 0;
        string number;

        /// Constructors
        JMP() : number("0") {}
        JMP (const string &num) { validation(num); }
        JMP (const char* num) { validation(num); }
        template <class T>
        JMP (T num) { validation(double_to_string(num)); }
        JMP (const JMP &j)
        {
            number = j.number;
            float_point_index = j.float_point_index;
        }

        /// Destructor
        virtual ~JMP() {}

        /// Stream operators
        friend std::ostream &operator<<(std::ostream &o, JMP j)
        {
            o<<(j.has_negative_sign ? '-' : j.has_positive_sign ? '+' : '\0');
            if (j.float_point_index != 0)
                j.number.insert(j.number.begin() + j.float_point_index, '.');
            o<<j.number;
            return o;
        }

        friend std::istream &operator>>(std::istream &i, JMP &j)
        {
            // Get the JMP object
            i>>j.number;
            return (i);
        }

        /// Optional functions
        void clear()
        {
            number.clear();
            has_negative_sign = false;
            has_positive_sign = false;
            float_point_index = 0;
        }

        long long int to_int()
        {
            string copy_of_number = number;
            if (float_point_index != 0)
                copy_of_number.insert(copy_of_number.begin() + float_point_index, '.');
            return atoi(std::move(copy_of_number.c_str()));
        }

        long double to_double()
        {
            string copy_of_number = number;
            if (float_point_index != 0)
                copy_of_number.insert(copy_of_number.begin() + float_point_index, '.');
            return std::stod(copy_of_number);
        }

        string to_string()
        {
            string copy_of_number = number;
            if (float_point_index != 0)
                copy_of_number.insert(copy_of_number.begin() + float_point_index, '.');
            return copy_of_number;
        }

        void internal_conversion_to_int()
        {
            number = number.substr(0, float_point_index);
            float_point_index = 0;
        }

        void append (const string &num)
        {
            if (!num.empty() && std::find_if(num.begin(), 
                 num.end(), [](unsigned char c) { return !std::isdigit(c); }) == num.end())
                number.append(num);
        }

        bool is_empty() const
        {
            return number.empty();
        }

        bool is_decimal() const
        {
            return float_point_index != 0;
        }

        bool is_integer() const
        {
            return float_point_index == 0;
        }

        ulli size() const
        {
            return number.size();
        }

        ulli allocated() const
        {
            return (number.capacity() * sizeof(char)) + sizeof(ulli) + sizeof(bool) * 2;
        }

        /// Assignment operator
        JMP &operator=(const string &num)
        {
            clear();
            // Check the validity of the number, if the number is invalid, so equal it to zero
            validation(num);
            return *this;
        }

        JMP &operator=(const char* num)
        {
            clear();
            // Check the validity of the number, if the number is invalid, so equal it to zero
            validation(num);
            return *this;
        }

        /// Shortcut operators
        JMP operator++(int);
        JMP operator--(int);
        JMP operator+(JMP &j);
        JMP operator*(JMP &j);
        JMP operator+(const long double &j);
        JMP operator+(string &num2_str);
        JMP operator+(const char* num2_str);
        friend JMP operator+(const long double &j, JMP &this_obj);
        friend JMP operator+(string &num2_str, JMP &this_obj);
        friend JMP operator+(const char* num2_str, JMP &this_obj);
        void operator+=(const long double &j);
        void operator+=(string &num2_str);
        void operator+=(const char* num2_str);
        friend void operator+=(long double &j, JMP &this_obj);
        friend void operator+=(string &num2_str, JMP &this_obj);
};

void JMP::FFT(std::complex<double>* a, ulli n, bool invert)
{
    // Bit-reversal permutation
    for (ulli i = 1, j = 0; i < n; ++i)
    {
        ulli bit = n >> 1;
        while (j >= bit)
        {
            j -= bit;
            bit >>= 1;
        }
        j += bit;
        if (i < j)
            swap(a[i], a[j]);
    }

    // Cooley-Tukey FFT algorithm
    for (ulli len = 2; len <= n; len <<= 1)
    {
        double angle = 2 * M_PI / len * (invert ? -1 : 1);
        std::complex<double> wlen(cos(angle), sin(angle));
        for (ulli i = 0; i < n; i += len)
        {
            std::complex<double> w(1);
            for (ulli j = 0; j < len / 2; ++j)
            {
                // Butterfly operation
                std::complex<double> u = a[i + j], v = a[i + j + len / 2] * w;
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
                w *= wlen;
            }
        }
    }

    // Invert the FFT if specified
    if (invert)
        for (ulli i = 0; i < n; ++i)
            a[i] /= n;  // Normalize the result by dividing each element by 'n'
}

string JMP::multiply(const string& num1, const string& num2)
{
    ulli n = 1;
    while (n < num1.size() + num2.size())
        n <<= 1;  // Find the smallest power of 2 that can hold the result of multiplication

    auto a = std::make_unique<std::complex<double>[]>(n);  // Complex array for the first number
    auto b = std::make_unique<std::complex<double>[]>(n);  // Complex array for the second number

    // Convert the numbers to complex representation
    for (ulli i = 0; i < num1.size(); ++i)
        a[i] = num1[num1.size() - i - 1] - '0';  // Reverse the order and subtract ASCII offset to get the digit value
    for (ulli i = 0; i < num2.size(); ++i)
        b[i] = num2[num2.size() - i - 1] - '0';

    // Perform FFT on the complex arrays
    FFT(a.get(), n, false);  // Perform forward FFT on the first number
    FFT(b.get(), n, false);  // Perform forward FFT on the second number

    // Multiply the complex arrays element-wise
    for (ulli i = 0; i < n; ++i)
        a[i] *= b[i];

    // Perform inverse FFT
    FFT(a.get(), n, true);  // Perform inverse FFT on the multiplied result

    ulli carry = 0;
    string product;
    for (ulli i = 0; i < n; ++i) {
        // Retrieve the real part of each element and perform carry operation
        ulli digit = static_cast<ulli>(round(a[i].real())) + carry;
        product += '0' + (digit % 10);  // Convert the digit to ASCII character
        carry = digit / 10;
    }
    // Remove leading zeros from the product
    while (product.size() > 1 && product.back() == '0')
        product.pop_back();

    reverse(product.begin(), product.end());  // Reverse the product to correct the order
    return product;
}



void JMP::validation (const string &num)
{
    // If number is empty so is not valid
    if (num.empty())
    {
        number = "0";
        return;
    }

    bool valid = true;
    int number_of_dots = 0;
    for (int i=1; i<num.length(); i++)
    {
        // If the number character is not in the range 0-9 and the number character is not '.'-
        // then this character is invalid
        if ((num[i] < '0' || num[i] > '9') && num[i] != '.')
            valid = false;
        
        // If the number character is '.', so we add 1 to number_of_dots to know how many dots we have in-
        // the number characters, then update the float_point_index to know-
        // where is the point index in the number
        if (num[i] == '.')
        {
            number_of_dots++;
            float_point_index = i;
        }
    }

    // "If conditions" for falsing the validity of the number string
    if ((num[0]  < '0' ||  num[0]  > '9') && (num[0] != '-' && num[0] != '+')  ||
            (num[0] == '0' && !(num[1] == '.' && (num[2] >= '0' && num[2] <= '9'))) ||
            (num[1] == '0'  && (num[0] == '-' || num[0] == '+')) ||
        (num.back() == '.' || number_of_dots > 1))
        valid = false;
    
    // "If conditions" for truing the validity of the number string
    valid = num == "0" || num == "+0" || num == "-0" ? true : valid;

    // We set the float_point_index to zero when the number is invalid.
    // Because if the next value is an integer number, and we have a specific float_point_index, some-
    // calculations will fail and give wrong answers.
    float_point_index = valid ? float_point_index : 0;            
    number = valid ? num : "0";

    // Set the number sing
    if (valid)
    {
        if (number[0] == '-')
        {
            float_point_index = float_point_index > 0 ? float_point_index - 1 : 0;
            number.erase(number.begin());
            has_negative_sign = true;
        } else if (number[0] == '+') {
            float_point_index = float_point_index > 0 ? float_point_index - 1 : 0;
            number.erase(number.begin());
            has_positive_sign = true;
        } else
            has_negative_sign = has_positive_sign = false;

        // We need to remove the float sign from the number so that we don't have a problem finding a specific index
        if (float_point_index != 0)
            number.erase(number.begin() + float_point_index);
    }
}

bool JMP::which_is_bigger(const string &num1, const string &num2) const
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

void JMP::summation (JMP &sum_obj, const string &num1, const string &num2,
                        bool &first_number_is_bigger, bool &second_number_is_bigger,
                        bool &first_number_has_negative_sign, bool &second_number_has_negative_sign)
{
    // Now we ready to add two numbers together
    if (first_number_is_bigger && (first_number_has_negative_sign == second_number_has_negative_sign))
    {
        int difference_of_two_numbers = num1.size() - num2.size();
        for (int i=num1.size() - 1; i>=0; i--)
        {
            if (i >= difference_of_two_numbers)
                sum_obj.number[i] += num2[i - difference_of_two_numbers] - '0';
            if (i != 0 && sum_obj.number[i] > '9')
            {
                sum_obj.number[i - 1] += (sum_obj.number[i] - '0') / 10;
                sum_obj.number[i] -= (sum_obj.number[i] - '0') / 10 * 10;
            } else if (i == 0 && sum_obj.number[i] > '9') {
                sum_obj.number = '1' + sum_obj.number;
                sum_obj.number[1] -= (sum_obj.number[1] - '0') / 10 * 10;
                sum_obj.float_point_index = sum_obj.float_point_index != 0 ? sum_obj.float_point_index + 1 : 0;
            }
        }
    } else if (second_number_is_bigger && (first_number_has_negative_sign == second_number_has_negative_sign)) {
        int difference_of_two_numbers = num2.size() - num1.size();
        for (int i=num2.size() - 1; i>=0; i--)
        {
            if (i >= difference_of_two_numbers)
                sum_obj.number[i] += num1[i - (difference_of_two_numbers)] - '0';

            if (i != 0 && sum_obj.number[i] > '9')
            {
                sum_obj.number[i - 1] += (sum_obj.number[i] - '0') / 10;
                sum_obj.number[i] -= (sum_obj.number[i] - '0') / 10 * 10;
            } else if (i == 0 && sum_obj.number[i] > '9') {
                sum_obj.number = '1' + sum_obj.number;
                sum_obj.number[1] -= (sum_obj.number[1] - '0') / 10 * 10;
                sum_obj.float_point_index = sum_obj.float_point_index != 0 ? sum_obj.float_point_index + 1 : 0;
            }
        }
    } else if (first_number_is_bigger && (first_number_has_negative_sign != second_number_has_negative_sign)) {
        int difference_of_two_numbers = num1.size() - num2.size();
        for (int i=num1.size() - 1; i>=0; i--)
        {
            if (i >= difference_of_two_numbers)
                sum_obj.number[i] -= num2[i - difference_of_two_numbers] - '0';

            if (sum_obj.number[i] < '0')
            {
                sum_obj.number[i] += 10;
                sum_obj.number[i - 1]--;
            }
        }
    } else if (second_number_is_bigger && (has_negative_sign != second_number_has_negative_sign)) {
        int difference_of_two_numbers = num2.size() - num1.size();
        for (int i=num2.size() - 1; i>=0; i--)
        {
            if (i >= difference_of_two_numbers)
                sum_obj.number[i] -= num1[i - difference_of_two_numbers] - '0';

            if (sum_obj.number[i] < '0')
            {
                sum_obj.number[i] += 10;
                sum_obj.number[i - 1]--;
            }
        }
    }
}

void JMP::equalizing_figures(JMP &j)
{
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
}

void JMP::trim_the_number(JMP &j, bool bigger_number_is_negative)
{
    while (j.number[0] == '0')
    {
        j.number.erase(j.number.begin());
        if (j.float_point_index > 0)
        {
            j.float_point_index--;
            if (j.float_point_index == 0)
            {
                j.float_point_index++;
                j.number = "0" + j.number;
                break;
            }
        }
    }

    // Remove the ending-unusable zeros
    while (j.number[j.number.size() - 1] == '0' && j.float_point_index != 0)
        j.number.erase(j.number.begin() + j.number.size() - 1);

    if (j.number.empty())
        j.number = "0";
    else if (bigger_number_is_negative)
        j.has_negative_sign = true;

    if (j.float_point_index != 0 && j.float_point_index == j.number.size())
        j.number.append("0");
}

JMP JMP::operator++(int)
{
    // +1 the number
    int last_integer_index = float_point_index != 0 ? float_point_index : number.length() - 1;
    if (has_negative_sign == false)
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
                has_negative_sign = false;
                has_positive_sign = true;
            } else if (number[i] == '0' && i == 0) {
                number.erase(number.begin());
            }
        }
    }

    return *this;
}

JMP JMP::operator--(int)
{
    // -1 the number
    int last_integer_index = float_point_index != 0 ? float_point_index : number.size();
    if (has_negative_sign == false)
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
                has_negative_sign = true;
                has_positive_sign = false;
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

    return *this;
}

JMP JMP::operator+(JMP &j)
{
    JMP sum_obj = JMP("0");
    int temp_number_size = number.size(), temp_second_number_size = j.number.size();

    equalizing_figures(j);

    // Check which number is bigger, and we equal the sum object number to the biggest number
    bool this_number_is_bigger = false, second_number_is_bigger = false;
    if (which_is_bigger(number, j.number) == 0)
    {
        sum_obj.number = number;

        if (float_point_index != 0)
            sum_obj.float_point_index = float_point_index;
        else if (float_point_index == 0 && j.float_point_index != 0)
            sum_obj.float_point_index = temp_number_size;
        else
            sum_obj.float_point_index = 0;
        this_number_is_bigger = true;
    } else {
        sum_obj.number = j.number;

        if (j.float_point_index != 0)
            sum_obj.float_point_index = j.float_point_index;
        else if (j.float_point_index == 0 && float_point_index != 0)
            sum_obj.float_point_index = temp_second_number_size;
        else
            sum_obj.float_point_index = 0;
        second_number_is_bigger = true;
    }

    // Get sum of the two filtered strings
    summation(sum_obj, number, j.number, this_number_is_bigger, second_number_is_bigger, has_negative_sign, j.has_negative_sign);

    /* Trim the number means if we have a number such as '000012.32400' after the summation of two numbers, we trim the number to '12.324'
     * (-999900 + 999912) = 000012  ---> 12
     * (-0.2222 + 12.2222) = 12.0000 ---> 12
     * (-9900.22 + 9912.22) = 0012.00 ---> 12
     */
    trim_the_number(sum_obj, (this_number_is_bigger && has_negative_sign) || (second_number_is_bigger && j.has_negative_sign));

    return sum_obj;
}

JMP JMP::operator*(JMP &j)
{
    JMP sum_obj("0");
    equalizing_figures(j);
    sum_obj.number = multiply(number, j.number);

    bool this_number_is_bigger = false, second_number_is_bigger = false;

    if (which_is_bigger(number, j.number) == 0)
        this_number_is_bigger = true;
    else
        second_number_is_bigger = true;

    unsigned long long int sum_of_decimals_of_two_numbers =
        (number.size() - (float_point_index == 0 ? number.size() : float_point_index)) +
        (j.number.size() - (j.float_point_index == 0 ? j.number.size() : j.float_point_index));

    sum_obj.float_point_index = sum_obj.number.size() - sum_of_decimals_of_two_numbers;
    trim_the_number(sum_obj, (this_number_is_bigger && has_negative_sign) || (second_number_is_bigger && j.has_negative_sign));
    return sum_obj;
}

JMP JMP::operator+(const long double &j)
{
    JMP sum_obj = JMP("0"), num2(double_to_string(j));
    int temp_number_size = number.size(), temp_second_number_size = num2.number.size();
    equalizing_figures(num2);

    // Check which number is bigger, and we equal the sum object number to the biggest number
    bool this_number_is_bigger = false, second_number_is_bigger = false;
    if (which_is_bigger(number, num2.number) == 0)
    {
        sum_obj.number = number;
        if (float_point_index != 0)
            sum_obj.float_point_index = float_point_index;
        else if (float_point_index == 0 && num2.float_point_index != 0)
            sum_obj.float_point_index = temp_number_size;
        else
            sum_obj.float_point_index = 0;
        this_number_is_bigger = true;
    } else {
        sum_obj.number = num2.number;
        if (num2.float_point_index != 0)
            sum_obj.float_point_index = num2.float_point_index;
        else if (num2.float_point_index == 0 && float_point_index != 0)
            sum_obj.float_point_index = temp_second_number_size;
        else
            sum_obj.float_point_index = 0;
        second_number_is_bigger = true;
    }

    summation(sum_obj, number, num2.number, this_number_is_bigger, second_number_is_bigger, has_negative_sign, num2.has_negative_sign);
    trim_the_number(sum_obj, (this_number_is_bigger && has_negative_sign) || (second_number_is_bigger && num2.has_negative_sign));

    return sum_obj;
}

JMP JMP::operator+(string &num2_str)
{
    JMP sum_obj = JMP("0"), num2(num2_str);
    int temp_number_size = number.size(), temp_second_number_size = num2.number.size();
    equalizing_figures(num2);

    bool this_number_is_bigger = false, second_number_is_bigger = false;
    if (which_is_bigger(number, num2.number) == 0)
    {
        sum_obj.number = number;
        if (float_point_index != 0)
            sum_obj.float_point_index = float_point_index;
        else if (float_point_index == 0 && num2.float_point_index != 0)
            sum_obj.float_point_index = temp_number_size;
        else
            sum_obj.float_point_index = 0;
        this_number_is_bigger = true;
    } else {
        sum_obj.number = num2.number;
        if (num2.float_point_index != 0)
            sum_obj.float_point_index = num2.float_point_index;
        else if (num2.float_point_index == 0 && float_point_index != 0)
            sum_obj.float_point_index = temp_second_number_size;
        else
            sum_obj.float_point_index = 0;
        second_number_is_bigger = true;
    }

    summation(sum_obj, number, num2.number, this_number_is_bigger, second_number_is_bigger, has_negative_sign, num2.has_negative_sign);
    trim_the_number(sum_obj, (this_number_is_bigger && has_negative_sign) || (second_number_is_bigger && num2.has_negative_sign));

    return sum_obj;
}

JMP JMP::operator+(const char* num_str)
{
    JMP sum_obj = JMP("0"), num2(num_str);
    int temp_number_size = number.size(), temp_second_number_size = num2.number.size();
    equalizing_figures(num2);

    bool this_number_is_bigger = false, second_number_is_bigger = false;
    if (which_is_bigger(number, num2.number) == 0)
    {
        sum_obj.number = number;
        if (float_point_index != 0)
            sum_obj.float_point_index = float_point_index;
        else if (float_point_index == 0 && num2.float_point_index != 0)
            sum_obj.float_point_index = temp_number_size;
        else
            sum_obj.float_point_index = 0;
        this_number_is_bigger = true;
    } else {
        sum_obj.number = num2.number;
        if (num2.float_point_index != 0)
            sum_obj.float_point_index = num2.float_point_index;
        else if (num2.float_point_index == 0 && float_point_index != 0)
            sum_obj.float_point_index = temp_second_number_size;
        else
            sum_obj.float_point_index = 0;
        second_number_is_bigger = true;
    }

    summation(sum_obj, number, num2.number, this_number_is_bigger, second_number_is_bigger, has_negative_sign, num2.has_negative_sign);
    trim_the_number(sum_obj, (this_number_is_bigger && has_negative_sign) || (second_number_is_bigger && num2.has_negative_sign));

    return sum_obj;
}

JMP operator+(const long double &j, JMP &this_obj)
{
    JMP sum_obj = JMP(0), num2(double_to_string(j));
    double check;
    if (modf(j, &check) == 0.0)
    {
        num2.number = num2.number.substr(0, num2.float_point_index);    
        num2.float_point_index = 0;
    }

    int temp_number_size = this_obj.number.size(), temp_second_number_size = num2.number.size();
    this_obj.equalizing_figures(num2);

    bool this_number_is_bigger = false, second_number_is_bigger = false;
    if (this_obj.which_is_bigger(this_obj.number, num2.number) == 0)
    {
        sum_obj.number = this_obj.number;
        if (this_obj.float_point_index != 0)
            sum_obj.float_point_index = this_obj.float_point_index;
        else if (this_obj.float_point_index == 0 && num2.float_point_index != 0)
            sum_obj.float_point_index = temp_number_size;
        else
            sum_obj.float_point_index = 0;
        this_number_is_bigger = true;
    } else {
        sum_obj.number = num2.number;
        if (num2.float_point_index != 0)
            sum_obj.float_point_index = num2.float_point_index;
        else if (num2.float_point_index == 0 && this_obj.float_point_index != 0)
            sum_obj.float_point_index = temp_second_number_size;
        else
            sum_obj.float_point_index = 0;
        second_number_is_bigger = true;
    }

    this_obj.summation(sum_obj, this_obj.number, num2.number, this_number_is_bigger, second_number_is_bigger, this_obj.has_negative_sign, num2.has_negative_sign);
    this_obj.trim_the_number(sum_obj, (this_number_is_bigger && this_obj.has_negative_sign) || (second_number_is_bigger && num2.has_negative_sign));

    return sum_obj;
}

JMP operator+(string &num2_str, JMP &this_obj)
{
    JMP sum_obj = JMP("0"), num2(num2_str);
    int temp_number_size = this_obj.number.size(), temp_second_number_size = num2.number.size();
    this_obj.equalizing_figures(num2);

    bool this_number_is_bigger = false, second_number_is_bigger = false;
    if (this_obj.which_is_bigger(this_obj.number, num2.number) == 0)
    {
        sum_obj.number = this_obj.number;
        if (this_obj.float_point_index != 0)
            sum_obj.float_point_index = this_obj.float_point_index;
        else if (this_obj.float_point_index == 0 && num2.float_point_index != 0)
            sum_obj.float_point_index = temp_number_size;
        else
            sum_obj.float_point_index = 0;
        this_number_is_bigger = true;
    } else {
        sum_obj.number = num2.number;
        if (num2.float_point_index != 0)
            sum_obj.float_point_index = num2.float_point_index;
        else if (num2.float_point_index == 0 && this_obj.float_point_index != 0)
            sum_obj.float_point_index = temp_second_number_size;
        else
            sum_obj.float_point_index = 0;
        second_number_is_bigger = true;
    }

    this_obj.summation(sum_obj, this_obj.number, num2.number, this_number_is_bigger, second_number_is_bigger, this_obj.has_negative_sign, num2.has_negative_sign);
    this_obj.trim_the_number(sum_obj, (this_number_is_bigger && this_obj.has_negative_sign) || (second_number_is_bigger && num2.has_negative_sign));

    return sum_obj;
}

JMP operator+(const char* num2_str, JMP &this_obj)
{
    JMP sum_obj = JMP("0"), num2(num2_str);
    int temp_number_size = this_obj.number.size(), temp_second_number_size = num2.number.size();
    this_obj.equalizing_figures(num2);

    bool this_number_is_bigger = false, second_number_is_bigger = false;
    if (this_obj.which_is_bigger(this_obj.number, num2.number) == 0)
    {
        sum_obj.number = this_obj.number;
        if (this_obj.float_point_index != 0)
            sum_obj.float_point_index = this_obj.float_point_index;
        else if (this_obj.float_point_index == 0 && num2.float_point_index != 0)
            sum_obj.float_point_index = temp_number_size;
        else
            sum_obj.float_point_index = 0;
        this_number_is_bigger = true;
    } else {
        sum_obj.number = num2.number;
        if (num2.float_point_index != 0)
            sum_obj.float_point_index = num2.float_point_index;
        else if (num2.float_point_index == 0 && this_obj.float_point_index != 0)
            sum_obj.float_point_index = temp_second_number_size;
        else
            sum_obj.float_point_index = 0;
        second_number_is_bigger = true;
    }

    this_obj.summation(sum_obj, this_obj.number, num2.number, this_number_is_bigger, second_number_is_bigger, this_obj.has_negative_sign, num2.has_negative_sign);
    this_obj.trim_the_number(sum_obj, (this_number_is_bigger && this_obj.has_negative_sign) || (second_number_is_bigger && num2.has_negative_sign));

    return sum_obj;
}

void JMP::operator+=(const long double &j)
{
    *this = *this + j;
}

void JMP::operator+=(string &num2_str)
{
    *this = *this + num2_str;
}

void JMP::operator+=(const char* num2_str)
{
    *this = *this + num2_str;
}

void operator+=(long double &j, JMP &this_obj)
{
    j = (j + this_obj).to_double();
}

void operator+=(string &j, JMP &this_obj)
{
    j = (j + this_obj).to_string();
}