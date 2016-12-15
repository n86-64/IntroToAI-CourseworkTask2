//
//  SolutionListOperations.c
//  NQueens-Example
//
//  Created by Jim Smith on 25/09/2014.
//  Copyright (c) 2014 James Smith. All rights reserved.
//




#include <stdio.h>
#include <stdlib.h>

#pragma warning (disable : 4996)

#include "StructureDefinitions.h"
#include "SolutionListOperations.h"

#include "PathFindingSpecificSolutionOperations.h"


/* this is just a really handy function to use for debugging or for dealing with unexpected situations in your code*/
    void PrintThisMessageAndExit(char *message)
  {
    //char throwawayToEndProramme;
    printf("%s\n",message);
#ifndef FINALTEST
    //    printf("press any key to continue");
    //scanf("%c",&throwawayToEndProramme);
#endif
    exit(0);
  }

//==========================

int GetIndexOfWorkingCandidateInThisList(candidateList thislist)
{
    extern candidateSolution workingCandidate;
    char wcvalues[N];
    int place=0, which=0, mismatches=N;
    
    //copy peg values from working candidate into conveniently named array becuase it is faster this way
    for(place=0;place<N;place++)
        wcvalues[place] = workingCandidate.variableValues[place];
    
    //start at the end of the list
    which = thislist.indexOfLastEntryAdded;
    //and loop through until we have found a match or reached the beginning
    while (which >=0)
      {
        // start looking peg by peg, stopping as soon as there is a mismatch
        for (place=0,mismatches = 0; (place < N)&& (mismatches ==0);place++)
            if (thislist.listEntries[which].variableValues[place] != wcvalues[place])
                mismatches++;
        if (mismatches>0) //no mismatches found so move to next one in the list
            which --;
        else
            break;
      }
    //end of which loop,  now just need to look and see if we found it
    if (which < 0)
        which = NOTFOUND;
    return  which;
}



//==============================================================================
void CleanCandidate( candidateSolution *toBeCleaned)
{
	int currentRow;
    ///can't clean something that doesn;t exist!
	if( toBeCleaned== (candidateSolution *)NULL)
		PrintThisMessageAndExit("error - parameter passed to CleanCandidate() was not valid address of candidate");

    ///to start with set the number of defined values to be zero in this solution
        toBeCleaned->numberOfDefinedValues =0;
    ///just to be on the safe size,  set each actual value to "UNUSED"
		for(currentRow = 0; currentRow < N; currentRow++)
            toBeCleaned->variableValues[currentRow] = UNUSED;
    ///and obvously there can't be any conflicts in an empty solution
        toBeCleaned->score=0;

}


/* void CleanListsOfSolutionsToStart(void)
 *this function runs through the two structures  we declared to hold our lists of candidate  and examinedsolutions and
 *sets each one to be empty
 * takes no parameters (because the list stuctures are declared as global and does not return any values
 */
void CleanListsOfSolutionsToStart(void)

{
    int currentSolution; //loop variables used to loop through the solutions
  
    // by referring to these as externs our compiler will check they exist in some other file when it builds the programme
    extern candidateList currentListOfCandidates, listOfExaminedCandidates;
    
	// loop through each solution in each list emptying the contents
    for (currentSolution=0;currentSolution<SIZEOFSOLUTIONLIST;currentSolution++)
      {
		  CleanCandidate ( &currentListOfCandidates.listEntries[currentSolution]);
		  CleanCandidate ( & listOfExaminedCandidates.listEntries[currentSolution]);
      }
    currentListOfCandidates.indexOfLastEntryAdded = listOfExaminedCandidates.indexOfLastEntryAdded = -1;
    
 
}//end of CleanListsOfSolutionsToStart(void)


/*  void CleanWorkingCandidate (void)
*  make a call to the generic function to do what it says on the can
*/
void CleanWorkingCandidate (void)
{
	extern candidateSolution workingCandidate;
	CleanCandidate(& workingCandidate);
}
	
	
	
	
	/*CopySolutionParam1_IntoSolutionParam2( candidateSolution *from, candidateSolution *to)
 * copy contensts of candidate soltion whoe address in memory is given by param 1
 * into the candidate soltion whose address in memory is geniven by param 2
 * does all error checking internally so no return
 */
void CopySolutionParam1_IntoSolutionParam2( candidateSolution *from, candidateSolution *to)
{
    
    int rowid;//loop variable
    
    //error checking - addreses in memory must have been designated as holding structures of the right type
    if(from == (candidateSolution *)NULL || to == (candidateSolution *)NULL )
        PrintThisMessageAndExit("invalid address provided in CopySolution() function");
    
    //now do a simple copy of the contents
    to->numberOfDefinedValues = from->numberOfDefinedValues;
    to->score = from->score;
    for ( rowid=0; rowid<from->numberOfDefinedValues;rowid++)
        to->variableValues[rowid] = from->variableValues[rowid];
    
    //and blank out the unused spaces
    for( rowid=from->numberOfDefinedValues; rowid < N;rowid++)
        to->variableValues[rowid] = UNUSED;
}



/* void CopySolutionFromCurrentListIntoWorkingCandidate(int solutionIndex);
 * makes a call to the generic copy function
 * presupoosed the existence of the global variables
 * to make a nice simple to call function
 */
void CopySolutionFromCurrentListIntoWorkingCandidate(int solutionIndex)
{
   //define the global variables as having beeen declared in a another file
	extern candidateList currentListOfCandidates;
    extern candidateSolution workingCandidate;
	//check that the index is not off the end of the list
	if (solutionIndex >= SIZEOFSOLUTIONLIST || solutionIndex <0)
		PrintThisMessageAndExit("solution index passed to function CopySolutionFromCurrentListIntoWorkingCandidate() is beyond bounds of array");
	// if we got this far we can do the copy using the generic function
    CopySolutionParam1_IntoSolutionParam2( &currentListOfCandidates.listEntries[solutionIndex], &workingCandidate );
}



/* generic function to add a candidate to a list
* firstr param is address of candidate ot add
* second is address of list ot receive
* does all the error handling in the function so no return value
*/
void AddSolutionPram1_ToListParam2(candidateSolution *toAdd, candidateList *receiver)
{
	int currentsize;

	//check parameters are valid
	if  ( toAdd == (candidateSolution *)NULL  || receiver ==(candidateList *)NULL)
		PrintThisMessageAndExit ("parameters to AddSolutionPram1_ToListParam2 are not valid pointers");

	//check reciever is not full
	else if ( receiver->indexOfLastEntryAdded == SIZEOFSOLUTIONLIST)
		PrintThisMessageAndExit ("can't add candidate  because receiving list is full");

	else
		{
			currentsize = receiver->indexOfLastEntryAdded+1; //add one because arrays start from zero
			CopySolutionParam1_IntoSolutionParam2(toAdd, & receiver->listEntries[currentsize ]);
			receiver->indexOfLastEntryAdded = currentsize;
	}



}





/* void AddWorkingCandidateToCurrentList(void)
 * calls generic  function 
 * error handlind done within function so on return
 */
void AddWorkingCandidateToCurrentList(void)
{
	extern candidateSolution workingCandidate;
	extern candidateList currentListOfCandidates;
	AddSolutionPram1_ToListParam2(&workingCandidate, &currentListOfCandidates);
}



/* void AddWorkingCandidateToExaminedList(void)
 * calls generic  function 
 * error handlind done within function so on return
 */
void AddWorkingCandidateToExaminedList(void)
{
	extern candidateSolution workingCandidate;
	extern candidateList listOfExaminedCandidates;
	AddSolutionPram1_ToListParam2(&workingCandidate, &listOfExaminedCandidates);
}
/* void RemoveFromListParam1_CandidateSolutionAtIndeParam2( candidateList *listToEdit, int solutionIndex)
 * generic function to remove a candidate solution from a list
 *
 * first parameter is the list to be edited
 * second parameter is the index of the solution to remove
 * all the error handling happens within the function so there is no return
 */

void RemoveFromListParam1_CandidateSolutionAtIndexParam2( candidateList *listToEdit, int solutionIndex)
{
    
    int numberOfEntriesInThisList; //declare int to hold number of solutions currently in the list
	 int copyingfrom, copyingto;// and two more to use when we shuffle things along
	 int row=0;

    //next we'll start off with a series of error checks before we do anything
    //each of these is serous enough to cause us to quit the programme
    
    //first of all, have we been given the address of a valid candidate list
    if( listToEdit == (candidateList *)(NULL))
        PrintThisMessageAndExit("first parameter passed was not a pointer to a valid list");

    // then of all check that the index we are given is valid
    else if ( (solutionIndex >= SIZEOFSOLUTIONLIST) || (solutionIndex <0))
        PrintThisMessageAndExit("oops - tried to remove a solution that lies beyond the bounds of our list");
 
	// if we've got here we know it is safe to try and access the lists
	else 
      {
        // last couple of tests
		  //find out how many entries are in the list
        numberOfEntriesInThisList = listToEdit->indexOfLastEntryAdded;
        // check that the list is not already empty
        if (numberOfEntriesInThisList<0)
            PrintThisMessageAndExit("oops - tried to remove an entry from an empty list");
        //check the index isn't too high
        if ( solutionIndex > numberOfEntriesInThisList)
            PrintThisMessageAndExit("oops - tried to remove a solution that does not exist in our list");



        //  ok, then we can proceed
        printf("removing solution at index %d \n", solutionIndex);
        //if the one to remove is the last on the list,  its all very simple
        if (solutionIndex == numberOfEntriesInThisList)
          {
			  //empty the contents of the place in the lsit occupied by the last solution added
            listToEdit->listEntries[solutionIndex].numberOfDefinedValues = 0;
            listToEdit->listEntries[solutionIndex].score = 0;
            for ( row=0;row < N;row++)
                listToEdit->listEntries[solutionIndex].variableValues[row] = UNUSED;
			//and reduce the count of number of things in the list
            listToEdit->indexOfLastEntryAdded --;
          }//end of code that just deleted the last entry
        
        
        else //otherwise we need to shuffle all the rest along, 
          {
           //start with the one to be deleted, and overwrite the contents with  the solution to the right
			  //then move right and repeat
            for(copyingto = solutionIndex; copyingto < listToEdit->indexOfLastEntryAdded;copyingto++)
              {
                copyingfrom = copyingto + 1;//overwrite with the contents of the solution to the right in the list
                
                listToEdit->listEntries[copyingto].numberOfDefinedValues =
                listToEdit->listEntries[copyingfrom].numberOfDefinedValues;
                
                listToEdit->listEntries[copyingto].score =
                listToEdit->listEntries[copyingfrom].score;
                for (row=0;row < N;row++)
                    listToEdit->listEntries[copyingto].variableValues[row] =
                    listToEdit->listEntries[copyingfrom].variableValues[row];
                
              }//end of copying loop
          }//end if code that deals with shuffling situation
        
      }//end of code for valid call
}//end of generic removefunction


//now we make a simple call to the generic function that hides all the complexity of calling with pointers etc.

void RemoveSolutionFromCurrentList(int solutionIndex)
{
    extern candidateList currentListOfCandidates;

    RemoveFromListParam1_CandidateSolutionAtIndexParam2(&currentListOfCandidates,solutionIndex);
}


//now this user call is jsut a wrapped up version of the generic form

void PrintWorkingCandidate()
{
    extern candidateSolution workingCandidate;
    PrintCandidateSolution(&workingCandidate);
}



/* void AddCandidateParam1_ToListParam2(candidateSolution * candidate, candidateList *listToChange)
 * generic version of a function to add a candidate solution to a list
 * first param is address of thing ot be added
 * second is addres of list ot add it to
 */

void AddCandidateParam1_ToListParam2(candidateSolution * candidate, candidateList *listToChange)
{
    int newpos; //get number of entries in list, loop variable for rows
    newpos = listToChange->indexOfLastEntryAdded+1;
    
    //error checking
    if(newpos ==SIZEOFSOLUTIONLIST)
        PrintThisMessageAndExit("can't add member - list is already full");
    
    //add the contents by using copy to overwrite the empty list entry
     CopySolutionParam1_IntoSolutionParam2(candidate,  &listToChange->listEntries[newpos]);
    //all done,  just now need to increment the counter in the list
    listToChange->indexOfLastEntryAdded = newpos;
    
}









//these two functions are just wrapped up to be easuer to use
void AddWorkingCandidateToOpenList(void)
{
    extern candidateList currentListOfCandidates;
    extern candidateSolution workingCandidate;
    AddCandidateParam1_ToListParam2(&workingCandidate,&currentListOfCandidates);
}


void AddWorkingCandidateToClosedList(void)
{
    extern candidateList listOfExaminedCandidates;
    extern candidateSolution workingCandidate;
    AddCandidateParam1_ToListParam2(&workingCandidate,&listOfExaminedCandidates);
    
}


/* 
*void ExtendWorkingCandidateByAddingValue(int value)
* function to add a new value on to the end if possible
* no return as all the error checking is done in house
*/
void ExtendWorkingCandidateByAddingValue(int newValue)
{
extern candidateSolution workingCandidate;
int currentLastPos=0;
//check it isn't already full
if (workingCandidate.numberOfDefinedValues==N)
	{ 
		PrintThisMessageAndExit (" can't add value to already full working candidate");
    }
else
 {
	 currentLastPos = workingCandidate.numberOfDefinedValues;
	 workingCandidate.variableValues[currentLastPos] = newValue;
	 workingCandidate.numberOfDefinedValues++;
 }


}



/* ChangeWorkingCandidateByReplaceValueinPlaceParam1_WithValueParam2(int positionToChange, int newValue)
* function TO Change a specific value in a solution ot a new one
* first param is index of value to change
* second is new value
* * no return as all the error checking is done in house
*/
void ChangeWorkingCandidateByReplaceValueinPlaceParam1_WithValueParam2(int positionToChange, int newValue)
{
extern candidateSolution workingCandidate;

    char errmessage[128] ;
//check we are trying to change  valid value that ha already been set
if (   (positionToChange >= workingCandidate.numberOfDefinedValues) || (positionToChange <0)  || (positionToChange >N)  )
  {
    sprintf(errmessage,"invalid value %d for positionToChange  passed to ChangeWorkingCandidate which has %d defined values...\n",positionToChange
            ,workingCandidate.numberOfDefinedValues);
	PrintThisMessageAndExit(errmessage);
  }
else
	workingCandidate.variableValues[positionToChange] = newValue;
}






