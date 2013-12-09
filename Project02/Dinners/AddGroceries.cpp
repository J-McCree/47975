/* 
 * File:   Add Separate Groceries to list, not included in dinner recipes
 * Author: Joshua McCree
 *
 * Created on December 8, 2013, 11:47 AM
 */

//Include system libraries
#include <iostream>
#include <ctime>
using namespace std;

#include "AddGroceries.h"

string AddGroceries::AddGroL(){
    char ch;
    string list;
    
    cout<<"Please enter the items you wish too add to the Grocery List"
            "Enter a * when you are done with the List: ";
    // Gets the name of the new dinner recipe
    cin.get(ch);
    while (ch != '*') {
        list += ch;
        cin.get(ch);
    }
    
    return list;
}
