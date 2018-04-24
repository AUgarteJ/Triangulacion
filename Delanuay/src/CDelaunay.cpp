#include "CDelaunay.h"
#include <gtest/gtest.h>

#include <time.h>
#include <algorithm>
#include <conio.h>
#include <math.h>

CDelaunay::CDelaunay()
{

}

CDelaunay::~CDelaunay()
{

}

void CDelaunay::swapPoints(sPoint *a, sPoint *b)
{
  sPoint temp = *a;
  *a = *b;
  *b = temp;


}

void CDelaunay::swapPointsInt(int *a, int *b)
{
  int temp = *a;
  *a = *b;
  *b = temp;


}

std::vector<sPoint> CDelaunay::fillPoints(int iNumPoints)
{
  sPoint Temp;
  std::vector<sPoint> vPoints;

  srand(time(NULL));

  for (int i = 0; i < iNumPoints; i++)
  {
    Temp.x = (rand() % 10) + 5;// 00) + 50;
    Temp.y = (rand() % 10) +1;// 600) + 50;
    vPoints.push_back(Temp);
  }

  return vPoints;
}

// Optimized implementation of Bubble sort

std::vector<sPoint> CDelaunay::bubbleSort(std::vector<sPoint> pointList, int iNumPoints)
{
  int i, j;
  bool swapped;
  for (i = 0; i < iNumPoints - 1; i++)
  {
    swapped = false;
    for (j = 0; j < iNumPoints - i - 1; j++)
    {
      if (pointList[j].x == pointList[j + 1].x)
      {
        if (pointList[j].y > pointList[j + 1].y)
          swapPoints(&pointList[j], &pointList[j + 1]);
        swapped = true;
      }

      if (pointList[j].x > pointList[j + 1].x)
      {
        swapPoints(&pointList[j], &pointList[j + 1]);
        swapped = true;
      }
    }

    // IF no two elements were swapped by inner loop, then break
    if (swapped == false)
      break;
  }

  m_vPointLists = pointList;

  return m_vPointLists;
}

std::vector<int> CDelaunay::bubbleSortInt(std::vector<int> intList, int iNumPoints)
{
  int i, j;
  bool swapped;
  for (i = 0; i < iNumPoints - 1; i++)
  {
    swapped = false;
    for (j = 0; j < iNumPoints - i - 1; j++)
    {

      if (intList[j] > intList[j + 1])
      {
        swapPointsInt(&intList[j], &intList[j + 1]);
        swapped = true;
      }
    }

    // IF no two elements were swapped by inner loop, then break
    if (swapped == false)
      break;
  }



  return intList;
}

void CDelaunay::partitionPoints()
{
  int index;
  int count = 0;
  CSubset temp;
  std::vector<int> indexVector;

  if (m_vPointLists.size() < 3)
    return;

   else
  {
   
   
    index = (m_vPointLists.size()) / 2;
    indexVector.push_back(index);
    int indexCount=0;
    indexCount++;
    int i = 0;
    while (index > 2)
    {
      
      
      index /= 2;
      for (i = 0; i < indexCount; i++)
      {
        
        indexVector.push_back(indexVector[i] + index);
           
      }
      indexVector.push_back(index);
      indexCount = indexVector.size();
    }

  }
  indexVector.push_back((m_vPointLists.size() - 1));
  indexVector = bubbleSortInt(indexVector, indexVector.size());


  int contIndx = 0;
  int currentIndex = indexVector[contIndx];
  for (int i = 0; i < m_vPointLists.size(); i++)
  {
    currentIndex = indexVector[contIndx];
    temp.addVertex(m_vPointLists[i]);


    if (i == currentIndex)
    {
      m_SubsetList.push_back(temp);
      temp.m_SubsetVector.clear();
      contIndx++;
      //currentIndex = indexVector[contIndx];
    }
  }
  edgesSubsets();
  nearEdges();
}

sCircle CDelaunay::circleFromPoints(sPoint *pt1, sPoint *pt2, sPoint *pt3)
{
  sCircle thisCircle;

  float yDelta_a = pt2->y - pt1->y;
  float xDelta_a = pt2->x - pt1->x;
  float yDelta_b = pt3->y - pt2->y;
  float xDelta_b = pt3->x - pt2->x;

  if (fabs(xDelta_a) <= 0.000000001 && fabs(yDelta_b) <= 0.000000001) {

    thisCircle.m_Center.x = 0.5*(pt2->x + pt3->x);
    thisCircle.m_Center.y = 0.5*(pt1->y + pt2->y);
    thisCircle.m_Center.z = pt1->z;
    thisCircle.m_dRadius = length(thisCircle.m_Center, *pt1);		// calc. radius


    return thisCircle;
  }
  // IsPerpendicular() assure that xDelta(s) are not zero
  float aSlope = yDelta_a / xDelta_a; // 
  float bSlope = yDelta_b / xDelta_b;
  if (fabs(aSlope - bSlope) <= 0.000000001) {	// checking whether the given points are colinear. 	
    thisCircle.m_dRadius = -1;
    return thisCircle;
  }


  // calc center
  thisCircle.m_Center.x = (aSlope*bSlope*(pt1->y - pt3->y) + bSlope*(pt1->x + pt2->x)
    - aSlope*(pt2->x + pt3->x)) / (2 * (bSlope - aSlope));
  thisCircle.m_Center.y = -1 * (thisCircle.m_Center.x - (pt1->x + pt2->x) / 2) / aSlope + (pt1->y + pt2->y) / 2;
  thisCircle.m_Center.z = pt1->z;

  thisCircle.m_dRadius = length(thisCircle.m_Center, *pt1);		// calc. radius
                                              //	TRACE(" Center: %f %f %f\n", m_Center.x(), m_Center.y(), m_Center.z());
                                              //	TRACE(" radius: %f %f %f\n", length(&m_Center,pt1), length(&m_Center,pt2),length(&m_Center,pt3));
  return thisCircle;
}

void CDelaunay::edgesSubsets()
{
  sEdge temp;
  for (int i = 0; i < m_SubsetList.size(); i++)
  {
    for (int j = 0; j < m_SubsetList[i].m_SubsetVector.size(); j++)
    {
      if (j == m_SubsetList[i].m_SubsetVector.size() - 1)
      {
        temp.a.x = m_SubsetList[i].m_SubsetVector[j].x;
        temp.a.y = m_SubsetList[i].m_SubsetVector[j].y;

        temp.b.x = m_SubsetList[i].m_SubsetVector[0].x;
        temp.b.y = m_SubsetList[i].m_SubsetVector[0].y;

        m_vEdges.push_back(temp);
        break;
        
      }
      else if (m_SubsetList[i].m_SubsetVector.size() == 2)
      {
        temp.a.x = m_SubsetList[i].m_SubsetVector[j].x;
        temp.a.y = m_SubsetList[i].m_SubsetVector[j].y;

        temp.b.x = m_SubsetList[i].m_SubsetVector[j+1].x;
        temp.b.y = m_SubsetList[i].m_SubsetVector[j+1].y;
        m_vEdges.push_back(temp);
        break;
      }


      temp.a.x = m_SubsetList[i].m_SubsetVector[j].x;
      temp.a.y = m_SubsetList[i].m_SubsetVector[j].y;

      temp.b.x = m_SubsetList[i].m_SubsetVector[j+1].x;
      temp.b.y = m_SubsetList[i].m_SubsetVector[j+1].y;
      m_vEdges.push_back(temp);
    }
   
 }
  
}

void CDelaunay::nearEdges()
{ 
  sEdge temp;
  sEdge subsetNeartesEdge;
  std::vector <sEdge> posibleEdges;
  for (int i = 0; i < m_SubsetList.size()-1; i+=2)
  {
    for (int j = 0; j < m_SubsetList[i].m_SubsetVector.size(); j++)
    {
      temp = subsetIterator(m_SubsetList[i].m_SubsetVector[j], i + 1);
      posibleEdges.push_back(temp);
    }

    subsetNeartesEdge = posibleEdges[0];
      for (int l = 0; l < posibleEdges.size(); l++)
        {
          if (posibleEdges[l].magnitude < subsetNeartesEdge.magnitude)
          subsetNeartesEdge = posibleEdges[l];
         }
      m_vSubsetNearEdges.push_back(subsetNeartesEdge);
      m_vEdges.push_back(subsetNeartesEdge);
      posibleEdges.clear();
  }
  

}

sEdge CDelaunay::subsetIterator(sPoint point,int i)
{
  float temp;
  float nearest;
  sEdge nearestEdge;
  nearestEdge.a.x = point.x;
  nearestEdge.a.y = point.y;
  nearestEdge.b.x = m_SubsetList[i].m_SubsetVector[0].x;
  nearestEdge.b.y = m_SubsetList[i].m_SubsetVector[0].y;
  nearest= length(m_SubsetList[i].m_SubsetVector[0], point);
  nearestEdge.magnitude = nearest;
  for (int k = 0; k < m_SubsetList[i].m_SubsetVector.size(); k++)
  {

    temp = length(m_SubsetList[i].m_SubsetVector[k], point);
    if (temp < nearest)
    {
      nearest = temp;
      nearestEdge.b.x = m_SubsetList[i].m_SubsetVector[k].x;
      nearestEdge.b.y = m_SubsetList[i].m_SubsetVector[k].y;
      nearestEdge.magnitude = temp;
    }

  }

  return nearestEdge;
}





