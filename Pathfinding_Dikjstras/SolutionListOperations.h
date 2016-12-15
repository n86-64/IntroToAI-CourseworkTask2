/**
@file  SolutionListOperations.h
@brief   functions that operate on solution lists

@author  Created by Jim Smith on 25/09/2014.
*  Copyright (c) 2014 James Smith. All rights reserved.
*/

#ifndef SolutionListOperations_h

#include "StructureDefinitions.h"

/*!
 @brief  Function used for error handling. Prints a message to screen and then exits the programme.
 
 @param message the string to be printed to screen (stdout) before the programme exits
 */
void PrintThisMessageAndExit(char *message);





/*!
 @brief function  to print the working candidate to screen
 
 Precondition: existence of global variable workingCandidate of type candidateSolution.
 Form of printout is problem-dependent
 */
void PrintWorkingCandidate();


/*!
 @brief function to find if a copy of a solution with the same values as the working candidate is already in a list, and if so where
 @param thislist pointer to a valid candidate list structure
 @return index of copy, NOTFOUND (-1) if not found
 Precondition: there is a global variable workingCandidate of type candidateSolution.
 
 Post-condition: programme will always exit: either with error message or with integer value of the copy
 */
 
int GetIndexOfWorkingCandidateInThisList(candidateList thislist);


/*!
 @brief  Function to "zero" the open and closed lists
 
Precondition: existence of two global variables: currentListOfCandidates and ListOfExaminedCandidates, both of type candidateList.

 
 Postcondition:  all entries in both arrays set to unused and indexOfLastEntryAdded set to UNUSED (-1).
 */
void CleanListsOfSolutionsToStart(void);
/*!
@brief  Function to initialise the structure holding the workingCandidate.
 
Will print error message and exit if this global variable does not exist or is not the right type.
 
 */
void CleanWorkingCandidate();


/*!
 @brief  Function to remove an entry from the structure holding the open list.
 
  Preconditions:
    (i) existence of  global variable: currentListOfCandidates  of type candidateList;
 (ii)    0 <= solutionIndex <=    currentListOfCandidates.indexOfLastEntryAdded .
 
 Postcondition: (i) Selected element of array removed;
 (ii) Value of indexOfLastEntryAdded decreased by one.
 
@param solutionIndex index of solution to remove from list
 */
void RemoveSolutionFromCurrentList(int solutionIndex);



/*!
 @brief  Copies the content of the selected member of the open list into the workingCandidate structure.
 
 Preconditions:
 (i) existence of  global variable: currentListOfCandidates  of type candidateList and workingCandidate of type candidateSolution;
 (ii)    0 <= solutionIndex <=    currentListOfCandidates.indexOfLastEntryAdded .
 
 Postconditions:  (i)   workingCandidate has new contents; (ii)  currentListOfCandidates is unchanged.
 
@param solutionIndex index of solution to copy from list.
 */
void CopySolutionFromCurrentListIntoWorkingCandidate(int solutionIndex);


/*!
@brief  Function to copy an entry from the workingCandidate into a new slot in the open list.

Precondition: (i) existence of  global variable: currentListOfCandidates  of type candidateList and workingCandidate of type candidateSolution.
  (ii) currentListOfCandidates.indexOfLastEntryAdded < SOLUTIONLISTSIZE

 Postconditions: (i)  workingCandidate unchanged; 
 (ii) copy of that solution added to the currentListOfCandidates in the next available slot;
(iii) Value of indexOfLastEntryAdded increased by one.
*/

void AddWorkingCandidateToCurrentList(void);






/*!
@brief  Function to copy an entry from the workingCandidate into a new slot in the closed list.
 
Precondition: (i) existence of  global variable: listOfExaminedCandidates  of type candidateList and workingCandidate of type candidateSolution;
 (ii) listOfExaminedCandidates.indexOfLastEntryAdded < SOLUTIONLISTSIZE
 
 Postconditions: (i)  workingCandidate unchanged;
 (ii) copy of that solution added to the listOfExaminedCandidates in the next available slot;
 (iii) Value of indexOfLastEntryAdded increased by one.

*/
void AddWorkingCandidateToExaminedList(void);


/*!
 @brief  Extends a partial solution by adding a new value
 
 Preconditions: (i) existence of global variable workingCandidate of type candidateSolution; (ii) workingCandidate is partial i.e. workingCandidate.numberOfDefinedValues <N.
 
 Postconditions: (i) workingCandidate.numberOfDefinedValues increased by 1; (ii) value added to array of variables. e.g. columnNumberfor next queen.

 @param newValue value to be added to partial solution  problem
 */
void ExtendWorkingCandidateByAddingValue(int newValue);



/*!
 @brief  Changes candidate solution but leaves its number of defined values unchanged
 
 Preconditions: (i) existence of global variable workingCandidate of type candidateSolution;
 (ii) workingCandidate is not empty i.e. workingCandidate.numberOfDefinedValues >0;  (iii) valid index i.e. 0<= positionToChange < workingCandidate.numberOfDefinedValues .
 
 Postconditions: (i) workingCandidate.numberOfDefinedValues unchanged; (ii) value added to array of variables. e.g. columnNumberfor next queen.
 
 @param positionToChange index of value to change.
 @param newValue         new value to put into the array at that index
 */
void ChangeWorkingCandidateByReplaceValueinPlaceParam1_WithValueParam2(int positionToChange, int newValue);


// these are some generic fuctions  I used to build the specific ones above
//  *****you shouldn't need to use them at this stage*******

/*!
 @brief  Function to copy contents of first solution into second
 

 Preconditions: (i) both parameters are valid pointers to candidate solutions.
 Postcondition (i) donor solution (from) unchanged; (ii)receiver solution (to) completely overwritten.
 
 
 @param from pointer to donor solution
 @param to   pointer to receiver
 */
void CopySolutionParam1_IntoSolutionParam2( candidateSolution *from, candidateSolution *to);


/*!
 @brief  Most general form of function to removes an entry (candidate solution) from a structure (candidateList).
 
 Preconditions:
 (i) pointers are to valid variables of the correct type.
 (ii)    0 <= solutionIndex <=    listToEdit->indexOfLastEntryAdded .
 
 Postcondition: (i) Selected element of array removed;
 (ii) Value of indexOfLastEntryAdded in listToEdit decreased by one.
 
 @param listToEdit    pointer to list to edit.
 @param solutionIndex index of solution to remove from list
 */
void RemoveFromListParam1_CandidateSolutionAtIndexParam2( candidateList *listToEdit, int solutionIndex);





/**
 @brief  Resets the contents of the structure holding a candidate solution so it is marked as  UNUSED
 
@param toBeCleaned address of candidate structure to clean
 */
void CleanCandidate( candidateSolution *toBeCleaned);



/*!
@brief  Function to copy a solution into a list.
 
Precondition: (i) both params are appropritate pointers to variables of correct type
 (ii) listOfExaminedCandidates.indexOfLastEntryAdded < SOLUTIONLISTSIZE
 
 Postconditions: (i)  toAdd unchanged;
 (ii) copy of toAdd added to receiver list in the next available slot;
 (iii) Value of indexOfLastEntryAdded in receiver list increased by one.
 
 @param toAdd    pointer to a candidateSolution
 @param receiver pointer to a candidateList
 */

void AddSolutionPram1_ToListParam2(candidateSolution *toAdd, candidateList *receiver);




#define SolutionListOperations_h ///<stops double inclusion


#endif
