#ifndef CORE_MANAGER
#define CORE_MANAGER

#include <stdio.h>
#include <vector>

#include <iostream>
#include <fstream>
#include <sstream>


using namespace std;

typedef vector<unsigned> Core_resource_in_type; 

class Core_Manager{
public:
	Core_Manager(fstream& ceres,int type);
	void refreshResourceTable();
	// void calibrateCoreErrorRate(); // Future Work

	/******************************
		read from environment.txt
	*******************************/
	vector<float>     m_core_error_rate; // to build CVATable for each Task in m_tasks
	vector<unsigned>   m_core_distribute; // core_id 0 is used for main thread (voting) and can not be assigned to pthread (fault injection)
	vector<float> hsieh_core_error_rate; //HSIEH's

	vector<Core_resource_in_type> m_resource_table; // record core_id ; not essential but easy for coding ; for CERES::NMRallocation // #
};

Core_Manager::Core_Manager(fstream& ceres_envir,int type){
    /**********************
    	ReadFile:
    	if environment.txt format has changed, modify this part

    	1.Core Distribution
    	2.Core Error Rate

    	HSIEH:
    	1. Core 0 is error free.
    	2. Starts from Core 1.
    	3. Length of m_core_error_rate is num of types.
    ***********************/
	printf("Core Distribution:\n");
	printf("-----------------------------\n");
	printf("| core_num  |  error_rate   |\n");
	printf("-----------------------------\n");

    string line;
    // ===================
    // For Ceres Developer
    // ===================
    // Core Distribution/Core Error Rate :
    for (int i = 0; i < 4; ++i){getline(ceres_envir, line);} 
  
    while(getline(ceres_envir, line)){

    	stringstream ss;
		ss<<line;
		int core_num;
		float error_rate;
		ss>>core_num>>error_rate;

		for (int i=0;i<core_num;++i)
		{
			hsieh_core_error_rate.push_back(error_rate*type);
		}

		m_core_error_rate.push_back(error_rate*type);
		m_core_distribute.push_back(core_num);	

		printf("|     %i     |  %E |\n", core_num, error_rate*type);
		printf("-----------------------------\n");
    }
	ceres_envir.close();

	this->refreshResourceTable();
}

void Core_Manager::refreshResourceTable(){ 

	// release and clear table	
	m_resource_table.clear();

	// build table
	unsigned core_id = 1;
	for (unsigned core_type = 0; core_type < m_core_distribute.size(); ++core_type){
		m_resource_table.push_back( Core_resource_in_type() );

		for (int core_num = 0; core_num < m_core_distribute.at(core_type); ++core_num){
			m_resource_table.at(core_type).push_back(core_id);
			++core_id;
		}		
	}

}

#endif
