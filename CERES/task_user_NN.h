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
    float w1[5] = {3.34474202,4.49330692,3.06601958,-2.49747356,-2.90299181} ;
    float b1=0.71302192;
    float err= my_data_ptr->errRate_data;

    Data* w1_Vec=new Data(w1,5,err);
    Element* b1_Vec=new Element(b1,err);

    for(unsigned i = 0 ; i < DATA_LENGTH ; i++ ){

      Element* activation_1 = new Element(0,err);
      
      for(unsigned j=0;j<5;j++){
        Element mult=*(w1_Vec->_elements[j])* my_data_ptr->m_inputs[j]->at(i);
        *activation_1=*activation_1+mult;
      }
      
      activation_1->_errRate = err;  // Wes adds on 15.09.19
      Element afterplus1 = *activation_1 + *b1_Vec;
      afterplus1._errRate = err;  // Wes adds on 15.09.19
      

      my_data_ptr->m_ceres.push_back(afterplus1);
    }
}

void* task1_2_kernel(void* threadarg)
{
    TaskData* my_data_ptr = (TaskData*)threadarg;
    float w1[5] = {-5.29711519,-3.22827412,-5.29484264,5.29276191,5.32641321} ;
    float b1=3.0993109;
    float err= my_data_ptr->errRate_data;

    Data* w1_Vec=new Data(w1,5,err);
    Element* b1_Vec=new Element(b1,err);

    for(unsigned i = 0 ; i < DATA_LENGTH ; i++ ){

      Element* activation_1 = new Element(0,err);
      
      for(unsigned j=0;j<5;j++){
        Element mult=*(w1_Vec->_elements[j])* my_data_ptr->m_inputs[j]->at(i);
        *activation_1=*activation_1+mult;
      }
      
      activation_1->_errRate = err;  // Wes adds on 15.09.19
      Element afterplus1 = *activation_1 + *b1_Vec;
      afterplus1._errRate = err;  // Wes adds on 15.09.19
      

      my_data_ptr->m_ceres.push_back(afterplus1);
    }
}

void* task1_3_kernel(void* threadarg)
{
    TaskData* my_data_ptr = (TaskData*)threadarg;
    float w1[5] = {2.2694254,2.41055964,2.03529273, -1.70765123, -1.81900576} ;
    float b1=2.21610593;
    float err= my_data_ptr->errRate_data;

    Data* w1_Vec=new Data(w1,5,err);
    Element* b1_Vec=new Element(b1,err);

    for(unsigned i = 0 ; i < DATA_LENGTH ; i++ ){

      Element* activation_1 = new Element(0,err);
      
      for(unsigned j=0;j<5;j++){
        Element mult=*(w1_Vec->_elements[j])* my_data_ptr->m_inputs[j]->at(i);
        *activation_1=*activation_1+mult;
      }
      
      activation_1->_errRate = err;  // Wes adds on 15.09.19
      Element afterplus1 = *activation_1 + *b1_Vec;
      afterplus1._errRate = err;  // Wes adds on 15.09.19
      

      my_data_ptr->m_ceres.push_back(afterplus1);
    }
}

void* task1_4_kernel(void* threadarg)
{
    TaskData* my_data_ptr = (TaskData*)threadarg;
    float w1[5] = {-1.35501447 ,2.96839852 ,-1.31688325 ,1.90292464 ,2.23585015} ;
    float b1=2.33828457;
    float err= my_data_ptr->errRate_data;

    Data* w1_Vec=new Data(w1,5,err);
    Element* b1_Vec=new Element(b1,err);

    for(unsigned i = 0 ; i < DATA_LENGTH ; i++ ){

      Element* activation_1 = new Element(0,err);
      
      for(unsigned j=0;j<5;j++){
        Element mult=*(w1_Vec->_elements[j])* my_data_ptr->m_inputs[j]->at(i);
        *activation_1=*activation_1+mult;
      }
      
      activation_1->_errRate = err;  // Wes adds on 15.09.19
      Element afterplus1 = *activation_1 + *b1_Vec;
      afterplus1._errRate = err;  // Wes adds on 15.09.19
      

      my_data_ptr->m_ceres.push_back(afterplus1);
    }
}

void* task1_5_kernel(void* threadarg)
{
    TaskData* my_data_ptr = (TaskData*)threadarg;
    float w1[5] = {-3.13217326 ,4.6369928 ,-3.23543471, 3.36045035, 3.3010985} ;
    float b1=-0.01475498;
    float err= my_data_ptr->errRate_data;

    Data* w1_Vec=new Data(w1,5,err);
    Element* b1_Vec=new Element(b1,err);

    for(unsigned i = 0 ; i < DATA_LENGTH ; i++ ){

      Element* activation_1 = new Element(0,err);
      
      for(unsigned j=0;j<5;j++){
        Element mult=*(w1_Vec->_elements[j])* my_data_ptr->m_inputs[j]->at(i);
        *activation_1=*activation_1+mult;
      }
      
      activation_1->_errRate = err;  // Wes adds on 15.09.19
      Element afterplus1 = *activation_1 + *b1_Vec;
      afterplus1._errRate = err;  // Wes adds on 15.09.19
      

      my_data_ptr->m_ceres.push_back(afterplus1);
    }
}

void* task1_6_kernel(void* threadarg)
{
    TaskData* my_data_ptr = (TaskData*)threadarg;
    float w1[5] = {-0.34432376, -2.09550161 ,-0.7350715 ,0.67006427, -0.4509977} ;
    float b1=-1.51117823;
    float err= my_data_ptr->errRate_data;

    Data* w1_Vec=new Data(w1,5,err);
    Element* b1_Vec=new Element(b1,err);

    for(unsigned i = 0 ; i < DATA_LENGTH ; i++ ){

      Element* activation_1 = new Element(0,err);
      
      for(unsigned j=0;j<5;j++){
        Element mult=*(w1_Vec->_elements[j])* my_data_ptr->m_inputs[j]->at(i);
        *activation_1=*activation_1+mult;
      }
      
      activation_1->_errRate = err;  // Wes adds on 15.09.19
      Element afterplus1 = *activation_1 + *b1_Vec;
      afterplus1._errRate = err;  // Wes adds on 15.09.19
      

      my_data_ptr->m_ceres.push_back(afterplus1);
    }
}

void* task2_1_kernel(void* threadarg)
{
    TaskData* my_data_ptr = (TaskData*)threadarg;
    float w1[6] = {-1.25192795 ,4.06880577, -5.18648015, 0.4441667, 0.1590802, 1.89289054} ;
    float b1=-2.77965095;
    float err= my_data_ptr->errRate_data;

    Data* w1_Vec=new Data(w1,6,err);
    Element* b1_Vec=new Element(b1,err);

    for(unsigned i = 0 ; i < DATA_LENGTH ; i++ ){

      Element* activation_1 = new Element(0,err);
      
      for(unsigned j=0;j<6;j++){
        Element mult=*(w1_Vec->_elements[j])* my_data_ptr->m_inputs[j]->at(i);
        *activation_1=*activation_1+mult;
      }
      
      activation_1->_errRate = err;  // Wes adds on 15.09.19
      Element afterplus1 = *activation_1 + *b1_Vec;
      afterplus1._errRate = err;  // Wes adds on 15.09.19
      

      my_data_ptr->m_ceres.push_back(afterplus1);
    }
}

void* task2_2_kernel(void* threadarg)
{
    TaskData* my_data_ptr = (TaskData*)threadarg;
    float w1[6] = {0.28435772 ,-1.24364154, 0.21174652, -0.69640082, -0.25443749, 1.18363778} ;
    float b1=0.12633329;
    float err= my_data_ptr->errRate_data;

    Data* w1_Vec=new Data(w1,6,err);
    Element* b1_Vec=new Element(b1,err);

    for(unsigned i = 0 ; i < DATA_LENGTH ; i++ ){

      Element* activation_1 = new Element(0,err);
      
      for(unsigned j=0;j<6;j++){
        Element mult=*(w1_Vec->_elements[j])* my_data_ptr->m_inputs[j]->at(i);
        *activation_1=*activation_1+mult;
      }
      
      activation_1->_errRate = err;  // Wes adds on 15.09.19
      Element afterplus1 = *activation_1 + *b1_Vec;
      afterplus1._errRate = err;  // Wes adds on 15.09.19
      

      my_data_ptr->m_ceres.push_back(afterplus1);
    }
}

void* task2_3_kernel(void* threadarg)
{
    TaskData* my_data_ptr = (TaskData*)threadarg;
    float w1[6] = {-1.08634864, 0.26283414, -2.50580624, -1.63161701, 0.52604288, -0.72073469} ;
    float b1=-2.20404104;
    float err= my_data_ptr->errRate_data;

    Data* w1_Vec=new Data(w1,6,err);
    Element* b1_Vec=new Element(b1,err);

    for(unsigned i = 0 ; i < DATA_LENGTH ; i++ ){

      Element* activation_1 = new Element(0,err);
      
      for(unsigned j=0;j<6;j++){
        Element mult=*(w1_Vec->_elements[j])* my_data_ptr->m_inputs[j]->at(i);
        *activation_1=*activation_1+mult;
      }
      
      activation_1->_errRate = err;  // Wes adds on 15.09.19
      Element afterplus1 = *activation_1 + *b1_Vec;
      afterplus1._errRate = err;  // Wes adds on 15.09.19
      

      my_data_ptr->m_ceres.push_back(afterplus1);
    }
}

void* task2_4_kernel(void* threadarg)
{
    TaskData* my_data_ptr = (TaskData*)threadarg;
    float w1[6] = {5.15081552 ,7.05885778, -0.0503846, -4.44395887, -3.05965155, -2.1843896} ;
    float b1=-3.4342127;
    float err= my_data_ptr->errRate_data;

    Data* w1_Vec=new Data(w1,6,err);
    Element* b1_Vec=new Element(b1,err);

    for(unsigned i = 0 ; i < DATA_LENGTH ; i++ ){

      Element* activation_1 = new Element(0,err);
      
      for(unsigned j=0;j<6;j++){
        Element mult=*(w1_Vec->_elements[j])* my_data_ptr->m_inputs[j]->at(i);
        *activation_1=*activation_1+mult;
      }
      
      activation_1->_errRate = err;  // Wes adds on 15.09.19
      Element afterplus1 = *activation_1 + *b1_Vec;
      afterplus1._errRate = err;  // Wes adds on 15.09.19
      

      my_data_ptr->m_ceres.push_back(afterplus1);
    }
}

void* task2_5_kernel(void* threadarg)
{
    TaskData* my_data_ptr = (TaskData*)threadarg;
    float w1[6] = {-1.65400634, 9.88830193, -0.34499852, 2.8425901, -4.51902195 ,-0.74625393} ;
    float b1= 1.3667506;
    float err= my_data_ptr->errRate_data;

    Data* w1_Vec=new Data(w1,6,err);
    Element* b1_Vec=new Element(b1,err);

    for(unsigned i = 0 ; i < DATA_LENGTH ; i++ ){

      Element* activation_1 = new Element(0,err);
      
      for(unsigned j=0;j<6;j++){
        Element mult=*(w1_Vec->_elements[j])* my_data_ptr->m_inputs[j]->at(i);
        *activation_1=*activation_1+mult;
      }
      
      activation_1->_errRate = err;  // Wes adds on 15.09.19
      Element afterplus1 = *activation_1 + *b1_Vec;
      afterplus1._errRate = err;  // Wes adds on 15.09.19
      

      my_data_ptr->m_ceres.push_back(afterplus1);
    }
}

void* task2_6_kernel(void* threadarg)
{
    TaskData* my_data_ptr = (TaskData*)threadarg;
    float w1[6] = {-1.97901499, 0.47183589, 0.35891135, 0.42480721, 1.35216801, -1.94697691} ;
    float b1=-2.59672072;
    float err= my_data_ptr->errRate_data;

    Data* w1_Vec=new Data(w1,6,err);
    Element* b1_Vec=new Element(b1,err);

    for(unsigned i = 0 ; i < DATA_LENGTH ; i++ ){

      Element* activation_1 = new Element(0,err);
      
      for(unsigned j=0;j<6;j++){
        Element mult=*(w1_Vec->_elements[j])* my_data_ptr->m_inputs[j]->at(i);
        *activation_1=*activation_1+mult;
      }
      
      activation_1->_errRate = err;  // Wes adds on 15.09.19
      Element afterplus1 = *activation_1 + *b1_Vec;
      afterplus1._errRate = err;  // Wes adds on 15.09.19
      

      my_data_ptr->m_ceres.push_back(afterplus1);
    }
}

void* task3_1_kernel(void* threadarg)
{
    TaskData* my_data_ptr = (TaskData*)threadarg;
    float w1[6] = {4.05415159 ,-1.17585038 ,-1.1172863 ,4.87636207, -4.0150085, -0.12332786} ;
    float b1=1.42746499;
    float err= my_data_ptr->errRate_data;

    Data* w1_Vec=new Data(w1,6,err);
    Element* b1_Vec=new Element(b1,err);

    for(unsigned i = 0 ; i < DATA_LENGTH ; i++ ){

      Element* activation_1 = new Element(0,err);
      
      for(unsigned j=0;j<6;j++){
        Element mult=*(w1_Vec->_elements[j])* my_data_ptr->m_inputs[j]->at(i);
        *activation_1=*activation_1+mult;
      }
      
      activation_1->_errRate = err;  // Wes adds on 15.09.19
      Element afterplus1 = *activation_1 + *b1_Vec;
      afterplus1._errRate = err;  // Wes adds on 15.09.19
      

      my_data_ptr->m_ceres.push_back(afterplus1);
    }
}

void* task3_2_kernel(void* threadarg)
{
    TaskData* my_data_ptr = (TaskData*)threadarg;
    float w1[6] = {0.96830273 ,-0.18804712, 2.03617029, -1.87078643 ,-1.75775287 ,1.27630257} ;
    float b1=-0.9163404;
    float err= my_data_ptr->errRate_data;

    Data* w1_Vec=new Data(w1,6,err);
    Element* b1_Vec=new Element(b1,err);

    for(unsigned i = 0 ; i < DATA_LENGTH ; i++ ){

      Element* activation_1 = new Element(0,err);
      
      for(unsigned j=0;j<6;j++){
        Element mult=*(w1_Vec->_elements[j])* my_data_ptr->m_inputs[j]->at(i);
        *activation_1=*activation_1+mult;
      }
      
      activation_1->_errRate = err;  // Wes adds on 15.09.19
      Element afterplus1 = *activation_1 + *b1_Vec;
      afterplus1._errRate = err;  // Wes adds on 15.09.19
      

      my_data_ptr->m_ceres.push_back(afterplus1);
    }
}

void* task3_3_kernel(void* threadarg)
{
    TaskData* my_data_ptr = (TaskData*)threadarg;
    float w1[6] = {1.79226917 ,1.01029005 ,0.21996993, 0.78737471, -3.59583778, 0.17194703} ;
    float b1=0.46843754;
    float err= my_data_ptr->errRate_data;

    Data* w1_Vec=new Data(w1,6,err);
    Element* b1_Vec=new Element(b1,err);

    for(unsigned i = 0 ; i < DATA_LENGTH ; i++ ){

      Element* activation_1 = new Element(0,err);
      
      for(unsigned j=0;j<6;j++){
        Element mult=*(w1_Vec->_elements[j])* my_data_ptr->m_inputs[j]->at(i);
        *activation_1=*activation_1+mult;
      }
      
      activation_1->_errRate = err;  // Wes adds on 15.09.19
      Element afterplus1 = *activation_1 + *b1_Vec;
      afterplus1._errRate = err;  // Wes adds on 15.09.19
      

      my_data_ptr->m_ceres.push_back(afterplus1);
    }
}

void* task3_4_kernel(void* threadarg)
{
    TaskData* my_data_ptr = (TaskData*)threadarg;
    float w1[6] = {0.70403566 ,0.23059577, -1.11903104, -0.60288492, -2.86706004, -1.31438627} ;
    float b1=-0.34252011;
    float err= my_data_ptr->errRate_data;

    Data* w1_Vec=new Data(w1,6,err);
    Element* b1_Vec=new Element(b1,err);

    for(unsigned i = 0 ; i < DATA_LENGTH ; i++ ){

      Element* activation_1 = new Element(0,err);
      
      for(unsigned j=0;j<6;j++){
        Element mult=*(w1_Vec->_elements[j])* my_data_ptr->m_inputs[j]->at(i);
        *activation_1=*activation_1+mult;
      }
      
      activation_1->_errRate = err;  // Wes adds on 15.09.19
      Element afterplus1 = *activation_1 + *b1_Vec;
      afterplus1._errRate = err;  // Wes adds on 15.09.19
      

      my_data_ptr->m_ceres.push_back(afterplus1);
    }
}

void* task3_5_kernel(void* threadarg)
{
    TaskData* my_data_ptr = (TaskData*)threadarg;
    float w1[6] = {4.96187752 ,-0.51618067, -0.14155255, 7.28783563, -5.70043919, 1.87655474} ;
    float b1=1.93287023;
    float err= my_data_ptr->errRate_data;

    Data* w1_Vec=new Data(w1,6,err);
    Element* b1_Vec=new Element(b1,err);

    for(unsigned i = 0 ; i < DATA_LENGTH ; i++ ){

      Element* activation_1 = new Element(0,err);
      
      for(unsigned j=0;j<6;j++){
        Element mult=*(w1_Vec->_elements[j])* my_data_ptr->m_inputs[j]->at(i);
        *activation_1=*activation_1+mult;
      }
      
      activation_1->_errRate = err;  // Wes adds on 15.09.19
      Element afterplus1 = *activation_1 + *b1_Vec;
      afterplus1._errRate = err;  // Wes adds on 15.09.19
      

      my_data_ptr->m_ceres.push_back(afterplus1);
    }
}

void* task3_6_kernel(void* threadarg)
{
    TaskData* my_data_ptr = (TaskData*)threadarg;
    float w1[6] = {-0.49642997 ,-0.89507476, 0.28944094, -0.60956388, -0.84637541, -2.07285507} ;
    float b1= -0.80327685;
    float err= my_data_ptr->errRate_data;

    Data* w1_Vec=new Data(w1,6,err);
    Element* b1_Vec=new Element(b1,err);

    for(unsigned i = 0 ; i < DATA_LENGTH ; i++ ){

      Element* activation_1 = new Element(0,err);
      
      for(unsigned j=0;j<6;j++){
        Element mult=*(w1_Vec->_elements[j])* my_data_ptr->m_inputs[j]->at(i);
        *activation_1=*activation_1+mult;
      }
      
      activation_1->_errRate = err;  // Wes adds on 15.09.19
      Element afterplus1 = *activation_1 + *b1_Vec;
      afterplus1._errRate = err;  // Wes adds on 15.09.19
      

      my_data_ptr->m_ceres.push_back(afterplus1);
    }
}

void* task4_1_kernel(void* threadarg)
{
    TaskData* my_data_ptr = (TaskData*)threadarg;
    float w1[6] = {-6.15789837 ,-0.99585765 ,-2.86240872, -1.39474059, -9.033459, 0.48235597} ;
    float b1= 6.57796715;
    float err= my_data_ptr->errRate_data;

    Data* w1_Vec=new Data(w1,6,err);
    Element* b1_Vec=new Element(b1,err);

    for(unsigned i = 0 ; i < DATA_LENGTH ; i++ ){

      Element* activation_1 = new Element(0,err);
      
      for(unsigned j=0;j<6;j++){
        Element mult=*(w1_Vec->_elements[j])* my_data_ptr->m_inputs[j]->at(i);
        *activation_1=*activation_1+mult;
      }
      
      activation_1->_errRate = err;  // Wes adds on 15.09.19
      Element afterplus1 = *activation_1 + *b1_Vec;
      afterplus1._errRate = err;  // Wes adds on 15.09.19
      

      my_data_ptr->m_ceres.push_back(afterplus1);
    }
}

void* task_kernel_sigmoid(void* threadarg)
{
  TaskData* my_data_ptr = (TaskData*)threadarg;
  float err=my_data_ptr->errRate_data;
  //<<"task_kernel_sigmoid err is "<<err<<endl;

  for(unsigned i = 0 ; i < DATA_LENGTH ; i++ ){

  float num = my_data_ptr->m_inputs[0]->at(i)._num;

  Element *gg=new Element(num,err);

  

  gg->Sigmoid();



    my_data_ptr->m_ceres.push_back(*gg);
  }
}

void* task_kernel_last(void* threadarg)
{
  TaskData* my_data_ptr = (TaskData*)threadarg;
  
  for(unsigned i = 0 ; i < DATA_LENGTH ; i++ ){
  float ans ;
  if(my_data_ptr->m_inputs[0]->at(i)._num>0.5)
    ans = 1 ;
  else
    ans = 0 ;

  Element *gg=new Element(ans,0);

  my_data_ptr->m_ceres.push_back(*gg);

  }

}



#endif
