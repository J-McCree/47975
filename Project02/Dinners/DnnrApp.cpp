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

//Begins the menu function
short Dinners::menu(){
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

void Dinners::kwnDinners(fstream &file){
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

void Dinners::addDinner(fstream &file, Dinners d){
    char x, ch;
    char pos;
    string tempBeg = "", tempEnd = "", tempAdd = "";
    
    do{
        pos = d.modify();
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
    d.newDinner(d.getMod());
    
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
void Dinners::newDinner(string meal){
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
void Dinners::rmvDinner(fstream &file){
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
char Dinners::modify(){
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

void Dinners::dlDinList(fstream &file){
    file.open("DinnerList.rtf", ios::out);
    file << " ";
    file.close();
}

Dinners Dinners::addDinList(Dinners d, int pos, int numDin){
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

void Dinners::randomDin(Dinners *d, int num){
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