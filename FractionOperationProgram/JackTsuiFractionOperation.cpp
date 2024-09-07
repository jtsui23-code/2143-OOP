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
    int num;
    int den;

    /**
     * Private: simplify
     * 
     * Description:
     *      Simplifies the fraction by dividing both numerator and denominator by their
     *      greatest common divisor.
     * 
     * Params:
     *      - Fraction& sim: Fraction object to simplify
     * 
     * Returns:
     *      - Fraction: The simplified fraction
     */
    Fraction simplify(Fraction& sim);


public:

    /**
     * Public: Constructor
     * 
     * Description:
     *      Default constructor for the Fraction class. Initializes fraction to 1/1.
     */
    Fraction();

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
    Fraction(int n, int d);
    
    /**
     * Public: operator+
     * 
     * Description:
     *      Overloads the + operator to add two Fraction objects.
     * 
     * Params:
     *      - Fraction& other: Fraction object to add
     * 
     * Returns:
     *      - Fraction: The result of the addition
     */
    Fraction operator+(Fraction& other);

    /**
     * Public: operator-
     * 
     * Description:
     *      Overloads the - operator to subtract one Fraction object from another.
     * 
     * Params:
     *      - Fraction& other: Fraction object to subtract
     * 
     * Returns:
     *      - Fraction: The result of the subtraction
     */
    Fraction operator-(Fraction& other);

    /**
     * Public: operator*
     * 
     * Description:
     *      Overloads the * operator to multiply two Fraction objects.
     * 
     * Params:
     *      - Fraction& other: Fraction object to multiply
     * 
     * Returns:
     *      - Fraction: The result of the multiplication
     */
    Fraction operator*(Fraction& other);

    /**
     * Public: operator/
     * 
     * Description:
     *      Overloads the / operator to divide one Fraction object by another.
     * 
     * Params:
     *      - Fraction& other: Fraction object to divide
     * 
     * Returns:
     *      - Fraction: The result of the division
     */
    Fraction operator/(Fraction& other);

    /**
     * Public: operator==
     * 
     * Description:
     *      Overloads the == operator to compare two Fraction objects for equality.
     * 
     * Params:
     *      - Fraction& other: Fraction object to compare
     * 
     * Returns:
     *      - bool: True if the fractions are equal, false otherwise
     */
    bool operator==(Fraction& other);

    /**
     * Public: operator<<
     * 
     * Description:
     *      Overloads the << operator to print a Fraction object.
     * 
     * Params:
     *      - ostream& os: Output stream object
     *      - const Fraction& frac: Fraction object to print
     * 
     * Returns:
     *      - ostream&: Output stream with the Fraction object printed
     */
    friend ostream& operator<<(ostream& os, const Fraction& frac) ;

};
    /**
     * Private: simplify
     * 
     * Description:
     *      Simplifies the fraction by dividing both numerator and denominator by their
     *      greatest common divisor.
     * 
     * Params:
     *      - Fraction& sim: Fraction object to simplify
     * 
     * Returns:
     *      - Fraction: The simplified fraction
     */
    Fraction Fraction::simplify(Fraction &sim)
    {
        //These are placeholders for the numerator and denominators
        int n = sim.num;
        int d = sim.den;
        
        //this loop will keep on dividing n/d until there is no remainder left
        while(d != 0)
        {
            //this variable keeps the previous value of divisor because the divisor will 
            // eventually hit zero 
            int hold = d;
            d = n % d;
            n = hold;
        }

        //the second to last divisor got from the loop is the greatest common divisor
        // both the numerator and denominator are divided by the divisor stored in n
        sim.num /= n;
        sim.den /= n;

        // the quotient is then returned as the simplified fraction form
        return sim;
    }

    /**
     * Public: operator+
     * 
     * Description:
     *      Overloads the + operator to add two Fraction objects.
     * 
     * Params:
     *      - Fraction& rhs: Fraction object to add
     * 
     * Returns:
     *      - Fraction: The result of the addition
     */
    Fraction Fraction::operator+(Fraction &rhs)
    {
        Fraction added;
        
        //This does multiplies both fractions to make the fractions
        // have the same denominator
        int lnum = this->num * rhs.den;
        int rnum = rhs.num   * this->den;
        int lden = this->den * rhs.den;

        //This adds the fraction after both of the fractions have a common denominator
        added.num = lnum + rnum;
        added.den = lden;

        //this calls the simplify function that will reinitialize the fraction object
        // before it is returned
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
     *      - Fraction& rhs: Fraction object to subtract
     * 
     * Returns:
     *      - Fraction: The result of the subtraction
     */
    Fraction Fraction::operator-(Fraction &rhs)
    {
        Fraction sub;
        
        //This does multiplies both fractions to make the fractions
        // have the same denominator
        int lnum = this->num * rhs.den;
        int rnum = rhs.num   * this->den;
        int lden = this->den * rhs.den;

        //This subtracts the fraction after both of the fractions have a common denominator
        sub.num = lnum - rnum;
        sub.den = lden;

        //this calls the simplify function that will reinitialize the fraction object
        // before it is returned
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
     *      - Fraction& rhs: Fraction object to multiply
     * 
     * Returns:
     *      - Fraction: The result of the multiplication
     */
    Fraction Fraction::operator*(Fraction &rhs)
    {
        //this creates a temporary Fraction object 
        Fraction multi;

        //The product of the numerator and denominator is stored in the temp Fraction
        // object
        multi.num = this->num * rhs.num;
        multi.den = this->den * rhs.den;

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
     *      - Fraction& rhs: Fraction object to divide
     * 
     * Returns:
     *      - Fraction: The result of the division
     */
    Fraction Fraction::operator/(Fraction &rhs)
    {
        //this creates a temporary Fraction object 
        Fraction divi;

        //The product of the first fraction and the second flipped fraction
        // is stored in the temp Fraction object
        divi.num = this->num * rhs.den;
        divi.den = this->den * rhs.num;

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
     *      - ostream& os: Output stream object
     *      - const Fraction& frac: Fraction object to print
     * 
     * Returns:
     *      - ostream&: Output stream with the Fraction object printed
     */
    std::ostream& operator<<(ostream& os, const Fraction &rhs)
    {
        return os << rhs.num << "/" << rhs.den;
    }

    bool Fraction:: operator==(Fraction& rhs)
    {   
        Fraction placeHolder = Fraction(this->num,this->den);

        Fraction simpL = simplify(placeHolder);

        Fraction simpR = simplify(rhs);

        return simpL.num == simpR.num && simpL.den == simpR.den;

        
    }


int main()
{
    Fraction f1(25,5);
    Fraction f2(3,4);
    Fraction f3;
    Fraction ff1(25,5);
    Fraction ff2(3,4);
    Fraction ff3;
    Fraction fgg1(25,5);
    Fraction fgg2(3,4);
    Fraction fgg3;
    Fraction fe1(25,5);
    Fraction fe2(3,4);
    Fraction fe3;

    Fraction fee1(25,5);
    Fraction fee2(3,4);

    bool result;

    result = fee1 == fee2;

    cout<< "(" << f1 << ") "<< "==" << " (" << f2<< ") " << " = " << result << endl;

    
    f3 = f1 * f2;
    cout<< "(" << f1 << ") "<< "*" << " (" << f2<< ") " << " = " << f3 << endl;


    ff3 = ff1 / ff2;
    cout<< "(" << ff1 << ") "<< "/" << " (" << ff2<< ") " << " = " << ff3 << endl;

    fgg3 = fgg1 - fgg2;
    cout<< "(" << fgg1 << ") "<< "-" << " (" << fgg2<< ") " << " = " << fgg3 << endl;

    fe3 = fe1 + fe2;
    cout<< "(" << fe1 << ") "<< "+" << " (" << fe2<< ") " << " = " << fe3 << endl;

    
}