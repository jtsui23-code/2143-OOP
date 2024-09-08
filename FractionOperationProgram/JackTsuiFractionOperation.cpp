/*****************************************************************************
*                    
*  Author:           Jack Tsui
*  Email:            jtsui1110@my.msutexas.edu
*  Label:            P01
*  Title:            Fraction Class
*  Course:           2143 OOP
*  Semester:         Fall 2024
* 
*  Description:
*        This program overrides the cout and +-/* operators for doing operations with 
*        fractions. There is a class Function name Fraction for creating fractions 
*        and doing math operations with them.
* 
*  Usage:
*        
* 
*  Files:            JackTsuiFractionOperation.cpp
*****************************************************************************/

#include<iostream>

using namespace std;

/**
 * Fraction
 * 
 * Description:
 *      This class creates a fraction object using two integers as numerator and 
 *      denominator. It also provides methods for arithmetic operations (addition, 
 *      subtraction, multiplication, division) and equality checks between fractions.
 *      Additionally, it overrides the output operator for printing fractions in a
 *      `numerator/denominator` format.
 * 
 * Public Methods:
 *      - Fraction          operator+(const Fraction& other fraction object) 
 *      - Fraction          operator-(const Fraction& other fraction object) 
 *      - Fraction          operator*(const Fraction& other fraction object)
 *      - Fraction          operator/(const Fraction& other fraction object) 
 *      - bool              operator==(const Fraction& other fraction object)     
 *      - friend            ostream& operator<<(ostream& os, const Fraction& other fraction object) 
 * 
 * Private Methods:
 *      - void              simplify(Fraction& fraction to simplify);                   
 * 
 * Usage: 
 *      - Fraction frac(1, 3);                // Creates a Fraction object representing 1/3
 *      - cout << frac;                      // Prints the fraction in the format "1/3"
 *      - Fraction f1(1, 2);                 // Creates a Fraction object representing 1/2
 *      - Fraction f2(3, 4);                 // Creates another Fraction object representing 3/4
 *      - Fraction result = f1 + f2;         // Adds two Fraction objects
 *      - cout << result;                   // Prints the result of the addition
 */

class Fraction
{
private:
    int num;  // Numerator of the fraction
    int den;  // Denominator of the fraction

    // Helper function to simplify a given Fraction by dividing both
    // the numerator and denominator by their greatest common divisor.
    Fraction simplify(Fraction& sim);

public:
    // Default constructor: Initializes the fraction as 1/1.
    Fraction();

    // Constructor: Initializes the fraction with a given numerator and denominator.
    Fraction(int n, int d);

    // Overloads the + operator to add two Fraction objects.
    Fraction operator+(Fraction& other);

    // Overloads the - operator to subtract one Fraction object from another.
    Fraction operator-(Fraction& other);

    // Overloads the * operator to multiply two Fraction objects.
    Fraction operator*(Fraction& other);

    // Overloads the / operator to divide one Fraction object by another.
    Fraction operator/(Fraction& other);

    // Overloads the == operator to compare two Fraction objects for equality.
    bool operator==(Fraction& other);

    // Overloads the << operator to print a Fraction object.
    friend ostream& operator<<(ostream& os, const Fraction& frac);
};


/**
 * Public: Constructor
 * 
 * Description:
 *      Default constructor for the Fraction class. Initializes fraction to 1/1.
 */
Fraction::Fraction()
{
    num = den = 1;  // Both numerator and denominator set to 1.
}


/**
 * Public: Constructor
 * 
 * Description:
 *      Constructor for the Fraction class. Initializes fraction with given numerator
 *      and denominator.
 * 
 * Params:
 *      - int n: Numerator of the fraction
 *      - int d: Denominator of the fraction
 */
Fraction::Fraction(int n, int d)
{
    if (d == 0)  // Check for invalid denominator (0).
    {
        cout << "Invalid denominator.\n";
    }
    num = n;   // Initialize numerator.
    den = d;   // Initialize denominator.
}

/**
 * Private: simplify
 * 
 * Description:
 *      Simplifies the fraction by dividing both numerator and denominator by their
     *      greatest common divisor (GCD).
 * 
 * Params:
 *      - Fraction& sim: Fraction object to simplify.
 * 
 * Returns:
 *      - Fraction: The simplified fraction.
 */
Fraction Fraction::simplify(Fraction &sim)
{
    // Temporary variables to hold numerator and denominator values.
    int n = sim.num;
    int d = sim.den;
    
    // Loop to find the greatest common divisor using the Euclidean algorithm.
    while (d != 0)
    {
        int hold = d;  // Store current denominator value.
        d = n % d;     // Update denominator with the remainder of n / d.
        n = hold;      // Set numerator to the previous denominator.
    }

    // Divide both numerator and denominator by the greatest common divisor (n).
    sim.num /= n;
    sim.den /= n;

    // Return the simplified fraction.
    return sim;
}


/**
 * Public: operator+
 * 
 * Description:
 *      Overloads the + operator to add two Fraction objects.
 * 
 * Params:
 *      - Fraction& rhs: Fraction object to add.
 * 
 * Returns:
 *      - Fraction: The result of the addition.
 */
Fraction Fraction::operator+(Fraction &rhs)
{
    Fraction added;  // Temporary Fraction object to hold the result.

    // Compute the new numerator and denominator for the result.
    int lnum = this->num * rhs.den;  // Left numerator adjusted to common denominator.
    int rnum = rhs.num * this->den;  // Right numerator adjusted to common denominator.
    int lden = this->den * rhs.den;  // Common denominator.

    // Add the numerators and assign to the result Fraction.
    added.num = lnum + rnum;
    added.den = lden;

    // Simplify the result before returning.
    added = simplify(added);
    return Fraction(added.num, added.den);
}


/**
 * Public: operator-
 * 
 * Description:
 *      Overloads the - operator to subtract one Fraction object from another.
 * 
 * Params:
 *      - Fraction& rhs: Fraction object to subtract.
 * 
 * Returns:
 *      - Fraction: The result of the subtraction.
 */
Fraction Fraction::operator-(Fraction &rhs)
{
    Fraction sub;  // Temporary Fraction object to hold the result.

    // Compute the new numerator and denominator for the result.
    int lnum = this->num * rhs.den;  // Left numerator adjusted to common denominator.
    int rnum = rhs.num * this->den;  // Right numerator adjusted to common denominator.
    int lden = this->den * rhs.den;  // Common denominator.

    // Subtract the numerators and assign to the result Fraction.
    sub.num = lnum - rnum;
    sub.den = lden;

    // Simplify the result before returning.
    sub = simplify(sub);
    return Fraction(sub.num, sub.den);
}


/**
 * Public: operator*
 * 
 * Description:
 *      Overloads the * operator to multiply two Fraction objects.
 * 
 * Params:
 *      - Fraction& rhs: Fraction object to multiply.
 * 
 * Returns:
 *      - Fraction: The result of the multiplication.
 */
Fraction Fraction::operator*(Fraction &rhs)
{
    Fraction multi;  // Temporary Fraction object to hold the result.

    // Multiply the numerators and denominators.
    multi.num = this->num * rhs.num;
    multi.den = this->den * rhs.den;

    // Simplify the result before returning.
    multi = simplify(multi);
    return Fraction(multi.num, multi.den);
}


/**
 * Public: operator/
 * 
 * Description:
 *      Overloads the / operator to divide one Fraction object by another.
 * 
 * Params:
 *      - Fraction& rhs: Fraction object to divide.
 * 
 * Returns:
 *      - Fraction: The result of the division.
 */
Fraction Fraction::operator/(Fraction &rhs)
{
    Fraction divi;  // Temporary Fraction object to hold the result.

    // Multiply the first fraction by the reciprocal of the second.
    divi.num = this->num * rhs.den;
    divi.den = this->den * rhs.num;

    // Simplify the result before returning.
    divi = simplify(divi);
    return Fraction(divi.num, divi.den);
}


/**
 * Public: operator<<
 * 
 * Description:
 *      Overloads the << operator to print a Fraction object.
 * 
 * Params:
 *      - ostream& os: Output stream object.
 *      - const Fraction& frac: Fraction object to print.
 * 
 * Returns:
 *      - ostream&: Output stream with the Fraction object printed.
 */
std::ostream& operator<<(ostream& os, const Fraction &rhs)
{
    // Output the fraction in the form "numerator/denominator".
    return os << rhs.num << "/" << rhs.den;
}


/**
 * Public: operator==
 * 
 * Description:
 *      Overloads the == operator to compare two Fraction objects for equality.
 * 
 * Params:
 *      - Fraction& rhs: Fraction object to compare.
 * 
 * Returns:
 *      - bool: True if the fractions are equal, false otherwise.
 */
bool Fraction::operator==(Fraction& rhs)
{
    // Simplify both fractions before comparison.
    Fraction simpL = simplify(*this);
    Fraction simpR = simplify(rhs);

    // Compare numerators and denominators of the simplified fractions.
    return simpL.num == simpR.num && simpL.den == simpR.den;
}

int main()
{

    return 0;
    
}