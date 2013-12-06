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
short menu();

void kwnDinners(fstream &);

void addDinner(fstream &, Dinners);
void newDinner(string);
void rmvDinner(fstream &);
char modify();

void dlDinList(fstream &);
void randomDin(Dinners *, int);

Dinners addDinList(Dinners, int, int);

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
        choice = menu();
        
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
                kwnDinners(dataFile);
                break;
            case 3:
                //Add dinner recipe
                addDinner(dataFile, thisDin);
                break;
            case 4:
                //Remove dinner recipe
                rmvDinner(dataFile);
                break;
            case 5:
                //Deletes the current list of dinners
                dlDinList(dataFile);
                
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
                    din[i] = addDinList(thisDin, i, n);
                    if(din[i].getCorrect() != true)i=i-1;
                }       
                break;
            case 7:
                randomDin(din, n);
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

//Begins the menu function
short menu(){
    //Declare and initialize variables
    fstream file;
    short c = 0;
    string words;

    //Opens the menu file
    file.open("Menu.txt", ios :: in);
      
    //Reads in each line from the file then outputs to the user
    if(file){
        while(file){
            getline(file, words);
            cout<<words<<endl;
        }
        file.clear();
        file.seekg(0L, ios :: beg);
    }
    
    file.close();
    //Gets the desired option from the user
    cout<<"Choice: ";
    cin>>c;
    
    //Returns the users option back to the main body
    return c;
}

void kwnDinners(fstream &file){
    char letter;
    
    file.open("DinnerOptions.rtf", ios :: in);
    
    cout<<"*******************LIST OF DINNERS***********************"<<endl;   
    
    //Stores the file input up to the insert line.
    if(file){
        file.get(letter);
        cout<<letter;
        while(letter != '*'){
            file.get(letter);
            cout<<letter;
        }
    }
    else cout<<"That file doesn't exist."<<endl;
    file.close();
}

void addDinner(fstream &file, Dinners d){
    char x, ch;
    char pos;
    string tempBeg = "", tempEnd = "", tempAdd = "";
    
    do{
        pos = modify();
    }while(pos != '!' && pos != '@' && pos !='#' && pos != '$');
    
    file.open("DinnerOptions.rtf", ios::in);
    
    //Stores the file input up to the insert line.
    file.get(x);
    tempBeg += x;
    while(x != pos){
        file.get(x);
        tempBeg += x;
    }
    d.setBeg(tempBeg);

    
    //Stores the file input after the insert line.
    file.get(x);
    tempEnd += x;
    while(x != '*')
    {
        file.get(x);
        tempEnd += x;
    }
    d.setEnd(tempEnd);
    
    //Gets the input from the user that is going to be added to the file.
    cout<<"Type the name of your new dinner recipe followed by a *"<<endl;
    cout<<"and once you are done, press [ENTER] to continue."<<endl;
    
    // Gets the name of the new dinner recipe
    cin.get(ch);
    while (ch != '*') {
        tempAdd += ch;
        cin.get(ch);
    }
    d.setMod(tempAdd);
    newDinner(d.getMod());
    
    tempBeg = d.getBeg() + d.getMod() + d.getEnd();
    d.setBeg(tempBeg);
    tempBeg.clear();
    
    file.close();
    
    //Rewrites the data file with the modified changes
    file.open("DinnerOptions.rtf", ios::out);
    file << d.getBeg();
    file.close();
}

//Runs a function to create the grocery list for the new dinner recipe
void newDinner(string meal){
    //Declare and initialize needed variables for this function
    fstream f;
    string temp = "";
    short x = meal.size()-1;
    char ch;
    char dish[x];

    //Removes the enter key stroke from the name of the meal.
    for(int i = 0; i < x; i++){
        dish[i] = meal[i+1];
    }
    temp = dish;
    temp = "Z" + temp + ".rtf";
    meal = "";

    f.open(temp.c_str(), ios::out);
    cout<<"\nPlease enter the list of items you will need to make this dish."<<endl;
    cout<<"You may finish your input at anytime by using the * key and pressing [ENTER]"<<endl;
    
    cin.get(ch);
    while (ch != '*') {
        meal += ch;
        cin.get(ch);
    }
    meal += ch;
    
    f<<meal;  
    f.close();
}
void rmvDinner(fstream &file){
    char x;
    char pos;
    string beg;
    string end;
    string input;
    
    do{
        pos = modify();
    }while(pos != '!' && pos != '@' && pos !='#' && pos != '$');
    
    file.open("DinnerOptions.rtf", ios::in);
    
    //Stores the file input up to the insert line.
    file.get(x);
    beg += x;
    while(x != pos){
        file.get(x);
        beg += x;
    }
 
    //Deletes the line after the search parameters
    getline(file, input);
    getline(file, input);
    
    //Stores the file input after the insert line.
    file.get(x);
    end += x;
    while(x != '*')
    {
        file.get(x);
        end += x;
    }  
    file.close();
    
    beg = beg + "\n" + end;
    
    file.open("DinnerOptions.rtf", ios::out);
    file << beg;
    file.close();
}

//Begins the modify function
char modify(){
    //Declare variables
    char mod;
 
    //Requests designated input from user to determine which catagory to alter
    cout<<"Would you like to modify a recipe under: "<<endl;
    cout<<"(!) Chicken"<<endl;
    cout<<"(@) Beef"<<endl;
    cout<<"(#) Pork/Ham"<<endl;
    cout<<"($) Sausage"<<endl;
    cout<<"Please enter the corresponding symbol: "<<endl;
    cin>>mod;
    
    return mod;
}

void dlDinList(fstream &file){
    file.open("DinnerList.rtf", ios::out);
    file << " ";
    file.close();
}

Dinners addDinList(Dinners d, int pos, int numDin){
    fstream file; 
    string temp;
    char x;
    
    temp.clear();
    d.setName("");
        
    cout<<"Dinner choice ("<<pos+1<<"): ";
    getline(cin, temp);
    d.setName(temp);

    d.setCorrect(false);
    temp = "z" + d.getName() + ".rtf"; 
    file.open(temp.c_str(), ios::in);
    temp.clear();
    
    if(file){
        cout<<"Thank you, it's grocery list has been saved."<<endl<<endl;
        d.setCorrect(true);

        file.get(x);
        while(x != '*')
        {
            temp += x;
            file.get(x);
        }
        d.setDef(temp);
    }
    else{
        cout<<"That isn't a valid dinner option. Please try naming a known dinner"<<endl;
    }
    file.close();
    
    return d;
}

void randomDin(Dinners *d, int num){
    int randDin;
    fstream file;
    string temp;
    char x;
    bool first = true;
    bool on[19];
    
    if(first == true){
        for(int i = 0; i < 20; i++){
        on[i] = true;
        }
        first = false;
    }
    
    
    for(int i = 0; i < num; ){
        randDin = rand()%20;
        
        if(randDin == 1 && on[0] == true){
            d[i].setName("Chicken Rolls");
            on[0] = false;
        }
        else if(randDin == 2 && on[1] == true){
            d[i].setName("Enchiladas");
            on[1] = false;
        }
        else if(randDin == 3 && on[2] == true){
            d[i].setName("Baked Potatoes");
            on[2] = false;
        }
        else if(randDin == 4 && on[3] == true){
            d[i].setName("BBQ Pulled Pork");
            on[3] = false;
        }
        else if(randDin == 5 && on[4] == true){
            d[i].setName("Beef and Broccoli");
            on[4] = false;
        }
        else if(randDin == 6 && on[5] == true){
            d[i].setName("Burritos");
            on[5] = false;
        }
        else if(randDin == 7 && on[6] == true){
            d[i].setName("Cordon Bleu");
            on[6] = false;
        }
        else if(randDin == 8 && on[7] == true){
            d[i].setName("Curry");
            on[7] = false;
        }
        else if(randDin == 9 && on[8] == true){
            d[i].setName("Ham Fried Rice");
            on[8] = false;
        }
        else if(randDin == 10 && on[9] == true){
            d[i].setName("Hamburgers");
            on[9] = false;
        }
        else if(randDin == 11 && on[10] == true){
            d[i].setName("Lasagna");
            on[10] = false;
        }
        else if(randDin == 12 && on[11] == true){
            d[i].setName("Navaho Tacos");
            on[11] = false;
        }
        else if(randDin == 13 && on[12] == true){
            d[i].setName("Pork Chops");
            on[12] = false;
        }
        else if(randDin == 14 && on[13] == true){
            d[i].setName("Pot Pie");
            on[13] = false;
        }
        else if(randDin == 15 && on[14] == true){
            d[i].setName("Potato Soup");
            on[14] = false;
        }
        else if(randDin == 16 && on[15] == true){
            d[i].setName("Roast");
            on[15] = false;
        }
        else if(randDin == 17 && on[16] == true){
            d[i].setName("Spaghetti");
            on[16] = false;
        }
        else if(randDin == 18 && on[17] == true){
            d[i].setName("Stew");
            on[17] = false;
        }
        else if(randDin == 19 && on[18] == true){
            d[i].setName("Stir Fry");
            on[18] = false;
        }
        else if(randDin == 20 && on[19] == true){
            d[i].setName("Stroganoff");
            on[19] = false;
        }
        else {
            continue;
        }
        
        temp = "z" + d[i].getName() + ".rtf"; 
        file.open(temp.c_str(), ios::in);

        temp.clear();
        if(file){
            cout<<"Thank you, it's grocery list has been saved."<<endl<<endl;

            file.get(x);
            while(x != '*')
            {
                temp += x;
                file.get(x);
            }
            d[i].setDef(temp);
        }
        else cout<<"Didn't find that file:  "<<temp<<endl;
        
        file.close();
        i++;
    }
}
