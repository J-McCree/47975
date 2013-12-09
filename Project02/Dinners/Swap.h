/* 
 * File:   Allows the user to swap their dinner option to make the 
 * corresponding days they want to make the meal on, mainly useful
 * if they chose to randomize their dinners for that set of meals
 * 
 * Author: Joshua McCree
 *
 * Created on December 8, 2013, 11:47 AM
 */

#ifndef SWAP_H
#define	SWAP_H

//Include my libraries
#include "Dinners.h"

//Include system libraries
using namespace std;

//Begins template for swap
template <class T>
class Swap{
    //Declare and initialize needed variables
    private:
        short choice1, choice2;
        T pos1, pos2, temp;
public:
    //Function prototype
    void swapPos(T &, T &);
    
    //Default constructor
    Swap(){
        choice1 = 0;
        choice2 = 0;
    }
    
    //Mutator Function
    void setChoice(short a, short b){
        choice1 = a;
        choice2 = b;
    }
    
    //Accessors Function
    short getPos1(){
        return choice1;
    }
    
    short getPos2(){
        return choice2;
    }
};

//Begin function swapPos
template <class T>
void Swap<T>::swapPos(T &pos1, T &pos2){
    T temp;
    
    temp = pos1;
    pos1 = pos2;
    pos2 = temp;
}
#endif	/* SWAP_H */

