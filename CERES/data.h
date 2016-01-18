#ifndef DATA_H
#define DATA_H
#include <vector>
#include <iostream>
#include <math.h>
#include <random>
#include <bitset>

using namespace std;

class Element{
public:
  Element (const float& nn=0,const float& err=0)
  {
    _num=nn;_errRate=err;
    //cout<<"Construting Element ... "<<_num<<" and err "<<_errRate<<endl;
  }
  Element operator + (const Element& n) const 
  {
      float result=_num+n._num;
      result = mask(result,_errRate);
    return Element(result,_errRate); 
  }
  Element operator - (const Element& n) const 
  {
      float result=_num-n._num;
      result = mask(result,_errRate);
    return Element(result,_errRate); 
  }
  Element operator * (const Element& n) const 
  { 
    float result=_num*n._num;
      result = mask(result,_errRate);
    return Element(result,_errRate);  
  }
  
  Element operator / (const Element& n) const 
  { 
    float result=_num/n._num;
      result = mask(result,_errRate);
    return Element(result,_errRate);  
  }
  
  Element operator & (const Element& n) const 
  { 
    float result=(int)_num&(int)n._num;
      result = mask(result,_errRate);
    return Element(result,_errRate);  
  }

   Element& operator += (const Element& n) 
   {
      float result=_num+n._num;
      _num = mask(result,_errRate);  
      return (*this); 
   }

   Element& operator = (const Element& n)
   {
      _num=n._num;
      _errRate=n._errRate;
      return (*this);
   }
    bool operator < (const Element& n)
   {
      return ( _num < n._num);
   }
   void setErr(const float &rr){_errRate=rr;}

   void Sigmoid()
   {
      //cout << "**********" << _errRate << " * " << pow(_errRate, 1.0/3.0) << endl;
      float result = (-1)*_num;
      result = mask(result,_errRate);
      result = (1+exp(result));
      result = mask(result,_errRate);
      result = (double)1/result;
      //float result = (double)1/(1+exp(-1*_num));
      //_num = mask(result,_errRate);
      _num = mask(result,_errRate);
   }

   float _num;
   float _errRate;

  /* Element operator - (const Element& n) const { return Element(_num-n._num); }
   Element& operator -= (const Element& n) { _num-=n._num; return (*this); }
   Element operator * (const Element& n) const { return Element(_num*n._num); }
   Element& operator *= (const Element& n) { _num*=n._num; return (*this); }
   bool operator == (const Element& n) const { return (_num==n._num); }
   bool operator != (const Element& n) const { return (_num!=n._num); }
   Element& operator = (const Element& n) { _num=n._num; return (*this); }*/
private:
  float mask(  float ff, const float&  err) const
  {
    float after;
    bitset<32> faultbit;

      std::random_device rd;
      std::mt19937 gen(rd());
      std::uniform_real_distribution<float> distribution(0.0,1.0);
      float number = distribution(gen);
      
      size_t bit_location = rand() % 32;  // 23 for only fraction

      //cout<<"add Masking..."<<"number "<<number<<"and err "<<err<<endl;
      
      if (err>number)
      {
        //cout<<ff<<" entering inject..."<<endl;
        //cout<<"Inserting faults at "<<bit_location<<endl;
        faultbit[bit_location]=1;
        //cout<<faultbit<<endl;
      }
      else
        after=ff;

      int faultMask=int(faultbit.to_ulong());

      int qq=*(int*)(&ff);

      int inter=faultMask ^ qq;

      after = *(float*)(&inter);

    return after;
  }
  float mask(  float ff, const float&  err)
{
    float after;
    bitset<32> faultbit;

      std::random_device rd;
      std::mt19937 gen(rd());
      std::uniform_real_distribution<float> distribution(0.0,1.0);
      float number = distribution(gen);

      //cout<<"muti Masking..."<<"number "<<number<<"and err "<<err<<endl;
      
      size_t bit_location = rand() % 32;  // 23 for only fraction
      
      if (err>number)
      {
        //cout<<ff<<" entering inject..."<<endl;
        //cout<<"Inserting faults at "<<bit_location<<endl;
        faultbit[bit_location]=1;
        //cout<<faultbit<<endl;
      }
      else
        after=ff;

      int faultMask=int(faultbit.to_ulong());

      int qq=*(int*)(&ff);

      int inter=faultMask ^ qq;

      after = *(float*)(&inter);

    return after;
  }
};

class Data{
public:
  Data(float* gg,const int & d,const float& err=0);
  ~Data();
  Element dotComp(Data* other);


  vector<Element*> _elements;
  int _dim;
  //float _errRate;  necessary!?
};
#endif
