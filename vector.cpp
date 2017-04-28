//
//  main.cpp
//  Data Structures HW 3
//
//  Created by Anish Malhotra on 2/17/16.
//  Copyright © 2016 CS2134. All rights reserved.
//

#include <iostream>
#include <iterator>
#include <string>
#include <vector>
using namespace std;

template <typename Object>
class Vector
{
public:
    explicit Vector( int initSize = 0 )
    : theSize{ initSize }, theCapacity{ initSize + SPARE_CAPACITY }
    { objects = new Object[ theCapacity ]; }
    
    Vector( const Vector & rhs )
    : theSize{ rhs.theSize }, theCapacity{ rhs.theCapacity }, objects{ nullptr }
    {
        objects = new Object[ theCapacity ];
        for( int k = 0; k < theSize; ++k )
            objects[ k ] = rhs.objects[ k ];
    }
    
    Vector & operator= ( const Vector & rhs )
    {
        Vector copy = rhs;
        std::swap( *this, copy );
        return *this;
    }
    
    ~Vector( )
    { delete [ ] objects; }
    
    Vector( Vector && rhs )
    : theSize{ rhs.theSize }, theCapacity{ rhs.theCapacity }, objects{ rhs.objects }
    {
        rhs.objects = nullptr;
        rhs.theSize = 0;
        rhs.theCapacity = 0;
    }
    
    Vector & operator= ( Vector && rhs )
    {
        std::swap( theSize, rhs.theSize );
        std::swap( theCapacity, rhs.theCapacity );
        std::swap( objects, rhs.objects );
        
        return *this;
    }
    
    bool empty( ) const
    { return size( ) == 0; }
    int size( ) const
    { return theSize; }
    int capacity( ) const
    { return theCapacity; }
    
    Object & operator[]( int index )
    {
        return objects[ index ];
    }
    
    const Object & operator[]( int index ) const
    {
        return objects[ index ];
    }
    
    void resize( int newSize )
    {
        if( newSize > theCapacity )
            reserve( newSize * 2 );
        theSize = newSize;
    }
    
    void reserve( int newCapacity )
    {
        if( newCapacity < theSize )
            return;
        
        Object *newArray = new Object[ newCapacity ];
        for( int k = 0; k < theSize; ++k )
            newArray[ k ] = std::move( objects[ k ] );
        
        theCapacity = newCapacity;
        std::swap( objects, newArray );
        delete [ ] newArray;
    }
    
    // Stacky stuff
    void push_back( const Object & x )
    {
        if( theSize == theCapacity )
            reserve( 2 * theCapacity + 1 );
        objects[ theSize++ ] = x;
    }
    // Stacky stuff
    void push_back( Object && x )
    {
        if( theSize == theCapacity )
            reserve( 2 * theCapacity + 1 );
        objects[ theSize++ ] = std::move( x );
    }
    
    
    // Iterator stuff: not bounds checked
    typedef Object * iterator;
    typedef const Object * const_iterator;
    
    iterator begin( )
    { return &objects[ 0 ]; }
    const_iterator begin( ) const
    { return &objects[ 0 ]; }
    iterator end( )
    { return &objects[ size( ) ]; }
    const_iterator end( ) const
    { return &objects[ size( ) ]; }
    
    iterator erase (iterator vItr) {
        copy(vItr+1, end(), vItr);
        resize(size()-1);
        return vItr;
    }
    
    static const int SPARE_CAPACITY = 2;
    
private:
    int theSize;
    int theCapacity;
    Object * objects;
};

class Student {
public:
    Student(double grade=0.0, const string& name="kid")
    :
    gpa(grade), name(name)
    {}
    
    double getGPA() const{
        return gpa;
    }
    
    friend ostream& operator<<(ostream& os, const Student& student);
    
private:
    double gpa;
    const string name;
};


ostream& operator<<(ostream& os, const Student& student)
{
    os << student.name << "has a GPA of: " << student.gpa;
    return os;
}

template<class Itr, class UnaryPred>
void print_if(Itr start, Itr end, UnaryPred pred){
    while(start != end){
        if(pred(*start))
            cout << *start << endl;
        start++;
    }
}

class GPA_in_range {
public:
    GPA_in_range(double l, double h)
    :
    low(l), high(h)
    {}
    
    bool operator()(Student& student) const{
        if(student.getGPA() >= low && student.getGPA() <= high)
            return true;
        else
            return false;
    }
    
private:
    double low,high;
};



int main(int argc, const char * argv[]) {
    Student* s1 = new Student(2.8,"jason");
    Student* s2 = new Student(3.7, "david");
    Student* s3 = new Student(3.4, "harry");
    Vector<Student*> students;
    students.push_back(s1);
    students.push_back(s2);
    students.push_back(s3);
    GPA_in_range gpa_check(3.0,4.0);
    //print_if(students.begin(), students.end() gpa_check);
    
    //THE ABOVE TEST DOES NOT WORK FOR SOME REASON?!?!
    
    Vector<Student*>::iterator itr = students.begin();
    students.erase(itr);
    
    //ERASE TEST WORKS
    return 0;
}
