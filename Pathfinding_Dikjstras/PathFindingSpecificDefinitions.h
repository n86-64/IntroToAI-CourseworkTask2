/**
 @file  PathFindingSpecificDefinitions.h
 @brief   useful definitions that are specific to the path-finding problem
 
 @author  Created by Jim Smith on 11/11/2015.
 *  Copyright (c) 2015 James Smith. All rights reserved.
 */

#ifndef Dijkstra_PathFindingSpecificDefinitions_h
#define Dijkstra_PathFindingSpecificDefinitions_h

#ifndef UNUSED
#define UNUSED -1
#endif

#ifndef BIGDIST
#define BIGDIST  ( (MAXX - MINX)*(MAXX- MINX) + (MAXY - MINY)*(MAXY - MINY) +10)
#endif

#ifndef XCOORD
#define XCOORD 0
#endif

#ifndef YCOORD
#define YCOORD 1
#endif

#ifndef PARENTXCOORD
#define PARENTXCOORD 2
#endif

#ifndef PARENTYCOORD
#define PARENTYCOORD 3
#endif

#ifdef N
#undef N
#endif

#define N 4

#ifndef SIZEOFSOLUTIONLIST
#define SIZEOFSOLUTIONLIST 1000
#endif


#ifndef SQEUCLIDEAN_DISTANCE
#define SQEUCLIDEAN_DISTANCE(a,b,c,d)  ( ((a-c)*(a-c)) + ( (b-d)*(b-d)))
#endif


#endif
