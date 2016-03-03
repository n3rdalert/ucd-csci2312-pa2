// Created by Jeffrey Cayton on 2/5/16.
//
//File: Point.cpp
//
//Description: this file contains the implementation of the Point class.

#include <cmath>        //Needed to perform distance formula calculation
#include <string>       //For string functions
#include <sstream>      //For string stream functions
#include <iostream>     //input/output

#include "Point.h"

using namespace std;


namespace Clustering
{

    unsigned int Point::__idGen = 0; // id generator


//-------------------------------------------------------
    //(Default) Constructor
    Point::Point(int holdDim)
    {
        __id = __idGen;
        //assign value of idGen to __id.

        __idGen++;
        //increment idGen

        __dim = holdDim;
        //Pass information from holdDim
        //into dimensions private variable.

        __values = new double[__dim];
        //dynamically allocated array
        //of doubles. Assigns value at
        //index to _values



        for (int n = 0; n < __dim; ++n) {
            __values[n] = 0;
        }
    }

//-------------------------------------------------------
    Point::Point(int dimensions, double *holdVal) {

        __id = __idGen;
        //assign __id to __idGen

        ++__idGen;
        //increment

        __dim = dimensions;
        //assign dimensions to __dim.

        __values = new double[__dim];
        //assign new array element to __values.

        for (int n = 0; n < __dim; ++n) {
            __values[n] = holdVal[n];
        }
    }

//-------------------------------------------------------
    //Copy Ctor
    Point::Point(const Point &copy)
    {
        __id = copy.__id;
        //assign value of __id to __id of point object.

        __dim = copy.__dim;
        //same as above, but assign dimension value.

        __values = new double[__dim];
        //creates new element to store values.


        for (int i = 0; i < __dim; i++) {
            __values[i] = copy.__values[i];
        }
    }

//-------------------------------------------------------

    //Overloaded Assignment Operator
    Point &Point::operator=(const Point &copy)
    {
        //If the object being called is not equal to
        //the cluster argument being passed, the inside statements
        //will run.
        if (this != &copy)
        {
            __dim = copy.__dim;
            __id = copy.__id;
                //assign values


            //If statement checks __values for a null value.
            //If not null, it will delete the values so
            //new data can be assigned.
            if (__values != nullptr)
                delete[] __values;

            //Declare new double array if
            //__values needed to be erased.
            __values = new double[__dim];


            //For loop assigns copied data to __values
            //at location 'n' in the
            for (int n = 0; n < __dim; ++n) {
                __values[n] = copy.__values[n];
            }
        }

        return *this;
    }

//-------------------------------------------------------

//Dtor
//Deletes point class object
//Deallocates memory.
    Point::~Point()
    {
        delete[] __values;

    }
//-------------------------------------------------------





//Accessors & Mutators Below
//-------------------------------------------------------
    //Get ID
    int Point::getId() const
    {
        return __id;
    }
//-------------------------------------------------------

    //Get Dimensions
    int Point::getDims() const
    {
        return __dim;
    }
//-------------------------------------------------------


    /*NOTE: If the setters do not work properly, think about
     * implementing if statement to check that __values
     * is a value greater than or equal to 0.*/
    //Set Value
    void Point::setValue(int dimension, double value)
    {
        __values[dimension] = value;
    }
//-------------------------------------------------------

    //Get Values
    double Point::getValue(int dimension) const
    {
        return __values[dimension];
    }
//-------------------------------------------------------

    //Distance-To Function
    //Calculates the distance of two points

    double Point::distanceTo(const Point &point) const
    {
        double distance;     //'distance' holds value for distance.
        double s = 0;           //'s' holds sum of points.

        for (int n = 0; n < point.__dim; ++n)
            s += (pow(this->__values[n] - point.__values[n], 2.0));

            distance = sqrt(s);
        //take square root of sum 's'

            return distance;
        //return the distance
    }
//-------------------------------------------------------




//OVERLOADED MEMBERS
//All overloaded members take a double as an argument
//named values.

//Overloaded *= operator.
    Point &Point::operator*=(double values)
    {

        for (int n = 0; n < __dim; ++n)
        {
            __values[n] *= values;
        }
        return *this;
    }

//Overloaded /= Operator
    Point &Point::operator/=(double values)
    {
        for (int n = 0; n < __dim; ++n)
        {
            __values[n] /= values;
        }
        return *this;

    }


//Overloaded * operator
    const Point Point::operator*(double values) const // prevent (p1 * 2) = p2;
    {
        for (int n = 0; n < __dim; ++n)

            __values[n] *= values;

        return *this;
    }


//Overloaded / operator.
    const Point Point::operator/(double values) const // p3 = p2 / 2;
    {
        for (int n = 0; n < __dim; ++n)

            __values[n] /= values;

        return *this;
    }



//Overloaded [] Operator
    double &Point::operator[](int index)
    {
        //Return values at index location 'index'
        return __values[index];
    }





//COMPOUND ASSIGNMENT OPERATOR
//-------------------------------------------------------
//Compound += Operator
    Point &operator+=(Point &leftPnt, const Point &rightPnt)   //implement this one with a loop
    {
        for (int n = 0; n < leftPnt.__dim; ++n)
            leftPnt.__values[n] += rightPnt.__values[n];
            //add the left-side values to the right-side values
            //return the left-side values below.

        return leftPnt;
    }
//-------------------------------------------------------

//Compound -= Operator
    Point &operator-=(Point &leftPnt, const Point &rightPnt)
    {
        if (leftPnt == rightPnt)
        {
            //if the left point is already equal to the right,
            //simply return the left point.
            return leftPnt;
        }


        else if (leftPnt.__dim == rightPnt.__dim)
        {
            for (int i = 0; i < leftPnt.__dim; ++i)
                leftPnt.__values[i] -= rightPnt.__values[i];
        }

        return leftPnt;
    }
//-------------------------------------------------------

//OVERLOADED OPERATORS
//All overloaded operator will take a left point and right point
//as their signature and will use the copy constructor
//to assign the values to an object.
//-------------------------------------------------------

    const Point operator+(const Point & leftPnt, const Point &rightPnt)
    {
        //Declare new Point object 'p'
        //with data from leftPnt
        Point p(leftPnt);

        //Use overloaded compound operator
        //to assign values of rightPnt into 'p'.
        p += rightPnt;

        //Return the new 'p' object.
        return p;
    }

//-------------------------------------------------------

//The same steps above are repeated below for the '-' operator.
    const Point operator-(const Point &leftPnt, const Point &rightPnt)
    {
        Point p(leftPnt);

        p -= rightPnt;

        return p;
    }
//-------------------------------------------------------

//Overloaded Equality Operator
    bool operator==(const Point & p1, const Point &p2)
    {
        //declare bool value; assign to true.
        bool temp = true;


        //If statement checks that p1 and p2 have matching
        //dimensions and ID's. Returns false if they aren't.
        if (p1.__dim != p2.__dim || p1.__id != p2.__id)
        {
            temp = false;
        }

        //As long as dimensions of point are greater than 0,
        //loop will run if statement testing for values
        //in both points.
        for (int n = 0; n < p1.getDims(); ++n)
        {
            if (p1.__values[n] != p2.__values[n])
            {
                temp = false;
            }
        }

        return temp;

    }

//-------------------------------------------------------

//Overloaded Inequality Operator
//The same steps above are repeated below for the '!='
//operator.

    bool operator!=(const Point &p1, const Point &p2)
    {
        bool temp = false;
        if (p1.__dim != p2.__dim || p1.__id != p2.__id)
        {
            //Returns true if they are not equal.
            temp = true;
        }

        for (int n = 0; n < p1.getDims(); ++n)
        {
            if (p1.__values[n] != p2.__values[n])
            {
                temp = true;
            }
        }

        return temp;

    }


//OVERLOADED COMPARISON OPERATORS
//All overloaded functions will take two point object
//references as their signature.
//-------------------------------------------------------

//Overloaded '<' Operator
    bool operator<(const Point &leftPnt, const Point &rightPnt)
    {
        bool temp = false;

        //For loop will run as long as
        //dimensions in point are greater than 0.
        for (int n = 0; n < leftPnt.__dim; n++)
        {
            //If statement compares values in the two points
            //Each case needs to be implemented otherwise
            //errors will be generated by the test script.
            if (leftPnt.__values[n] < rightPnt.__values[n])
                return true;

            if ( rightPnt.__values[n] > leftPnt.__values[n])   /// g
                return true;

            if (leftPnt.__values[n] > rightPnt.__values[n])    /// g
                return false;

            if (rightPnt.__values[n] < leftPnt.__values[n])    /// g
                return false;

            //Otherwise
            //else
            //    return false;
        }
        return temp;
    }
//-------------------------------------------------------

//Overloaded '>' Operator
//The same steps as above are repeated below for the greater than comparator
    bool operator>(const Point &leftPnt, const Point &rightPnt)
    {
        bool temp = true;

        //For loop will run as long as
        //dimensions in point are greater than 0.
        for (int n = 0; n < leftPnt.__dim; n++)
        {
            //Return true/false for all possible cases.
            if (leftPnt.__values[n] < rightPnt.__values[n])
                return false;

            if ( rightPnt.__values[n] > leftPnt.__values[n])   /// g
                return false;

            if (leftPnt.__values[n] > rightPnt.__values[n])    /// g
                return true;

            if (rightPnt.__values[n] < leftPnt.__values[n])    /// g
                return true;

        }
        return temp;
    }
//-------------------------------------------------------

//Overloaded '<=' Compound Operator
    bool operator<=(const Point &leftPnt, const Point &rightPnt)
    {
        //Check for valid dimensional point
        for (int n = 0; n < leftPnt.__dim; n++)

            //Test statement for left-side and right-side points
            //for being less than or equal and returns true
            if (leftPnt.__values[n] < rightPnt.__values[n] || leftPnt.__values[n] == rightPnt.__values[n])
            {
                return true;
            }

            //Otherwise
            return false;
    }
//-------------------------------------------------------

//Overloaded '>=' Compound Operator
//The same steps below are repeated as above for the '>=' operator.
    bool operator>=(const Point &leftPnt, const Point &rightPnt)
    {
        for (int n = 0; n < leftPnt.__dim; n++)

            if (leftPnt.__values[n] > rightPnt.__values[n] || leftPnt.__values[n] == rightPnt.__values[n])
            {
                return true;
            }

        //Otherwise
        return false;
    }
//-------------------------------------------------------


//OVERLOADED STREAM OPERATORS
//Each function will take an ostream object reference
//and a point object reference as its signature.
    ostream &operator<<(std::ostream &output, const Point &point)
    {
        int n = 0;
        //initializer is declared outside of for-loop
        //otherwise output statement outside of loop will not
        //recognize 'n' for the index in '__values.'


        //Loop checks dimensions and outputs
        //as long as dimensions are valid.
        for (; n < point.getDims(); ++n)
        {
            output << point.getValue(n);

            if(n != point.getDims() -1)
                output << ", ";
        }



        return output;
    }

//-------------------------------------------------------

    istream &operator>>(istream &input, Point &point)
    {
        int n = 0;
        string ln1, ln2;        //initialize two string variables; ln = line;

        while(!input.eof())
        {
            getline(input, ln1);

            stringstream strm1 (ln1);


            while (!strm1.eof())
            {
                getline(strm1, ln2);

                stringstream strm2 (ln2);

                strm2 >> point.__values[n];

                ++n;
            }
        }

        return input;



    }

//-------------------------------------------------------

}
