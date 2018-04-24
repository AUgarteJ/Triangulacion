#pragma once
#include <vector>


struct sPoint
{
  int x = 0, y = 0 , z = 0;
};

struct sCircle
{
  sPoint m_Center;
  float m_dRadius;
};

struct sEdge
{
  sPoint a;
  sPoint b;
  float magnitude;
};
class CSubset
{
public:

  std::vector <sPoint> m_SubsetVector;


  CSubset();
  ~CSubset();
  void addVertex(sPoint v);
 
  

};
static float length(sPoint a, sPoint b)
{
  float lenght;
  float x;
  float y;
  x = pow(a.x - b.x, 2);
  y = pow(a.y - b.y, 2);
  lenght = sqrt(x + y);
 // lenght= sqrt((pow((a.x - b.x), 2)) + ( pow((a.y - b.y), 2)));
 //lenght = abs(lenght);
  return  lenght;
}