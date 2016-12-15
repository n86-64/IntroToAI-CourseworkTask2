/**
 @file  PathFindingSpecificSolutionOperations.h
 @brief   functions that operate on candidate solutions that are specific to the path-finding task
 
 @author  Created by Jim Smith on 11/11/2015.
 *  Copyright (c) 2014 James Smith. All rights reserved.
 */


#ifndef __Dijkstra__PathFindingSpecificSolutionOperations__
#define __Dijkstra__PathFindingSpecificSolutionOperations__

#include <stdio.h>
#include <stdlib.h>
#include "PathFindingSpecificDefinitions.h"
#include "StructureDefinitions.h"
#include "PathFindingSpecificSolutionOperations.h"
#include "SolutionListOperations.h"
#include "worlds.h"


//this one updates the distance estimates of unvisited neighbours ofthe current cell
/*!
 @brief  updates the distance estimates of cells that are in the open list and are unvisited neighbours ofthe current cell
 
 Assumes the existnace of a variable of type candidateSolution called workingCandidate
 Assumes the existience of a variable of type candidateList called currentListOfCandidates
 Assumes the existence of a 2D cahr array called currentMap
 
 
 */void UpdateDistancesOfUnvisitedNeighboursOfWorkingCandidate(void);

//this isthe function we call when the goal is found
//calls a print function  both are problem specific
//and use the int
int numberOfCellsVisited ; ///<what it isays on the can - used to test implementation
/*!
 @brief  call this function once you have found the goal
 */void PrintFinalSolutionAndExit(void);

/*!
 @brief  prints out a current working candidate in the form of a map showing the current position (H), and the route from the start by followionfg parent cells backwards, and
 all the other poitns visitied that are not on the current route
 @param solution soliution to be illustrated
 */void PrintCandidateSolution (candidateSolution * solution);


/*!
 @brief  checks if a candidafe soltuion is at a given co-ordinate
 
 @param thisSol point ot check
 @param x       x coordinate to check against
 @param y       y co-ordinate ot check against
 
 @return 1 if true or 0 if not
 */int IsSolutionAtCoordinates( candidateSolution thisSol, int x, int y);

/*!
 @brief  finds position in list of candidate solution at a given (x,y)location
 

 
 @param listToExamine list to search through
 @param x             x location to look for
 @param y             y location to look for
 
 @return  index in list of solition at the point given,  or NOTFOUND if the solution meeting those conditions is not present
 */int FindIndexInList_Param1_OfSolutionAtX_Param2_YParam3( candidateList listToExamine, int x, int y);

#endif /* defined(__Dijkstra__PathFindingSpecificSolutionOperations__) */
