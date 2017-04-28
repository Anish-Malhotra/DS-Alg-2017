//
//  main.cpp
//  Data Structures Homework 4
//
//  Created by Anish Malhotra on 2/29/16.
//  Copyright © 2016 CS2134. All rights reserved.
//

#include <iostream>
#include <string>
#include <algorithm>
#include <functional>
#include <math.h>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

//class trainStopData as described in problem specifications from homework 3B
class trainStopData{
public:
    trainStopData(const string& stop_id, const string& stop_name, double stop_lat, double stop_lon)
    :
    stop_id(std::move(stop_id)), stop_name(std::move(stop_name)), stop_lat(stop_lat), stop_lon(stop_lon)
    {}
    
    string get_id() const{ return stop_id; }
    string get_stop_name() const{ return stop_name; }
    double get_latitude() const{ return stop_lat; }
    double get_longitude() const{ return stop_lon; }
    
private:
    double stop_lat, stop_lon;
    string stop_id, stop_name;
};

//--------------------------------------------- HAVERDIST ALGORITHM FROM TXT FILE --------------------

double degrad(double d) {
    return d * M_PI / 180;
}


// Code below is adapted from http://www.movable-type.co.uk/scripts/latlong.html
// FYI: That website has an applet that computes the haversine distance.
// It also has a link that will show the locations on a map,
// with a line between them.
double haverdist(double lat1, double longit1, double lat2, double longit2)
{
    double r = 6371;
    double dlat = degrad(lat2 - lat1);
    double dlongit = degrad(longit2 - longit1);
    double a = sin(dlat/2)*sin(dlat/2)+
    cos(degrad(lat1))*cos(degrad(lat2))*sin(dlongit/2)*sin(dlongit/2);
    double c = 2*atan2(sqrt(a),sqrt(1-a));
    return r*c;
}

//------------------------------------ BELOW USED IN HOMEWORK 3B -------------------------------------

//ADAPTED FROM http://www.cplusplus.com/forum/articles/9645/, string to double type conversion
double StringToDouble ( const string &Text ){
    stringstream ss(Text);
    double result;
    return ss >> result ? result : 0;
}

//------------------------------------- READS TRAIN STOP DATA INTO VECTOR -----------------------------

void readTrainStopData(vector<trainStopData>& trainData){
    string item;
    vector<string> items;
    vector<string> lines;
    ifstream ifs("MTA_train_stop_data.txt");
    string line;
    int count = 0;
    
    
    //READS ALL OF THE LINES AND PASSES THEM INTO STRINGSTREAMS (BESIDES FIRST LINE)
    while (getline(ifs, line))
    {
        stringstream ss(line);
        if(count==0){count++;} //checks if first line
        else{
            //LOOPS THROUGH LINE USING COMMA DELIMITER
            for(int j = 0; j <= 6; ++j){
                getline(ss, item, ',');
                //CHECKS IF IT IS THE 0TH, 2ND, 4TH OR 5TH SUBSTRING IN THE LINE (THE REQUIRED VALUES)
                if(j==0|j==2|j==4|j==5){
                    items.push_back(item);
                }
            }
            //CREATES A NEW trainStopData OBJECT AND PUSHES IT BACK TO THE VECTOR
            //OF TRAINSTOP OBJECTS
            trainStopData data(items[0], items[1], StringToDouble(items[2]), StringToDouble(items[3]));
            trainData.push_back(data);
            items.clear();
        }
    }

}

// ------------------------------------------ FUNCTORS FOR #1 ------------------------------

class isStopOnRoute{
public:
    isStopOnRoute(char route) : route(route) {}
    bool operator()(trainStopData stop) const{
        return *(stop.get_id().begin()) == route;
    }
    
private:
    char route;
};

class isSubwayStop{
public:
    isSubwayStop(const string& stopId) : stopId(std::move(stopId)) {}
    bool operator()(trainStopData stop) const{
        return stopId == stop.get_id();
    }
private:
    const string stopId;
};

class isSubwayStopNearX{
public:
    isSubwayStopNearX(double longitude, double latitude, double d)
    :
    longitude(longitude), latitude(latitude), d(d)
    {}
    
    bool operator()(trainStopData stop){
        return haverdist(stop.get_latitude(), stop.get_longitude(), latitude, longitude) <= d;
    }
private:
    double longitude, latitude, d;
};

class printTrainStopInfo{
public:
    printTrainStopInfo(){}
    void operator()(trainStopData stop) const{
        cout << stop.get_id() << ',' << stop.get_stop_name() << ',' << stop.get_latitude() << ',' << stop.get_longitude() << endl;
    }
};

//------------------------------------- PERFORM_IF TEMPLATED FUNCTION ----------------------

//DESIGNED PER HOMEWORK SPECS
template<class InputIterator, class UnaryPredicate, class OtherFunc>
int perform_if(InputIterator itrStart, InputIterator itrEnd, UnaryPredicate pred, OtherFunc op){
    int how_many = 0;
    for(InputIterator itr = itrStart; itr != itrEnd; ++itr){
        if ( pred( *itr ) )
        {
            op(*itr);
            how_many++;
        }
    }
    return how_many;
}

//-------------------------------------------  # 2 -----------------------------------------

//PROGRAMMED PER HOMEWORK SPECIFICATIONS
int GCD(int a, int b)
{
    if (b == 0)
        return a;
    else if( a < b )
        return GCD(b, a);
    else
        return GCD(b, a%b);
}

//-------------------------------------------- # 3 ----------------------------------------


//ACTUAL RECURSIVE DIVIDE AND CONQUER FUNCTION
template<class Object>
Object sumElements(typename vector<Object>::const_iterator lhs, typename vector<Object>::const_iterator rhs)
{
    if(lhs == rhs)
        return *lhs;
    size_t middle = (rhs - lhs)/2;
    auto midPoint = (lhs + middle);
    return (sumElements<Object>(lhs, midPoint) + sumElements<Object>(midPoint+1, rhs));
}

//DRIVER FUNCTION FOR THE RECURSIVE CALL WHICH SUMS A GIVEN VECTOR
template<class Object>
Object sumVector(const vector<Object>& a)
{
    if(a.size() == 1)
        return *(a.begin());
    return sumElements<Object>(a.begin(), (a.end()) -1);
}

//------------------------------------------ MAIN ------------------------------------------

int main(int argc, const char * argv[]) {
    
    vector<trainStopData> trainData;
    readTrainStopData(trainData);
    //LOADS ALL OF THE TRAIN STOP DATA INTO THE VECTOR
    
    cout << "Hello!" << endl;
    
    //THIS IS THE MENU WHICH UTILIZES THE FUNCTORS AND PERFORM_IF FUNCTION
    
    while(true){
        cout << "Please enter the letter of the operation you would like to perform" << endl << endl;
        cout << "a: Print out the information about all trains on a specific route" << endl;
        cout << "b: Print out the information about a specific train stop" << endl;
        cout << "c: Print out all the train stops within a certain distance" << endl;
        cout << "d: quit" << endl;
        char input;
        cin >> input;
        if(input == 'a'){
            char route;
            cout << "Please enter the route" << endl;
            cin >> route;
            isStopOnRoute r(route);
            printTrainStopInfo stop;
            perform_if(trainData.begin(), trainData.end(), r, stop);
            cout << "\n\n";
        }
        else if(input == 'b'){
            string stopName;
            cout << "Please enter the train stop" << endl;
            cin >> stopName;
            isSubwayStop name(stopName);
            printTrainStopInfo stop;
            perform_if(trainData.begin(), trainData.end(), name, stop);
            cout << "\n\n";
        }
        else if(input == 'c'){
            double lon, lat, d;
            cout << "Please enter a longitude followed by a space and then the latitude followed by a space and then the distance" << endl;
            cin >> lon >> lat >> d;
            isSubwayStopNearX near(lon, lat, d);
            printTrainStopInfo stop;
            perform_if(trainData.begin(), trainData.end(), near, stop);
            cout << "\n\n";
        }
        else if(input == 'd')
            break;
        else
            cout << "Not a valid input" << endl;
    }
    
    return 0;
}
