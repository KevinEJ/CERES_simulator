/********************
	User Interface
*********************/
#ifndef USER_DEFINE
#define USER_DEFINE

#include <vector>
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <complex>
#include "data.h"

using namespace std;

#define DATA_LENGTH 1
#define Input_number 10
class TaskData { 
public:
  TaskData(){errRate_data = 0;};
  void setErr(const float& rr)
  {
    errRate_data=rr;
  }
    vector<Element> m_ceres; // #
    vector<Element> m_final; // #
    vector<bool>   m_success; //#

  /******************************************
    define other datamember here

    if u have ptr datamember for calculation, 
    u have to write copy constructor urself
  ******************************************/
  vector<Element>  m_buffer ;
  vector<Element>* m_inputs[Input_number] ;
  char * message;
  float errRate_data;

} ;

	
void FFT(Element *, Element * , unsigned int , float) ;
void FFT_2(Element *, Element * , unsigned int , float) ;
void DFT (int, TaskData*);


void* task1_kernel(void* threadarg)
{
  /*-----------------
    don't touch
  -----------------*/
    TaskData* my_data_ptr = (TaskData*)threadarg;
    float err= my_data_ptr->errRate_data;
    printf("err = %f \n" , err);
   
    Element* a = new Element(10 , err) ; 
    Element* b = new Element(1 , err) ; 
    for(int i = 0 ; i < 10000 ; i++){
        *a += *b ; 
    }
    my_data_ptr->m_ceres.push_back(*a );
 
}
void* task0_kernel(void* threadarg)
{
  /*-----------------
    don't touch
  -----------------*/
    TaskData* my_data_ptr = (TaskData*)threadarg;
    float err= my_data_ptr->errRate_data;
    printf("err = %f \n" , err);
   
    Element* a = new Element(10 , err) ; 
    Element* b = new Element(1 , err) ; 
    for(int i = 0 ; i < 100 ; i++){
        *a += *b ; 
    }
    my_data_ptr->m_ceres.push_back(*a );
 
}
void* task2_kernel(void* threadarg)
{
  /*-----------------
    don't touch
  -----------------*/
    TaskData* my_data_ptr = (TaskData*)threadarg;
    float err= my_data_ptr->errRate_data;
    printf("err = %f \n" , err);
    int lenghth = 256 ; 
    int logN    = 8   ;
    Element* real = new Element[lenghth];
    Element* im   = new Element[lenghth];

    for(int i = 0 ; i < lenghth ; i++){
      Element* temp_1 = new Element(0,err);
      Element* temp_2 = new Element(i,err);
      real[i] = *temp_2;
      im[i] = *temp_1;
    }
    FFT_2(real , im , logN  , err)  ;
    Element* temp = new Element(0,0) ;
    for(int i = 0 ; i < lenghth ; i++){
      *temp += real[i] ;
      *temp += im[i] ;
    } 
    my_data_ptr->m_ceres.push_back(*temp );
 
}
void* task3_kernel(void* threadarg)
{
  /*-----------------
    don't touch
  -----------------*/
    TaskData* my_data_ptr = (TaskData*)threadarg;
    float err= my_data_ptr->errRate_data;
    printf("err = %f \n" , err);
    int lenghth = 1024 ; 
    int logN    = 10   ;
    Element* real = new Element[lenghth];
    Element* im   = new Element[lenghth];

    for(int i = 0 ; i < lenghth ; i++){
      Element* temp_1 = new Element(0,err);
      Element* temp_2 = new Element(i,err);
      real[i] = *temp_2;
      im[i] = *temp_1;
    }
    FFT_2(real , im , logN  , err)  ;
    Element* temp = new Element(0,0) ;
    for(int i = 0 ; i < lenghth ; i++){
      *temp += real[i] ;
      *temp += im[i] ;
    } 
    my_data_ptr->m_ceres.push_back(*temp );
 
}
void* task4_kernel(void* threadarg)
{
  /*-----------------
    don't touch
  -----------------*/
    TaskData* my_data_ptr = (TaskData*)threadarg;
    float err= my_data_ptr->errRate_data;
    printf("err = %f \n" , err);
    int lenghth = 2048 ; 
    int logN    = 12   ;
    Element* real = new Element[lenghth];
    Element* im   = new Element[lenghth];

    for(int i = 0 ; i < lenghth ; i++){
      Element* temp_1 = new Element(0,err);
      Element* temp_2 = new Element(i,err);
      real[i] = *temp_2;
      im[i] = *temp_1;
    }
    FFT_2(real , im , logN  , err)  ;
    Element* temp = new Element(0,0) ;
    for(int i = 0 ; i < lenghth ; i++){
      *temp += real[i] ;
      *temp += im[i] ;
    } 
    my_data_ptr->m_ceres.push_back(*temp );
 
}
void* task5_kernel(void* threadarg)
{
  /*-----------------
    don't touch
  -----------------*/
    TaskData* my_data_ptr = (TaskData*)threadarg;
    float err= my_data_ptr->errRate_data;
    printf("err = %f \n" , err);
    int lenghth = 4 ; 
    int logN    = 2   ;
    Element* real = new Element[lenghth];
    Element* im   = new Element[lenghth];

    for(int i = 0 ; i < lenghth ; i++){
      Element* temp_1 = new Element(0,err);
      Element* temp_2 = new Element(i,err);
      real[i] = *temp_2;
      im[i] = *temp_1;
    }
    FFT_2(real , im , logN  , err)  ;
    Element* temp = new Element(0,0) ;
    for(int i = 0 ; i < lenghth ; i++){
      *temp += real[i] ;
      *temp += im[i] ;
    } 
    my_data_ptr->m_ceres.push_back(*temp );
 
}
void* task6_kernel(void* threadarg)
{
  /*-----------------
    don't touch
  -----------------*/
    TaskData* my_data_ptr = (TaskData*)threadarg;
    float err= my_data_ptr->errRate_data;
    printf("err = %f \n" , err);
    int lenghth = 16 ; 
    int logN    = 4   ;
    Element* real = new Element[lenghth];
    Element* im   = new Element[lenghth];

    for(int i = 0 ; i < lenghth ; i++){
      Element* temp_1 = new Element(0,err);
      Element* temp_2 = new Element(i,err);
      real[i] = *temp_2;
      im[i] = *temp_1;
    }
    FFT_2(real , im , logN  , err)  ;
    Element* temp = new Element(0,0) ;
    for(int i = 0 ; i < lenghth ; i++){
      *temp += real[i] ;
      *temp += im[i] ;
    } 
    my_data_ptr->m_ceres.push_back(*temp );
    
}


void FFT(Element *real, Element *im , unsigned int logN = 10 , float err = 0 ) // logN is base 2 log(N)
{

    //const double MINPI = 3.1415926 ;
    //unsigned int logN = 10 ;  
    //unsigned int n=0, nspan, span, submatrix, node;
    //unsigned int N = 1<<logN;
    //double temp, primitive_root, angle, realtwiddle, imtwiddle;
 printf("FFT _ 1 \n");
    Element* MINPI = new Element(3.1415926 , err);
    Element* n  = new Element(0 , err) ; 
    Element* nspan  = new Element(0 , err) ; 
    Element* span   = new Element(0 , err) ; 
    Element* submatrix  = new Element(0 , err) ; 
    Element* node  = new Element(0 , err) ; 
    Element* N  = new Element( 1<<logN , err) ; 
    
    Element* temp= new Element(0 , err) ; 
    Element* primitive_root = new Element(0 , err) ; 
    Element* angle = new Element(0 , err) ; 
    Element* realtwiddle  = new Element(0 , err) ; 
    Element* imtwiddle  = new Element(0 , err) ; 

    Element* const_2 = new Element(2 , err);
    Element* const_1 = new Element(1 , err);
  //printf("FFT _ 2 \n");
    for(*span=(*N)/(*const_2); (int)(span->_num); *span=(*span)/(*const_2))      // loop over the FFT stages
    {
       *primitive_root = (*MINPI)/(*span);     // define MINPI in the header
  //printf("FFT _ 3 \n");
       
       for( ; (*submatrix)<((*N)/(*const_2))/(*span); (*submatrix) = *submatrix + (*const_1))
       {
  //printf("FFT _ 4 \n");
          for( ; (*node)<(*span); (*node) = (*node) + (*const_1))
          {
  //printf("FFT _ 5 \n");
 // //printf(" n = %f  \n" , n->_num );
 //printf(" nspan = %f  \n" , nspan->_num );
 //printf(" span = %f  \n" , span->_num );
            
            if(span->_num >= 16 ) break ;
            if(nspan->_num >= 16 ) break ;
            if(n->_num >= 16 ) break ;
            
            (*nspan) = *n+(*span);
            *temp = real[(int)n->_num] + real[(int)nspan->_num];       // additions & subtractions
            real[(int)nspan->_num] = real[(int)n->_num]-real[(int)nspan->_num];
            real[(int)n->_num] = *temp;
            *temp = im[(int)n->_num] + im[(int)nspan->_num];
            im[(int)nspan->_num] = im[(int)n->_num] - im[(int)nspan->_num];
            im[(int)n->_num] = *temp;
            
  //printf("FFT _ 6 \n");
            *angle = (*primitive_root) * (*node);      // rotations
            *realtwiddle = cos((int)angle->_num);
            *imtwiddle = sin((int)angle->_num);
            *temp = (*realtwiddle) * real[(int)nspan->_num] - (*imtwiddle) * im[(int)nspan->_num];
            im[(int)nspan->_num] = (*realtwiddle) * im[(int)nspan->_num] + (*imtwiddle) * real[(int)nspan->_num];
            real[(int)nspan->_num] = *temp;
            
            n++;   // not forget to increment n
            
          } // end of loop over nodes
         
  //printf("FFT _ 7 \n");
          *n = (*n+*span) & (*N-*const_1);   // jump over the odd blocks
        
        } // end of loop over submatrices
        
     } // end of loop over FFT stages
  //printf("FFT _ 8 \n");
 
} // end of FFT function

/*
void DFT (int point , TaskData* my_data_ptr){
      int input_num=point;

      complex <double> * input = new complex <double>[input_num];
      complex <double> * output = new complex <double>[input_num];
      complex <double> j (0.0, 1.0);
      complex <double> pi (3.14159, 0.0);
      complex <double> comk (0, 0);
      complex <double> comn (0, 0);
      complex <double> comnum (input_num, 0);
      complex <double> com2 (-2, 0);
      double k1 = 0;
      double k2 = 0;

  for( int i=0 ; i < input_num ; i++ ){
    input[i].real()=i+1 ;//static_cast<double>(rand()%100)/100;
    input[i].imag()=0;
  }

  for( int k=0 ; k < input_num ; k++ ){
    output[k].real()=0;
    output[k].imag()=0;
    comk.real()=k;
    for(int n=0 ; n < input_num ; n++){
      comn.real()=n;
      output[k] += input[n]*exp(pi*j*com2*comn*comk/comnum);
    }
  }
  // printf("%s \n", my_data_ptr -> message);
  for( int i=0 ; i < input_num ; i++ ){
        k1 = output[i].real();
        k2 = output[i].imag();
      my_data_ptr->m_ceres.push_back(k1);
      my_data_ptr->m_ceres.push_back(k2);
  }
}

*/
void FFT_2(Element *real, Element *im , unsigned int logN = 10 , float err = 0 ) // logN is base 2 log(N)
{

    const double MINPI = 3.1415926 ;
    //unsigned int logN = 10 ;  
    unsigned int n=0, nspan, span, submatrix, node;
    unsigned int N = 1<<logN;
    //double temp, primitive_root, angle, realtwiddle, imtwiddle;
    double primitive_root, angle ;
  //printf("FFT _ 1 \n");
//    Element* MINPI = new Element(3.1415926 , err);
//    Element* n  = new Element(0 , err) ; 
//    Element* nspan  = new Element(0 , err) ; 
//    Element* span   = new Element(0 , err) ; 
//    Element* submatrix  = new Element(0 , err) ; 
//    Element* node  = new Element(0 , err) ; 
//    Element* N  = new Element( 1<<logN , err) ; 
    
    Element* temp= new Element(0 , err) ; 
//    Element* primitive_root = new Element(0 , err) ; 
//    Element* angle = new Element(0 , err) ; 
    Element* realtwiddle  = new Element(0 , err) ; 
    Element* imtwiddle  = new Element(0 , err) ; 

//    Element* const_2 = new Element(2 , err);
//    Element* const_1 = new Element(1 , err);
  //printf("FFT _ 2 \n");
    for(span=N>>1; span; span>>=1)      // loop over the FFT stages
    {
       primitive_root = MINPI/span;     // define MINPI in the header
  //printf("FFT _ 3 \n");
       
       for( submatrix=0 ; submatrix < (N>>1)/span; submatrix = submatrix + 1)
       {
  //printf("FFT _ 4 \n");
          for( node = 0 ; node < span; node = node + 1)
          {
  //printf("FFT _ 5 \n");
 //printf(" n = %f  \n" , n->_num );
 //printf(" nspan = %f  \n" , nspan->_num );
 //printf(" span = %f  \n" , span->_num );
            nspan = n+span;
            *temp = real[n] + real[nspan];       // additions & subtractions
            real[nspan] = real[n]-real[nspan];
            real[n] = *temp;
            *temp = im[n] + im[nspan];
            im[nspan] = im[n] - im[nspan];
            im[n] = *temp;
            
  //printf("FFT _ 6 \n");
            angle = primitive_root * node;      // rotations
            realtwiddle->_num = cos(angle);
            imtwiddle->_num = sin(angle);
            *temp = (*realtwiddle) * real[nspan] - (*imtwiddle) * im[nspan];
            im[nspan] = (*realtwiddle) * im[nspan] + (*imtwiddle) * real[nspan];
            real[nspan] = *temp;
            
            n++;   // not forget to increment n
            
          } // end of loop over nodes
         
  //printf("FFT _ 7 \n");
          n = (n+span) & (N-1);   // jump over the odd blocks
        
        } // end of loop over submatrices
        
     } // end of loop over FFT stages
  //printf("FFT _ 8 \n");
 
}

#endif
