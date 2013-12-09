/* 
 * File:   main.cpp
 * Author: Wiggles
 *
 * Created on October 24, 2013, 7:03 PM
 */


//Include system libraries
#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

//Include my structures
#include "Swap.h"

//Begin main body of program
int main() {
    
    srand(static_cast<unsigned int>(time(0)));
    fstream dataFile;
    string list;

    //Include variables and initialize variables
    short choice = 0;
    short swap1 = 0, swap2 = 0;
    int n = 1;
    bool check = false, safety = false;
    
    //Include and initialize needed objects
    Dinners mod;    
    Dinners *din;
    Dinners thisDin;
    
    AddGroceries gList;
    
    Swap<Dinners> swapDin;
    
    //Introduction to program
    cout<<"Welcome to my dinner program, to begin please choose from the "
            "following menu options: "<<endl<<endl;   
    
    do{
        choice = thisDin.menu();
        
        //Performs a check to make sure the user started a dinner object
        if(choice > 5 && safety == false){
            cout<<"You have not yet created a dinner list to view or modify"<<endl;
            cout<<"So it has auto chosen this option for you to keep the program from crashing."<<endl<<endl;
            choice = 5;
        }
        
        //Begin the switch that will perform the desired choice of
        //the user based on their menu selection
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
                //Pick a dinner to add to the dinner list
                cout<<"Please enter the ("<<n<<") name(s) of a known dinner(s) you wish to add"<<endl;
                cin.ignore();
                
                //Runs a for loop that will keep requesting dinners from the user
                //Until the dinner list is full.
                for(int i = 0; i < n; i++){
                    thisDin = din[i];
                    din[i] = thisDin.addDinList(thisDin, i, n);
                    if(din[i].getCorrect() != true)i=i-1;
                }       
                break;
                
            case 7:
                //Randomizes the dinners to fill the dinner list
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
                //Create a custom Grocery List
                list = gList.AddGroL();
                gList.setGroList(list);
                break; 
                
            case 10:
                //Switch the position of two of the dinners on the Dinner list
                cout<<"Please enter the first dinner choices you wish to switch the place of: "<<endl;
                cin>>swap1;
                cout<<"And the second: "<<endl;
                cin>>swap2;
                
                //Runs a check to make sure the user isn't trying to swap
                //out of bounds of the options
                if(swap1 > 0 && swap1 <= n && swap2 > 0 && swap2 <= n){
                    swap1 -= 1;
                    swap2 -= 1;

                    //Swaps and re-arranges the information to the correct dinners
                    //match up to the correct days.
                    swapDin.setChoice(swap1, swap2);
                    swapDin.swapPos(din[swap1], din[swap2]);
                    din[swap1].setDay(swap1 + 1);
                    din[swap2].setDay(swap2 + 1);
                }
                else{
                    cout<<"That is out of the bounds of your dinners.";
                    cout<<"Please make a selection from the "<<n<<" Dinner options."<<endl;
                }               
 
                break;
                
            case 11:
                //Exports the Dinner list, and grocery list to the rtf document
                dataFile.open("DinnerList.rtf", ios::out);
                for(int i = 0; i < n; i++){
                    dataFile <<"Dinner Day(";
                    dataFile <<din[i].getDay();
                    dataFile <<"): ";
                    dataFile <<din[i].getName();
                    dataFile <<"\n";
                    dataFile << din[i].getDef();
                    dataFile <<"\n";
                }
                
                //Exports the custom grocery list to the DinnerList
                dataFile << "Custom Grocery List: \n" << gList.getGroList();
                dataFile.close();
                
                cout<<"Thank you, you will find your grocery list in the project"<<endl;
                cout<<"folder. It will be the file named DinnerList"<<endl;
                
                break;
                
            //Runs the default case if the user enters anything that isn't an option
            //Ends the program
            default:
                cout<<"You chose to exit the program..."<<endl; 
                choice = 12;
                break; 
        }
    } while(choice != 12);
    
    //If the user created a dinner object, deletes the dinner object
    if(check == true) delete []din; 
    dataFile.close();
    return 0;
}
