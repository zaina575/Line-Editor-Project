
#include <iostream>
#include "linelist.h"

LineList::LineList() //LineList constructor
{
	LineNode *line = new LineNode; //lineNode 1
	LineNode *line2 = new LineNode; //lineNode 2

	line -> info = topMessage; //top buffer
	currLine = line; //currLine set to lineNode
	currLineNum = 0; //int value that keeps track of current line number
	length = 0; //int value that keeps track of length of LineList
	line2 -> info = bottomMessage;// bottom buffer
	currLine -> back = NULL; //currLine back is set to NULL
	currLine -> next = line2; //currLine next is set to lineNode2
	line2 -> back = line; //lineNode2 back is set to line
	line2 -> next = NULL; //lineNode2 next is set to NULL
}

void LineList::goToTop() 
{
	// Post : Advances currLine to line 1

	//while loop that keeps going to the previous LineNode until it hits NULL
	while(currLine -> back !=  NULL){
		currLine = currLine -> back; //go back to the previous LineNode
		currLineNum--; //decrement currLineNum by 1
	}
	currLine = currLine -> next; //go to next node because we never want to be at the top buffer
	currLineNum = 1; //set currLineNum to 1 which is the first line
}

void LineList::goToBottom() 
{
	// Post : Advances currLine to last line

	//while loop that keeps going to the next LineNode until it hits NULL
	while(currLine -> next != NULL){
		currLine = currLine -> next; //go to the next LineNode
		currLineNum++; //increment currLineNum by 1
	}
	currLine = currLine -> back; //go to the previous node because we never want to be at the bottom buffer
	currLineNum--; //decrement currLineNum by 1 because you are going back one node
}

void LineList::insertLine(string newLine)
{
	// post : newLine has been inserted after the current line
	 if ( currLine -> info == bottomMessage ) //if currLine is equal to the bottom buffer, go back to the previous LineNode
           movePrevLine(); //calls movePrevLine method

	LineNode *newL = new LineNode; //create a new LineNode for the line you are about to insert
	newL -> info = newLine; //new LineNode info is equal to the string that we are passing into this method
	newL -> back = currLine; //link new LineNode's back to currLine
	newL -> next = currLine -> next; //link new LineNode's next to currLine's next
	
	currLine -> next -> back = newL; //link currLine Node's next's back to the new LineNode
	currLine -> next = newL; //link currLine Node's next to new LineNode
	currLine = currLine -> next; //set currLine Node to old currLine's next

	currLineNum++; //increment currLineNum
	length++; //increase the length by 1
}

void LineList::deleteLine()
{
	// post : deletes the current line leaving currentLine
	//	  pointing to line following

	if(length !=0){ //if the length is not zero then you can delete items

	if( currLine -> info == bottomMessage ){
		movePrevLine();}  //if the currentLine is at the bottom buffer go back to the previous line
	if( currLine -> info == topMessage ){ 
		moveNextLine();} //if the currentLine is at the top buffer go to the next line

	LineNode *dLine = currLine; //create a new LineList node for the line about to be deleted

	currLine = currLine -> next; //the new currentLine is the old currLine's next


	currLine -> back = dLine -> back; //link currLine's back to the line about to be deleted's back
	currLine -> back -> next  = dLine -> next; //link currLine's back's next to the line about to be deleted's next
	currLine = dLine -> back;	//set currLine back to it's original position


	dLine -> next = NULL; //set the dLine node's next to NULL
	dLine -> back = NULL; //set the dLine node's back to NULL
	
	delete dLine; //free up space in dLine Node
	dLine = NULL; //set dLine Node to NULL
	
	
	currLineNum--; //decrement currLineNum
	length--; //decrement length}
}}

void LineList::printList() 
{
	 //post: lists all the lines
	 int lineNum = 1; //set lineNum to 1

        LineNode *mark = currLine; //create a LineNode to keep track of where you are
        int markNum = currLineNum; //integer to keep track of where you are

        goToTop(); //calling goToTop to start the method 

        LineNode *line = currLine; //create a new LineNode and set it equal to the currLine

        while (line -> info != bottomMessage) //while it does not equal the bottom buffer continue to print
        {

                cout << lineNum << "> " << line -> info << endl; //print
                line = line -> next; //set new line node to the old line node's next
                lineNum++; //increment lineNum
        }

        currLine = mark; //change currLine to mark
        currLineNum = markNum; //change currLineNum to markNum


}

string LineList::getCurrLine() const
{
	//Post:  returns a string representing the line currently being pointed to by the
	//external pointer
	return currLine -> info; //get info about currLine

}

void LineList::moveNextLine()
{
	// Post : Advances currLine (unless already at last line)
	if(currLine -> next != NULL){ //move to the next node if there is one
		currLine = currLine -> next; //set currLine to currLine's next
		currLineNum++; //increment currLineNum
	}

	if(currLine -> info == bottomMessage){
		currLineNum = length+1;
	}

}

void LineList::movePrevLine()
{
	// Post: go to the line above it
	if(currLine -> back != NULL){ //move back if currLine's back does not equal NULL
		currLine = currLine -> back; //set currLine to currLine's back
		 currLineNum--; //decrement currLineNum
	}
	
	if(currLine -> info == topMessage){ //if it equals the top buffer
		currLineNum = 0;	//set currLineNum to 0
	
	}

}

int LineList::getCurrLineNum() const
{
	//Post: returns an integer that represents the CurrLineNum
	return currLineNum; //returns currLineNum

}

int LineList::getLength() const
{
	//Post: returns an integer that represents the length of the LineList
	return length; //returns length of LineList
}

