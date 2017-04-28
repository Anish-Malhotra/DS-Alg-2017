//
//  main.cpp
//  hw2
//
//  Created by Anish Malhotra on 2/25/17.
//  Copyright © 2017 CS2134. All rights reserved.
//

#include <iostream>
#include <ctime>
using namespace std;


//Timer class
class timer {
public:
    timer()
    :start(clock()), end(0)
    {};
    
    //Prints out elapsed time
    double elapsed(){
        end = clock();
        double diff = (double)end - start;
        return diff/CLOCKS_PER_SEC;
    }
    
    //Resets the timer
    void reset(){
        start = clock();
    }

private:
    long start,end;
};

/////////is_prime1
bool is_prime1(int n, int m=2){
    if(n == 2 || n==m)
        return true;
    if(is_prime1(m) && !(n%m))
        return false;
    return is_prime1(n, ++m);
}

int count_primes1(int n){
    int i = 0;
    for(int count = 2; count < n; ++count){
        if(is_prime1(count))
            ++i;
    }
    return i;
}


////////is_prime2
bool is_prime2(int n, int m=2){
    if(n == 2 || (n == m))
        return true;
    else if(!(n%m))
        return false;
    return is_prime2(n, ++m);
}

int count_primes2(int n){
    int i = 0;
    for(int count = 2; count < n; ++count){
        if(is_prime2(count))
            ++i;
    }
    return i;
}

////////is_prime3
bool is_prime3(int n, int m=2){
    if(n == 2 || (m*m)>n)
        return true;
    if(!(n%m))
        return false;
    return is_prime3(n, ++m);
}

int count_primes3(int n){
    int i = 0;
    for(int count = 2; count < n; ++count){
        if(is_prime3(count))
            ++i;
    }
    return i;
}

int main(int argc, const char * argv[]) {
    //101,110
    //72000,240000
    //2500000,12500000
    
    timer t;
    int i;
    /*i = count_primes1(2000);
    cout << t.elapsed() << endl;
    
    t.reset();
    i = count_primes1(110);
    cout << t.elapsed() << endl;*/
    
    t.reset();
    i = count_primes2(5000);
    cout << t.elapsed() << endl;
    
    /*t.reset();
    i = count_primes2(150000);
    cout << t.elapsed() << endl;*/
    
    t.reset();
    i = count_primes3(5000);
    cout << t.elapsed() << endl;
    
    /*t.reset();
    i = count_primes3(7300000);
    cout << t.elapsed() << endl;*/

    
    return 0;
}

///////////      WRITTEN PART       ///////////
///                                       ////
///                                      ////
/// Question 1 /////////////////////////////

/*  
    ___n___||___count_primes1___||___count_primes2___||___count_primes3____||_____
      100  ||      0.82175      ||      1.4e-05      ||       5e-06        ||
     2000  ||    more than 10s  ||     0.003528      ||      0.000132      ||
     5000  ||    more than 10s  ||     0.016256      ||      0.000541      ||
    10000  ||    more than 10s  ||     0.059678      ||      0.001048      ||
    20000  ||    more than 10s  ||     0.212773      ||      0.002732      ||
    50000  ||    more than 10s  ||      1.14194      ||      0.008856      ||
   100000  ||    more than 10s  ||      4.52824      ||      0.024572      ||
 
 */

///Question 2 /////////////////////////////
/*
 
 */

///Question 3 ////////////////////////////
/*
    a)  log(n^5)
        = 5log(n)
        Answer: O(log(n))
    
    b)  300n^2 + 20n + n^4
        Answer: O(n^2)
 
    c)  n * log(n + 12)
        Answer: O(n*log(n))
 
    d)  100n + 4n^2 + 12logn
        Answer: O(n^2)
 
    e)  logn + n/100
        Answer: O(n)
 
    f)  sqrt(6n) * (log(n+10))
        Answer: O(sqrt(n)*log(n))
 
    g)  n + (n-1) + (n-2) + ...
        = n(n+1)/2
        = (1/2) * (n^2 + n)
        Answer: O(n^2)
 */

///Question 4 ////////////////////////////
/*
    a)  for (i=0; i<n; i++)
            for (j=0; j<n; ++j)
                std::cout << "One more time!\n";
        Answer: O(n^2)
 
 b)     for (i=0; i<n; i++)
            for (j=0; j*j<n; ++j)
                std::cout << "Processing " << i << " and " << j << "\n";
        Answer: O(n^(3/2))
 
 c)     while (n >= 1) {
            std::cout << "Binary digit: " << n % 2 << "\n";
            n /= 2;
        }
        Answer: O(log(n))
 */