//
//  main.cpp
//  rbtree
//
//  Created by Anish Malhotra on 4/13/17.
//  Copyright © 2017 CS2134. All rights reserved.
//

#include <iostream>
#include <ctime>

using namespace std;

enum Color{red, black};

template <class T>
class RB;

template <class T>
class RBNode{
    RBNode<T>* parent, *left, *right;
    T data;
    Color color;
public:
    RBNode(RBNode* left=nullptr, RBNode* right=nullptr, RBNode* parent=nullptr, Color color=red, const T& data = T())
    :
    parent(parent), left(left), right(right), data(data), color(color){}
    
    friend class RB<T>;
};

template<class T>
class RB{
    RBNode<T>* root;
    
    void printInOrder(RBNode<T>* node){
        if(!node)
            return;
        printInOrder(node->left);
        cout << node->data << ',';
        printInOrder(node->right);
    }
    
    void LeftRotate(RBNode<T>*& node){
        
    }
    void RightRotate(RBNode<T>* node){
        
    }

    
public:
    RB(RBNode<T>* root=nullptr):root(root){}
    
    void printInOrder(){
        printInOrder(root);
    }
    
    void insert(const T& data){
        if(!root){
            root = new RBNode<T>(black,data);
            return;
        }
        RBNode<T>* child = root;
        RBNode<T>* parent;
        while(child){
            parent = child;
            if(data > child->data)
                child = child->right;
            else
                child = child->left;
        }
        child = new RBNode<T>*(parent, red, data);
        RBNode<T>* grandp = parent->parent;
        if(parent->color==red){
            if(parent == grandp->left){ //parent to new child is a left child
                if(grandp->right && grandp->right.color==red){ //if uncle to new child is red
                    if(grandp!=root)
                        grandp->color = red;
                    parent->color = black;
                    grandp->right = black;
                }
                else{ //uncle is nullptr or black
                    if(child == parent->right){ //RL scenario -> LR(PG), swap colors P,G
                        leftRotate(parent);
                        RightRotate(grandp);
                        parent->color = black;
                        grandp->color = red;
                    }
                }
            } //RR -> L(G), swap color P,G
            else{
            
            }
        }
    }
    
};


int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
