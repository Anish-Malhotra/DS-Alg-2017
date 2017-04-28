//
//  main.cpp
//  exam3review
//
//  Created by Anish Malhotra on 3/28/17.
//  Copyright © 2017 CS2134. All rights reserved.
//

#include <iostream>
#include <vector>
using namespace std;

template <class T>
class Stack{
public:
    Stack() : size(0), capacity(5) {data = new T[capacity];}
    ~Stack() {delete[] data;}
    Stack(const Stack& rhs);
    T& operator= (const Stack& rhs);
    
    void pop();
    void push(const T& element);
    T top();
    bool empty();
    int g_size();
    
private:
    T* data;
    int size, capacity;
    
    void growStack(){
        T* temp = new T[capacity*2];
        for(int i=0; i<size; ++i)
            temp[i] = data[i];
        delete[] data;
        data = temp;
        capacity *= 2;
        temp = nullptr;
    }
};

template<class T>
Stack<T>::Stack(const Stack<T>& rhs){
    size = rhs.size;
    capacity = rhs.capacity;
    data = new T[capacity];
    for(int i=0; i < size; ++i){
        data[i] = rhs.data[i];
    }
}

template<class T>
T& Stack<T>::operator= (const Stack& rhs){
    if(this == &rhs){
        return *this;
    }
    delete[] data;
    size = rhs.size;
    capacity = rhs.capacity;
    data = new T[capacity];
    for(int i=0; i < size; ++i){
        data[i] = rhs.data[i];
    }
    return *this;
}

template<class T>
void Stack<T>::pop() {
    if(size){
        size--;
    }
}

template<class T>
void Stack<T>::push(const T& element){
    if(size==capacity)
        growStack();
    data[size++] = element;
}

template<class T>
T Stack<T>::top(){
    if(size)
        return data[size-1];
    return T();
}

template<class T>
bool Stack<T>::empty() {
    return size==0;
}

template<class T>
int Stack<T>::g_size(){
    return size;
}

bool isOp(char c){
    switch(c){
        case '+': return true;
        case '-': return true;
        case '*': return true;
        case '/': return true;
    }
    return false;
}

char evaluatePostfix(const string& op){
    const char* ops = op.c_str();
    Stack<int> postfix;
    for(int i=0; ops[i]!='\0'; ++i){
        int result;
        if(!isOp(ops[i]))
            postfix.push(+ops[i]);
        switch(ops[i]){
            case '+': {
                result = (int)postfix.top();
                postfix.pop();
                result += (int)postfix.top();
                postfix.pop();
                postfix.push(result);
            }
            case '-': {
                result = (int)postfix.top();
                postfix.pop();
                result -= (int)postfix.top();
                postfix.pop();
                postfix.push((result*-1));
            }
            case '*': {
                result = (int)postfix.top();
                postfix.pop();
                result *= (int)postfix.top();
                postfix.pop();
                postfix.push(result);
            }
            /*case '/': {
                postfix.pop();
                result = postfix.top();
                postfix.pop();
                result /= postfix.top();
                postfix.pop();
                postfix.push(result);
            }*/
        }
    }
    return postfix.top();
}

int main(int argc, const char * argv[]) {
    cout << evaluatePostfix("123*+") << endl;
    return 0;
}
