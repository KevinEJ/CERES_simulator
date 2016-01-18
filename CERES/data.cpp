#include "data.h"
#include <iostream>

using namespace std;

Data::Data(float* gg,const int & d,const float & err)
{

	_dim=d;
	for(int i =0;i<d;++i)
	{
		Element* ee=new Element(gg[i],err);
		_elements.push_back(ee);
		//cout<<"Pushing "<<_elements[i]->_num<<endl;
	}
}

Data::~Data()
{
	for (unsigned int i=0;i<_elements.size();++i)
	{
		delete _elements[i];
		_elements[i]=0;
	}
	_elements.clear();
}

Element Data::dotComp(Data* other)
{
	Element result;
	if (other->_dim!=_dim)
	{
		cerr<<"Dimension unmatched !!"<<endl;
		return 0;
	}
	for(int i=0;i<_dim;++i)
	{
		result += (*_elements[i])*(*(other->_elements[i]));		
	}
	return result;
}

float* convertNum(const int& num,const int& base)
{
  float* out=new float [3];
  int count=0;
  int sign=1;
  int mod;
  int divi=num;
  
  do
  {
    mod=divi%base;
    divi/=base;
    if (mod>=10) 
    {
      out[count]=mod-10;
    }
    else
    {
      out[count]=mod-0;
    } 
    ++count;
  }
  while (count!=3);
  return out;
}