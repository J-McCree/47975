/* 
 * File:   Starts the dinner class that the DinnerApp will use to 
 * run all of its functions from, and inherits from the AddGrocery
 * file, because it adds grocery lists for each dinner the user selects
 * 
 * Author: Joshua McCree
 *
 * Created on December 8, 2013, 11:47 AM
 */

#ifndef DINNERS_H
#define	DINNERS_H
#include "AddGroceries.h"

using namespace std;

class Dinners : AddGroceries
{
private:    
    string name;
    string def;
    
    bool correct;
    short days;        
public:
    short menu();
 
    void instructions(fstream &, Dinners);
    void kwnDinners(fstream &);

    void addDinner(fstream &, Dinners);
    void newDinner(string);
    void rmvDinner(fstream &);
    char modify();

    void dlDinList(fstream &);
    void randomDin(Dinners *, int);

    Dinners addDinList(Dinners, int, int);
    
    //Constructors
    Dinners(){
        name = "";
        def = "";
        correct = false;
        days = 0;
    }
    
    //Mutator Functions
    void setBeg(string b){
        beg = b;
    }
    void setMod(string m){
        mod = m;
    }
    void setEnd(string e){
        end = e;
    }
    void setName(string n){
        name = n;
    }
    void setDef(string d){
        def = d;
    }
    void setCorrect(bool c){
        correct = c;
    }
    void setDay(short d){
        days = d;
    }
    
    //Accessors Functions
    string getBeg(){
        return beg;
    }
    
    string getMod(){
        return mod;
    }
    
    string getEnd(){
        return end;
    }
    
    string getName(){
        return name;
    }
    
    string getDef(){
        return def;
    }
    
    bool getCorrect(){
        return correct;
    }
    short getDay(){
        return days;
    }
};

#endif	/* DINNERS_H */

