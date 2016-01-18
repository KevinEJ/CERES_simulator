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

//2^input = data_length
#define DATA_LENGTH 32
#define Input_number 5


/***************************************
    - you may not modify this part
      CERES Voting Mechanism need this

    - fill m_ceres in kernal function
      and get m_final as result after robustComputing
  ***************************************/
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


void DFT (int, TaskData*);

/**********************
  kernel function 
***********************/
// task<layer_num>_<neuron_num>_kernel
void* task1_1_kernel(void* threadarg)
{
    TaskData* my_data_ptr = (TaskData*)threadarg;
   float err= my_data_ptr->errRate_data;

    Data* w1_Vec=new Data(w1,5,err);
    Element* b1_Vec=new Element(b1,err);

    for(unsigned i = 0 ; i < DATA_LENGTH ; i++ ){

      my_data_ptr->m_ceres.push_back(afterplus1);
    }
}
