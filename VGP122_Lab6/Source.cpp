#pragma once

#include <iostream>
#include <numeric>
#include <stdexcept>
#include <iostream>

// T is usually an integer type: int, long long, etc.
template<typename T = int>
class Rational
{
public:

    //Constructors
    Rational() : num_(0), den_(1) {}

    Rational(T num, T den = 1)
    {
        if (den == 0)
            throw std::invalid_argument("Denominator cannot be zero.");

        // Keep denominator positive (move sign to numerator)
        if (den < 0) {
            num = -num;
            den = -den;
        }

        // Reduce / simplify
        T g = std::gcd(num, den);
        num_ = num / g;
        den_ = den / g;
    }

    //Getters
    T numerator() const { return num_; }
    T denominator() const { return den_; }

    //Arithmetic operators
    Rational operator+(const Rational& rhs) const
    {
        return Rational(
            num_ * rhs.den_ + rhs.num_ * den_,
            den_ * rhs.den_
        );
    }

    Rational operator-(const Rational& rhs) const
    {
        return Rational(
            num_ * rhs.den_ - rhs.num_ * den_,
            den_ * rhs.den_
        );
    }

    Rational operator*(const Rational& rhs) const
    {
        return Rational(
            num_ * rhs.num_,
            den_ * rhs.den_
        );
    }

    Rational operator/(const Rational& rhs) const
    {
        if (rhs.num_ == 0)
            throw std::invalid_argument("Division by zero rational.");

        return Rational(
            num_ * rhs.den_,
            den_ * rhs.num_
        );
    }

    //Relational/equality operators
    bool operator==(const Rational& rhs) const
    {
        return num_ == rhs.num_ && den_ == rhs.den_;
    }

    bool operator!=(const Rational& rhs) const
    {
        return !(*this == rhs);
    }

    bool operator<(const Rational& rhs) const
    {
        return num_ * rhs.den_ < rhs.num_ * den_;
    }

    bool operator>(const Rational& rhs) const
    {
        return rhs < *this;
    }

    bool operator<=(const Rational& rhs) const
    {
        return !(*this > rhs);
    }

    bool operator>=(const Rational& rhs) const
    {
        return !(*this < rhs);
    }

private:
    T num_;
    T den_;
};

//Stream operators
template<typename T>
std::ostream& operator<<(std::ostream& os, const Rational<T>& r)
{
    return os << r.numerator() << '/' << r.denominator();
}

template<typename T>
std::istream& operator>>(std::istream& is, Rational<T>& r)
{
    T n, d;
    char slash;
    if (is >> n >> slash >> d && slash == '/') {
        r = Rational<T>(n, d);
    }
    else {
        is.setstate(std::ios::failbit);
    }
    return is;
}

int main()
{
    Rational<> r1(1, 2);   // 1/2
    Rational<> r2(3, 4);   // 3/4

    Rational<> sum = r1 + r2;
    Rational<> diff = r1 - r2;
    Rational<> prod = r1 * r2;
    Rational<> quot = r1 / r2;

    std::cout << "r1   = " << r1 << std::endl;
    std::cout << "r2   = " << r2 << std::endl;
    std::cout << "sum  = " << sum << std::endl;
    std::cout << "diff = " << diff << std::endl;
    std::cout << "prod = " << prod << std::endl;
    std::cout << "quot = " << quot << std::endl;

    // Relational tests
    std::cout << std::boolalpha;
    std::cout << "r1 == r2 : " << (r1 == r2) << std::endl;
    std::cout << "r1 < r2  : " << (r1 < r2) << std::endl;
    std::cout << "r1 > r2  : " << (r1 > r2) << std::endl;

    return 0;
}

