//
//  main.cpp
//  HW6
//
//  Created by Anish Malhotra on 3/21/16.
//  Copyright © 2016 CS2134. All rights reserved.
//

//
//  Modified from Weiss' linked list class

#include <iostream>
#include <algorithm>
#include <forward_list>
#include <list>
#include <functional>
#include <vector>

using namespace std;

template <typename Object>
class List
{
private:
    
    struct Node
    {
        Object  data;
        Node   *next;
        
        Node( const Object & d = Object{ },  Node * n = nullptr )
        : data{ d },  next{ n } { }
        
        Node( Object && d, Node * n = nullptr )
        : data{ std::move( d ) }, next{ n } { }
    };
    
public:
    class iterator
    {
    public:
        
        iterator( ): current( nullptr )
        { }
        
        Object & operator* ( )
        { return current->data; }
        
        const Object & operator* ( ) const
        { return  current->data; }
        
        iterator & operator++ ( )
        {
            this->current = this->current->next;
            return *this;
        }
        
        iterator operator++ ( int )
        {
            iterator old = *this;
            ++( *this );
            return old;
        }
        
        bool operator== ( const iterator & rhs ) const
        { return current == rhs.current; }
        
        bool operator!= ( const iterator & rhs ) const
        { return !( *this == rhs ); }
        
    private:
        Node * current;
        
        iterator( Node *p ) : current{ p }
        { }
        
        friend class List<Object>;
    };
    
public:
    List( )
    { header = new Node; }
    
    ~List( )
    {
        clear( );
        delete header;
    }
    
    List( const List & rhs ){
        header = new Node;
        Node* thisCur = header;
        for(iterator current = rhs.begin(); current != rhs.end(); ++current){
            thisCur->next = new Node(*current);
            thisCur = thisCur->next;
        }
    }
    
    List & operator= ( const List & rhs )
    {
        List copy = rhs;
        std::swap( *this, copy );
        return *this;
    }
    
    List( List && rhs ):header{ new Node }
    {
        header->next = rhs.header->next;
        rhs.header->next = nullptr;
    }
    
    List & operator= ( List && rhs )
    {
        std::swap( header, rhs.header );
        return *this;
    }
    
    iterator begin( ) const
    { return iterator( header->next ); }
    
    iterator end( ) const
    { return iterator( nullptr ); }
    
    iterator before_begin( ) const
    { return iterator( header ); }
    
    bool empty( ) const
    { return header->next == nullptr; }
    
    void clear( )
    {
        while( !empty( ) )
            pop_front( );
    }
    
    void pop_front( )
    { erase_after( before_begin( ) ); }
    
    iterator insert_after( iterator itr, const Object & x )
    {
        Node *p = itr.current;
        p->next = new Node{ x, p->next };
        
        return iterator(p->next);
    }
    
    void remove( const Object & x )
    {
        Node * prev = header;
        
        while ( prev->next != nullptr )
        {
            if ( prev->next->data == x )
                erase_after( iterator(prev) );
            else
                prev = prev->next;
        }
    }
    
    iterator erase_after( iterator itr )
    {
        Node *p = itr.current;
        Node *oldNode = p->next;
        
        p->next = oldNode->next;
        delete oldNode;
        
        return iterator( p->next );
    }
    
    Object & front( ){
        return *(header->next);
    }
    
    const Object & front( ) const;
    
    void merge( List & alist ){
        iterator alistItr = alist.begin();
        Node* end = header;
        while(end != nullptr){
            header = header->next;
        }
        while(!(alist.empty())){
            end = new Node(*alistItr);
            end = end->next;
            alistItr++;
        }
        alist.erase();
        this->sort();
    }
    
    void reverse( );
    
    template<class Predicate>
    void remove_if( Predicate pred ){
        for(iterator itrStart = this->before_begin(); itrStart != this->end(); ++itrStart){
            if(pred((itrStart.current)->next->data)){
                erase_after(itrStart);
            }
        }
    }
    
    iterator insert_after( iterator itr, Object && x ){
        Node *p = itr.current;
        p->next = new Node{ std::move(x), p->next };
        
        return iterator(p->next);
    }
    
    void remove_adjacent_duplicates(){
        Node* current = header;
        Node* curNext;
        while (current->next != nullptr){
            if (current->data == current->next->data){
                curNext = current->next->next;
                free(current->next);
                current->next = curNext;
            }
            else
                current = current->next;
        }
    }
    
private:
    Node *header;
    
};

template <typename Object>
class Queue{
private:
    struct Node
    {
        Object  data;
        Node   *next;
        
        Node( const Object & d = Object{ },  Node * n = nullptr )
        : data{ d },  next{ n } { }
        
        Node( Object && d, Node * n = nullptr )
        : data{ std::move( d ) }, next{ n } { }
    };

public:
    Queue()
    :
    size(0)
    {
        frontNode = new Node;
        backNode = frontNode;
    }
    
    void enqueue(Object & data){
        if(size == 0){
            frontNode->data = data;
            backNode = frontNode;
        }
        else{
            Node* current;
            while(current != backNode){
                current = current->next;
            }
            current = new Node(data);
            backNode = current;
        }
        size++;
    }
    
    void dequeue(){
        if(size!=0){
            Node* tmp = frontNode;
            frontNode = frontNode->next;
            delete tmp;
            size--;
        }
    }
    
    bool empty( ) const
    { return size==0; }
    
    Object front() const{
        return *frontNode;
    }
    
    Object back() const{
        return *backNode;
    }
    
    
private:
    Node * frontNode;
    Node * backNode;
    Node * current;
    int size;
};

bool is_379 (const double& value) { return (value==3.79); }


int main( int argc, const char * argv[] ) {
    /*List<double> first;
    first.insert_after(first.before_begin(), 3.79);
    first.insert_after(first.begin(), 3.79);
    first.insert_after(first.begin(), 1.54);
    first.insert_after(first.begin(), 3.79);
    first.insert_after(first.begin(), 1.54);
    first.insert_after(first.begin(), 1.54);

    List<double> second(first);
    for (double& x: first) std::cout << " " << x;
    std::cout << std::endl;
    
    first.remove_adjacent_duplicates();
    
    for (double& x: first) std::cout << " " << x;
    std::cout << std::endl;
    
    first.remove_if(is_379);
    
    for (double& x: first) std::cout << " " << x;
    std::cout << std::endl;*/

    
    return 0;
}

