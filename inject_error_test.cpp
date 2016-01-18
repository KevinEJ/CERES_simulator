#include <vector>
#include <iostream>
#include <math.h>
#include <random>
#include <bitset>

using namespace std;

int main() {
    float ff = 0.25;
    float after;
    bitset<32> faultbit;
      
      //size_t bit_location = rand() % 23;  // 23 for only fraction
      
        //cout<<ff<<" entering inject..."<<endl;
        //cout<<"Inserting faults at "<<bit_location<<endl;
        faultbit[25]=1;
        //cout<<faultbit<<endl;
 
      int faultMask=int(faultbit.to_ulong());

      int qq=*(int*)(&ff);

cout<< "before = " << qq << endl;
cout<< "mask = " << faultMask << endl;

      int inter=faultMask ^ qq;
cout<< "inter = before ^ mask = " << inter << endl;
      after = *(float*)(&inter);
cout<< "after =" << after << endl; 

    return 0;

}
