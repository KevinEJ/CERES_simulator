#ifndef CERES
#define CERES

#include <pthread.h>
/*
int pthread_create(pthread_t *thread, 
					const pthread_attr_t *attr,
   					void *(*start_routine)(void*),
   					void *arg);
*/
#include <algorithm>// std::count
#include <numeric>// std::accumulate

#include <vector>

#include <iostream>
#include <fstream>
#include <sstream>

#include <assert.h>
#include <stdlib.h>
#include <time.h>

#include "core_manager.h"
#include "task.h"
#include "task_user.h"

using namespace std;

void tellSniperCoreID(unsigned coreID){}
void SortTask(vector<Task*> &task_list){

	unsigned n = task_list.size();

	for (unsigned c = 0 ; c < n - 1 ; ++c)
	{
	  for (unsigned d = 0 ; d < n - c - 1; ++d)
	  {

	    unsigned ic = std::accumulate(task_list.at(d)->CVA_table.begin(), task_list.at(d)->CVA_table.end(), 0);
	    unsigned next_ic = std::accumulate(task_list.at(d + 1)->CVA_table.begin(), task_list.at(d + 1)->CVA_table.end(), 0);
	    if (ic > next_ic)
	    {
	      Task* swap = task_list.at(d);
	      task_list.at(d) = task_list.at(d+1);
	      task_list.at(d+1) = swap;
	    }
	  }
	}
}
typedef vector<float> CVA_score_table;

class TaskData;
class Task;
class Core_Manager;

class Ceres
{
public:
	Ceres(string , string );
	~Ceres();
	
	void robustComputing (vector<Task*> task_to_handle);

	//Ho
	void GG_robustCombuting(vector<Task*> task_to_handle , const int) ;
	void GG_random_robustCombuting(vector<Task*> task_to_handle) ;
	void robustComputing_modify (vector<Task*> task_to_handle) ;
	void robustComputing_CVA_alloaction (vector<Task*> task_to_handle) ;
private:
	Core_Manager* m_core_manager;
	vector<Task*> m_tasks;

	/********************
		    Basic 
	********************/
	void setCTVATable (void);

	void setCTVATable_modify (void);
	void setCTVATable_only_CVA (void);  // Wes 2015.11.10

	void NMRallocation (void);
	void parallelComputing (void);
	void Voting (void);
	void NMRVoting (void); // Wes

	//Ho
	void setAllReliaTable();
	void sortTaskByIns();
	void CVA_allocation();
	void GG_NMR_v1();
	void GG_NMR_v2();
	void GG_NMR_v3();
	void GG_NMR_v4();
	void GG_test_NMR();
	bool get_the_core(const int,Task*) ;
	bool get_best_coreID_from_CVAtable(Task*) ;
	void get_the_first_alloc_coreID_from_CVAtable(Task*) ;
	void get_the_first_relai_larger_than_target(Task*);

	void compute_complement_coreID(Task*) ;

	void GG_1_NMR();
	void GG_3_NMR();
	void GG_5_NMR();
	int transform(int);

	/********************
		   Advance 
	********************/
	void calbreCoreEnvir(void);
};

Ceres::Ceres(string type , string environment_setting ){
	//	readFile
	//string front="./CERES/environment2";  // simulation _q0_5
	string front = environment_setting ; 
    //front.append(type);
	int type_num=stoi(type);

	fstream ceres_envir;
	ceres_envir.open(front);
	assert( ("Can't open environment file,please put it in folder /CERES ! \n", ceres_envir) );
    printf("environment file import successfully... \n");
    
    // pass fstream ceres_envir to build core_manager 
    this->m_core_manager = new Core_Manager(ceres_envir,type_num);   
}

Ceres::~Ceres(){
	delete this->m_core_manager;
}

void Ceres::calbreCoreEnvir(){
	// future work

	// float delta = 
	// m_core_manager->calibrateCoreErrorRate(delta);
}

void Ceres::setCTVATable (){
	 
	// call Task::setCVATable in list m_tasks
	printf("\nset CTVAtable for each task... \n");
	//printf("task.size() = %d \n " , m_tasks.size() ) ;
    for (int task_th = 0; task_th < m_tasks.size(); ++task_th){
		m_tasks.at(task_th)->setCVATable(m_core_manager);
	}
}
void Ceres::setCTVATable_modify (){
	 
	// call Task::setCVATable in list m_tasks
	printf("\nset CTVAtable for each task... \n");
	for (int task_th = 0; task_th < m_tasks.size(); ++task_th){
		m_tasks.at(task_th)->setCVATable_modify (m_core_manager);
	}
}

void Ceres::setCTVATable_only_CVA (){
	 
	// call Task::setCVATable in list m_tasks
	printf("\nset CTVAtable for each task... \n");
	for (int task_th = 0; task_th < m_tasks.size(); ++task_th){
		m_tasks.at(task_th)->setCVATable_only_CVA (m_core_manager);
	}
}

void Ceres::robustComputing (vector<Task*> task_to_handle){
	printf("RobustComputing Start, %lu Tasks are parallel executing \n", task_to_handle.size());
		
		//	reset m_tasks
			m_tasks.clear();
		//	reset taskdata in task_to_handle
			for (unsigned i = 0; i < task_to_handle.size(); ++i)
			{
				TaskData* taskdata = task_to_handle.at(i)->m_task_data_ptr;

				taskdata->m_ceres.clear();
				taskdata->m_final.clear();
				taskdata->m_success.clear();
			}

		m_tasks = task_to_handle;

		this->setCTVATable();
		SortTask(m_tasks);

		this->NMRallocation();
		this->parallelComputing();
		this->Voting();
}
//Ho
void Ceres::robustComputing_modify (vector<Task*> task_to_handle){
	printf("RobustComputing Start, %lu Tasks are parallel executing \n", task_to_handle.size());
		
		//	reset m_tasks
			m_tasks.clear();
		//	reset taskdata in task_to_handle
			for (unsigned i = 0; i < task_to_handle.size(); ++i)
			{
				TaskData* taskdata = task_to_handle.at(i)->m_task_data_ptr;

				taskdata->m_ceres.clear();
				taskdata->m_final.clear();
				taskdata->m_success.clear();
			}

		m_tasks = task_to_handle;

		this->setCTVATable_modify();
		SortTask(m_tasks);

		this->NMRallocation();
		this->parallelComputing();
		this->Voting();
}
/*
void Ceres::robustComputing_CVA_alloaction (vector<Task*> task_to_handle){
	printf("\nRobustComputing Start, %lu Tasks are parallel executing \n", task_to_handle.size());

	//	reset m_tasks
			m_tasks.clear();
		//	reset taskdata in task_to_handle
			for (unsigned i = 0; i < task_to_handle.size(); ++i)
			{
				TaskData* taskdata = task_to_handle.at(i)->m_task_data_ptr;

				taskdata->m_ceres.clear();
				taskdata->m_final.clear();
				taskdata->m_success.clear();
			}

		m_tasks = task_to_handle;

		this->setCTVATable_only_CVA();
		SortTask(m_tasks);

		this->NMRallocation();
		this->parallelComputing();
		this->Voting();
}*/



//Ho
void Ceres::GG_robustCombuting(vector<Task*> task_to_handle , const int algo_type){
	printf("\n==================================================================================\n");

	printf("\nRobustComputing Start, %lu Tasks are parallel executing \n", task_to_handle.size());
		
		//	reset m_tasks
			m_tasks.clear();
		//	reset taskdata in task_to_handle
			for (unsigned i = 0; i < task_to_handle.size(); ++i)
			{
				TaskData* taskdata = task_to_handle.at(i)->m_task_data_ptr;

				taskdata->m_ceres.clear();
				taskdata->m_final.clear();
				taskdata->m_success.clear();
			}

		m_tasks = task_to_handle;

		cout << "start setAllReliaTable... " << endl ;
		setAllReliaTable() ;
		cout << "start sortTaskByIns... " << endl ;
		sortTaskByIns() ;
// simulation
        if(algo_type==1)
		    this->GG_NMR_v1();
        else if(algo_type==2)
		    this->GG_NMR_v2();
        else if(algo_type==3)
		    this->GG_NMR_v3();
        else if(algo_type==4)
		    this->GG_NMR_v4();
        else
            cerr << "algo type has someing wrong "<< endl ;
		//this->GG_test_NMR();
		//NMR_1
		//this->GG_1_NMR();
		////NMR_3
		//this->GG_3_NMR();
		////NMR_5
		//this->GG_5_NMR();
		this->parallelComputing();
		this->Voting();
		//this->NMRVoting();

    printf("\n==================================================================================\n");
}
//Ho
void Ceres::GG_random_robustCombuting(vector<Task*> task_to_handle){
	printf("\n==================================================================================\n");

	printf("\nRobustComputing Start, %lu Tasks are parallel executing \n", task_to_handle.size());
		
		//	reset m_tasks
			m_tasks.clear();
		//	reset taskdata in task_to_handle
			for (unsigned i = 0; i < task_to_handle.size(); ++i)
			{
				TaskData* taskdata = task_to_handle.at(i)->m_task_data_ptr;

				taskdata->m_ceres.clear();
				taskdata->m_final.clear();
				taskdata->m_success.clear();
			}

		m_tasks = task_to_handle;

		cout << "start setAllReliaTable... " << endl ;
		setAllReliaTable() ;
		//cout << "start sortTaskByIns... " << endl ;
		//sortTaskByIns() ;
// simulation
		//NMR_1
		//this->GG_1_NMR();
		////NMR_3
		//this->GG_3_NMR();
		////NMR_5
		this->GG_5_NMR();
		//this->GG_test_NMR() ;
        this->parallelComputing();
		//this->Voting();
        this->NMRVoting();
    printf("\n==================================================================================\n");
}

void Ceres::NMRallocation (void){
	/*********************************
		Developer Interface
		 - Algorithm NMRallocation :

		from CTVA_table to
			1. m_duplicate_num
			2. m_coreIDs
		of task in m_tasks
	**********************************/
	
	/*******************
		don't touch
	*******************/	
		m_core_manager->refreshResourceTable();
		// reset duplicate num
		for (unsigned task_th = 0; task_th < m_tasks.size(); ++task_th)
			m_tasks.at(task_th)->m_duplicate_num = 0;

	// build CTVA_score_table
	vector< vector<float> > CVTA_score_table;// 1/N
	
	// printf("\n CVTA_score_table: \n");
	for (unsigned task_th = 0; task_th < m_tasks.size(); ++task_th){
		CVTA_score_table.push_back( CVA_score_table() );

		unsigned N = m_core_manager->m_core_error_rate.size();
		
		for (unsigned core_type = 0; core_type < N; ++core_type)
		{
			CVTA_score_table.at(task_th).push_back( 1./float( m_tasks.at(task_th)->CVA_table.at(core_type) ) );
			// printf("%f ",CVTA_score_table.at(task_th).at(core_type));
		}
		// printf("\n");
	}

	vector<unsigned> core_num_list = m_core_manager->m_core_distribute;
	vector<unsigned> tasks_core_num;

	const unsigned C =  core_num_list.size();
	const unsigned T =  m_tasks.size();

	unsigned assignment_matrix[C][T];

	for (unsigned t = 0; t < T; ++t)
		tasks_core_num.push_back(0);

	for (unsigned c = 0; c < C; ++c)
		for(unsigned t = 0; t< T;++t)
			assignment_matrix[c][t] = 0;
	
	/*-------------------------
		Consider Priority:
			1.garbage_coreN_vec
			2.delta_mat(vec)
			3.score_vec
	-------------------------*/
	vector<unsigned> garbage_coreN_vec;
	vector<float> score_vec;

	vector< vector<unsigned> > delta_mat;// last core_type not consider
	for (unsigned i = 0; i < C-1; ++i)
		delta_mat.push_back(vector<unsigned>(T));
	
	// printf("\n delta_mat[T][C-1]: \n");
	for (unsigned t = 0; t < T; ++t){
		garbage_coreN_vec.push_back( std::count(m_tasks.at(t)->CVA_table.begin(), m_tasks.at(t)->CVA_table.end(),999) );
		score_vec.push_back( 0.f );

		for (unsigned c = 0; c < C - 1; ++c)
		{
			delta_mat.at(c).at(t) = m_tasks.at(t)->CVA_table.at(c + 1) - m_tasks.at(t)->CVA_table.at(c);
			// printf("%3d ",delta_mat.at(c).at(t));
		}
		// printf("\n");
	}

	vector<unsigned> task_handle;
	for (int t = 0; t < T; ++t)
		task_handle.push_back(t);
	
	bool finish = false;
	for (unsigned core_type = 0; core_type < C; ++core_type)
	{
		if(finish == true)
			break;

		vector<unsigned> delta_vec;
		if (core_type < C - 1) 
			delta_vec = delta_mat.at(core_type);

		while( core_num_list.at(core_type) > 0 ){

			// printf("\n******************************************\n");
			// pop_out task in task_handle if 
			// 	1. score achieved
			// 	2. handle 999 garbage cores
			for (unsigned i = 0; i < task_handle.size(); ++i){

				unsigned task_id = task_handle.at(i); //  

				if ( m_tasks.at(task_id)->CVA_table.at(core_type) == 999 ){
					if ( tasks_core_num.at(task_id) > 0 )
					{
						// avoid N = 2
						if (tasks_core_num.at(task_id) == 2)
						{
							cout<<"Notice: even condition!"<<endl;
						}
						else{
							task_handle.erase(std::remove(task_handle.begin(), task_handle.end(), task_id), task_handle.end());
						}
						
						// printf("Dropout garbage core for task %2d = ( \n",task_id);
					}
				}
				else if ( score_vec.at(task_id) >= 1.f ){
					// avoid N = 2
					if (tasks_core_num.at(task_id) == 2)
					{
						cout<<"Notice: even condition!"<<endl;// won't happen!
					}
					else{
						task_handle.erase(std::remove(task_handle.begin(), task_handle.end(), task_id), task_handle.end());
					}
	
					// printf("Sore achieved for task %2d = ) \n",task_id);
				}
			}

			if(task_handle.size() > 0){
				--core_num_list.at(core_type);

				// printf("task_handle: ");
				// for (int i = 0; i < task_handle.size(); ++i)
				// 	printf(" %d|",task_handle.at(i));
				// printf("\n");

				/*--------------------------------------------------------------------------
					Target: which task_type ??
					and then

					++assignment_matrix[core_type][task_type]
					score_vec.at(task_type) += CVTA_score_table[task_type][core_type]
				---------------------------------------------------------------------------*/
				unsigned task_type = task_handle.back();// default value

				unsigned garbage_coreN_most = 0; 
				for (unsigned i = 0; i < task_handle.size(); ++i)
					if (  garbage_coreN_vec.at(task_handle.at(i)) == garbage_coreN_vec.at(task_handle.back()) )
						garbage_coreN_most = garbage_coreN_vec.at(task_handle.at(i));
				// printf("\nStep 1:\n");
				// printf("garbage_coreN_most: %d \n",garbage_coreN_most);

				vector<unsigned> task_cand_step1; 
				for (int i = 0; i < task_handle.size(); ++i)
					if (  garbage_coreN_vec.at(task_handle.at(i)) == garbage_coreN_most )
						task_cand_step1.push_back(task_handle.at(i));

				if (task_cand_step1.size() == 1){
					// printf("~most garbage_coreN~\n");

					// Step 1
					task_type = task_cand_step1.back();
				}
				else
				{
					// printf("~same garbage_coreN~\n");
					
					if (core_type == C - 1){
						// Bypass Step2 and jump to Step3
						
						//Step 3
						float score_lowest = 1.f;
						for (int i = task_cand_step1.size() - 1; i >= 0 ; --i)
							if (  score_vec.at(task_cand_step1.at(i)) < score_lowest ){
								task_type = task_cand_step1.at(i);
								score_lowest = score_vec.at(task_type);
							}
						// printf("\nBypass Step2 and jump to Step3:\n");
						// printf("score_lowest: %f @ task_type: %d \n",score_lowest,task_type); 
					}
					else{
						unsigned delta_bigest = 0; 
						for (int i = 0; i < task_cand_step1.size(); ++i)
							if (  delta_vec.at(task_cand_step1.at(i)) > delta_bigest )
								delta_bigest = delta_vec.at(task_cand_step1.at(i));
						// printf("\nStep 2:\n");
						// printf("delta_bigest: %d \n",delta_bigest);

						vector<unsigned> task_cand_step2; 
						for (int i = 0; i < task_cand_step1.size(); ++i)
							if (  delta_vec.at(task_cand_step1.at(i)) == delta_bigest )
								task_cand_step2.push_back(task_cand_step1.at(i));

						if(task_cand_step2.size() == 1){
							// printf("~most Delta~\n");

							// Step 2
							task_type = task_cand_step2.back();
						}
						else{
							// printf("~same delta~\n");

							//Step 3
							float score_lowest = 1.f;
							for (int i = task_cand_step2.size() - 1; i >= 0 ; --i)
								if (  score_vec.at(task_cand_step2.at(i)) < score_lowest ){
									task_type = task_cand_step2.at(i);
									score_lowest = score_vec.at(task_type);
								}
							// printf("\nStep 3:\n");
							// printf("score_lowest: %f @ task_type: %d \n",score_lowest,task_type);
						}
					}
				}
				/*--------------
					and then
				--------------*/
				++assignment_matrix[core_type][task_type];
				++tasks_core_num.at(task_type);
				score_vec.at(task_type) += float( CVTA_score_table.at(task_type).at(core_type) );

				// printf("\n---core_type %d assign to task_type %d --- \n",core_type,task_type);
				// printf("score gain      : %3f \n",CVTA_score_table.at(task_type).at(core_type));
				// printf("accumulate score: %3f \n",score_vec.at(task_type));
			}
			else{
				finish = true;
				break;
			}
		}
	}

	/*-------------------------------
		transfer assignment mtrix to 
			1. m_duplicate_num
			2. m_coreIDs
		of task in m_tasks
	---------------------------------*/
	for (unsigned task_th = 0; task_th < m_tasks.size(); ++task_th){

		for (unsigned core_th = 0; core_th < m_core_manager->m_resource_table.size(); ++core_th){
			
			for (unsigned i = 0; i < assignment_matrix[core_th][task_th]; ++i)
			{
				m_tasks.at(task_th)->m_coreIDs.push_back( m_core_manager->m_resource_table.at(core_th).front() );
				m_core_manager->m_resource_table.at(core_th).erase( m_core_manager->m_resource_table.at(core_th).begin() );
			}
		}

		m_tasks.at(task_th)->m_duplicate_num = tasks_core_num.at(task_th);
	}

	printf("\nAssignment finished...\n");
	printf("assignmentmatrix: \n");

	for (int t = 0; t < T; ++t){
		for (int c = 0; c < C; ++c)
			printf("%2d ", assignment_matrix[c][t]);
		printf("\n");
	}
	printf("\n");

	printf("--------------------------------------\n");
	printf("| task accumulate score | total core |\n");
	printf("--------------------------------------\n");
	for (int t = 0; t < T; ++t){ 
		printf("|  T%d  |    %f    |    %3d     |\n", t + 1, score_vec.at(t), tasks_core_num.at(t));
		printf("--------------------------------------\n");
	}
	printf("\n");
}

void Ceres::CVA_allocation (){
	// refresh
	m_core_manager->refreshResourceTable();
	for (unsigned task_th = 0; task_th < m_tasks.size(); ++task_th)
            m_tasks.at(task_th)->m_duplicate_num = 0;
    // build CTVA table

    vector< vector<float> > CVTA_score_table;// 1/N
    
    // printf("\n CVTA_score_table: \n");
    for (unsigned task_th = 0; task_th < m_tasks.size(); ++task_th){
        CVTA_score_table.push_back( CVA_score_table() );

        unsigned N = m_core_manager->m_core_error_rate.size();
        
        for (unsigned core_type = 0; core_type < N; ++core_type)
        {
            CVTA_score_table.at(task_th).push_back( 1./float( m_tasks.at(task_th)->CVA_table.at(core_type) ) );
            // printf("%f ",CVTA_score_table.at(task_th).at(core_type));
        }
        // printf("\n");
    }
    
   

}


void Ceres::parallelComputing (void){

	vector< vector<pthread_t> > pthread_list_per_task;

	//	generate pthread object
	for (unsigned task_th = 0; task_th < m_tasks.size(); ++task_th)
	{
		vector<pthread_t> tem_p_vec;	
		pthread_list_per_task.push_back(tem_p_vec);

		unsigned N = m_tasks.at(task_th)->m_duplicate_num;

		for (unsigned n_th = 0; n_th < N; ++n_th)
		{
			pthread_t tem_p;
			pthread_list_per_task.at(task_th).push_back(tem_p);
		}
	}

	for (unsigned task_th = 0; task_th < m_tasks.size(); ++task_th)
	{
		unsigned N = m_tasks.at(task_th)->m_duplicate_num;

		PthreadFuncPointer pthread_func_ptr = m_tasks.at(task_th)->m_pthread_func_ptr;

		//	generate pthread and parallel computing
		for (unsigned n_th = 0; n_th < N; ++n_th)
		{
			// int core_id = m_tasks.at(task_th)->m_coreIDs.back();
			int core_id = m_tasks.at(task_th)->m_coreIDs[n_th];

			/////backtodec
			TaskData* temp = new TaskData( *(m_tasks.at(task_th)->m_task_data_ptr) );
		 	
			//temp->setErr( m_core_manager->m_core_error_rate.at(core_id-1) );
			temp->setErr( 1- (exp(-1*(m_core_manager->hsieh_core_error_rate.at(core_id-1)) * (m_tasks.at(task_th)->m_instruct_count) / (m_tasks.at(task_th)->m_operator_count)))); // Wes modified
			m_tasks.at(task_th)->m_task_data_ptrs_NMR.push_back(temp);
			
			TaskData* task_data_ptr =  m_tasks.at(task_th)->m_task_data_ptrs_NMR.at(n_th);
			//HSIEH
			//task_data_ptr->setErr( m_core_manager->m_core_error_rate.at(core_id-1) );
			task_data_ptr->setErr( 1- (exp(-1*(m_core_manager->hsieh_core_error_rate.at(core_id-1)) * (m_tasks.at(task_th)->m_instruct_count) / (m_tasks.at(task_th)->m_operator_count)))); // Wes modified

//cout<<"Task "<<task_th<<" runs on core id "<<core_id<<endl;
//cout << "lambda = " << m_core_manager->hsieh_core_error_rate.at(core_id-1) << endl;
//cout << "new error rate = " << 1- (exp(-1*(m_core_manager->hsieh_core_error_rate.at(core_id-1)) * (m_tasks.at(task_th)->m_instruct_count) / (m_tasks.at(task_th)->m_operator_count))) << endl;
//cout << endl;

			//	tell Sniper platform
			tellSniperCoreID( core_id );

			/////=======add ErrorRate member in TaskData and then propagate!!!!!======
			pthread_create(&pthread_list_per_task.at(task_th).at(n_th), NULL, (*pthread_func_ptr), (void*) task_data_ptr);

		}
	}
	
	//	pthread_join(p,NULL);
	for (int task_th = 0; task_th < pthread_list_per_task.size(); ++task_th)
	{
		for (unsigned n_th = 0; n_th < pthread_list_per_task.at(task_th).size(); ++n_th)
		{
			pthread_join(pthread_list_per_task.at(task_th).at(n_th),NULL);
		}
	}

}

void Ceres::Voting (void){
	printf("Start Voting ... \n\n");
	/*********************************
		Developer Interface
			- Voting Mechanism 	
		
		    - from m_ceres in m_task_data_ptrs_NMR 
		      to   m_finals in m_task_data_ptr 
		      of task in m_tasks 
	**********************************/
	for (unsigned task_th = 0; task_th < m_tasks.size(); ++task_th){

		int x = 0 ;
		unsigned N = m_tasks.at(task_th)->m_duplicate_num;
        if (N == 0) continue ;
		unsigned out_num_total = m_tasks.at(task_th)->m_task_data_ptrs_NMR.at(0)->m_ceres.size();

		TaskData *final_data = m_tasks.at(task_th)->m_task_data_ptr;
		for (unsigned out_num = 0; out_num < out_num_total; ++out_num){

			vector<float> out_cands;
			float final_val;

			for (unsigned n = 0; n < N; ++n){
				Element out = m_tasks.at(task_th)->m_task_data_ptrs_NMR.at(n)->m_ceres.at(out_num);
				//cout << "***task_th*n*out._num= " << task_th << ";" <<  n << ";" << out._num << endl ;
				out_cands.push_back(out._num);
			}

			// Majority Voting Mechanism ?? or > 2 Voting Mechanism ??
			bool is_success = false;

			for (int i = 0; i < out_cands.size(); ++i){
				float out = out_cands.at(i);
				unsigned count = std::count(out_cands.begin(), out_cands.end(), out);

				if (count > 1 || N == 1){
					final_val = out;
					is_success = true;
				}
			}

			if (is_success == false){
				//printf("Voting Failed *_* \n");
				//final_val = out_cands.at(0); // the result of best core in m_coreIDs

				//Ho
				unsigned lessID = m_tasks.at(task_th)->m_coreIDs[0] ;
				unsigned temp_i = 0 ; 
				for(unsigned i = 1 ; i <  m_tasks.at(task_th)->m_coreIDs.size() ; i++ ){
					if(m_tasks.at(task_th)->m_coreIDs[i] < lessID){
						lessID = m_tasks.at(task_th)->m_coreIDs[i] ;
						temp_i = i ;
					}
				}
				final_val = out_cands[temp_i] ;					
			}

			//cout << "***task_th*out._num= " << task_th << ";" << final_val << endl ;

			final_data->m_final.push_back(final_val);
			final_data->m_success.push_back(is_success);
		}

		/*******************
			don't touch
		*******************/	
		// delete TaskData in m_task_data_ptrs_NMR in list m_tasks
		for (unsigned n = 0; n < N; ++n)
			delete m_tasks.at(task_th)->m_task_data_ptrs_NMR.at(n);
		m_tasks.at(task_th)->m_task_data_ptrs_NMR.clear();
	}

}

// Wes, majority voting
void Ceres::NMRVoting (void){
	printf("Start NMR Voting ... \n\n");
	/*********************************

		Developer Interface
			- Voting Mechanism 	
		
		    - from m_ceres in m_task_data_ptrs_NMR 

		      to   m_finals in m_task_data_ptr 
		      of task in m_tasks 
	**********************************/

	for (unsigned task_th = 0; task_th < m_tasks.size(); ++task_th){

		int x = 0 ;

		unsigned out_num_total = m_tasks.at(task_th)->m_task_data_ptrs_NMR.at(0)->m_ceres.size();
		unsigned N = m_tasks.at(task_th)->m_duplicate_num;

		TaskData *final_data = m_tasks.at(task_th)->m_task_data_ptr;

		for (unsigned out_num = 0; out_num < out_num_total; ++out_num){

			vector<float> out_cands;
			float final_val;

			for (unsigned n = 0; n < N; ++n){
				Element out = m_tasks.at(task_th)->m_task_data_ptrs_NMR.at(n)->m_ceres.at(out_num);
				//cout << "***task_th*n*out._num= " << task_th << ";" <<  n << ";" << out._num << endl ;
				out_cands.push_back(out._num);
			}

			// Majority Voting Mechanism ?? or > 2 Voting Mechanism ??
			bool is_success = false;

			for (int i = 0; i < out_cands.size(); ++i){
				float out = out_cands.at(i);
				unsigned count = std::count(out_cands.begin(), out_cands.end(), out);

				if (count > ((float)N/2.0) || N == 1){  // count > 1
					final_val = out;
					is_success = true;
				}
			}

			if (is_success == false){
				//printf("Voting Failed *_* \n");
				//final_val = out_cands.at(0); // the result of best core in m_coreIDs
				
				//Wes
				final_val = out_cands[rand()%N];

				//Ho
				/*unsigned lessID = m_tasks.at(task_th)->m_coreIDs[0] ;
				unsigned temp_i = 0 ; 
				for(unsigned i = 1 ; i <  m_tasks.at(task_th)->m_coreIDs.size() ; i++ ){
					if(m_tasks.at(task_th)->m_coreIDs[i] < lessID){
						lessID = m_tasks.at(task_th)->m_coreIDs[i] ;
						temp_i = i ;
					}
				}
				final_val = out_cands[temp_i] ;	*/				
			}

			//cout << "***task_th*out._num= " << task_th << ";" << final_val << endl ;

			final_data->m_final.push_back(final_val);
			final_data->m_success.push_back(is_success);
		}

		/*******************
			don't touch
		*******************/	
		// delete TaskData in m_task_data_ptrs_NMR in list m_tasks
		for (unsigned n = 0; n < N; ++n)
			delete m_tasks.at(task_th)->m_task_data_ptrs_NMR.at(n);
		m_tasks.at(task_th)->m_task_data_ptrs_NMR.clear();
	}

}



//Hsieg
bool taskCompByIns(Task* a,Task* b)
{
	if (a->m_instruct_count > b->m_instruct_count)
		return true;
	else 
		return false;
}

void Ceres::sortTaskByIns()
{
	sort(m_tasks.begin(),m_tasks.end(),taskCompByIns);
}	

void Ceres::setAllReliaTable(){
	cout<<"set setReliaTable for each task..."<<endl;
	for (int task_th = 0; task_th < m_tasks.size(); ++task_th){
		m_tasks.at(task_th)->setReliaTable(m_core_manager);
	}
}

void Ceres::GG_NMR_v1(){
	m_core_manager->refreshResourceTable();
    //first allocation 
    // For each task , allocate a good core .
    for(unsigned i=0 ; i < m_tasks.size() ; i++ ){
    	m_tasks[i]->m_duplicate_num = 0 ;
        get_the_first_alloc_coreID_from_CVAtable(m_tasks[i]) ;
    }
    
    //now all tasks are allocated a good core
    for(unsigned i=0 ; i < m_tasks.size() ; i++ ){
        //select the remained best core to the tasks
        //get_best_coreID_from_CVAtable(m_tasks[i]) ;
        //compute_complement_coreID(m_tasks[i])  ;
        if(  (m_tasks[i]->Relia_table[ (m_tasks[i]->m_coreTypes.at(0))]) < (m_tasks[i]->m_reliability)  ){
            if(get_best_coreID_from_CVAtable(m_tasks[i]) ){
                compute_complement_coreID(m_tasks[i])  ;
            }
        }
    }



}
void Ceres::GG_NMR_v2(){
	m_core_manager->refreshResourceTable();
    //first allocation 
    // For each task , allocate a good core .
    for(unsigned i=0 ; i < m_tasks.size() ; i++ ){
    	m_tasks[i]->m_duplicate_num = 0 ;
        get_the_first_relai_larger_than_target(m_tasks[i]) ;
            
    }
    
    //now all tasks are allocated a good core
    for(unsigned i=0 ; i < m_tasks.size() ; i++ ){
        //select the remained best core to the tasks
        //cout << "m_tasks[i]->Relia_table[ (m_tasks[i]->m_coreTypes.at(0))  " << m_tasks[i]->Relia_table[ (m_tasks[i]->m_coreTypes.at(0))] << endl ; 
        //cout << "m_tasks[i]->m_reliability   "  << m_tasks[i]->m_reliability << endl ;

        if(  (m_tasks[i]->Relia_table[ (m_tasks[i]->m_coreTypes.at(0))]) < (m_tasks[i]->m_reliability)  ){
            if(get_best_coreID_from_CVAtable(m_tasks[i]) ){
                compute_complement_coreID(m_tasks[i])  ;
            }
        }
    }
}

void Ceres::GG_NMR_v3(){
	m_core_manager->refreshResourceTable();
    //first allocation 
    for(unsigned i=0 ; i < m_tasks.size() ; i++ ){
    	m_tasks[i]->m_duplicate_num = 0 ;
        get_the_core( 0 , m_tasks[i]) ;
    }
    
    //now all tasks are allocated a good core
    for(unsigned i=0 ; i < m_tasks.size() ; i++ ){
        if(  (m_tasks[i]->Relia_table[ (m_tasks[i]->m_coreTypes.at(0))]) < (m_tasks[i]->m_reliability)  ){
            if(get_best_coreID_from_CVAtable(m_tasks[i]) ){
                compute_complement_coreID(m_tasks[i])  ;
            }
        }
    }
}


void Ceres::GG_NMR_v4(){
	m_core_manager->refreshResourceTable();
    //first allocation 
    for(unsigned i=0 ; i < m_tasks.size() ; i++ ){
    	m_tasks[i]->m_duplicate_num = 0 ;
        //get_the_core( 0 , m_tasks[i]) ;
        get_the_first_relai_larger_than_target(m_tasks[i]) ;
    }
    
    //now all tasks are allocated a good core
    for(unsigned i=0 ; i < m_tasks.size() ; i++ ){
        if(  (m_tasks[i]->Relia_table[ (m_tasks[i]->m_coreTypes.at(0))]) < (m_tasks[i]->m_reliability)  ){
            if(get_best_coreID_from_CVAtable(m_tasks[i]) ){
                compute_complement_coreID(m_tasks[i])  ;
            }
        }
    }
    for(unsigned i=0 ; i < m_tasks.size() ; i++ ){
        if( m_tasks[i]-> m_duplicate_num == 3 ){
            float R_1 = (m_tasks[i]->Relia_table[ (m_tasks[i]->m_coreTypes.at(0))]);
            float R_2 = (m_tasks[i]->Relia_table[ (m_tasks[i]->m_coreTypes.at(1))]);
            float R_3 = (m_tasks[i]->Relia_table[ (m_tasks[i]->m_coreTypes.at(2))]);
            if( (R_1 + (1-R_1)*R_2*R_3) < m_tasks[i]->m_reliability ){
                get_the_core( 0 , m_tasks[i]) ;
            }
        }
    }
    for(unsigned i=0 ; i < m_tasks.size() ; i++ ){
        if( m_tasks[i]-> m_duplicate_num == 4 ){
            float R_1 = (m_tasks[i]->Relia_table[ (m_tasks[i]->m_coreTypes.at(0))]);
            float R_2 = (m_tasks[i]->Relia_table[ (m_tasks[i]->m_coreTypes.at(1))]);
            float R_3 = (m_tasks[i]->Relia_table[ (m_tasks[i]->m_coreTypes.at(2))]);
            float R_4 = (m_tasks[i]->Relia_table[ (m_tasks[i]->m_coreTypes.at(3))]);
            float R_total = R_1 + (1-R_1)*R_2    *R_3    *R_4
                                + (1-R_1)*(1-R_2)*R_3    *R_4
                                + (1-R_1)*R_2    *(1-R_3)*R_4
                                + (1-R_1)*R_2    *R_3    *(1-R_4) ;
            if(  R_total < m_tasks[i]->m_reliability ){
                get_the_core( 0 , m_tasks[i]) ;
            }
        }
    }
}


void Ceres::GG_test_NMR(){
	m_core_manager->refreshResourceTable();
    
    //it will only one task
    	m_tasks[0]->m_duplicate_num = 0 ;
        get_the_core(0 , m_tasks[0]) ;
}

void Ceres::get_the_first_relai_larger_than_target(Task* myTask){
	const double target_relia =  myTask->m_reliability ;
	//cout << "!!!!!" << target_relia << endl ;
    int       core_type ;
    unsigned  Core_ID   ;
    bool      gotten_core = false ;

    //cout << "myTask->Relia_table.size()" << myTask->Relia_table.size() << endl ;

    for(int i=myTask->Relia_table.size()-1 ; i > -1  ; i--){
    //	cout << "myTask->Relia_table[i]" << myTask->Relia_table[i] << endl ;
    
        if(myTask->Relia_table[i] > target_relia ){
            core_type = i ;
            get_the_core(core_type , myTask) ;
            gotten_core = true ;
            break ;
        }
      
    }    
    if(gotten_core == false){
        get_the_core( 0 , myTask ) ;
    }

}

void  Ceres::get_the_first_alloc_coreID_from_CVAtable(Task* myTask ){
    const double target_relia =  myTask->m_reliability ;
    int core_type ;
    unsigned Core_ID   ;
    bool     gotten_core = false ;

    
    for(unsigned i=0 ; i< (myTask->Relia_table.size())  ; i++){
        
        if(myTask->Relia_table[i] < (target_relia - 0.05) ){
            core_type = i ;
            get_the_core(core_type , myTask) ;
            gotten_core = true ;
            break ;
        }
        //get_the_core
    }    
    // every core > target - 0.
    if(gotten_core == false){
        core_type = (myTask->Relia_table.size()-1) ;
        get_the_core(core_type, myTask ) ;
    }
    
}

bool Ceres::get_the_core(const int core_type , Task* myTask){
    unsigned selected_ID ; 

    int temp_core_type = core_type ;

    bool if_gotten = false ;
        while(temp_core_type> -1 ){
            if( m_core_manager->m_resource_table[temp_core_type].size() > 0  ){
                selected_ID =  m_core_manager->m_resource_table[temp_core_type][0] ;
                m_core_manager->m_resource_table[temp_core_type].erase(m_core_manager->m_resource_table[temp_core_type].begin()) ;
                if_gotten = true ;
                break ;
            }
            temp_core_type-- ;
        }

        if(if_gotten==false){
            temp_core_type = core_type + 1 ;
                while( temp_core_type < m_core_manager->m_resource_table.size() ){
                	//cout << "m_resource_table[temp_core_type].size()   " << m_core_manager->m_resource_table[temp_core_type].size() << "   " <<  temp_core_type << endl ; 
                    if( m_core_manager->m_resource_table[temp_core_type].size() > 0  ){
                    selected_ID =  m_core_manager->m_resource_table[temp_core_type][0] ;
                    m_core_manager->m_resource_table[temp_core_type].erase(m_core_manager->m_resource_table[temp_core_type].begin()) ;
                    if_gotten = true ;
                    break ;
                }
                temp_core_type++ ;
            }
        }

        //printf(" set core_ID %3d , Core_type = %3d ,to Task %10d ....... \n" , selected_ID , temp_core_type , myTask->m_instruct_count );
        //printf("myTask->m_duplicate_num  =  %d \n", myTask->m_duplicate_num);
        if(myTask->Relia_table[temp_core_type] > 0.1 || myTask->m_duplicate_num == 0 ){
        //if(myTask->Relia_table[temp_core_type] > 0 || myTask->m_duplicate_num == 0 ){
        	if(if_gotten == false){
                cout << "gotten fail" << endl ;    
                return false ;
            }
            printf(" set core_ID %3d , Core_type = %3d ,to Task %10lu ....... \n" , selected_ID , temp_core_type , myTask->m_instruct_count );
            myTask->m_coreTypes.push_back(temp_core_type);
            myTask->m_coreIDs.push_back(selected_ID) ; 
            myTask->m_duplicate_num++;  //= 3  ; 
            return true ;
        }
        else{
        	return false ;
        }
}


bool Ceres::get_best_coreID_from_CVAtable(Task* myTask){
    return get_the_core(0,myTask) ;
}


void Ceres::compute_complement_coreID(Task* myTask ){
    double complement_relia ;
   
    int type_1 = myTask->m_coreTypes[0] ;
    int type_2 = myTask->m_coreTypes[1] ;

    double p1 = myTask->Relia_table[type_1];
    double p2 = myTask->Relia_table[type_2];

    bool if_gotten = false ; 
    if(p2 > p1){
        double temp = p1 ;
        p1 = p2 ;
        p2 = temp ;
    }

    double target_p3 = (myTask->m_reliability - p1) / ((1-p1)*p2) ; 

    if(target_p3 < 0.1 ){
    	target_p3 = 0.1 ;
    }

    for(int i = myTask->Relia_table.size()-1 ; i > -1 ; i-- ){
        if(myTask->Relia_table[i] > target_p3 ){
            get_the_core(i , myTask) ;
            if_gotten = true ;
            break ;
        } 
    }
    if(if_gotten == false){
        get_the_core(0 , myTask ); 
    }

}


void Ceres::GG_1_NMR(){
	m_core_manager->refreshResourceTable();
    
	//srand(time(NULL));
    //it will only one task
	for(unsigned i=0 ; i < m_tasks.size() ; i++ ){
    	    m_tasks[i]->m_duplicate_num = 0 ;     
    	    m_tasks.at(i)->m_coreIDs.clear();      
    	}

    for(unsigned i=0 ; i < m_tasks.size() ; i++ ){
    	int core_id ;
    	
    	core_id =  transform(rand()%24) ;
    	get_the_core(core_id , m_tasks[i] ) ;
    }
}

void Ceres::GG_3_NMR(){
	m_core_manager->refreshResourceTable();
    
    //it will only one task
	for(unsigned i=0 ; i < m_tasks.size() ; i++ ){
    	    m_tasks[i]->m_duplicate_num = 0 ;           
    	    m_tasks.at(i)->m_coreIDs.clear();      
    	}  

    for(unsigned i=0 ; i < m_tasks.size() ; i++ ){
    	int core_type ;
    	
    	for(unsigned k = 0 ; k < 3 ; k ++ ){	
    		core_type =  transform(rand()%24) ;
    		
    		//printf("core_type  =  %d \n",  core_type );
    		bool if_get_in_NMR_3 = get_the_core(core_type , m_tasks[i] ) ;
    		//printf("if_get_in_NMR_3  =  %d \n",  if_get_in_NMR_3 );
    	}
    }
}

void Ceres::GG_5_NMR(){
	m_core_manager->refreshResourceTable();
    
    //it will only one task
	for(unsigned i=0 ; i < m_tasks.size() ; i++ ){
    	    m_tasks[i]->m_duplicate_num = 0 ;           
    	    m_tasks.at(i)->m_coreIDs.clear();      
    	}  
    int count_total = 0; 
    for(unsigned k = 0 ; k < 5 ; k ++ ){	
        for(unsigned i=0 ; i < m_tasks.size() ; i++ ){
    	    
            int core_type ;
            
            bool if_get = false ;
    		int select_count = 0 ;
    		while(if_get==false){
                select_count ++ ;
                core_type =  transform(rand()%24) ;	
    		    //printf("core_type  =  %d \n",  core_type );
                if_get = get_the_core(core_type , m_tasks[i] ) ;
                if(select_count > 100) break ;
            }
            count_total++;
    		printf("total  =  %d \n",  count_total );
            if(count_total == 24) return ;
    	}
    }
}

int Ceres::transform(int a){
    if(a==0)
        return 0;
    else if(a>0 && a<4)
        return 1;
    else if(a>3 && a<12)
        return 2;
    else if(a>11 && a<20)
        return 3;
    else if(a>19 && a<23)
        return 4;
    else if(a>22)
        return 5;   
}


#endif

