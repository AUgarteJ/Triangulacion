#include "CSubset.h"
CSubset::CSubset()
{

}
CSubset::~CSubset()
{

}
void CSubset::addVertex(sPoint v)
{
  if(m_SubsetVector.size()<3)
     m_SubsetVector.push_back(v);
}