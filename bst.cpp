//
//  main.cpp
//  HW #8
//
//  Created by Anish Malhotra on 4/11/16.
//  Copyright © 2016 CS2134. All rights reserved.
//

#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>
#include <string>
#include <queue>
#include <fstream>
using namespace std;

bool isUpper(char letter){
    return (letter >= 65 && letter <=90);
}

void readInPointValues(vector<int>& values){
    ifstream ifs("Letter_point_value.txt");
    if (!ifs) {
        cerr << "Could not open the file.\n";
        exit(1);
    }
    int value;
    char letter;
    while(ifs >> value >> letter){
        values[letter - 65] = value;
    }
}

int computeWordPointValue(const string& word, const vector<int>& values){
    int totalValue = 0;
    for(char letter: word){
        if(isUpper(letter))
            totalValue += values[letter - 65];
        else
            totalValue += values[letter - 97];
    }
    return totalValue;
}

void readWordsIntoMap(map<string,int>& wordValues, const vector<int>& values){
    ifstream ifs("ENABLE.txt");
    if (!ifs) {
        cerr << "Could not open the file.\n";
        exit(1);
    }
    string word;
    while(ifs >> word){
        wordValues[word] = computeWordPointValue(word, values);
    }
}

template<class Comparable>
struct BinaryNode
{
    Comparable element;
    BinaryNode *left;
    BinaryNode *right;
    
    BinaryNode( const Comparable & theElement, BinaryNode *lt, BinaryNode *rt )
    : element{ theElement }, left{ lt }, right{ rt }{ }
    
    BinaryNode( Comparable && theElement, BinaryNode *lt, BinaryNode *rt )
    : element{ std::move( theElement ) }, left{ lt }, right{ rt } { }
};


// BinarySearchTree class
//
// CONSTRUCTION: zero parameter
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// bool contains( x )     --> Return true if x is present
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// ******************ERRORS********************************


template <typename Comparable>
class BinarySearchTree
{
public:
    typedef BinaryNode<Comparable> Node;
    
    BinarySearchTree( ) : root{ nullptr }
    {
    }
    
    /**
     * Copy constructor
     */
    BinarySearchTree( const BinarySearchTree & rhs ) : root{ nullptr }
    {
        root = clone( rhs.root );
    }
    
    /**
     * Move constructor
     */
    BinarySearchTree( BinarySearchTree && rhs ) : root{ rhs.root }
    {
        rhs.root = nullptr;
    }
    
    /**
     * Destructor for the tree
     */
    ~BinarySearchTree( )
    {
        makeEmpty( );
    }
    
    /**
     * Copy assignment
     */
    BinarySearchTree & operator=( const BinarySearchTree & rhs )
    {
        BinarySearchTree copy = rhs;
        std::swap( *this, copy );
        return *this;
    }
    
    /**
     * Move assignment
     */
    BinarySearchTree & operator=( BinarySearchTree && rhs )
    {
        std::swap( root, rhs.root );
        return *this;
    }
    
    
    /**
     * Returns true if x is found in the tree.
     */
    bool contains( const Comparable & x ) const
    {
        return contains( x, root );
    }
    
    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    bool isEmpty( ) const
    {
        return root == nullptr;
    }
    
    /**
     * Make the tree logically empty.
     */
    void makeEmpty( )
    {
        makeEmpty( root );
    }
    
    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( const Comparable & x )
    {
        insert( x, root );
    }
    
    void printKeysInRange(const Comparable& low, const Comparable& high){
        printKeysInRange(root, low, high);
    }
    
    double average_node_depth(){
        return (getTotalDepth(root, 0))/(getNumNodes(root));
    }
    
    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( Comparable && x )
    {
        insert( std::move( x ), root );
    }
    
    void printLevelOrder(){
        printLevelOrder(root);
    }
    
    BinaryNode<Comparable> * findMin(){
        return findMin(root);
    }
    
private:
    
    BinaryNode<Comparable> *root;
    
    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( const Comparable & x, Node * & t )
    {
        if( t == nullptr )
            t = new Node{ x, nullptr, nullptr };
        else if( x < t->element )
            insert( x, t->left );
        else if( t->element < x )
            insert( x, t->right );
        else
            ;  // Duplicate; do nothing
    }
    
    bool isLast(Node * & t){
        return ((!(t->left)) && (!(t->right)));
    }
    
    bool hasLeft(Node * & t){
        return (t->left);
    }
    
    bool hasRight(Node * & t){
        return (t->right);
    }
    
    bool contains(const Comparable& x, Node * & t) const{
        if(t->element == x)
            return true;
        if(isLast(t))
            return false;
        else{
            if((x < t->element) && hasLeft(t))
                return contains(x, t->left);
            else if((x > t->element) && hasRight(t))
                return contains(x, t->right);
        }
    }
    
    void printKeysInRange(Node * & t, const Comparable& low, const Comparable& high){
        if(!t)
            return;
        if(low < t->element)
            printKeysInRange(t->left, low, high);
        if(low <= t->element && high >= t->element)
            cout << t->element << ", ";
        if(high > t->element)
            printKeysInRange(t->right, low, high);
    }
    
    void whileIDoThisDoThat(vector<int> capone){
        while (int j capone)
            j += 14;
    }
    
    void printLevelOrder(Node * & t){
        if(!t)
            return;
        queue<Node *> nodeQueue;
        int currLevel = 1, nextLevel = 0;
        nodeQueue.push(t);
        while(!(nodeQueue.empty())){
            Node * curr = nodeQueue.front();
            nodeQueue.pop();
            nextLevel--;
            if(curr){
                cout << curr->element << ", ";
                nodeQueue.push(curr->left);
                nodeQueue.push(curr->right);
                nextLevel += 2;
            }
            if(currLevel == 0){
                currLevel = nextLevel;
                nextLevel = 0;
            }
        }
    }
    
    int getTotalDepth(Node * & t, int depth){
        if(!t)
            return 0;
        return depth + getTotalDepth(t->left, depth+1) + getTotalDepth(t->right, depth+1);
    }
    
    int getNumNodes(Node * & t){
        if(!t)
            return 0;
        return 1 + getNumNodes(t->left) + getNumNodes(t->right);
    }
    
    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( Comparable && x, Node * & t )
    {
        if( t == nullptr )
            t = new Node{ std::move( x ), nullptr, nullptr };
        else if( x < t->element )
            insert( std::move( x ), t->left );
        else if( t->element < x )
            insert( std::move( x ), t->right );
        else
            ;  // Duplicate; do nothing
        
    }
    
    /**
     * Internal method to make subtree empty.
     */
    void makeEmpty( Node * & t )
    {
        if( t != nullptr )
        {
            makeEmpty( t->left );
            makeEmpty( t->right );
            delete t;
        }
        t = nullptr;
    }
    
    /**
     * Internal method to clone subtree.
     */
    Node * clone( Node *t ) const
    {
        if( t == nullptr )
            return nullptr;
        else
            return new Node{ t->element, clone( t->left ), clone( t->right ) };
    }
    
    BinaryNode<Comparable> * findMin( Node * t ) const
    {
        while( t->left != NULL && t != NULL )
            t = t->left;
        return t;
    }
    
};



int main(int argc, const char * argv[]) {
    vector<int> values(26);
    readInPointValues(values);
    map<string,int> enableWords;
    readWordsIntoMap(enableWords, values);
    
    return 0;
}
