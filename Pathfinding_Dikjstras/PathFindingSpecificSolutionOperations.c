//
//  PathFindingSpecificSolutionOperations.c
//  Dijkstra
//
//  Created by Jim Smith on 05/11/2014.
//  Copyright (c) 2014 James Smith. All rights reserved.
//

#include "PathFindingSpecificSolutionOperations.h"






/* void PrintCandidateSolution (candidateSolution *solution)
 *  function to print to screen any candidate solution we choose
 *
 * This is the version for path-finding so we'll also call the function ot print a path
 * first parameter is the address of the candidate
 * all the error handling happens within the function so there is no return
 */
char temporaryMap[MAXX][MAXY];

void PrintCandidateSolution (candidateSolution * solution)
{

    int x,y,head;
      candidateSolution pathEndpoint;
    extern char currentMap[MAXX][MAXY];
    extern candidateList listOfExaminedCandidates, currentListOfCandidates;
    int parentIdx = 0;
    numberOfCellsVisited = 0;
  
    
    //check and exit if the solution does not exist
    if (solution == (candidateSolution *) NULL )
        //exit if it does not
        PrintThisMessageAndExit("tried to print a solution %d which is a non-valid index\n ");
    else
        //make a copy into our "endpoint"
        CopySolutionParam1_IntoSolutionParam2(solution, &pathEndpoint);
        
        
    CopyMap(currentMap,temporaryMap);//so we can mess around with the map if needed
    //write in the curent and closed lists
    for (head=0;head<listOfExaminedCandidates.indexOfLastEntryAdded; head++)
      {
        x = listOfExaminedCandidates.listEntries[head].variableValues[XCOORD];
        y = listOfExaminedCandidates.listEntries[head].variableValues[YCOORD];
        temporaryMap[x][y] = CLOSED;
      }
    for (head=0;head<currentListOfCandidates.indexOfLastEntryAdded; head++)
      {
        x = currentListOfCandidates.listEntries[head].variableValues[XCOORD];
        y = currentListOfCandidates.listEntries[head].variableValues[YCOORD];
        temporaryMap[x][y] = OPEN;
      }
    head = 1;
    //loop until  candidate position == entrance
    while (IsSolutionAtCoordinates(pathEndpoint, STARTX, STARTY)==0 )
      {
        //mark  candidate position on map as part of path
        if( head==1)
          {
            temporaryMap [ pathEndpoint.variableValues[XCOORD]][pathEndpoint.variableValues[YCOORD]] = 'H';
            head=0;
          }
        else
            temporaryMap [ pathEndpoint.variableValues[XCOORD]][pathEndpoint.variableValues[YCOORD]] = 'o';
        numberOfCellsVisited++;
        //find parent in closedList
        parentIdx = FindIndexInList_Param1_OfSolutionAtX_Param2_YParam3(listOfExaminedCandidates, pathEndpoint.variableValues[PARENTXCOORD], pathEndpoint.variableValues[PARENTYCOORD]);
        
        //if we did not the parent there is a problem
        if (parentIdx ==NOTFOUND)
            PrintThisMessageAndExit("problem in PrintCandidateSolution(): at to end of listOfExaminedCandidates without finding parent");
        else//otherwise  copy parent into path endpoint to move to it
            CopySolutionParam1_IntoSolutionParam2(&listOfExaminedCandidates.listEntries[parentIdx], &pathEndpoint);
        
        //go back to start of loop
      }
    temporaryMap[STARTX][STARTY] = 'o';
    //finally print out the map
    PrintMap(temporaryMap);
}





/* Update Distances of all unvisited neighbours of current working candidate */
void UpdateDistancesOfUnvisitedNeighboursOfWorkingCandidate(void)
{
    extern candidateSolution workingCandidate;
    extern candidateList currentListOfCandidates;
        extern char currentMap[MAXX][MAXY];
    float distanceMoved, currentEstimate, newEstimate;

    int newx=0, newy=0;
    int indexOfThisNeighbour = NOTFOUND;

    
    //go through each of the eight nearest neighbours in turn - so x+/- 1, y +/-1
    for( newx = workingCandidate.variableValues[XCOORD]-1; newx <= workingCandidate.variableValues[XCOORD]+1; newx ++ )
        for(newy=workingCandidate.variableValues[YCOORD]-1; newy <= workingCandidate.variableValues[YCOORD]+1; newy++)
          {
            //don't change where we are now
            if( newx==workingCandidate.variableValues[XCOORD] && newy==workingCandidate.variableValues[YCOORD])
                ;//do nothing
            //or obstacles
            else if (currentMap[newx][newy]== OBSTACLE)
                ; //do nothing
            //and to save time don't bother loloking if neighbour is out of bounds
            if (newx>= MAXX || newx < MINX || newy < MINY || newy >= MAXY)
                ; //do nothing
            // if we pass these tests it MIGHT be a valid unvisited cell
            else
              {
                indexOfThisNeighbour = FindIndexInList_Param1_OfSolutionAtX_Param2_YParam3(currentListOfCandidates, newx, newy);
                //don't do anything if its no longer unvisited
                if (indexOfThisNeighbour==NOTFOUND)
                    ;//do nothing
                else
                  {
                    //find out  our new distance estimate is lower
                    distanceMoved =(int) SQEUCLIDEAN_DISTANCE(newx, newy, workingCandidate.variableValues[XCOORD], workingCandidate.variableValues[YCOORD]);
                    newEstimate = workingCandidate.score + distanceMoved;
                    currentEstimate = currentListOfCandidates.listEntries[indexOfThisNeighbour].score;
                    if (newEstimate < currentEstimate)
                      {
                        //update distance
                       currentListOfCandidates.listEntries[indexOfThisNeighbour].score = newEstimate;
                        //and mark working candidate as the new parent
                        currentListOfCandidates.listEntries[indexOfThisNeighbour].variableValues[PARENTXCOORD] = workingCandidate.variableValues[XCOORD];
                        currentListOfCandidates.listEntries[indexOfThisNeighbour].variableValues[PARENTYCOORD] = workingCandidate.variableValues[YCOORD];
                      }
                        
                  }
              }
            
          }
    
 }


//this isthe function we call when the goal is found
void PrintFinalSolutionAndExit(void)
{
    //make sure we can access the proposed solution
    extern candidateSolution workingCandidate;
    int position;
    
    //check that working candidate should be at the exit
    if ( IsSolutionAtCoordinates(workingCandidate, ENDX, ENDY) != 1)
        PrintThisMessageAndExit("Error, path does not finish at end point");
 
        numberOfCellsVisited=0;
    
    //print the solution
    PrintWorkingCandidate();
    
    //CalculatePathLength
    //check this is the desired solution
    //if (    1==0)//dummy test for now
    //PrintThisMessageAndExit("sorry, this is not the final solution");
    
    //else //print in format to be automatically checked
      {
        printf("success: with path length %d cells \n", numberOfCellsVisited);
        position=0;
#ifndef FINALTEST
        while(position < (int)320000)
              position++;
#endif

      }
    exit(0);
    
}



/*  int IsSolutionAtCoordinates( candidateSolution *thisSol, int x, int y)
 * checks if a soltion is at a given position
 * params are soltion, x and y co-ordinates
 * return is 0 (false) or 1 (true)
 */
int IsSolutionAtCoordinates( candidateSolution thisSol, int x, int y)
{
    int result = 1;
    if ( thisSol.variableValues[XCOORD] != x)
        result = 0;
    if ( thisSol.variableValues[YCOORD] != y)
        result = 0;
    return result;

}



/* int FindIndexInList_Param1_OfSolutionAtX_Param2_YParam3( candidateList listToExamine, int x, int y)
* finds position in list of candidate solution at a given (x,y)location
* returns index or NOTFOUND
 */
int FindIndexInList_Param1_OfSolutionAtX_Param2_YParam3( candidateList listToExamine, int x, int y)
{
    int possibleIdx;
    //ok, might as well start at the back
    possibleIdx = listToExamine.indexOfLastEntryAdded;
    // and move forwards until we find the parent or reach the beginning of the list
    while(possibleIdx>=0 && IsSolutionAtCoordinates(listToExamine.listEntries[possibleIdx], x, y)==0  )
        possibleIdx--;
    
    if (possibleIdx <0)
        return NOTFOUND;
    else
        return possibleIdx;
    

}

