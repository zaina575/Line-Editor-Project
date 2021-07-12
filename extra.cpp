#include <iostream>
#include<fstream>
#include "linelist.h"
#include <stdlib.h>
#include <string>
#include <cstdlib>

using namespace std;

	void StartUp(int argc, char *argv[],LineList &L); //prototype for StartUp method
	void OpenFile(ifstream &infile, char *argv[], int argc); //prototype for OpenFile method
	void GetCommand(LineList &L, char &command); //prototype for GetCommand method
	void Insert(LineList &L);// prototype for Insert method
	void FinishUp(char *argv[], LineList &L); //prototype for FinishUp method




	int main(int argc, char *argv[]) //main method
	{

		

        	LineList L; //LineList object
	        char command; //character variable that stores command

        	StartUp (argc, argv, L); //call of StartUp method
		
		//do while for different commands 
       		do 
        	{
                	GetCommand (L, command); //call of GetCommand method 

                	switch((command)) //switch statement for each command
                	{
           
				case 'L':{ //case L
	                 	cin.ignore(1000000, '\n'); //captures just L 
			 	L.printList();  break;} //call printList method

                        	case 'I' : //case I
				{	
                         	Insert(L);     break;} //call Insert method
                        	
				case 'D' : //case D
			 	{	
                         	cin.ignore(1000000, '\n'); //captures just D
			 	L.deleteLine(); break;} //call deleteLine method

                        	case 'N' : //case N
				{	
			 	cin.ignore(1000000, '\n'); //captures just N
                         	L.moveNextLine(); break;} //call moveNextLine method

                        	case 'P' : //case P
				{		
                	 	cin.ignore(1000000, '\n'); //captures just P	 
		       	 	L.movePrevLine(); break;} //call movePrevLine method

				default: //default case
				{
		         	cin.ignore(1000000,'\n'); //ignores anything that is not one of these commands
				}
                	}

        		} while ((command) != 'E'); //stop when it equals E

        	FinishUp (argv, L); //call FinishUp method
        	return 0;
	}	

	//Post:Will open the file that is sent to the command line and 
	//LineList object will be intialized with whatever is already in the file 
	void StartUp(int argc, char *argv[], LineList &L){

		ifstream infile; //infile

		OpenFile(infile, argv, argc); //call OpenFile method
		string s; //string s

		 while (getline(infile, s)){ //getting each line
                       L.insertLine(s); //inserting each line in the fileas a seperate line
		
		}
		L.printList(); //print the list
		L.goToBottom(); //be at the bottom of the list
	}

	//Post: Will open the file that is sent to the command line	
	void OpenFile(ifstream &infile,char *argv[], int argc){

		if(argc == 1){ //if argc equals 1

		//  cout << "\033[1;31mbold red text\033[0m\n";

		cout << "\033[1;31mError: You have not entered a filename!\033[0m" << endl; //they did not enter a filename and display error message
		exit(1); //exit
		}

		string namef =argv[1]; //string for filename

                infile.open(namef.c_str(),ifstream::in); //open up file
	
	}

	//Post: Will take in the command on the command line
	void GetCommand(LineList &L, char &command){

		cout <<"\033[1m\033[34m";
		cout << L.getCurrLineNum() << "> "; //print
		cin >> command;	//take in command
		 cout << "\033[0m";

	}

	//Post: Will insert a Line 
	void Insert(LineList &L){
		cout << "\033[1m\033[35m" << (L.getCurrLineNum()+1) << "> "; //print
		cin.ignore(1000000,'\n'); //allows for new input
		string newL = ""; //string that stores the line you want to inpit
		getline(cin, newL); //put whole line's input in newL string
		
		L.insertLine(newL); //calling of insertLine method

		cout << "\033[0m";
	}

	//Post: Will close up file with the changes made
	void FinishUp(char *argv[], LineList &L){
		ofstream outfile; //out file

		string namef =argv[1]; //string for filename
		
		outfile.open(namef.c_str()); //open outfile
		
		L.goToTop(); //go to the top 

		//for loop that get every line and adds it to the file
		for(int j = 0; j < L.getLength(); j++){
		
			outfile << L.getCurrLine() << endl; //add currentLine to outfile
			L.moveNextLine(); //go to the next line
		}

		outfile.close(); //close the outfile
	}
