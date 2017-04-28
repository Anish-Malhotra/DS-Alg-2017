//
//  main.cpp
//  homework4
//
//  Created by Anish Malhotra on 4/25/17.
//  Copyright © 2017 CS2134. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;

template <class S>
struct Data{
    S data;
    Data(const S& data):data(data){}
};

//Hashing function-object using the Knuth Variant on Division method
class Hash{
public:
    int operator()(int key, int size){
        return ((key*(key+3)) % size);
    }
};

//Example notEquals function-object
template <class T>
class notEquals{
public:
    bool operator()(const T& lhs, const T& rhs){
        return (lhs.data == rhs.data);
    }
};

//Handles separate chaining using a doubly linked-list
template <class T>
struct MapNode{
    int key;
    T value;
    MapNode* next;
    MapNode* prev;
    
    MapNode(int key, const T& val):key(key),value(val),next(nullptr), prev(nullptr){}
    MapNode(MapNode* rhs):next(nullptr),prev(nullptr){
        key = rhs->key;
        value = rhs->value;
    }
};

//The actual implentation of the map on top of the MapNode pairs.
template<class T, class S, class F>
class DMap{
private:
    int size;
    S notEquals;
    F hashfunct;
    vector<MapNode<T>*> map;
public:
    
    //implemented using the specified function objects.
    DMap(const S& notEquals, const F& hashfunct):notEquals(notEquals), hashfunct(hashfunct){}
    
    ~DMap();
    
    void reHash();
    bool contains(const T& value);
    void remove(int key);
    void remove(int key, const T& value);
    void insert(MapNode<T>* toInsert);
    void insert(int key, const T& value);
};

//Regular destructor
template<class T, class S, class F>
DMap<T,S,F>::~DMap(){
    for(int i=0; i<map.size(); ++i){
        MapNode<T>* node = map[i];
        while(node){
            MapNode<T>* nextNode = node->next;
            delete node;
            node = nextNode;
        }
    }
    map.clear();
    size = 0;
}

//Resizes vector to a prime vector and reinserts MapNode pairs by reHashing the key-values.
//Rather costly, operates in O(n^2), provided insertion is O(1).
template<class T, class S, class F>
void DMap<T,S,F>::reHash(){
    vector<MapNode<T>*> newMap;
    std::copy(map.begin(), map.end(), newMap.begin());
    map.clear();
    map.resize((newMap.size()*2)+1);
    for(int i=0; i<newMap.size(); ++i){
        MapNode<T>* node = map[i];
        while(node){
            insert(node);
        }
    }
}

//Loops through all buckets and chains to find specific value, otherwise returns false.
//O(n^2), because we are hashing by key and not value. If hashing by value, would not need to
//        find a specific bucket.
template<class T, class S, class F>
bool DMap<T,S,F>::contains(const T &value){
    for(int i=0; i<map.size(); ++i){
        MapNode<T>* node = map[i];
        while(node){
            if(!(notEquals(node->value,value)))
                return true;
            node = node->next;
        }
    }
    return false;
}

//Removes the first value in the chain that is given by hash_function(key).
//O(1), because we are implementing using a doubly-linked-list and are just doing a pop_front()
template<class T, class S, class F>
void DMap<T,S,F>::remove(int key){
    int hash_result = hashfunct(key,map.size());
    if(!map[hash_result])
        return;
    MapNode<T>* begin = map[hash_result];
    map[hash_result] = begin->next;
    map[hash_result]->prev = nullptr;
    delete begin;
    size--;
}

//Removes a particular value in the chain that is given by hash_function(key).
//O(n), because we need to traverse the doubly-linked list in order to find MapNode pair with the proper value to remove
template<class T, class S, class F>
void DMap<T,S,F>::remove(int key, const T& value){
    int hash_result = hashfunct(key,map.size());
    if(!map[hash_result])
        return;
    MapNode<T>* node = map[hash_result];
    while(node){
        MapNode<T>* nextNode = node->next;
        if(!(notEquals(node->value,value))){
            node->prev->next = node->next;
            node->next->prev = node->prev;
            delete node;
        }
        node = nextNode;
    }
    size--;
}

/*Checks to see if the DMap contains the value given before attempting to insert.
  Inserts a new MapNode pair as the front of the chain (essentially a push_front at the bucket)
 
  ReHashes the DMap is the Load Factor is greater than the recommended 0.75
  
  Operates in O(1) besides checking to see if the value is contained */

template<class T, class S, class F>
void DMap<T,S,F>::insert(MapNode<T>* toInsert){
    if(contains(toInsert->value))
        return;
    int hash_result = hashfunct(toInsert->key,map.size());
    MapNode<T>* start = map[hash_result];
    toInsert->next = start;
    start->prev = toInsert;
    map[hash_result] = toInsert;
    size++;
    if(size > map.size() * 0.75)
        reHash();
    return;
}

//Wrapper function
template<class T, class S, class F>
void DMap<T,S,F>::insert(int key, const T& value){
    MapNode<T>* toInsert = new MapNode<T>(key, value);
    insert(toInsert);
}

int main(int argc, const char * argv[]) {
    /*Hash h;
    notEquals<Data<double>> n;
    DMap<Data<double>, notEquals<Data<double>>, Hash> map(n,h);
    
    map.insert(1,Data<double>(2.0));
    map.insert(1,Data<double>(3.0));
    map.insert(5,Data<double>(5.4));*/
    return 0;
}
