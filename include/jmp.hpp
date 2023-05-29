/* Definitions for JMP class functions   -*- mode: C++ -*-

Copyleft(🄯) All uses of this library are free.
  * This library is for challenging my (or your) C++ knowledge to write the good Multiple Precision Arithmetic Library,
    all advice or help would be appreciated.

Authors:
  * Jibel Sadeghi <itsjibel@gmail.com> */

#include <algorithm>
#include <complex>
#include <memory>

class jmp
{
    private:
        typedef unsigned long long int ulli;
        /// The main members of the class
        ulli float_point_index {0};
        long long int division_precision {20}, precision {-1};
        std::string number {"0"};
        bool initialized {false};

        /// The helper functions
        void validation (const std::string& num);
        bool which_string_number_is_bigger(const std::string& num1, const std::string& num2) const;
        void equalizing_figures(jmp& j);
        void trim_the_number(jmp& j, const bool bigger_number_is_negative);

        /// Arithmetic functions
        void FFT(std::complex<double>* a, ulli& n, const bool invert);
        std::string sum(const std::string& num1, const std::string& num2,
                        bool first_number_is_bigger, bool second_number_is_bigger,
                        bool first_number_is_negative, bool second_number_is_negative,
                        ulli& sum_obj_float_point_index);
        std::string multiply(const std::string& num1, const std::string& num2);
        std::string divide(const std::string num1, ulli num2);

    public:
        bool is_negative {false};
        /// Constructors
        jmp() {}
        explicit jmp(const std::string& num) { initialized = true; validation(num); }
        explicit jmp(const char* num)        { initialized = true; validation(num); }
        explicit jmp(long double num)
        {
            /// Counvert double to string
            // Create an output std::string stream object
            std::ostringstream strs;
            // Insert the value of 'num' into the output stream
            strs<<num;
            // Retrieve the contents of the output stream as a std::string and return it
            validation(strs.str());
            initialized = true;
        }

        jmp (const jmp& j)
        {
            number = j.number;
            float_point_index = j.float_point_index;
            is_negative = j.is_negative;
            initialized = true;
        }

        /// Destructor
        ~jmp() { reset(); }

        /// ostream operator
        friend std::ostream& operator<<(std::ostream& o, const jmp& j)
        {
            o<<(j.is_negative ? '-' : '\0');
            o<<j.number;
            return o;
        }

        void reset()
        {
            number = float_point_index = is_negative = initialized = 0;
            precision = -1;
        }

        // Getter functions
        std::string get_number() const
        {
            return number;
        }

        // Conversion functions
        jmp internal_conversion_to_int()
        {
            number = number.substr(0, float_point_index);
            float_point_index = 0;
            return *this;
        }

        jmp append (const std::string& num)
        {
            if (!num.empty() && std::find_if(num.begin(), 
                 num.end(), [](unsigned char c) { return !std::isdigit(c); }) == num.end())
                number.append(num);
            return *this;
        }

        jmp set_precision (long long int precision)
        {
            if (precision >= -1)
            {
                this->precision = precision;
                if (precision != -1)
                    number = number.substr(0, float_point_index + precision + (precision == 0 ? 0 : 1));
                float_point_index = precision == 0 ? 0 : float_point_index;
            }
            return *this;
        }

        void set_division_precision (long long int precision)
        {
            division_precision = precision >= 0 ? precision : 20;
        }

        jmp round_precision (long long int precision)
        {
            // Rounding the number in decimals
            if (precision == 0)
            {
                jmp one(1);
                if (number[float_point_index + 1] >= '5')
                    *this += one;
            } else {
                jmp number_add_after_rounding("0.1"), one_tenth("0.1");
                for (int i=1; i<precision; i++)
                    number_add_after_rounding *= one_tenth;

                if (number[float_point_index + precision + 1] >= '5')
                    *this += number_add_after_rounding;
            }

            if (precision >= -1)
            {
                if (precision != -1)
                    number = number.substr(0, float_point_index + precision + (precision == 0 ? 0 : 1));
                float_point_index = precision == 0 ? 0 : float_point_index;
                this->precision = precision;
            }
            return *this;
        }

        // About-number functions
        bool is_decimal() const { return float_point_index != 0; }
        bool is_integer() const { return float_point_index == 0; }
        bool is_initialized() const { return initialized; }
        ulli size()       const { return number.size(); }
        ulli allocated()  const { return (number.capacity() * sizeof(char)) + sizeof(ulli) + sizeof(bool) * 2; }

        /* =========================================
                      Summation operators
           ========================================= */
        jmp operator+(jmp& j);
        jmp operator+=(jmp& j);
        jmp operator++();
        jmp operator++(int);

        /* =========================================
                     Subtraction operators
           ========================================= */
        jmp operator-(jmp& j);
        jmp operator-=(jmp& j);
        jmp operator--(int);
        jmp operator--();

        /* =========================================
                    Multiplication operators
           ========================================= */
        jmp operator*(jmp& j);
        jmp operator*=(jmp& j);

        /* =========================================
                     Divideation operators
           ========================================= */
        jmp operator/(jmp& j);
        jmp operator/=(jmp& j);

        /* =========================================
                    Exponentiation function
           ========================================= */
        jmp powof(jmp j);

        /* =========================================
                     Conditional operators
           ========================================= */
        bool operator==(jmp& j) const;
        bool operator!=(jmp& j) const;
        bool operator<(jmp& j) const;
        bool operator<=(jmp& j) const;
        bool operator>(jmp& j) const;
        bool operator>=(jmp& j) const;
};

namespace JMP
{
    jmp abs(jmp& j)
    {
        j.is_negative = false;
        return j;
    }

    jmp fact(jmp& j)
    {
        jmp zero("0");
        if (j == zero)
            return jmp("1");
        if (j.is_decimal() || j < zero)
            std::__throw_logic_error("JMP::fact: Factorial is only defined for natural numbers.");

        jmp result("1");
        for (jmp i=jmp(1); i<=j; i++)
            result *= i;

        return result;
    }

    long long int to_int    (jmp j) { return atoi(j.get_number().c_str()); }
    long double   to_double (jmp j) { return std::stold(j.get_number()); }
    std::string   to_string (jmp j) { return j.get_number(); }
};

void jmp::FFT(std::complex<double>* a, ulli& n, const bool invert)
{
    const double angleMultiplier = (invert ? -2.0 : 2.0) * M_PI / n;

    // Bit-reversal permutation
    for (ulli i = 1, j = 0; i < n; ++i)
    {
        ulli bit = n >> 1;
        while (j & bit)
        {
            j ^= bit;
            bit >>= 1;
        }
        j ^= bit;

        if (i < j)
            std::swap(a[i], a[j]);
    }

    // Precompute twiddle factors and perform butterfly operations
    for (ulli len = 2; len <= n; len <<= 1)
    {
        const double deltaAngle = angleMultiplier * (n / len);
        const std::complex<double> omegaBase = std::polar(1.0, deltaAngle);
        std::complex<double> omega = 1.0;

        for (ulli i = 0; i < len / 2; ++i)
        {
            for (ulli j = i; j < n; j += len)
            {
                std::complex<double> u = a[j];
                std::complex<double> t = omega * a[j + len / 2];
                a[j] = u + t;
                a[j + len / 2] = u - t;
            }

            omega *= omegaBase;
        }
    }

    // Normalize the output if invert flag is set
    if (invert)
    {
        const double scale = 1.0 / n;
        for (ulli i = 0; i < n; ++i)
            a[i] *= scale;
    }
}

std::string jmp::multiply(const std::string& num1, const std::string& num2)
{
    const ulli size1 {num1.size()}, size2 {num2.size()};
    ulli n {1};
    while (n < size1 + size2)
        n <<= 1;
    std::unique_ptr<std::complex<double>[]> a = std::make_unique<std::complex<double>[]>(n);
    std::unique_ptr<std::complex<double>[]> b = std::make_unique<std::complex<double>[]>(n);

    // Convert input strings to complex number arrays
    for (ulli i{0}; i<size1; ++i)
        a[i] = num1[size1 - i - 1] - '0';
    for (ulli i{0}; i < size2; ++i)
        b[i] = num2[size2 - i - 1] - '0';

    // Perform FFT on both arrays
    FFT(a.get(), n, false);
    FFT(b.get(), n, false);

    // Multiply the transformed arrays element-wise
    for (ulli i{0}; i<n; ++i)
        a[i] *= b[i];

    // Perform inverse FFT to obtain the convolution result
    FFT(a.get(), n, true);

    ulli carry {0};
    std::string result;

    // Construct the result std::string by rounding the real parts and performing carry propagation
    for (ulli i{0}; i<n; ++i)
    {
        ulli digit {static_cast<ulli>(a[i].real() + 0.5) + carry};
        result += '0' + (digit % 10);
        carry = digit / 10;
    }

    // Remove trailing zeros from the result string
    while (result.size() > 1 && result.back() == '0')
        result.pop_back();

    // Efficiently reverse the result string
    ulli start {0}, end {result.size() - 1};
    while (start < end)
    {
        std::swap(result[start], result[end]);
        ++start;
        --end;
    }

    return result;
}

void jmp::validation (const std::string& num)
{
    number = num;
    // If number is empty so is not valid
    if (number.empty())
    {
        number = "0";
        return;
    }
    // We erase the number sign to just check that this number std::string indexes are number or aren't a number
    if (number[0] == '-')
    {
        number.erase(number.begin());
        float_point_index = float_point_index > 0 ? float_point_index - 1 : 0;
        is_negative = true;
    } else if (number[0] == '+') {
        number.erase(number.begin());
        float_point_index = float_point_index > 0 ? float_point_index - 1 : 0;
    }

    bool valid {true}, number_of_dots {0};
    for (ulli i{0}; i<number.size(); i++)
    {
        /* If the number character is '.', so we add 1 to number_of_dots to know how many dots we have in-
           the number characters, then update the float_point_index to know-
           where is the point index in the number */
        if (number[i] == '.')
        {
            if (number_of_dots == 1)
            {
                valid = false;
                break;
            }
            number_of_dots = 1;
            float_point_index = i;
        } else if (number[i] < '0' || number[i] > '9') {
            /* If the number character is not in the range 0-9 and the number character is not '.'-
               then this character is invalid */
            valid = false;
            break;
        }
    }

    // "If conditions" for falsing the validity of the number string
    if ((number[0] == '0' && number[1] != '.') ||
        number.front() == '.')
        valid = false;

    if (!valid)
        number = 48 + (valid = is_negative = float_point_index = false);

    /* If the last index of the number is a '.' character so the user meant that this number is-
       a float number so we do consider this for the JMP number. */
    if (number.back() == '.') number.push_back('0');

    /* If the number is valid, we match the decimal precision of the number-
       that we are going to put in our number member with the decimal precision of the class itself. */
    if (valid && precision != -1 && number.size() - 1 > float_point_index + precision)
        number = number.substr(0, float_point_index + precision + (precision != 0 ? 1 : 0));
}

bool jmp::which_string_number_is_bigger(const std::string& num1, const std::string& num2) const
{
    // This function takes two strings that number and compares them in terms of size
    // First of all, we check the simple things make the number bigger than other
    // It's clear if the number std::string has a bigger length when is bigger than other
    auto num1size {num1.size()}, num2size {num2.size()};
    if (num1size > num2size)
        return 0;
    else if (num2size > num1size)
        return 1;
    else
    {
        // If the two std::string numbers have the same length then we should check digit by digit to-
        // understand which number is bigger
        int counter {0};
        while (counter < num1size)
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

std::string jmp::sum (const std::string& num1, const std::string& num2,
                      bool first_number_is_bigger, bool second_number_is_bigger,
                      bool first_number_is_negative, bool second_number_is_negative,
                      ulli& sum_obj_float_point_index)
{
    std::string result = first_number_is_bigger ? num1 : num2;

    if (first_number_is_bigger && (first_number_is_negative == second_number_is_negative))
    {
        /* If the numbers have the same sign (both are positive or negative),
           and this number is bigger, so we sum the second number to this number like this: */
        auto difference_size_of_two_numbers {num1.size() - num2.size()};
        for (auto i{num1.size() - 1}; i>0; i--)
        {
            /* We start from the last digit of this number and move forwards to the second digit,
               and if the current digit is greater than the difference between the two digits,
               we add the current digit of this number to the second digit. */
            if (i >= difference_size_of_two_numbers)
                result[i] += num2[i - difference_size_of_two_numbers] - '0';

            /* If the current digit gets more than '9',
               then we add 1 to the previous digit and subtract 10 from the current digit */
            if (result[i] > '9')
            {
                result[i - 1] += 1;
                result[i] -= 10;
            }
        }

        // If the difference between two numbers is zero, we add the first digits of the two numbers together
        if (0 == difference_size_of_two_numbers)
            result[0] += num2[0] - '0';

        // And again do the previous condition for the first digit
        if (result[0] > '9')
        {
            result[0] -= 10;
            result = '1' + result;
            sum_obj_float_point_index = sum_obj_float_point_index != 0 ? sum_obj_float_point_index + 1 : 0;
        }
    }
    else if (second_number_is_bigger && (first_number_is_negative == second_number_is_negative))
    {
        // This is the same. Just for the second number instead of this number.
        auto difference_size_of_two_numbers {num2.size() - num1.size()};
        for (auto i{num2.size() - 1}; i>0; i--)
        {
            if (i >= difference_size_of_two_numbers)
                result[i] += num1[i - (difference_size_of_two_numbers)] - '0';
            if (i != 0 && result[i] > '9')
            {
                result[i - 1] += 1;
                result[i] -= 10;
            }
        }
        if (result[0] > '9')
        {
            result[0] -= 10;
            result = '1' + result;
            sum_obj_float_point_index = sum_obj_float_point_index != 0 ? sum_obj_float_point_index + 1 : 0;
        }
    }
    else if (first_number_is_bigger && (first_number_is_negative != second_number_is_negative))
    {
        /* If the number signs are not equal together and this number is bigger,
          so we subtract the second number from this number */
        auto difference_size_of_two_numbers {num1.size() - num2.size()};
        for (auto i{num1.size() - 1}; i>0; i--)
        {
            /* We start from the last digit of this number and move forwards to the second digit,
               and if the current digit is greater than the difference between the two digits,
               we subtract second number digit from the current digit of this number. */
            if (i >= difference_size_of_two_numbers)
                result[i] -= num2[i - difference_size_of_two_numbers] - '0';

            /* If the current digit gets less than '0',
               then we subtract 1 to the previous digit and add 10 to the current digit */
            if (result[i] < '0')
            {
                result[i] += 10;
                result[i - 1]--;
            }
        }
        /* If the difference size of two numbers is 0,
           then in the last action we subtract the first digit of the second number from this number.
         */
        if (0 == difference_size_of_two_numbers)
            result[0] -= num2[0] - '0';
    }
    else if (second_number_is_bigger && (is_negative != second_number_is_negative))
    {
        // This is the same. Just for the second number instead of this number.
        auto difference_size_of_two_numbers {num2.size() - num1.size()};
        for (auto i{num2.size() - 1}; i>0; i--)
        {
            if (i >= difference_size_of_two_numbers)
                result[i] -= num1[i - difference_size_of_two_numbers] - '0';

            if (result[i] < '0')
            {
                result[i] += 10;
                result[i - 1]--;
            }
        }

        if (0 == difference_size_of_two_numbers)
            result[0] -= num1[0] - '0';
    }
    return std::move(result);
}


std::string jmp::divide(const std::string num1, ulli num2)
{
    ulli divisor = num2, index {0};
    std::string result;
    int dividend {num1[index] - '0'};
    while (dividend < divisor)
        dividend = dividend * 10 + (num1[++index] - '0');

    while (num1.size() > index)
    {
        result += (dividend / divisor) + '0';
        dividend = (dividend % divisor) * 10 + num1[++index] - '0';
    }
    return result.length() == 0 ? "0" : result;
}

void jmp::equalizing_figures(jmp& j)
{
    // If two numbers do not have the same decimals, we add '0' decimals to the end of that number that has lower decimals.
    if (j.float_point_index != 0 && float_point_index != 0 && (number.size() - float_point_index) > (j.number.size() - j.float_point_index))
    {
        // It means this number has more decimals than second number
        // Now we need to know how many '0' decimals we should push back to the second number.
        long unsigned int how_many_zeros {(number.size() - float_point_index) - (j.number.size() - j.float_point_index)};
        for (int i{0}; i<how_many_zeros; i++)
            j.number.push_back('0');
    }
    else if (j.float_point_index != 0 && float_point_index != 0 && (number.size() - float_point_index) < (j.number.size() - j.float_point_index))
    {
        // It means the second number has more decimals than this number, so we equalize the figure of this number to the second number.
        long unsigned int how_many_zeros {(j.number.size() - j.float_point_index) - (number.size() - float_point_index)};
        for (int i{0}; i<how_many_zeros; i++)
            number.push_back('0');
    }
    else if (j.float_point_index != 0 && float_point_index == 0)
    {
        long unsigned int how_many_zeros {j.number.size() - j.float_point_index};
        for (int i{0}; i<how_many_zeros; i++)
            number.push_back('0');
    }
    else if (j.float_point_index == 0 && float_point_index != 0)
    {
        long unsigned int how_many_zeros {number.size() - float_point_index};
        for (int i{0}; i<how_many_zeros; i++)
            j.number.push_back('0');
    }
}

void jmp::trim_the_number(jmp& j, const bool bigger_number_is_negative)
{
    // Erase the useless beginning zeros after subtraction
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

    // Remove the ending useless zeros after subtraction
    while (j.number[j.number.size() - 1] == '0' && j.float_point_index != 0 && j.float_point_index != j.number.size())
        j.number.erase(j.number.begin() + j.number.size() - 1);

    if (j.number.empty())
        j.number = "0";
    else if (bigger_number_is_negative)
        j.is_negative = true;

    // If the float index is the last index of the number so we push back '0' to the number to have the valid number.
    if (j.float_point_index != 0 && j.float_point_index == j.number.size())
        j.number.append("0");
}

jmp jmp::operator+(jmp& j)
{
    // Erase the float point from numbers to start the calculation
    if (j.float_point_index != 0)
        j.number.erase(j.number.begin() + j.float_point_index);
    if (float_point_index != 0)
        number.erase(number.begin() + float_point_index);

    jmp sum_obj;
    ulli temp_number_size {number.size()}, temp_second_number_size {j.number.size()};
    equalizing_figures(j);
    // Check which number is bigger, and we equal the sum object number to the biggest number
    bool this_number_is_bigger {false}, second_number_is_bigger {false};
    if (which_string_number_is_bigger(number, j.number) == 0)
    {
        if (float_point_index != 0)
            sum_obj.float_point_index = float_point_index;
        else if (j.float_point_index != 0)
            sum_obj.float_point_index = temp_number_size;
        this_number_is_bigger = true;
    } else {
        if (j.float_point_index != 0)
            sum_obj.float_point_index = j.float_point_index;
        else if (float_point_index != 0)
            sum_obj.float_point_index = temp_second_number_size;
        second_number_is_bigger = true;
    }

    // Get sum of the two filtered strings
    sum_obj.number = sum(number, j.number, this_number_is_bigger, second_number_is_bigger,
                         is_negative, j.is_negative, sum_obj.float_point_index);

    /* Trim the number means if we have a number such as '000012.32400' after the sum of two numbers, we trim the number to '12.324'
     * (-999900 + 999912) = 000012  ---> 12
     * (-0.2222 + 12.2222) = 12.0000 ---> 12
     * (-9900.22 + 9912.22) = 0012.00 ---> 12 */
    trim_the_number(sum_obj, (this_number_is_bigger && is_negative) || (second_number_is_bigger && j.is_negative));
    
    // Add float point to numbers
    if (float_point_index != 0)
        number.insert(number.begin() + float_point_index, '.');
    if (j.float_point_index != 0)
        j.number.insert(j.number.begin() + j.float_point_index, '.');
    if (sum_obj.float_point_index != 0)
        sum_obj.number.insert(sum_obj.number.begin() + sum_obj.float_point_index, '.');

    sum_obj.is_negative = (j.is_negative && second_number_is_bigger) || (is_negative && this_number_is_bigger);

    return sum_obj;
}

jmp jmp::operator*(jmp& j)
{
    // Erase the float point from numbers to start the calculation
    if (j.float_point_index != 0 && j.float_point_index < j.number.size())
        j.number.erase(j.number.begin() + j.float_point_index);
    if (float_point_index != 0 && float_point_index < number.size())
        number.erase(number.begin() + float_point_index);

    jmp mul_obj;
    if (j.number == "1")
        mul_obj = jmp(number);
    else if (number == "1")
        mul_obj = jmp(j.number);
    else
        mul_obj.number = multiply(number, j.number);

    ulli sum_of_decimals_of_two_numbers {
        (number.size() - (float_point_index == 0 ? number.size() : float_point_index)) +
        (j.number.size() - (j.float_point_index == 0 ? j.number.size() : j.float_point_index))};

    /* When we have two numbers like 0.0001, and 0.00002,
       mul_obj gets 2 because 1 * 2 is 2, and sum_of_decimals_of_two_numbers gets 9-
       because we have 4 decimals in 0.0001 and 5 decimals in 0.00002,
       so if we want to get correct multiplication,
       we have to add '0' sum_of_decimals_of_two_numbers - mul_obj.number.size() times-
       to begin of the number to get the correct multiplication result, which is 0.000000003.
       (8 zeros to the beginning of '3' result give '000000003' and we add one '0' for the decimal number to have 0.0000...) */
    while (mul_obj.number.size() <= sum_of_decimals_of_two_numbers)
        mul_obj.number = "0" + mul_obj.number;

    mul_obj.float_point_index = mul_obj.number.size() - sum_of_decimals_of_two_numbers;

    /* Determining the negativity of a number from the simple principle of-
       negative in positive negative and positive in negative negative */
    mul_obj.is_negative = (is_negative == true && j.is_negative == false) ||
                          (is_negative == false && j.is_negative == true);

    // Add float point to numbers
    if (float_point_index != 0)
        number.insert(number.begin() + float_point_index, '.');
    if (j.float_point_index != 0)
        j.number.insert(j.number.begin() + j.float_point_index, '.');
    if (mul_obj.float_point_index != 0 && mul_obj.float_point_index != mul_obj.number.size())
        mul_obj.number.insert(mul_obj.number.begin() + mul_obj.float_point_index, '.');

    // Remove the ending useless zeros after multiplication
    while (mul_obj.float_point_index != 0 && mul_obj.number[mul_obj.number.size() - 1] == '0' &&
           (mul_obj.float_point_index <= mul_obj.number.size() - 1))
        mul_obj.number.erase(mul_obj.number.begin() + mul_obj.number.size()  - 1);

    return mul_obj;
}

jmp jmp::operator-(jmp& j)
{
    jmp negative(j);
    negative.is_negative = true;
    return *this + negative;
}

jmp jmp::operator/(jmp& j)
{
    jmp check("0.0"), check2("0");
    if (j == check || j == check2)
        std::__throw_logic_error("jmp::operator/: Can not do division operation for zero.");

    bool first_time = true;
    /// Make ready the numbers for division
    /* Erase the float point from numbers to start the calculation
       and if the numbers for division is decimal we convert them to integer. */
    if (j.float_point_index != 0)
        j.number.erase(j.number.begin() + j.float_point_index);
    if (float_point_index != 0)
        number.erase(number.begin() + float_point_index);

    // Equalize the number of decimals
    while (number.size() - float_point_index < j.number.size() - j.float_point_index &&
          (j.float_point_index != 0 || float_point_index != 0))
        number.push_back('0');
    while (j.number.size() - j.float_point_index < number.size() - float_point_index &&
          (j.float_point_index != 0 || float_point_index != 0))
        j.number.push_back('0');

    // Delete the beginning zeros from number that have '0' in the beginning
    ulli number_of_deleted_zeros {0}, number_of_deleted_zeros_j {0};
    while (number[0] == '0')
    {
        number.erase(number.begin());
        number_of_deleted_zeros++;
    }
    while (j.number[0] == '0')
    {
        number_of_deleted_zeros_j++;
        j.number.erase(j.number.begin());
    }

    /* Set the float point index to zero to don't make a mistake in the calculation,
       and save them for restoring the numbers to default. */
    ulli temp_float_point_index {float_point_index}, j_temp_float_point_point = j.float_point_index;
    float_point_index = j.float_point_index = 0;

    jmp div_obj;
    /* If the number will divide by 1 when we are sure the result will be the number we have,
       so we equal the 'div_obj' to the number, if the number will not divide by 1, we do the division */
    if (j.number == "1" || j.number == "1.0")
        div_obj = jmp(number);
    else if (which_string_number_is_bigger("18446744073099999999", j.number) == 1)
        std::__throw_range_error("jmp::operator/: Divisor can not be larger than 18446744073099999999.");
    else
    {
        ulli num2 = std::stoull(j.number);
        std::string quotient = divide(number, num2);
        jmp jmp_quotient(quotient);
        jmp sub(JMP::to_string(jmp_quotient * j));
        jmp remaining = *this - sub, zero("0.0");
        ulli temp_remaining_size = remaining.number.size();

        while (remaining != zero)
        {
            if (first_time)
            {
                first_time = false;
                quotient.append(".");
            }

            if (remaining.float_point_index != 0)
                remaining.number.erase(remaining.number.begin() + remaining.number.find('.'));

            while (temp_remaining_size >= remaining.number.size())
                remaining.number.push_back('0');

            quotient.append(divide(remaining.number, num2));
            if (quotient.size() - quotient.find('.') > division_precision)
            {
                quotient = quotient.substr(0, quotient.find('.') + division_precision + 1);
                break;
            }
            temp_remaining_size = remaining.number.size();
            jmp_quotient = jmp(quotient);
            jmp current_result = jmp_quotient * j;
            jmp n(number);
            remaining = n - current_result;
        }
        div_obj = jmp(quotient);
    }

    // Add the deleted zeros from numbers
    for (ulli i=0; i<number_of_deleted_zeros; i++)
        number.insert(number.begin(), '0');
    for (ulli i=0; i<number_of_deleted_zeros_j; i++)
        j.number.insert(j.number.begin(), '0');

    float_point_index = temp_float_point_index;
    j.float_point_index = j_temp_float_point_point;
    // Add float point to numbers
    if (float_point_index != 0)
        number.insert(number.begin() + float_point_index, '.');
    if (j.float_point_index != 0)
        j.number.insert(j.number.begin() + j.float_point_index, '.');

    // Set the negativity of the division product
    div_obj.is_negative = (is_negative == true && j.is_negative == false) ||
                          (is_negative == false && j.is_negative == true);

    // Set the decimal of the division product
    jmp one_tenth("0.1"), zero("0.0");
    if (div_obj != zero)
    for (ulli i=0; i<abs((number.size()-(float_point_index != 0 ? float_point_index : number.size()+1)-1) -
                         (j.number.size()-(j.float_point_index != 0 ? j.float_point_index : j.number.size()+1)-1)); i++)
        div_obj *= one_tenth;

    return div_obj;
}

jmp jmp::operator++()
{
    jmp one("1");
    *this += one;
    return *this;
}

jmp jmp::operator--()
{
    jmp one("1");
    *this -= one;
    return *this;
}

jmp jmp::operator++(int)
{
    jmp temp(*this), one("1");
    *this += one;
    return temp;
}

jmp jmp::operator--(int)
{
    jmp temp = *this, one("1");
    *this -= one;
    return temp;
}

jmp operator+(const long double j, jmp& this_obj)
{
    jmp num2(j);
    return this_obj + num2;
}

jmp jmp::operator+=(jmp& num2_str)
{
    *this = *this + num2_str;
    return *this;
}

jmp jmp::operator*=(jmp& num2_str)
{
    *this = *this * num2_str;
    return *this;
}

jmp jmp::operator-=(jmp& j)
{
    *this = *this - j;
    return *this;
}

long double operator+=(long double j, jmp& this_obj)
{
    j = JMP::to_double(j + this_obj);
    return j;
}

jmp jmp::powof(jmp j)
{
    jmp result("1"), negative_one("-1");
    if (j.is_negative)
        while (j++ <= negative_one)
            result = result / *this;
    else
        while (--j > negative_one)
            result *= *this;
    return result;
}

bool jmp::operator==(jmp& j) const
{
    return (is_negative ? "-" : "") + number == (j.is_negative ? "-" : "") + j.number ? true : false;
}

bool jmp::operator!=(jmp& j) const
{
    return (is_negative ? "-" : "") + number != (j.is_negative ? "-" : "") + j.number ? true : false;
}

bool jmp::operator<(jmp& j) const
{
    if (*this == j)
        return false;

    if (is_negative && j.is_negative == false)
        return true;
    else if (is_negative == false && j.is_negative)
        return false;

    bool which_number_is_bigger = which_string_number_is_bigger(number, j.number);
    if (which_number_is_bigger == 1 && j.is_negative)
        return false;
    else if (which_number_is_bigger == 0 && is_negative == true)
        return true;
    else if (which_number_is_bigger == 1 && j.is_negative == false)
        return true;
    return false;
}

bool jmp::operator<=(jmp& j) const
{
    return *this < j || *this == j ? true : false;
}

bool jmp::operator>(jmp& j) const
{
    return *this < j == false && *this != j ? true : false;
}

bool jmp::operator>=(jmp& j) const
{
    return *this > j || *this == j ? true : false;
}