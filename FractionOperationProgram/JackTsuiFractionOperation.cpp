//Jack Tsui
// 2143 OOP
// Fraction Operation Program 1
// 9 - 5 - 2024

//This program overrides the cout and +-*/ operators 
// for doing operations with fractions
// There is a class Function for creating fractions and doing 
// math operations with them
// The program does all four +-*/ operations to the same
// Two fractions and prints the result in the terminal

#include<iostream>

using namespace std;


class Fraction
{
    int num;
    int den;

public:

    Fraction()
    {
        num = den = 1;
    }

    Fraction(int n, int d)
    {
        num = n;
        den = d;
    }

    //this function is type fraction and recieves 1 parameter
    // the parameter is a fraction object passed by reference
    // this function simplifies the fraction passed to it
    Fraction simplify(Fraction &sim)
    {
        //These are placeholders for the numerator and denonminators

        int n = sim.num;
        int d = sim.den;
        
        //this loop will keep on dividing n/d until there is no remainder left

         while(d!=0)
        {
            //this variable keeps the previous value of divsor because the divsor will 
            // eventually hit zero 
            int hold = d;
            d = n % d;

            n = hold;
        }

        //the second to last divsor got from the loop is the greatest common divider
        // both the numerator and denominator is divided by the divsor stored in n
        sim.num /= n;
        sim.den /= n;

        // the quotient is then returned as the simplified fraction form

        return sim;

    }

    //This function type is ostream and it recieves two parameters
    // the function recieves a ostream object by reference and a 
    // Fraction object by reference
    // This funciton has the friend keyword so it can access the 
    // private data of the Fraction object rhs
    // This function overrided the output operator so you can
    // print out the contents of a Fraction object without needing
    // the print method
    friend ostream& operator<<(ostream& os, const Fraction &rhs)
    {
        return os <<rhs.num<<"/"<< rhs.den;
    }

    //This function type is Fraction and recieves 1 parameters
    // the function recieves a 
    // Fraction object by reference
    // This function overrided the addition operator so you can
    // add two Fraction object without needing
    // to specify data of the object
     Fraction operator+(Fraction &rhs)
    {
        Fraction added;
        
          //This does multiplies both fractions to make the fractions
        // have the same denominator
        int lnum = this->num * rhs.den;


        int rnum = rhs.num   * this->den;

        int lden = this->den * rhs.den;

        //This adds the fraction after both of the fractions have a common denominator
        //this->num = this->num - rhs.num;
        //This sets the numerator and the denominator of the temporary Fraction object
        // to the values of the added fractions
        added.num = lnum + rnum;

        added.den = lden;


        //this calls the simplify function that will reinitialize the fraction object
        // before it is returned
        added = simplify(added);
        return Fraction(added.num, added.den);
        
    }

    //This function type is Fraction and recieves 1 parameters
    // the function recieves a 
    // Fraction object by reference
    // This function overrided the subtraction operator so you can
    // subtract two Fraction object without needing
    // to specify data of the object
     Fraction operator-(Fraction &rhs)
    {
        Fraction sub;
        
        //This does multiplies both fractions to make the fractions
        // have the same denominator
        int lnum = this->num * rhs.den;


        int rnum = rhs.num   * this->den;

        int lden = this->den * rhs.den;

        //This subtracts the fraction after both of the fractions have a common denominator
        //this->num = this->num - rhs.num;
        //This sets the numerator and the denominator of the temporary Fraction object
        // to the values of the subtracted fractions
        sub.num = lnum - rnum;

        sub.den = lden;

        //this calls the simplify function that will reinitialize the fraction object
        // before it is returned
        sub = simplify(sub);
        return Fraction(sub.num, sub.den);
        
    }

    //This function type is Fraction and recieves 1 parameters
    // the function recieves a 
    // Fraction object by reference
    // This function overrided the multiply operator so you can
    // multiply two Fraction object without needing
    // to specify data of the object
     Fraction operator*(Fraction &rhs)
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

    //This function type is Fraction and recieves 1 parameters
    // the function recieves a 
    // Fraction object by reference
    // This function overrided the division operator so you can
    // divid two Fraction object without needing
    // to specify data of the object
     Fraction operator/(Fraction &rhs)
    {
        //this creates a temporary Fraction object 
        Fraction divi;

        
        //The product of the first fraction and the second flipped fraction
        // is stored in the temp Fraction
        // object
        divi.num = this->num * rhs.den;

        divi.den = this->den * rhs.num;

        divi = simplify(divi);

        return Fraction(divi.num, divi.den);
    }

};
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

    f3 = f1 * f2;
    cout<< "(" << f1 << ") "<< "*" << " (" << f2<< ") " << " = " << f3 << endl;


    ff3 = ff1 / ff2;
    cout<< "(" << ff1 << ") "<< "/" << " (" << ff2<< ") " << " = " << ff3 << endl;

    fgg3 = fgg1 - fgg2;
    cout<< "(" << fgg1 << ") "<< "-" << " (" << fgg2<< ") " << " = " << fgg3 << endl;

    fe3 = fe1 + fe2;
    cout<< "(" << fe1 << ") "<< "-" << " (" << fe2<< ") " << " = " << fe3 << endl;
}