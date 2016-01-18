#include <cstdlib>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <iostream>
#include <fstream> 
#include <sstream>
#include <vector>
#include <time.h>

#include "CERES.h"

#define LAYER_SIZE 1 

using namespace std;

void Ceres_GenResultFile (Ceres &ceres, vector<Task*> task_to_handle, unsigned times);

int main(int argc,char* argv[])
{
	if (argc!=7)
	{
		cerr<<"Usage: ./ceres_exe <numbers> <envir_type> <dot_protect> <algo> <environment_setting> <random Number>"<<endl;
		return -1;
	}

	istringstream ss(argv[1]);
	int RUNsize;
	if (!(ss>>RUNsize)||!(RUNsize>0))
	{	
		cerr<<"Usage: ./ceres_exe <numbers> <envir_type> <dot_protect> <algo> <environment_setting>"<<endl;
		cerr<<"Invalid number "<<argv[1]<<endl;
		return -1;
	}

	string envir(argv[2]);
	istringstream dicc(argv[2]);
	int env_type;
	//if ((envir!="1")&&(envir!="3")&&(envir!="5"))
	if (!(dicc>>env_type)||!(env_type>0))
	{
		cerr<<"Usage: ./ceres_exe <numbers> <envir_type> <dot_protect> <algo> <environment_setting>"<<endl;
		cerr<<"Invalid type "<<argv[2]<<endl;
		return -1;
	}

	istringstream ss1(argv[3]);
	istringstream ss2(argv[4]);
	float dot_protect;
	float sig_protect;
	if (!(ss1>>dot_protect)||!(dot_protect>0))
	{	
		cerr<<"Usage: ./ceres_exe <numbers> <envir_type> <dot_protect> <algo> <environment_setting>"<<endl;
		cerr<<"Invalid number "<<argv[3]<<endl;
		return -1;
	}

	if (!(ss2>>sig_protect))
	{	
		cerr<<"Usage: ./ceres_exe <numbers> <envir_type> <dot_protect> <sig_protect>"<<endl;
		cerr<<"Invalid number "<<argv[4]<<endl;
		return -1;
	}
	
    string envir_setting(argv[5]);
    fstream test_open;
	test_open.open(envir_setting);
	assert( ("Can't open environment file,please put it in folder /CERES ! \n", test_open) );
    printf("environment file import successfully... \n");
	test_open.close();

    istringstream s_rand_num(argv[6]);
    int rand_num = 0 ;
    if(!(s_rand_num>>rand_num) || !(rand_num>0) ){
		cerr<<"Usage: ./ceres_exe <numbers> <envir_type> <dot_protect> <algo> <environment_setting> <rand_num>"<<endl;
        cerr << "Invalid random num " << argv[6] << endl ;
        return -1 ;
    }
    srand(time(NULL));
	
	Ceres my_ceres(envir , envir_setting);
	/****************************
		User Interface
			- create TaskData
			- setting TaskData Value
			- create task(&task_kernel, instruction_num, reliability, &taskdata)
			- push every task into task_to_handle
			- use my_ceres.robustComputing(task_to_handle) 
				or  Ceres_GenResultFile(my_ceres, task_to_handle, run times);
			
			- taskgraph looks like
	****************************/
    int total_core_used = 0 ;
    int random_times = RUNsize ; 
    RUNsize = 1 ;
	ofstream err_free_file;
	err_free_file.open("./Result/error_free_result.txt", ios::out|ios::trunc);
    ofstream final_file; 
    final_file.open("./Result/final_result.txt", ios::out|ios::app);
for(int t = 0 ; t < random_times ; ++t  ){	
    //int task_num = 1;
    //int task_num = (rand()%rand_num )+1 ; 
    int task_num = rand_num ; 
	/*--------------------
		create TaskData
	--------------------*/
	TaskData* tds[task_num];
	for (int i = 0; i < task_num; ++i)
		tds[i] = new TaskData();
	
	vector<Task*> task_to_handle[1];//nine stages!!!
	/*---------------------------------------------------------------------
		create task(&task_kernel, instruction_num, reliability, &taskdata)
	---------------------------------------------------------------------*/
	Task* tasks[task_num];
	//-------------------//
	printf("Set values \n");
//100,200,400,800,1600,3200
	//layer 1 , two input using 18000, five use 45000
    for (int task_id = 0 ; task_id < task_num ; task_id ++){
        int ins_num = pow( 2 , (rand()%6) ) * 100  ;
	    //int ins_num = 1600 ;
        //tasks[task_id] = new Task(&task6_kernel, pow(2,task_id)*100  , dot_protect , tds[task_id], 170);
        tasks[task_id] = new Task(&task6_kernel, ins_num  , dot_protect , tds[task_id], 170);
    }
    /*
    tasks[1] = new Task(&task6_kernel, rand()%3200, dot_protect , tds[1], 150);
    tasks[2] = new Task(&task6_kernel, rand()%3200, dot_protect , tds[2], 150);
	tasks[3] = new Task(&task6_kernel, rand()%3200, dot_protect , tds[3], 150);
	tasks[4] = new Task(&task6_kernel, rand()%3200, dot_protect , tds[4], 150);
	tasks[5] = new Task(&task6_kernel, rand()%3200, dot_protect , tds[5], 150);
	tasks[6] = new Task(&task6_kernel, rand()%3200, dot_protect , tds[6], 150);
    tasks[7] = new Task(&task6_kernel, rand()%3200, dot_protect , tds[7], 150);
	tasks[8] = new Task(&task6_kernel, rand()%3200, dot_protect , tds[8], 150);
	tasks[9] = new Task(&task6_kernel, rand()%3200, dot_protect , tds[9], 150);
	tasks[10] = new Task(&task6_kernel, rand()%3200 , dot_protect , tds[10], 150);
	tasks[11] = new Task(&task6_kernel, rand()%3200 , dot_protect , tds[11], 150);
	*/
    //layer 1
	for(unsigned int k=0;k<task_num;++k)
		task_to_handle[0].push_back(tasks[k]);
//---------------------------error_free result------------------------------//
	//ofstream err_free_file;
	//err_free_file.open("./Result/error_free_result.txt", ios::out|ios::trunc);
	
	// put error_free result into m_ceres in original taskdata
	printf("Computimg error_free result on core_id 0 ...\n");

	err_free_file<<"Error_Free Result :\n";
	
for (unsigned layer_count = 0 ; layer_count < LAYER_SIZE ; layer_count++){
	
     //printf("layer_count ... %d \n" , layer_count);

	err_free_file<<"================================================"<<endl;
	err_free_file<<" Stages "<< layer_count <<endl;
	
	unsigned num_task = task_to_handle[layer_count].size();

	for (unsigned t_th = 0; t_th < num_task; ++t_th){
     //printf("t_th ... %d \n" , t_th);

		err_free_file<<"  task_"<<t_th<<"\n"<<"         ";

		Task* task_ptr = task_to_handle[layer_count].at(t_th);

     //printf("t_th ... %d \n" , t_th);
		( *(task_ptr->m_pthread_func_ptr) )( (void*) task_ptr->m_task_data_ptr );
     //printf("t_th ... %d \n" , t_th);
		vector<Element> err_free = task_ptr->m_task_data_ptr->m_ceres;
		
    //printf("t_th ... %d \n" , t_th);
		//printf("err_free is %d \n", err_free.size() ) ;

		for (unsigned i = 0; i < err_free.size(); ++i){
			err_free_file<<err_free.at(i)._num<<" ";
		}		
		
		// ho
		(task_ptr->m_task_data_ptr->m_buffer) = task_ptr->m_task_data_ptr->m_ceres ;

		err_free_file<<"\n";

		//reset m_ceres
		task_ptr->m_task_data_ptr->m_ceres.clear();
	}
	//err_free_file<<"\n \n";
}
	//err_free_file.close();

//---------------------------error_free result------------------------------//
	string exp_type_1 = "Random" ; 
    cout << sig_protect << "typetype" << endl ;
    if ( sig_protect == 1 )
	    exp_type_1 = "GG" ;  
	else if (sig_protect == 2 ) 
	    exp_type_1 = "GG" ;
	else if (sig_protect == 3 ) 
	    exp_type_1 = "GG" ;
	else if (sig_protect == 4 ) 
	    exp_type_1 = "GG" ;
	else if (sig_protect == 0 ) 
	    exp_type_1 = "CTVA" ;
	else if (sig_protect == 5 ) 
	    exp_type_1 = "Random" ;
    else {
        cerr << "Algorithm type should be 0 or 1" << endl ; 
        return 0 ;
    }
    //string exp_type_2 = "Random_" ;

cout<<"Error free ends... "<<endl<<endl;

//ofstream final_file; 
//final_file.open("./Result/final_result.txt", ios::out|ios::app);

cout<<"===========================TOTAL RUN STARTS...============================="<<endl;
//////////THIS i is RUN SIZE!!!!/////////////////////
for(size_t i = 0 ; i < RUNsize ;i++){
	printf("First layer \n");
//	
	if(exp_type_1 == "GG")
		my_ceres.GG_robustCombuting(task_to_handle[0] , sig_protect);
	else if(exp_type_1 == "Random")
		my_ceres.GG_random_robustCombuting(task_to_handle[0]);
	else
		my_ceres.robustComputing_modify(task_to_handle[0]);
	
	final_file<<"Count "<<i<<endl;
    
//==================output_file===============================================//
cout<<"===========================Start output file...============================="<<endl;
	for (unsigned layer_count =0 ; layer_count < LAYER_SIZE ; layer_count++){

		final_file<<"================================================"<<endl;
		final_file<<" Stages "<<layer_count<<endl;
		
		for (unsigned t_th = 0; t_th < task_to_handle[layer_count].size(); ++t_th){
			final_file<<"  task_" <<t_th<<"\n"<<"         ";
			vector<Element> final = task_to_handle[layer_count].at(t_th)->m_task_data_ptr->m_final;
			for (unsigned i = 0; i < final.size(); ++i){
				final_file<<final.at(i)._num<<" ";
			}
				final_file<<"\n";
		}
			final_file.flush();	
	}	
}
for (int x = 0 ; x < task_to_handle[0].size() ; x ++){
    cout << "core consumption of task " << x << " = " << task_to_handle[0][x]->m_duplicate_num << endl ;
    total_core_used += task_to_handle[0][x]->m_duplicate_num ;
}
//final_file.close();
cout<<"===========================Finiah...============================="<<endl;
	//return (0);

 } // for random
    cout << "total_core_used = " << total_core_used << endl ;
    final_file << "total_core_used = " << total_core_used << " " << endl ;
	err_free_file << "total_core_used = " << total_core_used << " " << endl ;
    final_file.close();
	err_free_file.close();
}//total main()



typedef vector<float> result;


