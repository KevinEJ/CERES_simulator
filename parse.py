import os
import pdb

Random_tasks = ['4','5','6','7','8']
Env          = ["env3" , "env4" , "env5" , "env6" , "env7" , "env8" ]
algo         = ["CTVA" , "NMR_5" , "GG_4"]
Result = []
for i in range(len(Random_tasks)):
    for t in range(len(algo)):
        for y in range(len(Env)):
            Result.append("rd_num." + Env[y] + ".95.100." + algo[t] + "." + Random_tasks[i])

#random_env1.95.50.CTVA.4

result_list = open("total_result.csv" , 'a')
result_list.write(Result[0]) 
result_list.write("\n") 
for idx in range(len(Result)):
    os.chdir(Result[idx]) # change work dir
    accu = open("accu.txt" , 'r')
    accu_list =  accu.readlines()
    accu_sp   = list(accu_list[1].split(' '))
    accuracy_str = str(accu_sp[3][0:3])
    core_sp  = list(accu_list[2].split(' '))
    core_str = str(core_sp[1])

    Result_sp = Result[idx].split('.')
    result_list.write( Result_sp[1] + ' , ' + Result_sp[4] + ' , '+ Result_sp[5] + ' , ')
    result_list.write( accuracy_str + ' , ' + core_str )
    #pdb.set_trace()
    os.chdir("../") # change work dir
