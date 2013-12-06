//Include system libraries
#include <iostream>
#include <iomanip>
#include <fstream>
#include <ctime>
using namespace std;

//Include my structures
#include "Dinners.h"

void Dinners::instructions(fstream &file, Dinners d){
    //Opens the instruction file
    string temp;
    file.open("Instructions.rtf", ios :: in);
    
    //Reads in each line from the file then outputs to the user
    if(file){
        while(file){
            getline(file, temp);
            d.setMod(temp);
            cout<<d.getMod()<<endl;
        }
        file.clear();
        file.seekg(0L, ios :: beg);
        
        file.close();
    }
}
