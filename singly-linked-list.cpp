//
//  main.cpp
//  rec12
//
//  Created by Anish Malhotra on 11/20/15.
//  Copyright © 2015 CS1124. All rights reserved.
//

#include <iostream>
#include <cstdlib> // To allow NULL if no other includes
#include <string>
#include <vector>
#include <fstream>
using namespace std;

struct Node {
    Node(int data = 0, Node* link = NULL) : data(data), link(link) {}
    int data;
    Node* link;
};

void listInsertHead(int entry, Node*& headPtr);
Node* find(Node& head, int data);
Node* getEnd(Node& head);
void Splice(Node& node, Node& head);
void printList(Node& head);
Node* isSublist(Node& list, Node& sublist);

bool operator==(Node& one, Node& two){
    return one.data == two.data;
}

int main(int argc, const char * argv[]) {
    Node head(5);
    Node head2(7);
    head.link = &head2;
    Node head3(9);
    head2.link = &head3;
    Node head4(1);
    head3.link = &head4;
    
    cout << "List 1: " << endl;
    printList(head);
    
    cout << '\n' << "List 2: " << endl;
    Node head21(6);
    Node head22(3);
    head21.link = &head22;
    Node head23(2);
    head22.link = &head23;
    printList(head21);
    
    Splice(head2, head21);
    cout << '\n' << "Spliced List: " << endl;
    printList(head);
    
    cout << "------------------------------------------------------------------" << endl;
    
    Node one(1);
    Node nine(9, &one);
    Node two(2, &nine);
    Node three(3, &two);
    Node six(6, &three);
    Node seven(7, &six);
    Node five(5, &seven);

    Node nine1(9);
    Node two1(2, &nine1);
    Node three1(3, &two1);
    Node six1(6, &three1);
    
    Node* check = isSublist(five, six1);
    cout << check << endl;
    printList(*(find(five,six1.data)));
    
    Node three2(3);
    Node two2(2,&three2);
    Node six2(6,&two2);
    
    Node* check2 = isSublist(five, six2);
    if(check2 == NULL)
        cout << '\n' << "NULL" << endl;
    //cout << check2->data << endl;
    
    Node four3(4);
    Node one3(1,&four3);
    Node nine3(9,&one3);
    Node two3(2,&nine3);
    
    Node* check3 = isSublist(five, two3);
    if(check3 == NULL)
        cout << '\n' << "NULL" << endl;
    
    return 0;
}

Node* find(Node& head, int data){
    Node* temp = &head;
    while(temp != NULL){
        if(temp->data == data)
            break;
        temp = temp->link;
    }
    return temp;
}

void listInsertHead(int entry, Node*& headPtr) {
    headPtr = new Node(entry, headPtr);
}

Node* getEnd(Node& head){
    Node* temp = &head;
    while(temp->link != NULL)
        temp = temp->link;
    return temp;
}

void Splice(Node& node, Node& head){
    Node* temp = node.link;
    node.link = &head;
    Node* temp2 = getEnd(head);
    temp2->link = temp;
}

void printList(Node& head){
    Node* temp = &head;
    while(temp != NULL){
        cout << temp->data << endl;
        temp = temp->link;
    }
}

Node* isSublist(Node& list, Node& sublist){
    Node* head = find(list, sublist.data);
    if(head == NULL)
        return head;
    Node* sublistNext = sublist.link;
    Node* headNext = head->link;
    while(sublistNext != NULL && headNext != NULL){
        if (*sublistNext == *headNext){
            sublistNext = sublistNext->link;
            headNext = headNext->link;
        }
        else{
            if(find(*(head->link),sublist.data) == NULL){
                return NULL;
            }
            else{
                return isSublist(*(find(*(head->link),sublist.data)),sublist);
            }
        }
    }
    if(headNext == NULL)
        return NULL;
    return head;
}
