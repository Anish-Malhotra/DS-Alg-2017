//
//  main.cpp
//  Exam 2 review
//
//  Created by Anish Malhotra on 2/27/17.
//  Copyright © 2017 CS2134. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <map>
using namespace std;

class Point{
public:
    Point(int x, int y):x(x),y(y){}
    int x;
    int y;
};

class functorPenis{
public:
    bool operator() (int x) {
        return (x>12);
    }
};

template<class T, class C>
class filter_iterator{
public:
    filter_iterator(vector<T>& data, C* compare)
    :
    data(data), compare(compare)
    {
        loc=0;
        pred = (*compare)(data[loc]);
    }
    
    filter_iterator(const filter_iterator& rhs)
    :
    data(rhs.data), compare(rhs.compare), pred(rhs.pred), loc(rhs.loc)
    {}
    
    T& operator* (){
        return data[loc];
    }
    
    void reInitPred(){
        pred = (*compare)(data[loc]);
    }
    
    filter_iterator operator++ (int){
        filter_iterator temp(*this);
        loc++;
        reInitPred();
        while(!pred && loc<data.size()){
            loc++;
            reInitPred();
        }
        return temp;
    }
    
    filter_iterator operator+ (int foo){
        filter_iterator temp(*this);
        temp.loc += foo;
        return temp;
    }
    
    filter_iterator operator+ (size_t foo){
        filter_iterator temp(*this);
        temp.loc += foo;
        return temp;
    }
    
    bool operator== (const filter_iterator& other){
        return (data.begin() == other.data.begin());
    }
    
    bool operator< (const filter_iterator& other){
        return (loc < other.loc);
    }
    
private:
    vector<T> data;
    C* compare;
    bool pred;
    int loc;
};
                   
double calculateDistance(const Point& p){
    return sqrt((double)pow(p.x, 2) + (double)pow(p.y,2));
}


//using insertion sort
void sortByDistance(vector<Point>& points){
    for(int i=0; i<points.size(); ++i){
        for(int j=i; j>0 && (calculateDistance(points[j-1]) > calculateDistance(points[j])); j--){
            int x = points[j].x;
            int y = points[j].y;
            points[j].x = points[j-1].x;
            points[j].y = points[j-1].y;
            points[j-1].x = x;
            points[j-1].y = y;
        }
    }
}

vector<int> getSubwayTimes(const multimap<char, int>& lineTimes, char line){
    vector<int> subwayTimes;
    multimap<char,int>::const_iterator itr;
    for(itr = lineTimes.begin(); itr!=lineTimes.end(); ++itr){
        if(itr->first == line)
            break;
    }
    for(; itr!=lineTimes.end(); ++itr){
        if(itr->first != line)
            break;
        subwayTimes.push_back(itr->second);
    }
    return subwayTimes;
}



int main(int argc, const char * argv[]) {
    Point p1(0,0);
    Point p2(1,1);
    Point p3(2,3);
    Point p4(3,3);
    Point p5(-5,-8);
    vector<Point> points;
    points.push_back(p3);
    points.push_back(p1);
    points.push_back(p2);
    points.push_back(p4);
    points.push_back(p5);
    
    for(const Point& p : points){
        cout << p.x << ", " << p.y << endl;
    }
    cout << "---------------------------" << endl;
    sortByDistance(points);
    for(const Point& p : points){
        cout << p.x << ", " << p.y << endl;
    }
    cout << "---------------------------" << endl;
    
    vector<int> v;
    v.push_back(4);
    v.push_back(12);
    v.push_back(14);
    v.push_back(6);
    v.push_back(3);
    v.push_back(7);
    v.push_back(8);
    v.push_back(2);
    
    for(int i=0; i<v.size(); ++i){
        cout << v[i] << endl;
    }
    cout << "---------------------------" << endl;

    
    functorPenis* c;
    filter_iterator<int, functorPenis> filt(v, c);
    filter_iterator<int, functorPenis> filt2(filt);
    filt2 = filt2 + v.size();
    while(filt < filt2){
        cout << *filt << endl;
        filt++;
    }
    
    cout << "---------------------------" << endl;

    multimap<char, int> D;
    D.insert(std::make_pair('c',2));
    D.insert(std::make_pair('c',5));
    D.insert(std::make_pair('c',3));
    D.insert(std::make_pair('c',8));
    D.insert(std::make_pair('c',14));
    D.insert(std::make_pair('c',7));
    D.insert(std::make_pair('a',2));
    D.insert(std::make_pair('a',5));
    D.insert(std::make_pair('a',7));
    
    map<char,int> E;
    E['c'] = 5;
    vector<int> times = getSubwayTimes(D, 'c');
    for(int i : times)
        cout << i << endl;
    return 0;
}
