//
//  main.cpp
//  Homework 3
//
//  Created by Anish Malhotra on 3/26/17.
//  Copyright © 2017 CS2134. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

//Flight class, everything is public as specified
class Flight{
public:
    Flight(const string& source, const string& destination, int flightNo, int flyTime):
    source(source), destination(destination), flightNo(flightNo), flyTime(flyTime)
    {}
    
    string source, destination;
    int flightNo, flyTime;
};

//functor #1, compares a string and a Flight source
class equalByDeparture{
public:
    bool operator() (const string& value, const Flight& foo){
        return value == foo.source;
    }
};

//functor #2, compares a string and Flight destination
class equalByDestination{
public:
    bool operator() (const string& value, const Flight& foo){
        return value == foo.destination;
    }
};

//Finds all occurences of a value of type H specified by the predicate in the data set.
template<class T, class S, class H>
vector<T> find(vector<T>& data, S comparator, H& value){
    vector<T> search_result;
    typename vector<T>::iterator itr = data.begin();
    
    //Loop through the data
    for(; itr!=data.end(); ++itr){
        if(comparator(value, *itr)) //Use comparator on value, and current Flight in data
            search_result.push_back(*itr);
    }
    return search_result;
}

/*Prints out the largest outdegree by comparing sizes of subvectors determined by the result of find
  on each unique city */
void printMaxOutdegree(vector<Flight>& data){
    string destination;
    long max_outdegree = 0;
    
    equalByDestination comparator;
    vector<Flight> data_sample;
    
    //Loop through data
    for(vector<Flight>::iterator itr = data.begin(); itr != data.end(); ++itr){
        if(destination != itr->destination){
            //Saves a rebuild of the subvector if the current city is already the city with the largest outdegree
            
            data_sample = find(data, comparator, itr->destination); //Build the subvector
            if(data_sample.size() != max_outdegree){
                if(data_sample.size() > max_outdegree){
                    max_outdegree = data_sample.size();
                    destination = itr->destination;
                }
            }
        }
    }
    cout << destination << ": " << max_outdegree << endl;
}

//Opens a filestream at the specified path and reads the datafile into a vector of Flights
vector<Flight> readData(const string& path){
    vector<Flight> data;
    ifstream ifs;
    ifs.open(path.c_str());
    if(!ifs){
        cerr << "Couldn't open filepath";
        return data;
    }
    int flightNo, flyTime;
    string source, destination;
    while(ifs >> flightNo >> source >> destination >> flyTime){
        Flight foo(source, destination, flightNo, flyTime);
        data.push_back(foo);
    }
    ifs.close();
    return data;
}

int main(int argc, const char * argv[]) {
    vector<Flight> data = readData("HW3Data.txt");
    printMaxOutdegree(data);
    return 0;
}
