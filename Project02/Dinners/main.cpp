/* 
 * File:   main.cpp
 * Author: Wiggles
 *
 * Created on October 24, 2013, 7:03 PM
 */


//Include system libraries
#include <iostream>
#include <iomanip>
#include <fstream>
#include <ctime>
using namespace std;

//Include my structures
#include "Dinners.h"

//Include function prototypes


//Begin main body of program
int main() {
    srand(static_cast<unsigned int>(time(0)));
    fstream dataFile;

    //Include variables and initialize variables
    short choice = 0;
    int n = 1;
    bool check = false, safety = false;
    
    Dinners mod;    
    Dinners *din;
    Dinners thisDin;
    
    //Introduction to program
    cout<<"Welcome to my dinner program, to begin please choose from the "
            "following menu options: "<<endl<<endl;   
    
    do{
        choice = thisDin.menu();
        
        if(choice > 5 && safety == false){
            cout<<"You have not yet created a dinner list to view or modify"<<endl;
            cout<<"So it has auto chosen this option for you to keep the program from crashing."<<endl<<endl;
            choice = 5;
        }
        
        switch(choice){
            case 1:
                //View instructions
                thisDin.instructions(dataFile, thisDin);
                break;
            case 2:
                //View dinners
                thisDin.kwnDinners(dataFile);
                break;
            case 3:
                //Add dinner recipe
                thisDin.addDinner(dataFile, thisDin);
                break;
            case 4:
                //Remove dinner recipe
                thisDin.rmvDinner(dataFile);
                break;
            case 5:
                //Deletes the current list of dinners
                thisDin.dlDinList(dataFile);
                
                //Validates that the array structure will need to be deleted
                check = true;
                
                cout<<"How many dinners would you like?"<<endl;
                cin>>n;
                
                //Creates a dynamic array of structures that will hold the new dinners
                din = new Dinners[n];
                for(int i = 0; i < n; i++){
                    din[i].setDay(i+1);
                }
                safety = true;
                break;
            case 6:
                cout<<"Please enter the ("<<n<<") name(s) of a known dinner(s) you wish to add"<<endl;
                cin.ignore();
                
                for(int i = 0; i < n; i++){
                    thisDin = din[i];
                    din[i] = thisDin.addDinList(thisDin, i, n);
                    if(din[i].getCorrect() != true)i=i-1;
                }       
                break;
            case 7:
                thisDin.randomDin(din, n);
                break;
            case 8:
                //View current dinner list
                for(int i = 0; i < n; i++){
                    cout<<"Dinner ("<<din[i].getDay()<<"): "<<din[i].getName()<<endl;
                    cout<<din[i].getDef()<<endl;
                }
                break;
            case 9:
                dataFile.open("DinnerList.rtf", ios::out);
                for(int i = 0; i < n; i++){
                    dataFile <<"Dinner (";
                    dataFile <<din[i].getDay();
                    dataFile <<"): ";
                    dataFile <<din[i].getName();
                    dataFile <<"\n";
                    dataFile << din[i].getDef();
                    dataFile <<"\n";
                }
                dataFile.close();
                cout<<"Thank you, you will find your grocery list in the project"<<endl;
                cout<<"folder. It will be the file named DinnerList"<<endl;
                break;
            default:
                cout<<"You chose to exit the program..."<<endl; 
                choice = 10;
                break; 
        }
    } while(choice != 10);
    
    if(check == true) delete []din; 
    dataFile.close();
    return 0;
}
