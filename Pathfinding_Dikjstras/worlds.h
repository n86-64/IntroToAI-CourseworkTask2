//
//  worlds.h
//  Dijkstra
// holds maps of the worlds to be used ot test the pah-finding algorithm
//  Created by Jim Smith on 05/11/2014.
//  Copyright (c) 2014 James Smith. All rights reserved.
//
/**
 @file worlds.h
 @brief Definitions of seach maps and some functions to manipulate them
 */
#ifndef Dijkstra_worlds_h
#define Dijkstra_worlds_h

//to make things easier we will use fixed sized worlds
#define MINX 0
#define MINY 0
#define MAXX 20
#define MAXY  20

#define OBSTACLE '#' ///<ascii char for filled square
#define OCCUPIED '-' ///<ascii char for square with something on it
#define CLOSED '-' ///< ascii char for visited square
#define OPEN '.'   ///<ascii char for unvisited square

#define STARTX  5
#define STARTY MINY
#define ENDX  15
#define ENDY (MAXY -1)



/**
 *  function to copy contents of one map into another
 *
 *  @param from "DONOR" 2d array of chars of fixed size MAXX x MAXY
 *  @param to   "RECEIVER" 2d array of chars of fixed size MAXX x MAXY
 */
void CopyMap( const char from[MAXX][MAXY], char to[MAXX][MAXY]);
/**
 *  function that prints the contents oif a map to stdout (usually the screen)
 *
 *  @param map 2D arrays of chars to be printed out
 */
void PrintMap (char map[MAXX][MAXY]);
/**
 *  function to interpret command line options as choice of which map to use
 *
 *  @param argc number of string tokens on comand line
 *  @param argv array of strings holding the command line broken down into tokens
 */
void   ReadComandLineAndSetMap(int argc, const char * argv[]);
#endif
