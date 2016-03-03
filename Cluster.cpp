//
//Written By Jeff Cayton
//
//
//


#include <cassert>
#include <sstream>
#include <iomanip>

#include "Cluster.h"

namespace Clustering {

 //Default values for the node point.
    LNode::LNode(const Point &newPnt, LNodePtr nxtPnt) : point(newPnt)
    {
        point = newPnt;
        next = nxtPnt;
    }
//-------------------------------------------------------

//Default Ctor
    Cluster::Cluster()
    {
        __size = 0;
        __points = NULL;
    }

//-------------------------------------------------------

//Constructor
    Cluster::Cluster(const Cluster &cluster) : Cluster()
    {
        //Run a for loop to check that cluster size is greater
        //than 0.
        for (int n = 0; n < cluster.getSize(); ++n)
        {
            //invoke add function to add cluster being
            //passed into the constructor.

            add(cluster[n]);
        }
    }

//-------------------------------------------------------

//Overloaded '=' Operator
    Cluster &Cluster::operator=(const Cluster &cluster) {
//Check that size is greater than 0.
        if (__size > 0)
        {
            //Create temp node, and cursor
            //to navigate list.
            LNodePtr temp;
            LNodePtr cursor = __points;

            while (cursor != NULL)
            {
                temp = cursor;
                cursor = cursor->next;

                //delete the temp node
                //after the assignment has completed.
                delete temp;
            }

            //initialize size of cluster to 0.
            __size = 0;
        }

        for (int n = 0; n < cluster.getSize(); ++n)
        {
            add(cluster[n]);
        }
        return *this;       //return the dereferenced object.
    }

//-------------------------------------------------------

//Get Size member function
//Returns the size of the cluster.
    int Cluster::getSize() const
    {
        return __size;
    }

//-------------------------------------------------------

//Dtor for Cluster Class
    Cluster::~Cluster()
    {
        //decalre new LNode Variable
        LNodePtr cursor;


        //While points is not equal to nullptr,
        //assign cursor value of __points.
        while (__points != nullptr)
        {
            cursor = __points;

            __points = cursor->next;

            //Remove the node once
            //the operations have been completed.
            //NOTE: never call the delete function
            //unless we want to decrease the number of nodes.
            delete cursor;
        }
    }

//-------------------------------------------------------

//Add Function
//Takes const Point reference as an argument.
    void Cluster::add(const Point &p)
    {

        //Check for an empty list.
        if (__size == 0)
        {
            ++__size;

            //Create a new node with values from p.
            LNodePtr newNode = new LNode(p ,nullptr);

            //Assign newNode to __points
            __points = newNode;


        }

        //Otherwise, if the list is NOT empty
        else
        {
            //Use contains function to check for p
            //inside of the list. Return if value is present.
            if (contains(p))
                return;


            //Variables to keep track of node pointers
            LNodePtr after;
            LNodePtr before;

            //Initializes the beginning of the list
            after = __points;

            before = nullptr;

            //Use while loop to locate where to
            //insert new node
            while (after != nullptr)
            {

                //If value of p is less than
                //value of point object after it,
                if (p < after->point)
                {

                    //If ptr before is equal to null,
                    //create new node with data from "after"
                    //and assign to __points.
                    if (before == nullptr)
                    {
                        // First element in list
                        __points = new LNode(p, after);

                        ++__size;

                        //Node has been added to the list.
                        //Exit the loop to continue running program.
                        return;
                    }


                    //Otherwise, if "after" is not first node in the list
                    else
                    {
                       //create new node with data from after and
                        //assign to before.
                        before->next = new LNode(p, after);

                        ++__size;

                        //Return to the program when the node
                        //has been inserted.
                        return;
                    }
                }

                //Assign after to before,
                //and then have after point to the next
                //node ptr.
                before = after;
                after = after->next;

            }

            //If there are no nodes in the list,
            //simply insert at the back of the list.
            before->next = new LNode(p, nullptr);

            ++__size;
        }
    }


//-------------------------------------------------------

//Remove Function
//The steps above are repeated below but are used
//to remove a node in the list
    const Point &Cluster::remove(const Point &p)
    {
        //Begin by testing for if p is in the
        //list
        if (contains(p))
        {
            //Create variables to keep track of
            //node pointers
            LNodePtr after;
            LNodePtr before = nullptr;

            //assign value of points to
            //after node.
            after = __points;

            //As long as after does not equal null,
            //execute the loop.
            while (after != nullptr)
            {
                //If point of after node is equal to p,
                //continue into the statement.
                if (after->point == p)
                {
                    //As long as before statement is true,
                    //check if before is equal to null.
                    //
                    if (before == nullptr)
                    {
                        //assign value of after->next
                        //to __points.
                        __points = after->next;


                        //delete the node and decrement the size
                        //of the list.
                        delete after;

                        --__size;

                    }


                    //Otherwise
                    else
                    {
                        // not first
                        before->next = after->next;
                        delete after;

                        --__size;

                        break;
                    }
                }

                before = after;
                after = after->next;
            }
        }

        return p;
    }

//-------------------------------------------------------
//Contains Function
//Takes a const Point reference as the signature

    bool Cluster::contains(const Point &p)
    {
        LNodePtr next = __points;

        //While node doesn't equal nullptr
        while (next != nullptr)
        {
            //Statement checks if the nodes are equal before
            //continuing.

            if (next->point.getId() == p.getId())

                //If the points are equal, return true.
                return true;

            //Otherwise, assign value of next
                //node to next.
            else
                next = next->next;
        }

        //Exit loop and return false
        //if the point is not found.
        return false;
    }

//-------------------------------------------------------

//Overloaded operators

//Overloaded indexing operator
    const Point &Cluster::operator[](unsigned int index) const
    {
        assert (__size > 0);
        LNodePtr cursor = __points;

        for (int n = 0; n < index; ++n)
        {
            cursor = cursor->next;
        }
        return cursor->point;
    }

//-------------------------------------------------------

//Compound Assignment Operators

    Cluster &Cluster::operator+=(const Point &p)
    {
        //Invoke add function on point object
        add(p);

        //return the dereferenced object.
        return *this;
    }
//-------------------------------------------------------

//The same steps above are repeated below but for the -= operator.
    Cluster &Cluster::operator-=(const Point &p) {
        remove(p);

        return *this;
    }
//-------------------------------------------------------

//Overloaded Compound Assignment Operator
//This will create a union of two point objects.
    Cluster &Cluster::operator+=(const Cluster &rightPnt)
    {

        for (int n = 0; n < rightPnt.getSize(); ++n)
        {
            add(rightPnt[n]);
        }

        //return the dereferenced object
        return *this;
    }

//-------------------------------------------------------

//Overloaded Compund -= Operator
//
    Cluster &Cluster::operator-=(const Cluster &rhs) { // (asymmetric) difference
        for (int n = 0; n < rhs.getSize(); ++n)
        {
            remove(rhs[n]);
        }

        //Return the dereferenced object
        return *this;
    }
//-------------------------------------------------------

    //THESE ARE NOT USED IN THIS PROGRAM.
//    // Private Member functions
//    void Cluster::__del()
//    {
//        // stub
//    }
//
//    void Cluster::__cpy(LNodePtr pts)
//    {
//        // stub
//    }
//
//    bool Cluster::__in(const Point &p) const
//    {
//        return true;
//    }

//-------------------------------------------------------

//Overloaded Stream Operators

//Overloaded Extraction Operator
    std::ostream &operator<<(std::ostream &output, const Cluster &cluster)
    {

        //output cluster as long as cluster size is greater than 0
        for (int n = 0; n < cluster.getSize(); ++n)
        {
            output << cluster[n] << std::endl;
        }

        return output;
    }

//-------------------------------------------------------

//Overloaded Insertion Operator
    std::istream &operator>>(std::istream &input, Cluster &cluster) {

        //While not end of file
        while (!input.eof())
        {

            Point p(1);

            //create new string object
            std::string string1;

            //Use getline to read input into string1
            std::getline(input, string1);

            //if string length is greater than 0,
            //execute inside statement
            if (string1.length() > 0) {
                std::stringstream ss(string1);

                //read string stream object into point object.
                ss >> p;


                //call add function for cluster object
                //pass value of p into add as signature.
                cluster.add(p);
            }
        }

        //Return the input
        return input;
    }

//-------------------------------------------------------

//Overloaded Equality Operator
    bool operator==(const Cluster &leftPnt, const Cluster &rightPnt)
    {
        //If size of left point is not equal to size of right point
        //return false value.
        if (leftPnt.getSize() != rightPnt.getSize())
            return false;

        //As long as size of left point is greater than 0,
        //and if left point does not equal right point, return false.
        for (int n = 0; n < leftPnt.getSize(); ++n)
        {
            if (leftPnt[n] != rightPnt[n])

                return false;
        }

        //OTHERWISE
        return true;
    }

//-------------------------------------------------------

//Overloaded inequality operator
    bool operator!=(const Cluster &leftPnt, const Cluster &rightPnt)
    {
        return !(leftPnt == rightPnt);
    }
//-------------------------------------------------------

//Cluster & Point Arithmetic

    const Cluster operator+(const Cluster &leftPnt, const Point &rightPnt)
    {
        //Put value of leftPnt into sum cluster object.
        Cluster sum(leftPnt);

        //add right point using overloaded compound assignment operator
        sum += rightPnt;

        //return the sum
        return sum;
    }

//-------------------------------------------------------

//the steps above are repeated below but for the subtraction operator

    const Cluster operator-(const Cluster &leftPnt, const Point &rightPnt)
    {
        Cluster diff(leftPnt);
        diff -= rightPnt;
        return diff;
    }

//-------------------------------------------------------

//Cluster Arithmetic for Two Cluster Objects
    //Steps in the below functions are alos the same as above.
    const Cluster operator+(const Cluster &leftPnt, const Cluster &rightPnt)
    {
        Cluster sum(leftPnt);
        sum += rightPnt;
        return sum;
    }

//-------------------------------------------------------

//Cluster Arithmetic for assymetric difference

    const Cluster operator-(const Cluster &leftPnt, const Cluster &rightPnt)
    {
        Cluster diff(leftPnt);
        diff -= rightPnt;
        return diff;
    }

//-------------------------------------------------------
}

