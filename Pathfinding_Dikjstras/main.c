/*
 * File:   main.c
 * Author: j4-smith
 *  Dijksatra path finding example in C
 * First Created on 5 November 2014, 18:42
 * Modified in light of student progress
 */


#include <stdio.h>
#include <stdlib.h>

#include "PathFindingSpecificDefinitions.h"
#include "StructureDefinitions.h"
#include "SolutionListOperations.h"

#include "PathFindingSpecificSolutionOperations.h"
#include  "worlds.h"


candidateSolution workingCandidate;//this one will hold the soltion we arecurrently considering
candidateList  currentListOfCandidates; // this list will store all the soltion we;ve created but not examined yet
candidateList listOfExaminedCandidates; // this is where we will store all the ones we're done with
                                        // this one is  a copy of the map we are currently examining

char currentMap[MAXX][MAXY]; //<===================NEW

//MAXX, MINX,MAXY,MINY are dimensions of the world
// STARTX, STARTY, ENDX, ENDY are the starting and ending positions


//=================================================
/* and here are some more useful functions I have written for you
  *
 * This is the only one which is different to before, and I have written it to save you time
 * It updates the distance estimates of unvisited neighbours of the current cell
 * void UpdateDistancesOfUnvisitedNeighboursOfWorkingCandidateNeighbours(void);
 *
 *  These final few are functions for manipulating maps that I am giving you to let you focus on the logic
 *  void   ReadComandLineAndSetMap(int argc, const char * argv[]);     <===============NEW
 *  void CopyMap( const char from[MAXX][MAXY], char to[MAXX][MAXY]);   <=============NEW ( but you don't need to use it)
 *  void PrintMap (char map[MAXX][MAXY]);                              <======== NEW (but you don't need to use it)
 *  this checks if a candidate soltuion is at a given co-ordinate
 * int IsSolutionAtCoordinates( candidateSolution thisSol, int x, int y);   <============== NEW
 *
 *  finally this macro tells you the distance between two points with x,y co-ordinates (a,b) and (c,d)
 *  #define SQEUCLIDEAN_DISTANCE(a,b,c,d)   ( (a-c)*(a-c) + (b-d)*(b-d))   <======================== NEW
 */
//************************ don't edit anything above this line***********************//


int main(int argc, const char * argv[])
{
    
    /* the next set of variables get used within our main function
     * but aren't declared globally becuase we don't want the other functions to change them inadvertently */
    
    int indexOfSolutionWeAreLookingAt; //index in list of current solution being examined
    int closestSoFar; //used to find which to move next   <=======NEW
    int closestEstimatedDistance; //used to find which to move next    <=======NEW
    int x,y; //<=====might be useful


                        //start off by emptying the lists of candidate solutions
    CleanListsOfSolutionsToStart();
    CleanWorkingCandidate();
    
    ReadComandLineAndSetMap(argc,argv);
    
    //this time we put all the unvisited cells that aren't obstacles into the open list to start
    // we could manage the list on-the-fly which might be faster if we have big map
    //to start off with everywhere except the start point has a huge estimated distance
	for (x = MINX; x < MAXX; x++) 
	{
		for (y = MINY; y < MAXY; y++) 
		{
			if (currentMap[x][y] != (char)OBSTACLE)
			{
				//build new node with these values
				//note that therte are four variables and I have #defined names for them to make the code more readable
				workingCandidate.variableValues[XCOORD] = workingCandidate.variableValues[PARENTXCOORD] = x;
				workingCandidate.variableValues[YCOORD] = workingCandidate.variableValues[PARENTYCOORD] = y;
				workingCandidate.numberOfDefinedValues = 4;

				if (x == STARTX && y == STARTY)
					workingCandidate.score = 0;
				else
					workingCandidate.score = BIGDIST;

				//add it to the open list
				AddWorkingCandidateToCurrentList();
				//andmarkthis cell on the map as open for graphical display
				currentMap[x][y] = OPEN;
			}
		}
	}
        
    
    //set the working candidate to the start position
    workingCandidate.variableValues[XCOORD] = workingCandidate.variableValues[PARENTXCOORD] = STARTX;
    workingCandidate.variableValues[YCOORD] = workingCandidate.variableValues[PARENTYCOORD] =  STARTY;
    workingCandidate.score = 0;

    PrintWorkingCandidate();
    
    //Now we will go into a while loop examining solutions until we get to the goal


    
    // end of  while loop dealing with search
    
    //if you are at the goal print out the ending message
    
    
    
    return 0;
}



