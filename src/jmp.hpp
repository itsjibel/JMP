#include <algorithm>
#include <complex>
#include <string>
using std::string;

string double_to_string(const long double& num)
{
    // Create an output string stream object
    std::ostringstream strs;
    // Insert the value of 'num' into the output stream
    strs << num;
    // Retrieve the contents of the output stream as a string and return it
    return strs.str();
}

class jmp
{
    private:
        typedef unsigned long long int ulli;
        void validation (const string& num);
        bool which_is_bigger(const string& num1, const string& num2) const;
        void equalizing_figures(jmp& j);
        void trim_the_number(jmp& j, const bool& bigger_number_is_negative);

        /// Arithmetic functions
        void FFT(std::complex<double>* a, size_t& n, const bool& invert);
        void summation(jmp& sum_obj, const string& num1, const string& num2,
                        bool& first_number_is_bigger, bool& second_number_is_bigger,
                        bool& first_number_has_negative_sign, bool& second_number_has_negative_sign);
        string multiply(const string& num1, const string& num2);

    public:
        bool has_negative_sign {false}, has_positive_sign {false};
        ulli float_point_index {0};
        string number;

        /// Constructors
        jmp() : number("0") {}
        jmp (const string& num) { validation(num); }
        jmp (const char* num) { validation(num); }
        template <class T>
        jmp (T num) { validation(double_to_string(num)); }
        jmp (const jmp& j)
        {
            number = j.number;
            float_point_index = j.float_point_index;
            has_negative_sign = j.has_negative_sign;
            has_positive_sign = j.has_positive_sign;
        }

        /// Destructor
        virtual ~jmp() {}

        /// Stream operators
        friend std::ostream& operator<<(std::ostream& o, const jmp& j)
        {
            o<<(j.has_negative_sign ? '-' : j.has_positive_sign ? '+' : '\0');
            o<<j.number;
            return o;
        }

        friend std::istream& operator>>(std::istream& i, jmp& j)
        {
            // Get the jmp object
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

        // Conversion functions
        long long int to_int()    { return atoi(std::move(number.c_str())); }
        long double   to_double() { return std::stod(number); }
        string        to_string() { return number; }

        void internal_conversion_to_int()
        {
            number = number.substr(0, float_point_index);
            float_point_index = 0;
        }

        void append (const string& num)
        {
            if (!num.empty() && std::find_if(num.begin(), 
                 num.end(), [](unsigned char c) { return !std::isdigit(c); }) == num.end())
                number.append(num);
        }

        // About-number functions
        bool is_empty()   const { return number.empty(); }
        bool is_decimal() const { return float_point_index != 0; }
        bool is_integer() const { return float_point_index == 0; }
        ulli size()       const { return number.size(); }
        ulli allocated()  const { return (number.capacity() * sizeof(char)) + sizeof(ulli) + sizeof(bool) * 2; }

        /// Assignment operator
        jmp operator=(const string& num)
        {
            clear();
            validation(num);
            return *this;
        }
        jmp operator=(const char* num)
        {
            clear();
            validation(num);
            return *this;
        }

        /*=========================================
                    Summation operators
          =========================================*/
        jmp operator+(jmp& j);
        jmp operator+(const long double& j);
        jmp operator+(string& num2_str);
        jmp operator+(const char* num2_str);
        friend jmp operator+(const long double& j, jmp& this_obj);
        friend jmp operator+(string& num2_str, jmp& this_obj);
        friend jmp operator+(const char* num2_str, jmp& this_obj);
        void operator+=(jmp& num2_str);
        void operator+=(const long double& j);
        void operator+=(string& num2_str);
        void operator+=(const char* num2_str);
        friend void operator+=(long double& j, jmp& this_obj);
        friend void operator+=(string& num2_str, jmp& this_obj);
        jmp operator++();
        jmp operator++(int);

        /*=========================================
                   Subtraction operators
          =========================================*/
        jmp operator-(jmp& j);
        jmp operator-(const long double& j);
        jmp operator-(string& num2_str);
        jmp operator-(const char* num2_str);
        friend jmp operator-(const long double& j, jmp& this_obj);
        friend jmp operator-(string& num2_str, jmp& this_obj);
        friend jmp operator-(const char* num2_str, jmp& this_obj);
        void operator-=(const long double& j);
        void operator-=(string& num2_str);
        void operator-=(jmp& num2_str);
        void operator-=(const char* num2_str);
        friend void operator-=(long double& j, jmp& this_obj);
        friend void operator-=(string& num2_str, jmp& this_obj);
        jmp operator--(int);
        jmp operator--();

        /*=========================================
                   Multiplication operators
          =========================================*/
        jmp operator*(jmp& j);
        jmp operator*(const long double& j);
        jmp operator*(string& num2_str);
        jmp operator*(const char* num2_str);
        friend jmp operator*(const long double& j, jmp& this_obj);
        friend jmp operator*(string& num2_str, jmp& this_obj);
        friend jmp operator*(const char* num2_str, jmp& this_obj);
        void operator*=(const long double& j);
        void operator*=(string& num2_str);
        void operator*=(jmp& num2_str);
        void operator*=(const char* num2_str);
        friend void operator*=(long double& j, jmp& this_obj);
        friend void operator*=(string& num2_str, jmp& this_obj);

        /*=========================================
                  Exponentiation operators
          =========================================*/
        jmp operator^(jmp& j);

        /*=========================================
                   Conditional operators
          =========================================*/
        bool operator==(jmp& j);
        bool operator==(const long double& j);
        bool operator==(string& j);
        bool operator==(const char* j);
        friend bool operator==(const long double& j, jmp& this_obj);
        friend bool operator==(string& j, jmp& this_obj);
        friend bool operator==(const char* j, jmp& this_obj);
        bool operator!=(jmp& j);
        bool operator!=(const long double& j);
        bool operator!=(string& j);
        bool operator!=(const char* j);
        friend bool operator!=(const long double& j, jmp& this_obj);
        friend bool operator!=(string& j, jmp& this_obj);
        friend bool operator!=(const char* j, jmp& this_obj);
        bool operator<(jmp& j);
        bool operator<(const long double& j);
        bool operator<(string& j);
        bool operator<(const char* j);
        friend bool operator<(const long double& j, jmp& this_obj);
        friend bool operator<(string& j, jmp& this_obj);
        friend bool operator<(const char* j, jmp& this_obj);
        bool operator<=(jmp& j);
        bool operator<=(const long double& j);
        bool operator<=(string& j);
        bool operator<=(const char* j);
        friend bool operator<=(const long double& j, jmp& this_obj);
        friend bool operator<=(string& j, jmp& this_obj);
        friend bool operator<=(const char* j, jmp& this_obj);
        bool operator>(jmp& j);
        bool operator>(const long double& j);
        bool operator>(string& j);
        bool operator>(const char* j);
        friend bool operator>(const long double& j, jmp& this_obj);
        friend bool operator>(string& j, jmp& this_obj);
        friend bool operator>(const char* j, jmp& this_obj);
        bool operator>=(jmp& j);
        bool operator>=(const long double& j);
        bool operator>=(string& j);
        bool operator>=(const char* j);
        friend bool operator>=(const long double& j, jmp& this_obj);
        friend bool operator>=(string& j, jmp& this_obj);
        friend bool operator>=(const char* j, jmp& this_obj);
};

void jmp::FFT(std::complex<double>* a, size_t& n, const bool& invert) {
    // Calculate angle multiplier based on invert flag
    const double angleMultiplier { (invert ? -1.0 : 1.0) * 2.0 * M_PI / n };

    // Precompute twiddle factors (rotation angles) and store them in twiddleFactors array
    std::complex<double> twiddleFactors[n];
    for (size_t i{0}; i < n; ++i) {
        const double angle { i * angleMultiplier };
        twiddleFactors[i] = std::polar(1.0, angle);
    }

    size_t j {0};
    // Perform bit-reversal permutation on the input array
    for (size_t i{1}; i < n; ++i) {
        size_t bit { n >> 1 };
        while (((j ^= bit) & bit) == 0)
            bit >>= 1;
        if (i < j)
            swap(a[i], a[j]);
    }

    // Perform butterfly operations for different lengths (powers of 2)
    for (size_t len{2}; len <= n; len <<= 1) {
        const size_t halfLen { len >> 1 }, twiddleStep { n / len };
        for (size_t i{0}; i < n; i += len) {
            std::complex<double>* pa { a + i };
            for (size_t j{0}; j < halfLen; ++j) {
                const std::complex<double> u { *pa };
                const std::complex<double> v { *(pa + halfLen) * twiddleFactors[j * twiddleStep] };
                *pa = u + v;
                *(pa + halfLen) = u - v;
                pa++;
            }
        }
    }

    // Normalize the output if invert flag is set
    if (invert) {
        for (size_t i{0}; i < n; ++i)
            a[i] /= n;
    }
}

string jmp::multiply(const string& num1, const string& num2)
{
    const size_t size1 {num1.size()}, size2 {num2.size()};
    size_t n {1};
    while (n < size1 + size2)
        n <<= 1;
    std::complex<double> a[n], b[n];

    // Convert input strings to complex number arrays
    for (size_t i{0}; i<size1; ++i)
        a[i] = num1[size1 - i - 1] - '0';
    for (size_t i{0}; i < size2; ++i)
        b[i] = num2[size2 - i - 1] - '0';

    // Perform FFT on both arrays
    FFT(a, n, false);
    FFT(b, n, false);

    // Multiply the transformed arrays element-wise
    for (size_t i{0}; i<n; ++i)
        a[i] *= b[i];

    // Perform inverse FFT to obtain the convolution result
    FFT(a, n, true);

    ulli carry {0};
    string product;

    // Construct the product string by rounding the real parts and performing carry propagation
    for (size_t i{0}; i<n; ++i)
    {
        ulli digit {static_cast<ulli>(a[i].real() + 0.5) + carry};
        product += '0' + (digit % 10);
        carry = digit / 10;
    }

    // Remove trailing zeros from the product string
    while (product.size() > 1 && product.back() == '0')
        product.pop_back();

    // Efficiently reverse the product string
    size_t start {0}, end {product.size() - 1};
    while (start < end)
    {
        std::swap(product[start], product[end]);
        ++start;
        --end;
    }

    return product;
}

void jmp::validation (const string& num)
{
    number = num;

    // If number is empty so is not valid
    if (number.empty())
    {
        number = "0";
        return;
    }

    // We erase the number sign to just check that this number string indexes are number or aren't a number
    if (number[0] == '-')
    {
        number.erase(number.begin());
        float_point_index = float_point_index > 0 ? float_point_index - 1 : 0;
        has_negative_sign = true;
    } else if (number[0] == '+') {
        number.erase(number.begin());
        float_point_index = float_point_index > 0 ? float_point_index - 1 : 0;
        has_positive_sign = true;
    }

    bool valid {true};
    size_t number_of_dots {0};
    for (size_t i{0}; i<number.length(); i++)
    {
        // If the number character is not in the range 0-9 and the number character is not '.'-
        // then this character is invalid
        if ((number[i] < '0' || number[i] > '9') && number[i] != '.')
        {
            valid = false;
            break;
        }

        // If the number character is '.', so we add 1 to number_of_dots to know how many dots we have in-
        // the number characters, then update the float_point_index to know-
        // where is the point index in the number
        if (number[i] == '.')
        {
            number_of_dots++;
            if (number_of_dots > 1)
            {
                valid = false;
                break;
            }
            float_point_index = i;
        }
    }

    // "If conditions" for falsing the validity of the number string
    if ((number[0] == '0' && number[1] != '.') ||
        (number.front() == '.'))
        valid = false;

    // "If conditions" for truing the validity of the number string
    valid = number == "0" || number == "+0" || number == "-0" ? true : valid;

    // We set the float_point_index to zero when the number is invalid.
    // Because if the next value is an integer number, and we have a specific float_point_index, some-
    // calculations will fail and give wrong answers.
    float_point_index = valid ? float_point_index : 0;

    // If the last index of the number is a '.' character so the user meant that this number is-
    // a float number so we do consider this for the JMP number.
    if (number.back() == '.' && valid)
        number.push_back('0');

    // If the number is valid, so it is; but if the number isn't valid, then we value the number to zero
    number = valid ? number : "0";

    // If the number is not valid, we will set the sign of the number that set above with false
    if (valid == false)
        has_negative_sign = has_positive_sign = false;
}

bool jmp::which_is_bigger(const string& num1, const string& num2) const
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
        int counter {0};
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

void jmp::summation (jmp& sum_obj, const string& num1, const string& num2,
                     bool& first_number_is_bigger, bool& second_number_is_bigger,
                     bool& first_number_has_negative_sign, bool& second_number_has_negative_sign)
{
    // Now we ready to add two numbers together
    if (first_number_is_bigger && (first_number_has_negative_sign == second_number_has_negative_sign))
    {
        long unsigned int difference_of_two_numbers {num1.size() - num2.size()};
        for (long int i{num1.size() - 1}; i>=0; i--)
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
        long unsigned int difference_of_two_numbers {num2.size() - num1.size()};
        for (int i{num2.size() - 1}; i>=0; i--)
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
        long unsigned int difference_of_two_numbers {num1.size() - num2.size()};
        for (int i{num1.size() - 1}; i>=0; i--)
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
        long unsigned int difference_of_two_numbers {num2.size() - num1.size()};
        for (int i{num2.size() - 1}; i>=0; i--)
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

void jmp::equalizing_figures(jmp& j)
{
    // If two numbers do not have the same decimals, we add '0' decimals to the end of that number that has lower decimals.
    if (j.float_point_index != 0 && float_point_index != 0 && (number.size() - float_point_index) > (j.number.size() - j.float_point_index))
    {
        // It means this object number has more decimals than second number
        // Now we need to know how many '0' decimals we should push back to the second number. (that number has lower decimals)
        long unsigned int how_many_zeros {(number.size() - float_point_index) - (j.number.size() - j.float_point_index)};
        for (int i{0}; i<how_many_zeros; i++)
            j.number.push_back('0');
    }
    else if (j.float_point_index != 0 && float_point_index != 0 && (number.size() - float_point_index) < (j.number.size() - j.float_point_index))
    {
        // It means second number has more decimals than this object number
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

void jmp::trim_the_number(jmp& j, const bool& bigger_number_is_negative)
{
    while (j.number[0] == '0' && j.float_point_index != 1)
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

jmp jmp::operator+(jmp& j)
{
    if (j.float_point_index != 0 && j.float_point_index < j.number.size())
        j.number.erase(j.number.begin() + j.float_point_index);
    else j.float_point_index = 0;

    if (float_point_index != 0 && float_point_index < number.size())
        number.erase(number.begin() + float_point_index);
    else float_point_index = 0;

    jmp sum_obj("0");
    size_t temp_number_size {number.size()}, temp_second_number_size {j.number.size()};
    equalizing_figures(j);
    // Check which number is bigger, and we equal the sum object number to the biggest number
    bool this_number_is_bigger {false}, second_number_is_bigger {false};
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
    if (float_point_index != 0)
        number.insert(number.begin() + float_point_index, '.');
    if (j.float_point_index != 0)
        j.number.insert(j.number.begin() + j.float_point_index, '.');
    if (sum_obj.float_point_index != 0)
        sum_obj.number.insert(sum_obj.number.begin() + sum_obj.float_point_index, '.');
    
    if ((second_number_is_bigger && has_negative_sign == false && j.has_negative_sign) ||
        (has_negative_sign && this_number_is_bigger))
    {
        //printf("Sum object %s\n", sum_obj.number.c_str());
        sum_obj.has_negative_sign = true;
    }
    return sum_obj;
}

jmp jmp::operator*(jmp& j)
{
    if (j.float_point_index != 0 && j.float_point_index < j.number.size())
        j.number.erase(j.number.begin() + j.float_point_index);
    else j.float_point_index = 0;

    if (float_point_index != 0 && float_point_index < number.size())
        number.erase(number.begin() + float_point_index);
    else float_point_index = 0;

    jmp mul_obj("0");
    if (j.number == "1")
        mul_obj = number;
    else if (number == "1")
        mul_obj = j.number;
    else
        mul_obj.number = multiply(number, j.number);

    ulli sum_of_decimals_of_two_numbers {
        (number.size() - (float_point_index == 0 ? number.size() : float_point_index)) +
        (j.number.size() - (j.float_point_index == 0 ? j.number.size() : j.float_point_index))};

    while (mul_obj.number.size() <= sum_of_decimals_of_two_numbers)
        mul_obj.number = "0" + mul_obj.number;

    mul_obj.float_point_index = mul_obj.number.size() - sum_of_decimals_of_two_numbers;

    if ((has_negative_sign == true && j.has_negative_sign == false) ||
        (has_negative_sign == false && j.has_negative_sign == true))
        mul_obj.has_negative_sign = true;

    if (float_point_index != 0)
        number.insert(number.begin() + float_point_index, '.');
    if (j.float_point_index != 0)
        j.number.insert(j.number.begin() + j.float_point_index, '.');
    if (mul_obj.float_point_index != 0 && mul_obj.float_point_index != mul_obj.number.size())
        mul_obj.number.insert(mul_obj.number.begin() + mul_obj.float_point_index, '.');

    while (mul_obj.float_point_index != 0 && (mul_obj.float_point_index <= mul_obj.number.size() - 1) &&
        mul_obj.number[mul_obj.number.size() - 1] == '0')
        mul_obj.number.erase(mul_obj.number.begin() + mul_obj.number.size()  - 1);

    return mul_obj;
}

jmp jmp::operator-(jmp& j)
{
    jmp negative = j;
    negative.has_negative_sign = true;
    return *this + negative;
}

jmp jmp::operator++()
{
    *this += 1;
    return *this;
}

jmp jmp::operator--()
{
    *this -= 1;
    return *this;
}

jmp jmp::operator++(int)
{
    jmp temp(*this);
    *this += 1;
    return temp;
}

jmp jmp::operator--(int)
{
    jmp temp = *this;
    *this -= 1;
    return temp;
}

jmp jmp::operator+(const long double& j)
{
    jmp num2(j);
    return *this + num2;
}

jmp jmp::operator*(const long double& j)
{
    jmp num2(j);
    return *this * num2;
}

jmp jmp::operator-(const long double& j)
{
    jmp num2(j);
    return *this - num2;
}

jmp jmp::operator+(string& num2_str)
{
    jmp num2(num2_str);
    return *this + num2;
}

jmp jmp::operator*(string& num2_str)
{
    jmp num2(num2_str);
    return *this * num2;
}

jmp jmp::operator-(string& num2_str)
{
    jmp num2(num2_str);
    return *this - num2;
}

jmp jmp::operator+(const char* num_str)
{
    jmp num2(num_str);
    return *this + num2;
}

jmp jmp::operator*(const char* num_str)
{
    jmp num2(num_str);
    return *this * num2;
}

jmp jmp::operator-(const char* num_str)
{
    jmp num2(num_str);
    return *this - num2;
}

jmp operator+(const long double& j, jmp& this_obj)
{
    jmp num2(j);
    return this_obj + num2;
}

jmp operator*(const long double& j, jmp& this_obj)
{
    jmp num2(j);
    return this_obj * num2;
}

jmp operator-(const long double& j, jmp& this_obj)
{
    jmp num2(j);
    return this_obj - num2;
}

jmp operator+(string& num2_str, jmp& this_obj)
{
    jmp num2(num2_str);
    return this_obj + num2;
}

jmp operator*(string& num2_str, jmp& this_obj)
{
    jmp num2(num2_str);
    return this_obj * num2;
}

jmp operator-(string& num2_str, jmp& this_obj)
{
    jmp num2(num2_str);
    return this_obj - num2;
}

jmp operator+(const char* num2_str, jmp& this_obj)
{
    jmp num2(num2_str);
    return this_obj + num2;
}

jmp operator*(const char* num2_str, jmp& this_obj)
{
    jmp num2(num2_str);
    return this_obj * num2;
}

jmp operator-(const char* num2_str, jmp& this_obj)
{
    jmp num2(num2_str);
    return this_obj - num2;
}

void jmp::operator+=(const long double& j)
{
    *this = *this + j;
}

void jmp::operator*=(const long double& j)
{
    *this = *this * j;
}

void jmp::operator-=(const long double& j)
{
    *this = *this - j;
}

void jmp::operator+=(string& num2_str)
{
    *this = *this + num2_str;
}

void jmp::operator*=(string& num2_str)
{
    *this = *this * num2_str;
}

void jmp::operator-=(string& num2_str)
{
    *this = *this - num2_str;
}

void jmp::operator+=(jmp& num2_str)
{
    *this = *this + num2_str;
}

void jmp::operator*=(jmp& num2_str)
{
    *this = *this * num2_str;
}

void jmp::operator-=(jmp& num2_str)
{
    *this = *this - num2_str;
}

void jmp::operator+=(const char* num2_str)
{
    *this = *this + num2_str;
}

void jmp::operator*=(const char* num2_str)
{
    *this = *this * num2_str;
}

void jmp::operator-=(const char* num2_str)
{
    *this = *this - num2_str;
}

void operator+=(long double& j, jmp& this_obj)
{
    j = (j + this_obj).to_double();
}

void operator*=(long double& j, jmp& this_obj)
{
    j = (j * this_obj).to_double();
}

void operator-=(long double& j, jmp& this_obj)
{
    j = (j - this_obj).to_double();
}

void operator+=(string& j, jmp& this_obj)
{
    j = (j + this_obj).to_string();
}

void operator*=(string& j, jmp& this_obj)
{
    j = (j * this_obj).to_string();
}

void operator-=(string& j, jmp& this_obj)
{
    j = (j - this_obj).to_string();
}

jmp jmp::operator^(jmp& j)
{
    string temp_base = number;
    while (--j > "0")
        *this *= temp_base;
    return *this;
}

bool jmp::operator==(jmp& j)
{
    if ((has_negative_sign ? "-" : "") + number == (j.has_negative_sign ? "-" : "") + j.number)
        return true;
    else
        return false;
}

bool jmp::operator==(const long double& j)
{
    jmp num2(j);
    return *this == num2 ? true : false;
}

bool jmp::operator==(string& j)
{
    jmp num2(j);
    return *this == num2 ? true : false;
}

bool jmp::operator==(const char* j)
{
    jmp num2(j);
    return *this == num2 ? true : false;
}

bool operator==(const long double& j, jmp& this_obj)
{
    jmp num2(j);
    return this_obj == num2 ? true : false;
}

bool operator==(string& j, jmp& this_obj)
{
    jmp num2(j);
    return this_obj == num2 ? true : false;
}

bool operator==(const char* j, jmp& this_obj)
{
    jmp num2(j);
    return this_obj == num2 ? true : false;
}

bool jmp::operator!=(jmp& j)
{
    if ((has_negative_sign ? "-" : "") + number != (j.has_negative_sign ? "-" : "") + j.number)
        return true;
    else
        return false;
}

bool jmp::operator!=(const long double& j)
{
    jmp num2(j);
    return *this != num2 ? true : false;
}

bool jmp::operator!=(string& j)
{
    jmp num2(j);
    return *this != num2 ? true : false;
}

bool jmp::operator!=(const char* j)
{
    jmp num2(j);
    return *this != num2 ? true : false;
}

bool operator!=(const long double& j, jmp& this_obj)
{
    jmp num2(j);
    return this_obj != num2 ? true : false;
}

bool operator!=(string& j, jmp& this_obj)
{
    jmp num2(j);
    return this_obj != num2 ? true : false;
}

bool operator!=(const char* j, jmp& this_obj)
{
    jmp num2(j);
    return this_obj != num2 ? true : false;
}

bool jmp::operator<(jmp& j)
{
    if (*this == j)
        return false;

    if (has_negative_sign && j.has_negative_sign == false)
        return true;
    else if (has_negative_sign == false && j.has_negative_sign)
        return false;

    bool which_number_is_bigger = which_is_bigger(number, j.number);
    if (which_number_is_bigger == 1 && j.has_negative_sign)
        return false;
    else if (which_number_is_bigger == 0 && has_negative_sign == true)
        return true;
    else if (which_number_is_bigger == 1 && j.has_negative_sign == false)
        return true;
    return false;
}

bool jmp::operator<(const long double& j)
{
    jmp num2(j);
    return *this < num2 ? true : false;
}

bool jmp::operator<(string& j)
{
    jmp num2(j);
    return *this < num2 ? true : false;
}

bool jmp::operator<(const char* j)
{
    jmp num2(j);
    return *this < num2 ? true : false;
}

bool operator<(const long double& j, jmp& this_obj)
{
    jmp num2(j);
    return num2 < this_obj ? true : false;
}

bool operator<(string& j, jmp& this_obj)
{
    jmp num2(j);
    return num2 < this_obj ? true : false;
}

bool operator<(const char* j, jmp& this_obj)
{
    jmp num2(j);
    return num2 < this_obj ? true : false;
}

bool jmp::operator<=(jmp& j)
{
    return *this < j || *this == j ? true : false;
}

bool jmp::operator<=(const long double& j)
{
    jmp num2(j);
    return *this <= num2 ? true : false;
}

bool jmp::operator<=(string& j)
{
    jmp num2(j);
    return *this <= num2 ? true : false;
}

bool jmp::operator<=(const char* j)
{
    jmp num2(j);
    return *this <= num2 ? true : false;
}

bool operator<=(const long double& j, jmp& this_obj)
{
    jmp num2(j);
    return num2 <= this_obj ? true : false;
}

bool operator<=(string& j, jmp& this_obj)
{
    jmp num2(j);
    return num2 <= this_obj ? true : false;
}

bool operator<=(const char* j, jmp& this_obj)
{
    jmp num2(j);
    return num2 <= this_obj ? true : false;
}

bool jmp::operator>(jmp& j)
{
    return *this < j == false && *this != j ? true : false;
}

bool jmp::operator>(const long double& j)
{
    jmp num2(j);
    return *this > num2 ? true : false;
}

bool jmp::operator>(string& j)
{
    jmp num2(j);
    return *this > num2 ? true : false;
}

bool jmp::operator>(const char* j)
{
    jmp num2(j);
    return *this > num2 ? true : false;
}

bool operator>(const long double& j, jmp& this_obj)
{
    jmp num2(j);
    return num2 > this_obj ? true : false;
}

bool operator>(string& j, jmp& this_obj)
{
    jmp num2(j);
    return num2 > this_obj ? true : false;
}

bool operator>(const char* j, jmp& this_obj)
{
    jmp num2(j);
    return num2 > this_obj ? true : false;
}

bool jmp::operator>=(jmp& j)
{
    return *this > j || *this == j ? true : false;
}

bool jmp::operator>=(const long double& j)
{
    jmp num2(j);
    return *this >= num2 ? true : false;
}

bool jmp::operator>=(string& j)
{
    jmp num2(j);
    return *this >= num2 ? true : false;
}

bool jmp::operator>=(const char* j)
{
    jmp num2(j);
    return *this >= num2 ? true : false;
}

bool operator>=(const long double& j, jmp& this_obj)
{
    jmp num2(j);
    return num2 >= this_obj ? true : false;
}

bool operator>=(string& j, jmp& this_obj)
{
    jmp num2(j);
    return num2 >= this_obj ? true : false;
}

bool operator>=(const char* j, jmp& this_obj)
{
    jmp num2(j);
    return num2 >= this_obj ? true : false;
}