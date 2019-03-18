/*
 * AUTHOR: Aaron Creor
 * 
 * CONTACT INFORMATION: aaronmacleod123@gmail.com
 *
 * CREATION DATE: November 16, 2017
 *
 * PROBLEM STATEMENT: Allow user to Save, Store, and Display a created address book.
 *
 * PROGRAM DESCRIPTION: Modularized program allows a user to save and store various information
 * 						about a person and save it to a seperate document. This allows the user
 *						to close and reopen the program without losing their data. Menu driven.
 *
 * RUN INSTRUCTIONS: From the first menu you are given different options, 
 *                   Get Data: Allows you to input a Name, Address, and Zip code for 1 person
 *                   Display: Displays all held data
 *                   Sort: Sorts data in one of 3 ways
 *                   Remove: Allows you to remove entries by 1 of 3 parameters
 *                   Find: Allows you to search for data by 1 of 3 parameters
 *                   Edit: Allows you to edit data on all paramters
 *                   Save: Saves data held in vectors to disk
 *                   Load: Loads files on disk to Vector
 *                   Makes sure when entering a name you use the formatting specified
 *                   To use a menu just type the letter between the brackets(A) (B) (C)
 *                   In sub menus there is 4 options
 *                   (N)ame, (Z)ip, (A)ddress, and (B)ack [to go back]
 */
#include <iostream>
#include <string>  
#include <sstream>
#include <cstring>
#include <cmath>
#include <iomanip>
#include <vector>
#include <fstream>
#include <windows.h>
using namespace std;
char MenuResponseFunction(); //Declaration of functions
void getInfo();
void displayData();
void sortData();
void deleteData();
void sortZip();
void sortName();
void sortAddress();
void removeName();
void removeZip();
void removeAddress();
void miniSort();
void findData();
void findName();
void findAddress();
void findZip();
void editData();
void editbyName();
void editbyAddress();
void editbyZip();
void saveData();
void loadData();
void loadName();
void loadAddress();
void loadZip();
ifstream finZip, finAddress, finName; //allows reading from files
ofstream fout; //allows for writing to files
const int MAX = 100; //Maximum number of data sets allowed
vector <string> Names(MAX);   //Vector holding name data
vector <string> Address(MAX); //Vector holding Address data
vector <string> ZipCode(MAX); //Vector holding Zip Codes
int counter = 0; //Total number of data sets, starts at 1 instead of 0
 /* 
 NAME: main()
  * TASK: Allows user to access various functions
  * through a switch driven menu
  * ACCEPTS: Accepts user defined Char from MenuResposeFunction()
  * RETURNS: Function based on user input
  * MODIFIES: none
  */
int main(int argc, char *argv[]){
	bool run = true;
	do{
        switch (MenuResponseFunction()){ //Input from MenuResponseFunction()                
            case 'G': getInfo(); break;//Calls getInfo()      
            case 'g': getInfo(); break; 
            case 'D': displayData(); break;//Calls displayData()
            case 'd': displayData(); break;
            case 'S': sortData(); break;//Calls sortData()
            case 's': sortData(); break;
            case 'R': deleteData(); break;//Calls deleteData()
            case 'r': deleteData(); break;  
            case 'F': findData(); break;//Calls findData()
            case 'f': findData(); break;
            case 'E': editData(); break;//Calls editData()
            case 'e': editData(); break;
            case 'A': saveData(); break;//Calls saveData()
            case 'a': saveData(); break;
            case 'L': loadData(); break;//Calls loadData()
            case 'l': loadData(); break;           
			case 'Q': run = false; break;//Kills program
			case 'q': run = false; break; 
			default : cout << "Invalid" << endl;
		}
	} while (run);
	cout << endl << "Program Terminated" << endl;
	system("pause");
	return 0;
}
 /* 
  * NAME: MenuResponseFunction()
  * TASK: Get user defined char for switch in main()
  * ACCEPTS: Accepts user input in form of Char 
  * RETURNS: Char to main()
  * MODIFIES: None
  */
char MenuResponseFunction(){                                               
	char response; //Stores users response to menu
    cout << endl << "Please select an option" << endl
	<< "(G)et Info, (D)isplay, (S)ort, (R)emove, (F)ind, (E)dit, s(A)ve, (L)oad, (Q)uit" << endl
	<< "> ";
	cin >> response; //Passed to main()
	cin.ignore(256, '\n');
	return (response); //Returns input to main()
}
 /* 
  * NAME: WriteInColor()
  * TASK: Function Allows use of colour text on speicifed lines
  * ACCEPTS: None
  * RETURNS: Coloured text when called
  * MODIFIES: None
  */
void WriteInColor(unsigned short color, string outputString){
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hcon, color);
    cout << outputString;
}
 /* 
  * NAME: getInfo()
  * TASK: Gets User defined data and stores to vector
  * ACCEPTS: Accepts user defined strings
  * RETURNS: Returns strings to global vectors
  * MODIFIES: Vectors Names, ZipCode, and Address. Increments counter
  */
void getInfo(){
    string Name, Zip, AddressInfo; //Passed to Vectors after loop completes
    bool run = true; //Used to terminate while loop when needed
    char save, repeat; //Used for if loops that prompt user response
    while (run == true){ //Loop will get data sets until user terminates the loop
        WriteInColor(12,"(Firstname Lastname)");
        cout << endl;
        WriteInColor(07,"Please insert a name: ");
        getline(cin,Name);
        cout << "Please insert an address: ";
        getline(cin,AddressInfo);
        cout << "Please insert a ZIP code: ";
        getline(cin,Zip);
        cout << endl << "Do you wish to save this data? <y/n>: ";
        cin	>> save;
        if(toupper(save) == 'Y'){ //Confirms if user wishes to save data set
            counter++;
            string tmp, firstname, lastname; //Stores name data temporarily
            tmp = Name; //Temporary holder for name data
            ZipCode[counter] = Zip;
            Address[counter] = AddressInfo;
            int found; //Position of space in name;
            found=tmp.find(" ");
	        lastname = tmp.substr (++found, 20); 
	        firstname = tmp.substr (0, --found);
	        Names[counter] = lastname + ", " + firstname;
	        
        }
        cout << "Do you wish to add another data set? <y/n>: ";
        cin >> repeat;
        if(toupper(repeat) == 'N'){ //Confirms if user wishes to add a new data set
            run = false;
        }
        cin.clear();  //Clears cin buffer
        fflush(stdin);
        miniSort();//Runs miniSort()
	}
}
 /* 
  * NAME: displayData()
  * TASK: Displays stored data within vectors (Names, Address, ZipCode)
  * ACCEPTS: Accepts data stored in vectors
  * RETURNS: Returns displayed data to console
  * MODIFIES: None
  */
void displayData(){  
    for(int x=1; x<=counter; x++){
        if(Names[x] != ""){                        //Displays data in a box
            cout << "_______________________"      //_______________________
            << endl << Names[x]                    //Name, Example
            << endl << Address[x]                  //Address
            << endl << ZipCode[x]                  //Zip
            << endl << "_______________________"   //_______________________
            << endl;
        }
    }
}
 /* 
  * NAME: sortData()
  * TASK: Prompts user to select from various sort methods
  * ACCEPTS: Accepts user input in form of Char
  * RETURNS: Returns call to sub sort function
  * MODIFIES: None
  */
void sortData(){
    char sort; //Used to define sorting method
    bool run; //Used for sort menu
    cout << "Sort by (N)ame, (A)ddress, or (Z)ip? Go (B)ack?" << endl;
    cout << "> ";
    cin >> sort;
        switch(sort){
            case 'N': sortName(); break;//Calls sortName()
            case 'n': sortName(); break;
            case 'Z': sortZip(); break;//Calls sortZip()
            case 'z': sortZip(); break;
            case 'A': sortAddress(); break;//Calls sortAddress()
            case 'a': sortAddress(); break;
            case 'B': run = false; break;//Kills function
            case 'b': run = false; break;
            default: cout << "Invalid." << endl;
    }
}
 /* 
  * NAME: sortAddress()
  * TASK: Sorts data by Address
  * ACCEPTS: Accepts none
  * RETURNS: Returns vector sorted by Address
  * MODIFIES: All data stored in vectors (Names, Address, ZipCode)
  */
void sortAddress(){
    for (int y=0; y<counter; y++){ //Sorts data by Address
        for (int z=1; z<counter; z++){
            if (Address[z] > Address[z+1]){
                swap(Names[z], Names[z+1]);//Swaps Names
                swap(ZipCode[z], ZipCode[z+1]);//Swaps ZipCodes
                swap(Address[z], Address[z+1]);//Swaps Addresses
            }
        }
    }
	cout << "Sort Complete!";    
}
 /* 
  * NAME: sortZip()
  * TASK: Sorts data by Zip code
  * ACCEPTS: Accepts none
  * RETURNS: Returns vector sorted by Zip code
  * MODIFIES: All data stored in vectors (Names, Address, ZipCode)
  */
void sortZip(){
    for (int y=0; y<counter; y++){ //Sorts data by Zip
        for (int z=1; z<counter; z++){
            if (ZipCode[z] > ZipCode[z+1]){
                swap(Names[z], Names[z+1]);//Swaps Names
                swap(ZipCode[z], ZipCode[z+1]);//Swaps ZipCodes
                swap(Address[z], Address[z+1]);//Swaps Addresses
            }
        }
    }
    cout << "Sort Complete!";
}
 /* 
  * NAME: sortName()
  * TASK: Sorts data by last name
  * ACCEPTS: Accepts none
  * RETURNS: Returns vector sorted by last name
  * MODIFIES: All data stored in vectors (Names, Address, ZipCode)
  */
void sortName(){
    for (int y=0; y<counter; y++){ //Sorts data by last name
        for (int z=1; z<counter; z++){
            if (Names[z] > Names[z+1]){
                swap(Names[z], Names[z+1]);//Swaps Names
                swap(ZipCode[z], ZipCode[z+1]);//Swaps ZipCodes
                swap(Address[z], Address[z+1]);//Swaps Addresses
            }
        }
    }
    cout << "Sort Complete!";
}
 /* 
  * NAME: deleteData()
  * TASK: Prompts user for removal method and calls function
  * ACCEPTS: User input to determine removal method
  * RETURNS: Call for sub removal function
  * MODIFIES: none
  */
void deleteData(){
    char remove; //Used to define removal
    bool run; //Used for removal menu
    cout << "Remove by (N)ame, (A)ddress, or (Z)ip? Go (B)ack?" << endl;
    cout << "> ";
    cin >> remove;
        switch(remove){
            case 'N': removeName(); break;//Calls removeName()
            case 'n': removeName(); break;
            case 'Z': removeZip(); break;//Calls removeZip()
            case 'z': removeZip(); break;
            case 'A': removeAddress(); break;//Calls removeAddress()
            case 'a': removeAddress(); break;
            case 'B': run = false; break;//Kills function
            case 'b': run = false; break;
            default: cout << "Invalid." << endl;
        }
}
 /* 
  * NAME: removeName()
  * TASK: Remove all files with user defined name
  * ACCEPTS: User input to determine removed name
  * RETURNS: List without defined name
  * MODIFIES: All data stored in vectors (Names, Address, ZipCode)
  */
void removeName(){
    string remove; //Name to be removed    
    bool run = 0;         
	cout << "Please insert the name you wish to remove" << endl;
	WriteInColor(12,"(Lastname, Firstname)");
	cout << endl;
	WriteInColor(07,"> ");
    cin.clear();  //Clears cin buffer
    fflush(stdin);
	getline(cin,remove);
    for(int i=0;i<=counter;i++){ //Searches for name to be removed
        if(remove==Names[i]){                             
            cout << Names[i] << " Removed!" << endl; 
            Names[i] = ""; //Changes name in designated position to ""
            ZipCode[i] = "";//Changes ZipCode in designated position to ""
            Address[i] = "";//Changes Address in designated position to ""
            run = 1;     
        }              
    }
    if(run == 0){
        cout << remove << " Not found" << endl;
        }
    miniSort(); //Pushes blank data to back
}
 /* 
  * NAME: removeZip()
  * TASK: Remove all files with user defined Zip Code
  * ACCEPTS: User input to determine removed Zip Code
  * RETURNS: List without defined Zip Codes
  * MODIFIES: All data stored in vectors (Names, Address, ZipCode)
  */
void removeZip(){
    string remove; //Zip to be removed    
    bool run = 0;         
	cout << "Please insert the Zip Code you wish to remove" << endl;
	cout << "> ";
    cin.clear();  //Clears cin buffer
    fflush(stdin);
	getline(cin,remove);
    for(int i=0;i<=counter;i++){ //Searches for name to be removed
        if(remove==ZipCode[i]){                             
            cout << ZipCode[i] << " Removed!" << endl; 
            Names[i] = "";//Changes name in designated position to ""
            ZipCode[i] = "";//Changes Zip in designated position to ""
            Address[i] = "";//Changes Address in designated position to ""
            run = 1;     
        }              
    }
    if(run == 0){
        cout << remove << " Not found" << endl;
        }
    void miniSort(); //Pushes blank data to back
}
 /* 
  * NAME: removeAddress()
  * TASK: Remove all files with user defined Address
  * ACCEPTS: User input to determine removed Addresses
  * RETURNS: List without defined Addresses
  * MODIFIES: All data stored in vectors (Names, Address, ZipCode)
  */
void removeAddress(){
    string remove; //Address to be removed    
    bool run = 0;         
	cout << "Please insert the Address you wish to remove" << endl;
	cout << "> ";
    cin.clear();  //Clears cin buffer
    fflush(stdin);
	getline(cin,remove);
    for(int i=0;i<=counter;i++){ //Searches for name to be removed
        if(remove==Address[i]){                             
            cout << Address[i] << " Removed!" << endl; 
            Names[i] = "";//Changes name in designated position to ""
            ZipCode[i] = "";//Changes Zip in designated position to ""
            Address[i] = "";//Changes Address in designated position to ""
            run = 1;     
        }              
    }
    if(run == 0){
        cout << remove << " Not found" << endl;
        }
    void miniSort(); //Pushes blank data to back
}
 /* 
  * NAME: miniSort()
  * TASK: Push blank strings to end of vector
  * ACCEPTS: None
  * RETURNS: Sorted Vectors
  * MODIFIES: All data stored in vectors (Names, Address, ZipCode)
  */
void miniSort(){
    for (int y=0; y<counter; y++){//Runs through vector multiple times to find blank strings
        for (int z=1; z<counter; z++){
            if (Names[z] == ""){
                swap(Names[z], Names[z+1]);//Swaps blank names to back of vector
                swap(ZipCode[z], ZipCode[z+1]);//Swaps blank ZipCodes to back of vector
                swap(Address[z], Address[z+1]);//Swaps blank Addresses to back of vector
            }
        }
    }
}
 /* 
  * NAME: findData()
  * TASK: Prompts user for search method
  * ACCEPTS: User input in form of string
  * RETURNS: Sub search function
  * MODIFIES: None
  */
void findData(){
    char find; //Used to define search
    bool run; //Used for removal menu
    cout << "Search by (N)ame, (A)ddress, or (Z)ip? Go (B)ack?" << endl;
    cout << "> ";
    cin >> find;
        switch(find){
            case 'N': findName(); break;//Calls findName()
            case 'n': findName(); break;
            case 'Z': findZip(); break;//Calls findZip()
            case 'z': findZip(); break;
            case 'A': findAddress(); break;//Calls findAddress()
            case 'a': findAddress(); break;
            case 'B': run = false; break;//Kills function
            case 'b': run = false; break;
            default: cout << "Invalid." << endl;
        }
    cin.clear();//Clears cin buffer
    fflush(stdin);
}
 /* 
  * NAME: findName()
  * TASK: Searches vectors for specified Name
  * ACCEPTS: User input to define searched vector
  * RETURNS: Requested data to console
  * MODIFIES: None
  */
void findName(){
    string search;
    bool b = 0;
    cout << "Please input a name" << endl;
    WriteInColor(12,"(Lastname, Firstname)");
    cout << endl;
    WriteInColor(7,"> ");
    cin.clear();  //Clears cin buffer
    fflush(stdin);
    getline(cin,search);                             
	cout << "Searching. . . " << endl; 
    for(int i=0;i<=counter;i++){
        if(search==Names[i]){
            cout << "Found in Postion: " << i << endl;//Outputs data position
            cout << "_______________________" 
            << endl << Names[i]
            << endl << Address[i]
            << endl << ZipCode[i]
            << endl << "_______________________"
            << endl;    
            b = 1;
        }              
    }
    if(b == 0){
        cout << search << " Not found" << endl;
    }
    cout << "Search Complete" << endl;
    cin.clear();
    fflush(stdin);
}
 /* 
  * NAME: findZip()
  * TASK: Searches vectors for specified Zip Code
  * ACCEPTS: User input to define searched vector
  * RETURNS: Requested data to console
  * MODIFIES: None
  */
void findZip(){
    string search;
    bool b = 0;
    cout << "Please input a Zip Code" << endl;
    cout << "> ";
    cin.clear();  //Clears cin buffer
    fflush(stdin);
    getline(cin,search);                             
	cout << "Searching. . . " << endl; 
    for(int i=0;i<=counter;i++){
        if(search==ZipCode[i]){
            cout << "Found in Postion: " << i << endl;//Outputs data position
            cout << "_______________________"
            << endl << Names[i]
            << endl << Address[i]
            << endl << ZipCode[i]
            << endl << "_______________________"
            << endl;    
            b = 1;    
        }              
    }
    if(b == 0){
        cout << search << " Not found" << endl;
    }
    cout << "Search Complete" << endl;	
}
 /* 
  * NAME: findAddress()
  * TASK: Searches vectors for specified Address
  * ACCEPTS: User input to define searched vector
  * RETURNS: Requested data to console
  * MODIFIES: None
  */
void findAddress(){
    string search;
    bool b = 0;
    cout << "Please input an Address" << endl;
    cout << "> ";
    cin.clear();  //Clears cin buffer
    fflush(stdin);
    getline(cin,search);                             
	cout << "Searching. . . " << endl; 
    for(int i=0;i<=counter;i++){
        if(search==Address[i]){
            cout << "Found in Postion: " << i << endl;//Outputs data position
            cout << "_______________________"
            << endl << Names[i]
            << endl << Address[i]
            << endl << ZipCode[i]
            << endl << "_______________________"
            << endl;    
            b = 1;    
        }              
    }
    if(b == 0){
        cout << search << " Not found" << endl;
    }
    cout << "Search Complete" << endl;	
}
 /* 
  * NAME: editData()
  * TASK: Searches vectors for specified data, prompts user to edit
  * ACCEPTS: User input to define searched vector
  * RETURNS: Requested data to console
  * MODIFIES: All data stored in vectors (Names, Address, ZipCode)
  */
void editData(){
    char edit; //Used to define edit
    bool run; //Used for removal menu
    cout << "Edit by (N)ame, (A)ddress, or (Z)ip? Go (B)ack?" << endl;
    cout << "> ";
    cin >> edit;
        switch(edit){
            case 'N': editbyName(); break;//Calls editbyName()
            case 'n': editbyName(); break;
            case 'Z': editbyZip(); break;//Calls editbyZip()
            case 'z': editbyZip(); break;
            case 'A': editbyAddress(); break;//Calls editbyAddress()
            case 'a': editbyAddress(); break;
            case 'B': run = false; break;//Kills function
            case 'b': run = false; break;
            default: cout << "Invalid." << endl;
        }
}
 /* 
  * NAME: editbyName()
  * TASK: Searches vectors for specified Name to be edited
  * ACCEPTS: User input to define searched vector
  * RETURNS: Requested data to console to be edited
  * MODIFIES: All Names stored in vectors (Names)
  */
void editbyName(){
    string search;//Used to search for specified data
    bool b = 0;
    cout << "Please input a name" << endl;
    WriteInColor(12,"(Lastname, Firstname)");
    cout << endl;
    WriteInColor(7,"> ");
    cin.clear();  //Clears cin buffer
    fflush(stdin);
    getline(cin,search);                             
	cout << endl;
	for(int i=0;i<=counter;i++){
        if(search==Names[i]){
            string Name;
            char save; //Used to confirm change in data
            cout << "Found in Postion: " << i << endl;//Outputs data position
            cout << "(Firstname Lastname)";
            cout << endl << "Please insert a name: ";
            getline(cin,Name);
            cout << endl << "Do you wish to save this data? <y/n>: ";
            cin	>> save;
            if(toupper(save) == 'Y'){ //Confirms if user wishes to save data set
                string tmp, firstname, lastname; //Stores name data temporarily
                tmp = Name;
                int found; //Position of space in name;
                found=tmp.find(" ");
                lastname = tmp.substr (++found, 20); 
                firstname = tmp.substr (0, --found);
                Names[i] = lastname + ", " + firstname;
                b = 1;
            } 
        }             
    }
    if(b == 0){
        cout << search << " Not found" << endl;
    }	
    cin.clear();  //Clears cin buffer
    fflush(stdin);
}
 /* 
  * NAME: editbyZip()
  * TASK: Searches vectors for specified ZIPCODE to be edited
  * ACCEPTS: User input to define searched vector
  * RETURNS: Requested data to console to be edited
  * MODIFIES: All ZipCodes stored in vectors (ZipCode)
  */
void editbyZip(){
    string search;//Used to search for specified data
    bool b = 0;
    cout << "Please input a Zip Code" << endl;
    cout << "> ";
    cin.clear();  //Clears cin buffer
    fflush(stdin);
    getline(cin,search);                             
	cout << endl;
	for(int i=0;i<=counter;i++){
        if(search==ZipCode[i]){
            string Zip;
            char save; //Used to confirm change in data
            cout << "Found in Postion: " << i << endl;//Outputs data position
            cout << endl << "Please insert a ZipCode: ";
            getline(cin,Zip);
            cout << endl << "Do you wish to save this data? <y/n>: ";
            cin	>> save;
            if(toupper(save) == 'Y'){ //Confirms if user wishes to save data set
                ZipCode[i] = Zip;
                b = 1;
            } 
        }             
    }
    if(b == 0){
        cout << search << " Not found" << endl;
    }	
    cin.clear();  //Clears cin buffer
    fflush(stdin);     
}
 /* 
  * NAME: editbyAddress()
  * TASK: Searches vectors for specified Address to be edited
  * ACCEPTS: User input to define searched vector
  * RETURNS: Requested data to console to be edited
  * MODIFIES: All Addresses stored in vectors (ZipCode)
  */
void editbyAddress(){
    string search; //Used to search for specified data
    bool b = 0;
    cout << "Please input an Address" << endl;
    cout << "> ";
    cin.clear();  //Clears cin buffer
    fflush(stdin);
    getline(cin,search);                             
	cout << endl;
	for(int i=0;i<=counter;i++){
        if(search==Address[i]){
            string Addressdata;
            char save; //Used to confirm change in data
            cout << "Found in Postion: " << i << endl;//Outputs data position
            cout << endl << "Please insert an Address: ";
            getline(cin,Addressdata);
            cout << endl << "Do you wish to save this data? <y/n>: ";
            cin	>> save;
            if(toupper(save) == 'Y'){ //Confirms if user wishes to save data set
                Address[i] = Addressdata;
                b = 1;
            } 
        }             
    }
    if(b == 0){
        cout << search << " Not found" << endl;
    }	
    cin.clear();  //Clears cin buffer
    fflush(stdin);     
}
 /* 
  * NAME: saveData()
  * TASK: Saves data to external file
  * ACCEPTS: All vectors used to store data to write to file
  * RETURNS: Files created to program folder
  * MODIFIES: None
  */
void saveData(){
    fout.open("Names.txt", ios::app); //Creates/Opens file to be saved to
    for(int x=1; x<=counter; x++){
        fout << Names[x] << endl;
    }
    fout.close();//Closes Names.txt
    fout.open("ZIP.txt", ios::app); //Creates/Opens file to be saved to
    for(int x=1; x<=counter; x++){
        fout << ZipCode[x] << endl;
    }
    fout.close();//Closes ZIP.txt
    fout.open("Address.txt", ios::app); //Creates/Opens file to be saved to
    for(int x=1; x<=counter; x++){
        fout << Address[x] << endl;
    }
    fout.close();//Closes Address.txt
    WriteInColor(10,"Save complete!");
    WriteInColor(7,"");
}
 /* 
  * NAME: loadData()
  * TASK: loads data from external files
  * ACCEPTS: external data in form of text files
  * RETURNS: data from files to Zip, name, and address vectors
  * MODIFIES: Vectors used to store data
  */
void loadData(){
	WriteInColor(10,"Loading Names. . .");
	cout << endl;
    loadName(); //calls loadName() 
    cout << "Loading Addresses. . . " << endl;
    loadAddress();//calls loadAddress() 
    cout << "Loading Zip Codes. . ." << endl;
    loadZip();//calls loadZip() 
    cout << "Load complete!";
    WriteInColor(7,"");
    miniSort();//Runs miniSort()
}
 /* 
  * NAME: loadName()
  * TASK: loads data from Names.txt
  * ACCEPTS: external data in form of text files
  * RETURNS: data from files to Names vector
  * MODIFIES: Vectors used to store data
  */
void loadName(){
    int pointer; //holds size of file
    finName.open("Names.txt", ios::app);
    if (finName.fail()) {//Output if error
        cerr << "Could not open intput file Names.txt" << endl;
        system("pause"); 
        exit(1);
	}
	pointer++;
	getline(finName,Names[pointer]);
    for(int ndx = 1; !finName.eof(); ndx++){//Reads until end of file
	    pointer++;	
   		getline(finName,Names[pointer]);
   	}
   	finName.close();//Closes File being read from
   	finName.clear();
}
 /* 
  * NAME: loadAddress()
  * TASK: loads data from Address.txt
  * ACCEPTS: external data in form of text files
  * RETURNS: data from files to Address vector
  * MODIFIES: Vectors used to store data
  */
void loadAddress(){
    int pointer; //holds size of file
    finAddress.open("Address.txt", ios::app);
    if (finAddress.fail()) {//Output if error
        cerr << "Could not open intput file Address.txt" << endl;
        system("pause"); 
        exit(1);
	}
	pointer++;
	getline(finAddress,Address[pointer]);
    for(int ndx = 1; !finAddress.eof(); ndx++){//Reads until end of file
	    pointer++;	
   		getline(finAddress,Address[pointer]);
   	}
   	finAddress.close(); //Closes File being read from
   	finAddress.clear();
}
 /* 
  * NAME: loadZip()
  * TASK: loads data from ZIP.txt
  * ACCEPTS: external data in form of text files
  * RETURNS: data from files to ZipCode vector
  * MODIFIES: Vectors used to store data
  */
void loadZip(){
    int pointer; //holds size of file
    finZip.open("ZIP.txt", ios::app);
    if (finZip.fail()) {//Output if error
        cerr << "Could not open intput file ZIP.txt" << endl;
        system("pause"); 
        exit(1);
	}
	pointer++;
	getline(finZip,ZipCode[pointer]);
    for(int ndx = 1; !finZip.eof(); ndx++){//Reads until end of file
	    pointer++;	
   		getline(finZip,ZipCode[pointer]);
   	}
   	finZip.close();//Closes File being read from
	finZip.clear();
	counter = pointer;//Assigns # of lines in file to global counter
}   
