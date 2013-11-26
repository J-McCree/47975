/* 
 * File:   main.cpp
 * Author: Dr. Mark E. Lehr
 * Created on November 25, 2013, 7:52 PM
 */

//Libraries
#include <iostream>
using namespace std;

//Our Libraries
#include "SimpleVector.h"

//Driver for simple vector
int main(int argc, char** argv) {
    //Declare
    const int SIZE=10;
    SimpleVector<int> s(SIZE);
    //Input values
    for(int i=0;i<s.size();i++){
        s[i]=i;
    }
    //Pop and push a few values
    cout<<"popping off "<<s.pop()<<endl;
    cout<<"popping off "<<s.pop()<<endl;
    s.push(50000);
    s.push(60000);
    //Output the result
    for(int i=0;i<s.size();i++){
        cout<<s[i]<<endl;
    }
    //Exit stage right
    return 0;
}

