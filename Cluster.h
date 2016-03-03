#ifndef CLUSTERING_CLUSTER_H
#define CLUSTERING_CLUSTER_H

#include "Point.h"

namespace Clustering {

    //typedef Point *PointPtr;
    typedef struct LNode *LNodePtr;

    //STRUCT LNode
    struct LNode
    {

        Point point;
        LNodePtr next;
        LNode(const Point &p, LNodePtr n);

    };

    //CLASS CLUSTER
    class Cluster
    {

        int __size;
        LNodePtr __points;

//        void __del();
//        void __cpy(LNodePtr pts);
//        bool __in(const Point &p) const;


    public:
        //Default Constructor
        Cluster();

        // The big three: cpy ctor, overloaded operator=, dtor
        Cluster(const Cluster &);
        Cluster &operator=(const Cluster &);
        ~Cluster();

        // Getters/setters
        int getSize() const; // TODO add to the requirements

        // Set functions: They allow calling c1.add(c2.remove(p));
        void add(const Point &); // TODO add asc order to the requirements
        const Point &remove(const Point &);
        bool contains(const Point &);

        // Overloaded operators

        // Members: Subscript
        const Point &operator[](unsigned int index) const; // notice: const

        // Members: Compound assignment (Point argument)
        Cluster &operator+=(const Point &);
        Cluster &operator-=(const Point &);

        // Members: Compound assignment (Cluster argument)
        Cluster &operator+=(const Cluster &); // union
        Cluster &operator-=(const Cluster &); // (asymmetric) difference

        // Friends: IO
        friend std::ostream &operator<<(std::ostream &, const Cluster &);   //Const because we're reading out
        friend std::istream &operator>>(std::istream &, Cluster &);         //not const because reading in.
                                                                            // we WANT to change the value when reading in.

        // Friends: Comparison
        friend bool operator==(const Cluster &, const Cluster &);
        friend bool operator!=(const Cluster &, const Cluster &);

        // Friends: Arithmetic (Cluster and Point)
        friend const Cluster operator+(const Cluster &, const Point &);
        friend const Cluster operator-(const Cluster &, const Point &);

        // Friends: Arithmetic (two Clusters)
        friend const Cluster operator+(const Cluster &, const Cluster &); // union
        friend const Cluster operator-(const Cluster &, const Cluster &); // (asymmetric) difference

    };

}
#endif //CLUSTERING_CLUSTER_H
