/*!
\file CDelauney.h
\author Alberto Flores Guzmán
\brief Declares the Delaunay trianguling functions 
\date 26-03-18

\details Declares a Delauney class,  and contains
sorting  operations

\version 1.0
\copyright Alberto Flores Guzmán
*/

#pragma once

#include "CSubset.h"
#include <iostream>
#include <vector>





class CDelaunay {

public:
  CDelaunay();
  ~CDelaunay();

public:
  std::vector<sPoint> m_vPointLists;
  std::vector<sEdge>  m_vEdges;
  std::vector<sEdge>  m_vSubsetNearEdges;
  std::vector<CSubset> m_SubsetList;

public:
  void swapPoints(sPoint *a, sPoint *b);
  void swapPointsInt(int *a, int *b);
  std::vector<sPoint>fillPoints(int iNumPoints);
  std::vector<sPoint> bubbleSort(std::vector<sPoint> pointList, int iNumPoints);
  std::vector<int> CDelaunay::bubbleSortInt(std::vector<int> intList, int iNumPoints);
  void partitionPoints();
  sCircle circleFromPoints(sPoint *pt1, sPoint *pt2, sPoint *pt3);
  std::vector<sPoint>sortingPoints(std::vector<sPoint> filledPointsList);
  void edgesSubsets();
  void nearEdges();
 sEdge subsetIterator(sPoint point, int i);


};

