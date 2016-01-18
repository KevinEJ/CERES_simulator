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

#define LAYER_SIZE 9 

using namespace std;

void Ceres_GenResultFile (Ceres &ceres, vector<Task*> task_to_handle, unsigned times);

int main(int argc,char* argv[])
{
	if (argc!=5)
	{
		cerr<<"Usage: ./ceres_exe <numbers> <envir_type> <dot_protect> <sig_protect>"<<endl;
		return -1;
	}

	istringstream ss(argv[1]);
	int RUNsize;
	if (!(ss>>RUNsize)||!(RUNsize>0))
	{	
		cerr<<"Usage: ./ceres_exe <numbers> <envir_type> <dot_protect> <sig_protect>"<<endl;
		cerr<<"Invalid number "<<argv[1]<<endl;
		return -1;
	}

	string envir(argv[2]);
	istringstream dicc(argv[2]);
	int env_type;
	//if ((envir!="1")&&(envir!="3")&&(envir!="5"))
	if (!(dicc>>env_type)||!(env_type>0))
	{
		cerr<<"Usage: ./ceres_exe <numbers> <envir_type> <dot_protect> <sig_protect>"<<endl;
		cerr<<"Invalid type "<<argv[2]<<endl;
		return -1;
	}

	istringstream ss1(argv[3]);
	istringstream ss2(argv[4]);
	float dot_protect;
	float sig_protect;
	if (!(ss1>>dot_protect)||!(dot_protect>0))
	{	
		cerr<<"Usage: ./ceres_exe <numbers> <envir_type> <dot_protect> <sig_protect>"<<endl;
		cerr<<"Invalid number "<<argv[3]<<endl;
		return -1;
	}

	if (!(ss2>>sig_protect)||!(sig_protect>0))
	{	
		cerr<<"Usage: ./ceres_exe <numbers> <envir_type> <dot_protect> <sig_protect>"<<endl;
		cerr<<"Invalid number "<<argv[4]<<endl;
		return -1;
	}
		
	srand(time(NULL));
	
	Ceres my_ceres(envir);
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
	int task_num = 39;

	/*--------------------
		create TaskData
	--------------------*/
	TaskData* tds[task_num];
	for (int i = 0; i < task_num; ++i)
		tds[i] = new TaskData();
	
	vector<Task*> task_to_handle[9];//nine stages!!!
	/*---------------------------------------------------------------------
		create task(&task_kernel, instruction_num, reliability, &taskdata)
	---------------------------------------------------------------------*/
	Task* tasks[task_num];
	//-------------------//
	printf("Set values \n");

	//five inputs
	vector<Element> input_1 ; //= { 0,0,1,1 } ;
	vector<Element> input_2 ; //= { 0,1,0,1 } ;
	vector<Element> input_3 ;
	vector<Element> input_4 ;
	vector<Element> input_5 ;

	// WHY 500???? HSIEH//// 
	for(unsigned num_input = 0 ; num_input < RUNsize ; num_input ++){
		for(unsigned int i=0;i<32;++i)
		{
			if (i/16==0)				
				(input_1).push_back(Element(0,0));
			else		
				(input_1).push_back(Element(1,0));

			if (i/8==0)
				(input_2).push_back(Element(0,0));
			else if (i/8==1)
				(input_2).push_back(Element(1,0));
			else if (i/8==2)
				(input_2).push_back(Element(0,0));
			else
				(input_2).push_back(Element(1,0));

			if (i/4==0)
				(input_3).push_back(Element(0,0));
			else if (i/4==1)
				(input_3).push_back(Element(1,0));
			else if (i/4==2)
				(input_3).push_back(Element(0,0));
			else if (i/4==3)
				(input_3).push_back(Element(1,0));
			else if (i/4==4)
				(input_3).push_back(Element(0,0));
			else if (i/4==5)
				(input_3).push_back(Element(1,0));
			else if (i/4==6)
				(input_3).push_back(Element(0,0));
			else
				(input_3).push_back(Element(1,0));

			if (i/2==0)
				(input_4).push_back(Element(0,0));
			else if (i/2==1)
				(input_4).push_back(Element(1,0));
			else if (i/2==2)
				(input_4).push_back(Element(0,0));
			else if (i/2==3)
				(input_4).push_back(Element(1,0));
			else if (i/2==4)
				(input_4).push_back(Element(0,0));
			else if (i/2==5)
				(input_4).push_back(Element(1,0));
			else if (i/2==6)
				(input_4).push_back(Element(0,0));
			else if (i/2==7)
				(input_4).push_back(Element(1,0));
			else if (i/2==8)
				(input_4).push_back(Element(0,0));
			else if (i/2==9)
				(input_4).push_back(Element(1,0));
			else if (i/2==10)
				(input_4).push_back(Element(0,0));
			else if (i/2==11)
				(input_4).push_back(Element(1,0));
			else if (i/2==12)
				(input_4).push_back(Element(0,0));
			else if (i/2==13)
				(input_4).push_back(Element(1,0));
			else if (i/2==14)
				(input_4).push_back(Element(0,0));
			else
				(input_4).push_back(Element(1,0));

			if (i%2==0)
				(input_5).push_back(Element(0,0));
			else
				(input_5).push_back(Element(1,0));

		}

	}

	vector<Element>* pointer_input_1 = &input_1; 
	vector<Element>* pointer_input_2 = &input_2;
	vector<Element>* pointer_input_3 = &input_3;
	vector<Element>* pointer_input_4 = &input_4;
	vector<Element>* pointer_input_5 = &input_5;

	printf("Set initial inputs \n");

	for(unsigned int j=0;j<6;++j)
	{
		tds[j]->m_inputs[0]= (pointer_input_1);
		tds[j]->m_inputs[1]= (pointer_input_2);
		tds[j]->m_inputs[2]= (pointer_input_3);
		tds[j]->m_inputs[3]= (pointer_input_4);
		tds[j]->m_inputs[4]= (pointer_input_5);
	}

	//layer 1 and sigmoid
	for(unsigned int k=0;k<6;++k)
	{
		tds[k+6]->m_inputs[0] = &tds[k]->m_buffer ;
	}

    //layer 1 and 2
	for(unsigned int k=0;k<6;++k)
	{
		for(unsigned int q=0;q<6;++q)
		{
			tds[k+12]->m_inputs[q]= &tds[q+6]->m_buffer ;
		}
	}

	//layer 2 and sigmoid
	for(unsigned int k=0;k<6;++k)
	{
		tds[k+18]->m_inputs[0]= &tds[k+12]->m_buffer ;
	}

	//layer 2 and 3
	for(unsigned int k=0;k<6;++k)
	{
		for(unsigned int q=0;q<6;++q)
		{
			tds[k+24]->m_inputs[q]= &tds[q+18]->m_buffer ;
		}
	}

	//layer 3 and sigmoid
	for(unsigned int k=0;k<6;++k)
		tds[k+30]->m_inputs[0]= &tds[k+24]->m_buffer ;

	//layer 3 and 4
	for(unsigned int q=0;q<6;++q)
		tds[36]->m_inputs[q]=&tds[q+30]->m_buffer;

	//layer 4 and sigmoid
	tds[37]->m_inputs[0]=&tds[36]->m_buffer ;

	//last
	tds[38]->m_inputs[0] = &tds[37]->m_buffer ;

//----------------------------------------------------------------------------//

	//layer 1 , two input using 18000, five use 45000
	tasks[0] = new Task(&task1_1_kernel, 760  , dot_protect , tds[0], 11);
	tasks[1] = new Task(&task1_2_kernel, 760  , dot_protect , tds[1], 11);
	tasks[2] = new Task(&task1_3_kernel, 760  , dot_protect , tds[2], 11);
	tasks[3] = new Task(&task1_4_kernel, 760  , dot_protect , tds[3], 11);
	tasks[4] = new Task(&task1_5_kernel, 760  , dot_protect , tds[4], 11);
	tasks[5] = new Task(&task1_6_kernel, 760  , dot_protect , tds[5], 11);
	
	//layer 1 begin sigmoid
	for(unsigned int k=0;k<6;++k)
	{
		tasks[k+6] = new Task(&task_kernel_sigmoid, 190  , sig_protect , tds[k+6], 3);//sig
	}

	//layer 2
	tasks[12] = new Task(&task2_1_kernel, 800  , dot_protect , tds[12], 13);
	tasks[13] = new Task(&task2_2_kernel, 800  , dot_protect , tds[13], 13);
	tasks[14] = new Task(&task2_3_kernel, 800  , dot_protect , tds[14], 13);
	tasks[15] = new Task(&task2_4_kernel, 800  , dot_protect , tds[15], 13);
	tasks[16] = new Task(&task2_5_kernel, 800  , dot_protect , tds[16], 13);
	tasks[17] = new Task(&task2_6_kernel, 800  , dot_protect , tds[17], 13);
	
	//layer 2 begin sigmoid
	for(unsigned int k=0;k<6;++k)
	{
		tasks[k+18] = new Task(&task_kernel_sigmoid, 190  , sig_protect , tds[k+18], 3);//sig
	}

	//layer 3
	tasks[24] = new Task(&task3_1_kernel, 800  , dot_protect , tds[24], 13);
	tasks[25] = new Task(&task3_2_kernel, 800  , dot_protect , tds[25], 13);
	tasks[26] = new Task(&task3_3_kernel, 800  , dot_protect , tds[26], 13);
	tasks[27] = new Task(&task3_4_kernel, 800  , dot_protect , tds[27], 13);
	tasks[28] = new Task(&task3_5_kernel, 800  , dot_protect , tds[28], 13);
	tasks[29] = new Task(&task3_6_kernel, 800  , dot_protect , tds[29], 13);

	//layer 3 begin sigmoid
	for(unsigned int k=0;k<6;++k)
	{
		tasks[k+30] = new Task(&task_kernel_sigmoid, 190  , sig_protect , tds[k+30], 3);//sig
	}

	//layer 4
	tasks[36] = new Task(&task4_1_kernel, 800  , dot_protect , tds[36], 13);

	//layer 4 begin sigmoid
	tasks[37] = new Task(&task_kernel_sigmoid, 190  , sig_protect , tds[37], 3);

	//Just doing threshold!! not considered as a task!!!!
	tasks[38] = new Task(&task_kernel_last, 1  , 0.00001 , tds[38], 3);

    ////jjjjjjj

	//layer 1
	for(unsigned int k=0;k<6;++k)
		task_to_handle[0].push_back(tasks[k]);
	
	//layer 1 sig
	for(unsigned int k=0;k<6;++k)
		task_to_handle[1].push_back(tasks[k+6]);

	//layer 2
	for(unsigned int k=0;k<6;++k)
		task_to_handle[2].push_back(tasks[k+12]);

	//layer 2 sig
	for(unsigned int k=0;k<6;++k)
		task_to_handle[3].push_back(tasks[k+18]);

	//layer 3
	for(unsigned int k=0;k<6;++k)
		task_to_handle[4].push_back(tasks[k+24]);

	//layer 3 sig
	for(unsigned int k=0;k<6;++k)
		task_to_handle[5].push_back(tasks[k+30]);

	//layer 4
	task_to_handle[6].push_back(tasks[36]);

	//layer 4 sig
	task_to_handle[7].push_back(tasks[37]);

	task_to_handle[8].push_back(tasks[38]);

//---------------------------error_free result------------------------------//
	ofstream err_free_file;
	err_free_file.open("./Result/error_free_result.txt", ios::out|ios::trunc);
	
	// put error_free result into m_ceres in original taskdata
	printf("Computimg error_free result on core_id 0 ...\n");

	err_free_file<<"Error_Free Result :\n";
	
for (unsigned layer_count = 0 ; layer_count < LAYER_SIZE ; layer_count++){

	err_free_file<<"================================================"<<endl;
	err_free_file<<" Stages "<< layer_count <<endl;
	
	unsigned num_task = task_to_handle[layer_count].size();

	for (unsigned t_th = 0; t_th < num_task; ++t_th){

		err_free_file<<"  task_"<<t_th<<"\n"<<"         ";

		Task* task_ptr = task_to_handle[layer_count].at(t_th);

		( *(task_ptr->m_pthread_func_ptr) )( (void*) task_ptr->m_task_data_ptr );

		vector<Element> err_free = task_ptr->m_task_data_ptr->m_ceres;
		
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
	err_free_file.close();

//---------------------------error_free result------------------------------//

	string exp_type_1 = "Random" ;  
	//string exp_type_2 = "Random_" ;

cout<<"Error free ends... "<<endl<<endl;

ofstream final_file; 
final_file.open("./Result/final_result.txt", ios::out|ios::app);

cout<<"===========================TOTAL RUN STARTS...============================="<<endl;
//////////THIS i is RUN SIZE!!!!/////////////////////
for(size_t i = 0 ; i < RUNsize ;i++){
	printf("First layer \n");
//	
	if(exp_type_1 == "Random")
		my_ceres.GG_robustCombuting(task_to_handle[0]);
	else
		my_ceres.robustComputing_modify(task_to_handle[0]);
	
	for (unsigned int k=0;k<6;++k)
		tds[k]->m_buffer = tds[k]->m_final ;

	printf("First layer before sigmoid \n");
//	
	if(exp_type_1 == "Random")
		my_ceres.GG_robustCombuting(task_to_handle[1]);
	else
		my_ceres.robustComputing_modify(task_to_handle[1]);		
	
	for (unsigned int k=0;k<6;++k)
		tds[k+6]->m_buffer = tds[k+6]->m_final ;



	printf("Second layer \n");
	
	if(exp_type_1 == "Random")
		my_ceres.GG_robustCombuting(task_to_handle[2]);	
	else	
		my_ceres.robustComputing_modify(task_to_handle[2]);

	for (unsigned int k=0;k<6;++k)
		tds[k+12]->m_buffer = tds[k+12]->m_final ;


	printf("Second layer before sigmoid \n");
	
	if(exp_type_1 == "Random")
		my_ceres.GG_robustCombuting(task_to_handle[3]);	
	else	
		my_ceres.robustComputing_modify(task_to_handle[3]);

	for (unsigned int k=0;k<6;++k)
		tds[k+18]->m_buffer = tds[k+18]->m_final ;

	printf("Third layer \n");
	
	if(exp_type_1 == "Random")
		my_ceres.GG_robustCombuting(task_to_handle[4]);	
	else	
		my_ceres.robustComputing_modify(task_to_handle[4]);

	for (unsigned int k=0;k<6;++k)
		tds[k+24]->m_buffer = tds[k+24]->m_final ;

	printf("Third layer before sigmoid \n");
	
	if(exp_type_1 == "Random")
		my_ceres.GG_robustCombuting(task_to_handle[5]);	
	else	
		my_ceres.robustComputing_modify(task_to_handle[5]);

	for (unsigned int k=0;k<6;++k)
		tds[k+30]->m_buffer = tds[k+30]->m_final ;

	printf("Fourth layer \n");
	
	if(exp_type_1 == "Random")
		my_ceres.GG_robustCombuting(task_to_handle[6]);	
	else	
		my_ceres.robustComputing_modify(task_to_handle[6]);

	tds[36]->m_buffer = tds[36]->m_final ;

	if(exp_type_1 == "Random")
		my_ceres.GG_robustCombuting(task_to_handle[7]);	
	else	
		my_ceres.robustComputing_modify(task_to_handle[7]);

	tds[37]->m_buffer = tds[37]->m_final ;


	my_ceres.robustComputing_modify(task_to_handle[8]);

	tds[38]->m_buffer = tds[38]->m_final ;
	
	final_file<<"Count "<<i<<endl;

//==================output_file===============================================//
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
}final_file.close();

	return (0);
}



typedef vector<float> result;

void Ceres_GenResultFile (Ceres &ceres, vector<Task*> task_to_handle, unsigned times){
	unsigned T = task_to_handle.size();

	/*-------------------
	   Error Free Result
	--------------------*/
	ofstream err_free_file;
	err_free_file.open("./Result/error_free_result.txt", ios::out|ios::trunc);
	
	// put error_free result into m_ceres in original taskdata
	printf("Computimg error_free result on core_id 0 ...\n");

	err_free_file<<"Error_Free Result :\n";

	for (unsigned t_th = 0; t_th < T; ++t_th){

		err_free_file<<" task_"<<t_th<<"\n"<<"         ";

		Task* task_ptr = task_to_handle.at(t_th);

		// call kernel function
		( *(task_ptr->m_pthread_func_ptr) )( (void*) task_ptr->m_task_data_ptr );
		vector<Element> err_free = task_ptr->m_task_data_ptr->m_ceres;

		for (unsigned i = 0; i < err_free.size(); ++i){
			err_free_file<<err_free.at(i)._num<<" ";
		}
		err_free_file<<"\n";

		//reset m_ceres
		task_ptr->m_task_data_ptr->m_ceres.clear();
	}
	err_free_file.close();

	/*-------------------
	   	Final Result
	--------------------*/
	ofstream final_file; 
	final_file.open("./Result/final_result.txt", ios::out|ios::app);

	for (unsigned t = 1; t <= times; ++t)
	{
		// original senior's 
		//ceres.robustComputing(task_to_handle);
		// original senior's modify 
		//ceres.robustComputing_modify(task_to_handle);
		// ours NMR and NMR_1,3,5
		ceres.GG_robustCombuting(task_to_handle);
		

		// final_file<<" time "<<t<<":\n";

		for (unsigned t_th = 0; t_th < T; ++t_th){

			final_file<<"  task "<<t_th<<"\n"<<"         ";

			vector<Element> final = task_to_handle.at(t_th)->m_task_data_ptr->m_final;

			for (unsigned i = 0; i < final.size(); ++i){
				final_file<<final.at(i)._num<<" ";
			}
			final_file<<"\n";
		}
		final_file<<"\n";
		final_file.flush();
	}	
	final_file.close();
}


