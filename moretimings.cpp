//
//  main.cpp
//  Data Structures Homework #1
//
//  Created by Anish Malhotra on 2/2/16.
//  Copyright © 2016 CS2134. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
using namespace std;

class timer {
public:
    timer() : start(clock()) {}
    double elapsed() { return ( clock() - start ) / CLOCKS_PER_SEC; }
    void reset() { start = clock(); }
private:
    double start;
};

/**
 * Cubic maximum contiguous subsequence sum algorithm.
 */
int maxSubSum1( const vector<int> & a )
{
    int maxSum = 0;
    
    for( int i = 0; i < a.size( ); ++i )
        for( int j = i; j < a.size( ); ++j )
        {
            int thisSum = 0;
            
            for( int k = i; k <= j; ++k )
                thisSum += a[ k ];
            
            if( thisSum > maxSum )
                maxSum   = thisSum;
        }
    
    return maxSum;
}

/**
 * Quadratic maximum contiguous subsequence sum algorithm.
 */
int maxSubSum2( const vector<int> & a )
{
    int maxSum = 0;
    
    for( int i = 0; i < a.size( ); ++i )
    {
        int thisSum = 0;
        for( int j = i; j < a.size( ); ++j )
        {
            thisSum += a[ j ];
            
            if( thisSum > maxSum )
                maxSum = thisSum;
        }
    }
    
    return maxSum;
}


/**
 * Linear-time maximum contiguous subsequence sum algorithm.
 */
int maxSubSum4( const vector<int> & a )
{
    int maxSum = 0, thisSum = 0;
    
    for( int j = 0; j < a.size( ); ++j )
    {
        thisSum += a[ j ];
        
        if( thisSum > maxSum )
            maxSum = thisSum;
        else if( thisSum < 0 )
            thisSum = 0;
    }
    
    return maxSum;
}

int main(int argc, const char * argv[]) {
    cout.precision(numeric_limits<double>::digits10 + 1);
    cout << CLOCKS_PER_SEC  << " clocks per second " << endl << endl;
    
    timer t;
    double nuClicks;
    // other code to fill in the vector with n items, etc.
    vector<int> nums;
    for(int i=0; i<128; ++i){
        int x = ((rand() % 2001) - 1000);
        nums.push_back(x);
    }
    t.reset();
    maxSubSum1(nums);
    nuClicks = t.elapsed();
    cout << nums.size() << " elements, cubic algorithm runtime: " << nuClicks << endl;
    
    t.reset();
    maxSubSum2(nums);
    nuClicks = t.elapsed();
    cout << nums.size() << " elements, quadratic algorithm runtime: " << nuClicks << endl;
    
    t.reset();
    maxSubSum4(nums);
    nuClicks = t.elapsed();
    cout << nums.size() << " elements, linear algorithm runtime: " << nuClicks << endl;
    
    nums.clear();
    for(int i=0; i<256; ++i){
        int x = ((rand() % 2001) - 1000);
        nums.push_back(x);
    }
    
    cout << "--------------------------------------" << endl;
    
    t.reset();
    maxSubSum1(nums);
    nuClicks = t.elapsed();
    cout << nums.size() << " elements, cubic algorithm runtime: " << nuClicks << endl;
    
    t.reset();
    maxSubSum2(nums);
    nuClicks = t.elapsed();
    cout << nums.size() << " elements, quadratic algorithm runtime: " << nuClicks << endl;
    
    t.reset();
    maxSubSum4(nums);
    nuClicks = t.elapsed();
    cout << nums.size() << " elements, linear algorithm runtime: " << nuClicks << endl;
    
    nums.clear();
    
    for(int i=0; i<512; ++i){
        int x = ((rand() % 2001) - 1000);
        nums.push_back(x);
    }
    
    cout << "--------------------------------------" << endl;
    
    t.reset();
    maxSubSum1(nums);
    nuClicks = t.elapsed();
    cout << nums.size() << " elements, cubic algorithm runtime: " << nuClicks << endl;
    
    t.reset();
    maxSubSum2(nums);
    nuClicks = t.elapsed();
    cout << nums.size() << " elements, quadratic algorithm runtime: " << nuClicks << endl;
    
    t.reset();
    maxSubSum4(nums);
    nuClicks = t.elapsed();
    cout << nums.size() << " elements, linear algorithm runtime: " << nuClicks << endl;
    
    nums.clear();

    for(int i=0; i<1024; ++i){
        int x = ((rand() % 2001) - 1000);
        nums.push_back(x);
    }
    
    cout << "--------------------------------------" << endl;
    
    t.reset();
    maxSubSum1(nums);
    nuClicks = t.elapsed();
    cout << nums.size() << " elements, cubic algorithm runtime: " << nuClicks << endl;
    
    t.reset();
    maxSubSum2(nums);
    nuClicks = t.elapsed();
    cout << nums.size() << " elements, quadratic algorithm runtime: " << nuClicks << endl;
    
    t.reset();
    maxSubSum4(nums);
    nuClicks = t.elapsed();
    cout << nums.size() << " elements, linear algorithm runtime: " << nuClicks << endl;
    
    nums.clear();
    
    for(int i=0; i<2048; ++i){
        int x = ((rand() % 2001) - 1000);
        nums.push_back(x);
    }
    
    cout << "--------------------------------------" << endl;
    
    t.reset();
    maxSubSum1(nums);
    nuClicks = t.elapsed();
    cout << nums.size() << " elements, cubic algorithm runtime: " << nuClicks << endl;
    
    t.reset();
    maxSubSum2(nums);
    nuClicks = t.elapsed();
    cout << nums.size() << " elements, quadratic algorithm runtime: " << nuClicks << endl;
    
    t.reset();
    maxSubSum4(nums);
    nuClicks = t.elapsed();
    cout << nums.size() << " elements, linear algorithm runtime: " << nuClicks << endl;
    
    nums.clear();
    
    for(int i=0; i<4096; ++i){
        int x = ((rand() % 2001) - 1000);
        nums.push_back(x);
    }
    
    cout << "--------------------------------------" << endl;
    
    t.reset();
    maxSubSum1(nums);
    nuClicks = t.elapsed();
    cout << nums.size() << " elements, cubic algorithm runtime: " << nuClicks << endl;
    
    t.reset();
    maxSubSum2(nums);
    nuClicks = t.elapsed();
    cout << nums.size() << " elements, quadratic algorithm runtime: " << nuClicks << endl;
    
    t.reset();
    maxSubSum4(nums);
    nuClicks = t.elapsed();
    cout << nums.size() << " elements, linear algorithm runtime: " << nuClicks << endl;
    
    nums.clear();
    
    
    
    
    cout << "\n-----------------NUMBER #2---------------------" << endl;

    cout << "\n---------------2a------------------" << endl;
    t.reset();
    int sum = 0;
    for (int i = 0; i < 256; i++)
        ++sum;
    nuClicks = t.elapsed();
    
    cout << "256 elements, 2a algorithm runtime: " << nuClicks << endl;
    
    t.reset();
    sum = 0;
    for (int i = 0; i < 512; i++)
        ++sum;
    nuClicks = t.elapsed();
    
    cout << "512 elements, 2a algorithm runtime: " << nuClicks << endl;
    
    t.reset();
    sum = 0;
    for (int i = 0; i < 1024; i++)
        ++sum;
    nuClicks = t.elapsed();
    
    cout << "1024 elements, 2a algorithm runtime: " << nuClicks << endl;
    
    t.reset();
    sum = 0;
    for (int i = 0; i < 2048; i++)
        ++sum;
    nuClicks = t.elapsed();
    
    cout << "2048 elements, 2a algorithm runtime: " << nuClicks << endl;
    
    t.reset();
    sum = 0;
    for (int i = 0; i < 4096; i++)
        ++sum;
    nuClicks = t.elapsed();
    
    cout << "4096 elements, 2a algorithm runtime: " << nuClicks << endl;

    cout << "\n---------------2b------------------" << endl;

    t.reset();
    sum = 0;
    for(int i = 0; i < 256; i++)
        for(int j = 0; j < 256; ++j)
            ++sum;
    nuClicks = t.elapsed();
    
    cout << "256 elements, 2b algorithm runtime: " << nuClicks << endl;
    
    t.reset();
    sum = 0;
    for(int i = 0; i < 512; i++)
        for(int j = 0; j < 512; ++j)
            ++sum;
    nuClicks = t.elapsed();
    
    cout << "512 elements, 2b algorithm runtime: " << nuClicks << endl;
    
    t.reset();
    sum = 0;
    for(int i = 0; i < 1024; i++)
        for(int j = 0; j < 1024; ++j)
            ++sum;
    nuClicks = t.elapsed();
    
    cout << "1024 elements, 2b algorithm runtime: " << nuClicks << endl;
    
    t.reset();
    sum = 0;
    for(int i = 0; i < 2048; i++)
        for(int j = 0; j < 2048; ++j)
            ++sum;
    nuClicks = t.elapsed();
    
    cout << "2048 elements, 2b algorithm runtime: " << nuClicks << endl;
    
    t.reset();
    sum = 0;
    for(int i = 0; i < 4096; i++)
        for(int j = 0; j < 4096; ++j)
            ++sum;
    nuClicks = t.elapsed();
    
    cout << "4096 elements, 2b algorithm runtime: " << nuClicks << endl;
    
    cout << "\n---------------2c------------------" << endl;
    
    t.reset();
    sum = 0;
    for(int i = 0; i < 256; i++)
        for(int j = 0; j < i; ++j)
            ++sum;
    nuClicks = t.elapsed();
    
    cout << "256 elements, 2c algorithm runtime: " << nuClicks << endl;
    
    t.reset();
    sum = 0;
    for(int i = 0; i < 512; i++)
        for(int j = 0; j < i; ++j)
            ++sum;
    nuClicks = t.elapsed();
    
    cout << "512 elements, 2c algorithm runtime: " << nuClicks << endl;
    
    t.reset();
    sum = 0;
    for(int i = 0; i < 1024; i++)
        for(int j = 0; j < i; ++j)
            ++sum;
    nuClicks = t.elapsed();
    
    cout << "1024 elements, 2c algorithm runtime: " << nuClicks << endl;
    
    t.reset();
    sum = 0;
    for(int i = 0; i < 2048; i++)
        for(int j = 0; j < i; ++j)
            ++sum;
    nuClicks = t.elapsed();
    
    cout << "2048 elements, 2c algorithm runtime: " << nuClicks << endl;
    
    t.reset();
    sum = 0;
    for(int i = 0; i < 4096; i++)
        for(int j = 0; j < i; ++j)
            ++sum;
    nuClicks = t.elapsed();
    
    cout << "4096 elements, 2c algorithm runtime: " << nuClicks << endl;
    
    cout << "\n--------------2d-------------------" << endl;
    
    t.reset();
    sum = 0;
    for(int i = 0; i < 256; i++)
        for(int j = 0; j < 256; ++j)
            for(int k = 0; k < 256; ++k)
                ++sum;
    nuClicks = t.elapsed();
    
    cout << "256 elements, 2d algorithm runtime: " << nuClicks << endl;
    
    t.reset();
    sum = 0;
    for(int i = 0; i < 512; i++)
        for(int j = 0; j < 512; ++j)
            for(int k = 0; k < 512; ++k)
                ++sum;
    nuClicks = t.elapsed();
    
    cout << "512 elements, 2d algorithm runtime: " << nuClicks << endl;
    
    t.reset();
    sum = 0;
    for(int i = 0; i < 1024; i++)
        for(int j = 0; j < 1024; ++j)
            for(int k = 0; k < 1024; ++k)
                ++sum;
    nuClicks = t.elapsed();
    
    cout << "1024 elements, 2d algorithm runtime: " << nuClicks << endl;
    
    t.reset();
    sum = 0;
    for(int i = 0; i < 2048; i++)
        for(int j = 0; j < 2048; ++j)
            for(int k = 0; k < 2048; ++k)
                ++sum;
    nuClicks = t.elapsed();
    
    cout << "2048 elements, 2d algorithm runtime: " << nuClicks << endl;
    
    t.reset();
    sum = 0;
    for(int i = 0; i < 4096; i++)
        for(int j = 0; j < 4096; ++j)
            for(int k = 0; k < 4096; ++k)
                ++sum;
    nuClicks = t.elapsed();
    
    cout << "4096 elements, 2d algorithm runtime: " << nuClicks << endl;
    
    return 0;
}
