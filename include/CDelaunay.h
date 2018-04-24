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

#include <iostream>
#include <vector>

struct sPoint 
{
  int x, y;
};

vector<sPoint> vPointsList;

class CDelaunay {

  CDelaunay();
  ~CDelaunay();

  vector<sPoint>fillPoints(int iNumPoints);
  vector<sPoint>sortingPoints(vector<sPoint> filledPointsList);

  

};