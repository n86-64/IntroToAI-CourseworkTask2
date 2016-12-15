/*
*  StructureDefinitions.h
*  
*  This is a header file where I define some problem-sepcific types such as structures
*  so that I can refer to things in my code using names that make sense in the context of the problem
*  Created by Jim Smith on 25/09/2014.
*  Copyright (c) 2014 James Smith. All rights reserved.
*/


// this line, with the ones at the bottom, stops the file and all its definitions being included in our source code twice
#ifndef Generic_StructureDefinitions_h
/**
 @file StructureDefinitions.h
 @brief Definitions of constant values and the data structures.
 */




#include "PathFindingSpecificDefinitions.h"


#define NOTFOUND -1
//============================
/**
 *  @brief Definition of struct datatype for candidate solution
 *
 * This is the definition of how we will represent each candidate solution
 *  and its associated information.
 *
 * Clearly this is problem-dependant
 */

typedef struct {
    int numberOfDefinedValues;///< how many variables in thre representation of a solution have their vales set
    int variableValues [N]; ///< and what  are they: for example if the queen in row 5 is in column 6 we set variableValues[5] = 6;
    int score; ///< measure of how infeasible the solution is - more is worse for minimisation,  e.g. NQueens
} candidateSolution;

/**
 @brief  Definition of a datatype for a list of candidate solutions
 
  Datatype to hold a collection of  candidate solutions in the form of an array
 along with a  variable that tells us the array index of the last entry in the list.
 
 NOTE  that it is intended that all add/remove actions are done via the provided functions so that the internal counter of the numer of entries is kept correct
 */
typedef struct {
    candidateSolution listEntries[SIZEOFSOLUTIONLIST]; ///< The array of candidate solutions
    int indexOfLastEntryAdded; ///< Index in array of last member used: this is automatically incremented and decremented by my functions
} candidateList;




// this line stops any problems with double-inclusion of this header file
#define Generic_StructureDefinitions_h


#endif
