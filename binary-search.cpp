//
//  main.cpp
//  rec14
//
//  Created by Anish Malhotra on 12/11/15.
//  Copyright © 2015 CS1124. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include <climits>
using namespace std;

struct Node {
    Node(int x = 0, Node* l = NULL) : data(x), link(l) {}
    int data;
    Node* link;
};

class A { void f(){cout << 'A' << endl;} };
class B { void f(){cout << 'B' << endl;} };
class C : public A ,public B { };

template <typename T>
template <typename C<T>>


struct TNode {
    TNode(int data = 0, TNode *left = nullptr, TNode *right = nullptr)
    : data(data), left(left), right(right) {}
    int data;
    TNode *left, *right;
};

int maxTwoInt(int one, int two){
    if(one > two)
        return one;
    else if(two > one)
        return two;
    else
        return two;
}

int maxThreeInt(int one, int two, int three){
    int max1 = maxTwoInt(one, two);
    return maxTwoInt(max1, three);
}

void listDisplay(const Node* headPtr) {
    // Declare a temporary variable to use to "walk down" the list.
    const Node* p = headPtr;
    // Loop through the list.  Note the test condition.  If p is NULL
    // that means that we are not pointing to a node anymore.
    while (p != NULL) {
        // If we came into the loop then we must be pointing to a node
        // so display the data.
        cout << p->data << ' ';
        // Now we need to set the pointer to the point to the next node.
        // Be careful to note that we CANNOT just say, "p++;".  Be sure
        // that you know why!
        p = p->link;
    }
    cout << endl;
}

void printBinary(int n){
    if(n>1){
        printBinary(n/2);
    }
    cout << n%2;
}

void f(int n) {
    if (n > 1) {
        cout << 'a';
        f(n/2);
        cout << 'b';
        f(n/2);
    }
    cout << 'c';
}

char binarySearch(char* sortedArray, char a, int start, int end){
    if(start > end){
        return 0;
    }
    int mid = (start+end)/2;
    if(sortedArray[mid] == a){
        return mid;
    }
    else if(a > sortedArray[mid]){
        return binarySearch(sortedArray, a, mid+1, end);
    }
    else{
        return binarySearch(sortedArray, a, start, mid-1);
    }
}

Node* newList(Node* list1, Node* list2){
    if(!list1)
        return NULL;
    Node* list3 = new Node();
    if(list1){
        list3->data = (list1->data + list2->data);
        list3->link = newList(list1->link, list2->link);
    }
    return list3;
}

Node* newList2(Node* list1, Node* list2){
    if(!(list1->link))
        return new Node(list1->data + list2->data);
    return new Node(list1->data + list2->data, newList2(list1->link,list2->link));
}

int maxTree(TNode* tree){
    if(!tree)
        return INT_MIN;
    int lmax = maxTree(tree->left);
    int rmax = maxTree(tree->right);
    return maxThreeInt(lmax, rmax, tree->data);
}

int sum(char* cstring){
    if(*cstring == '\0'){
        return 0;
    }
    int charSum = cstring[0] + sum(cstring+1);
    return charSum;
}

int main(int argc, const char * argv[]) {
    //printBinary(9);
    Node h1(9);
    h1.link = new Node(5);
    Node h2(4);
    h1.link->link = new Node(6);
    h2.link = new Node(5);
    h2.link->link = new Node(6);
    listDisplay(&h1);
    listDisplay(&h2);
    Node* h3 = newList2(&h1, &h2);
    listDisplay(h3);
    cout << '\n';
    f(4);
    cout << '\n';
    C c;

    return 0;
}
