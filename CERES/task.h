#ifndef TASK
#define TASK

#include <vector>
#include <math.h>

#include <iostream>
#include <iomanip> 

#include "task_user.h"
#include "core_manager.h"

#define MASK_RATE 0.7
#define instruction_count_CVA 190

using namespace std;

unsigned nchoosek(unsigned n, unsigned k){
	if (k == 0) 
		return 1;
	return ( (n * nchoosek(n - 1, k - 1)) / k);
}

typedef void* (*PthreadFuncPointer) (void*);

class TaskData;
class Core_Manager;

class Task
{
public:
	//Pass into through constructor
		PthreadFuncPointer m_pthread_func_ptr;// pass this into pthread_create as Func Arg
		long unsigned m_instruct_count; 
		float m_reliability;
		TaskData *m_task_data_ptr;// original TaskData
		
	//	num depend on NMR allocation m_duplicate_num
	//	for each duplicate thread point to different TaskData object to fill each m_ceres
	vector<TaskData*> m_task_data_ptrs_NMR; // #
	
	vector<unsigned> CVA_table;
	
	//HSIEH
	vector<float> Relia_table;

	unsigned m_duplicate_num; // #
	vector<unsigned> m_coreIDs;
	//Ho
	vector<int>      m_coreTypes ;

	//Wes
	unsigned m_operator_count;



	Task(const PthreadFuncPointer pthread_func_ptr, const unsigned instruc_num, const float reliability, TaskData* task_data_ptr, const unsigned operator_count);
	void setCVATable(const Core_Manager* core_manager);

	//Ho
	void setCVATable_modify (const Core_Manager* core_manager);
	void setCVATable_only_CVA (const Core_Manager* core_manager);  // Wes
	//HSIEH
	void setReliaTable(const Core_Manager* core_manager);
};



Task::Task(const PthreadFuncPointer pthread_func_ptr,
			 const unsigned instruc_num,
			 const float reliability,
			 TaskData* task_data_ptr,
			 const unsigned operator_count ) : m_duplicate_num(0)
{
	m_pthread_func_ptr = pthread_func_ptr;
	m_instruct_count = instruc_num;
	m_reliability = reliability;
	m_task_data_ptr = task_data_ptr;
	m_operator_count = operator_count;
}

void Task::setCVATable(const Core_Manager* core_manager){

	/**************************
		Developer Interface
		- Build CVA_table :
	***************************/

	CVA_table.clear();

	vector<float> reliab_list; // [ R0 R1 R2 ...]

	// build reliab_list
	for (int core_type = 0; core_type < core_manager->m_core_error_rate.size(); ++core_type)
	{
		float reliab;
		reliab = exp(-1*
			core_manager->m_core_error_rate.at(core_type)*
			float(this->m_instruct_count)*MASK_RATE
			);
		reliab_list.push_back(reliab);
	}

	float target_reliab = this->m_reliability;
	unsigned N_max = 5; // max N for NMR

	printf("Task Instruction Num : %8ld | target : %f | CVAtable : ", this->m_instruct_count, target_reliab);
	for (int core_type = 0; core_type < reliab_list.size(); ++core_type)
	{
		unsigned N;
		float reliab = reliab_list.at(core_type);

		// cout<<"target_reliab: "<<target_reliab<<endl;
		// cout<<"reliab: "<<reliab<<endl;
		
		if (reliab > target_reliab){
			N = 1;
		}
		else if(reliab >= 0.5){
			float temp_reliab = 0.f;

			// Teresa Original
			// for (unsigned n = 3; n <= N_max; n += 2){
			// 	unsigned half_n = n/2 + 1;
			// 	temp_reliab = 0.f;

			// 	for (int k = half_n; k <= n; ++k){
			// 		temp_reliab += float( nchoosek(n,k) )*pow(reliab, k)*pow(1 - reliab,n-k);
			// 	}
			// 	if (temp_reliab > target_reliab){
			// 		N = n;
			// 		break;
			// 	}			
			// }
			for (unsigned n = 2; n <= N_max; n += 1){
				temp_reliab = 0.f;

				for (int k = 3; k <= n; ++k){ // 2 is lower than 1 for reliab
					temp_reliab += float( nchoosek(n,k) )*pow(reliab, k)*pow(1 - reliab,n-k);
				}
				if (temp_reliab > target_reliab){
					N = n;
					break;
				}			
			}

			if(temp_reliab < target_reliab){// Need to break Task into small pieces!			
				    N = N_max;
			}
		}
		else{
			N = 999;
		}


		this->CVA_table.push_back(N);
		printf("%3d ", N);
	}
	printf("\n");
}
//Ho  for target_reliability = 0.95
void Task::setCVATable_modify(const Core_Manager* core_manager){

	/**************************
		Developer Interface
		- Build CVA_table :
	***************************/

	CVA_table.clear();

	vector<float> reliab_list; // [ R0 R1 R2 ...]

	// build reliab_list
	for (int core_type = 0; core_type < core_manager->m_core_error_rate.size(); ++core_type)
	{
		float reliab;
		reliab = exp(-1*
			core_manager->m_core_error_rate.at(core_type)*
			float(this->m_instruct_count)*MASK_RATE
			);
		reliab_list.push_back(reliab);
	}

	float target_reliab = this->m_reliability;
	unsigned N_max = 5; // max N for NMR

	printf("Task Instruction Num : %8ld | target : %f | CVAtable : ", this->m_instruct_count, target_reliab);
	for (int core_type = 0; core_type < reliab_list.size(); ++core_type)
	{
		unsigned N;
		float reliab = reliab_list.at(core_type);

		// cout<<"target_reliab: "<<target_reliab<<endl;
		// cout<<"reliab: "<<reliab<<endl;
		if(target_reliab == 0.95){	
		    if (reliab > target_reliab){
			    N = 1;
		    }
    		else if(reliab >= 0.84){
	    		N = 3 ;			
		    }
    		else if(reliab >= 0.73){
	    		N = 4 ;
		    }
    		else if(reliab >= 0.64){
	    		N = 5 ;
		    }
    		else{
	    		N = 999;
		    }
        }
       else if(target_reliab == 0.9){	
		    if (reliab > target_reliab){
			    N = 1;
		    }
    		else if(reliab >= 0.77){
	    		N = 3 ;			
		    }
    		else if(reliab >= 0.65){
	    		N = 4 ;
		    }
    		else if(reliab >= 0.57){
	    		N = 5 ;
		    }
    		else{
	    		N = 999;
		    }
        }
        else
            cerr << "target_reliab " << endl ;

		this->CVA_table.push_back(N);
		printf("%3d ", N);
	}
	printf("\n");
}

void Task::setCVATable_only_CVA(const Core_Manager* core_manager){

	/**************************
		Developer Interface
		- Build CVA_table :
	***************************/

	CVA_table.clear();

	vector<float> reliab_list; // [ R0 R1 R2 ...]

	// build reliab_list
	for (int core_type = 0; core_type < core_manager->m_core_error_rate.size(); ++core_type)
	{
		float reliab;
		reliab = exp(-1*
			core_manager->m_core_error_rate.at(core_type)*
			instruction_count_CVA * MASK_RATE
			);
		reliab_list.push_back(reliab);
	}

	float target_reliab = this->m_reliability;
	unsigned N_max = 5; // max N for NMR

	printf("Task Instruction Num : %8ld | target : %f | CVAtable : ", this->m_instruct_count, target_reliab);
	for (int core_type = 0; core_type < reliab_list.size(); ++core_type)
	{
		unsigned N;
		float reliab = reliab_list.at(core_type);

		// cout<<"target_reliab: "<<target_reliab<<endl;
		// cout<<"reliab: "<<reliab<<endl;
	    if(target_reliab == 0.95){	
		    if (reliab > target_reliab){
			    N = 1;
		    }
    		else if(reliab >= 0.84){
	    		N = 3 ;			
		    }
    		else if(reliab >= 0.73){
	    		N = 4 ;
		    }
    		else if(reliab >= 0.64){
	    		N = 5 ;
		    }
    		else{
	    		N = 999;
		    }
        }
       else if(target_reliab == 0.9){	
		    if (reliab > target_reliab){
			    N = 1;
		    }
    		else if(reliab >= 0.77){
	    		N = 3 ;			
		    }
    		else if(reliab >= 0.65){
	    		N = 4 ;
		    }
    		else if(reliab >= 0.57){
	    		N = 5 ;
		    }
    		else{
	    		N = 999;
		    }
        }
        else
            cerr << "target_reliab " << endl ;


		this->CVA_table.push_back(N);
		printf("%3d ", N);
	}
	printf("\n");
}

void Task::setReliaTable(const Core_Manager* core_manager){

	Relia_table.clear();

    cout<<"reliab: " ;
	// build reliab_list
	for (int core_type = 0; core_type < core_manager->m_core_error_rate.size(); ++core_type)
	{
		float reliab;
		reliab = exp(-1*
			core_manager->m_core_error_rate.at(core_type)*
			float(this->m_instruct_count)*MASK_RATE);
		cout << setw(15) << reliab << " " ; 
		Relia_table.push_back(reliab);
	}
	cout << endl ;
	//float target_reliab = this->m_reliability;

}

#endif
