/* 
 * File:   Add Separate Groceries to list, not included in dinner recipes
 * Author: Joshua McCree
 *
 * Created on December 8, 2013, 11:47 AM
 */

#ifndef ADDGROCERIES_H
#define	ADDGROCERIES_H

#include <iostream>

using namespace std;

class AddGroceries{

private:
    string GroList;
    
public:
    
    string beg, mod, end;
    string AddGroL();
    
    //Default constructor
    AddGroceries(){
        GroList = "";
        beg = "";
        mod = "";
        end = "";
    }
    
    //Constructor
    AddGroceries(string g){
        GroList = g;
    }
    
    //Mutator Function
    void setGroList(string g){
        GroList = g;
    }
    
    //Accessors function
    string getGroList(){
        return GroList;
    }
    
};


#endif	/* ADDGROCERIES_H */

