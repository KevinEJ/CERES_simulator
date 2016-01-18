#!/bin/bash

#Predefined Reliab. and Enviro. type
aa=00
bb=95
a=`printf "%02g" $aa`
b=`printf "%02g" $bb`
cc=1
dd=3
ee=5
ff=100
c=`printf "%01g" $cc`
d=`printf "%01g" $dd`
e=`printf "%01g" $ee`
f=`printf "%01g" $ff`

#Parameters to set to run exp.
num=1000
algo=rd_num
ceres_env=$f
ceres_env_num=$ff

envir_setting1=./CERES/environment1
envir_setting2=./CERES/environment2
envir_setting3=./CERES/environment3
envir_setting4=./CERES/environment4
envir_setting5=./CERES/environment5
envir_setting6=./CERES/environment6
envir_setting7=./CERES/environment7
envir_setting8=./CERES/environment8

for env in $envir_setting3 $envir_setting4 $envir_setting5 $envir_setting6 $envir_setting7 $envir_setting8 
do
    for rand_num in 4 6 8 10 12
    do
        #for algo_type in CTVA GG_1 GG_2 GG_3 GG_4
        for algo_type in CTVA GG_4 NMR_5
        do
            if [ $env == $envir_setting3 ];then
                dir=$algo.env3.$b.$ceres_env.$algo_type.$rand_num
            elif [ $env == $envir_setting4 ];then
                dir=$algo.env4.$b.$ceres_env.$algo_type.$rand_num
            elif [ $env == $envir_setting5 ];then
                dir=$algo.env5.$b.$ceres_env.$algo_type.$rand_num
            elif [ $env == $envir_setting6 ];then
                dir=$algo.env6.$b.$ceres_env.$algo_type.$rand_num
            elif [ $env == $envir_setting7 ];then
                dir=$algo.env7.$b.$ceres_env.$algo_type.$rand_num
            elif [ $env == $envir_setting8 ];then
                dir=$algo.env8.$b.$ceres_env.$algo_type.$rand_num
            else
                echo "dir wrong"
            fi
            
            #dir=$algo.$env.$b.$ceres_env.$algo_type.$rand_num
            mkdir -p $dir
            mkdir -p $dir/log
            mkdir -p Result
            echo "Running $algo_type envir_type [$env]  envir = [$ceres_env]  rand_num = [$rand_num] ..."
            	log=$dir/log/$dir.log
                if [ "$algo_type" == "CTVA" ];then
                    #echo " ./ceres_exe $num $ceres_env_num 0.95 0 $env $rand_num >& $log "
            	    ./ceres_exe $num $ceres_env_num 0.95 0 $env $rand_num >& $log
                elif [ "$algo_type" == "GG_1" ];then
            	    ./ceres_exe $num $ceres_env_num 0.95 1 $env $rand_num >& $log
                elif [ "$algo_type" == "GG_2" ];then
            	    ./ceres_exe $num $ceres_env_num 0.95 2 $env $rand_num >& $log
                elif [ "$algo_type" == "GG_3" ];then
            	    ./ceres_exe $num $ceres_env_num 0.95 3 $env $rand_num >& $log
                elif [ "$algo_type" == "GG_4" ];then
            	    ./ceres_exe $num $ceres_env_num 0.95 4 $env $rand_num >& $log
                elif [ "$algo_type" == "NMR_5" ];then
            	    ./ceres_exe $num $ceres_env_num 0.95 5 $env $rand_num >& $log
                else
                    echo "algo_type wrong!!!!!!!!!"
                fi
            echo "Checking with python script ..."
            	log=$dir/log/$dir.stats.log
            	python Newtest.py >& $log
            echo "Copying Result ..."
            	cp Result/accu.txt $dir/accu.txt
            	cp Result/error_free_result.txt $dir/error_free_result.txt
            	cp Result/final_result.txt $dir/final_result.txt
            echo "Cleaning Result ..."
            	rm -rf Result/*
        done
    done
done
           




#
#
#dir=$algo.$b.$ceres_env.CTVA.4
#mkdir -p $dir
#mkdir -p $dir/log
#mkdir -p Result
#echo "Running $algo envir = [$ceres_env], dot = [$b], sig = [$a] ..."
#	log=$dir/log/$dir.log
#	./ceres_exe $num $ceres_env_num 0.95 0 $envir_setting1 4 >& $log
#echo "Checking with python script ..."
#	log=$dir/log/$dir.stats.log
#	python Newtest.py >& $log
#echo "Copying Result ..."
#	cp Result/accu.txt $dir/accu.txt
#	cp Result/error_free_result.txt $dir/error_free_result.txt
#	cp Result/final_result.txt $dir/final_result.txt
#echo "Cleaning Result ..."
#	rm -rf Result/*
#
#dir=$algo.$b.$ceres_env.GG_1.4
#mkdir -p $dir
#mkdir -p $dir/log
#mkdir -p Result
#echo "Running $algo envir = [$ceres_env], dot = [$b], sig = [$b] ..."
#	log=$dir/log/$dir.log
#	./ceres_exe $num $ceres_env_num 0.95 1 $envir_setting1 4 >& $log
#echo "Checking with python script ..."
#	log=$dir/log/$dir.stats.log
#	python Newtest.py >& $log
#echo "Copying Result ..."
#	cp Result/accu.txt $dir/accu.txt
#	cp Result/error_free_result.txt $dir/error_free_result.txt
#	cp Result/final_result.txt $dir/final_result.txt
#echo "Cleaning Result ..."
#	rm -rf Result/*
#
#dir=$algo.$b.$ceres_env.GG_2.4
#mkdir -p $dir
#mkdir -p $dir/log
#mkdir -p Result
#echo "Running $algo envir = [$ceres_env], dot = [$b], sig = [$b] ..."
#	log=$dir/log/$dir.log
#	./ceres_exe $num $ceres_env_num 0.95 2 $envir_setting1 4 >& $log
#echo "Checking with python script ..."
#	log=$dir/log/$dir.stats.log
#	python Newtest.py >& $log
#echo "Copying Result ..."
#	cp Result/accu.txt $dir/accu.txt
#	cp Result/error_free_result.txt $dir/error_free_result.txt
#	cp Result/final_result.txt $dir/final_result.txt
#echo "Cleaning Result ..."
#	rm -rf Result/*
#
### random = 6
#
#dir=$algo.$b.$ceres_env.CTVA.6
#mkdir -p $dir
#mkdir -p $dir/log
#mkdir -p Result
#echo "Running $algo envir = [$ceres_env], dot = [$b], sig = [$a] ..."
#	log=$dir/log/$dir.log
#	./ceres_exe $num $ceres_env_num 0.95 0 $envir_setting1 6 >& $log
#echo "Checking with python script ..."
#	log=$dir/log/$dir.stats.log
#	python Newtest.py >& $log
#echo "Copying Result ..."
#	cp Result/accu.txt $dir/accu.txt
#	cp Result/error_free_result.txt $dir/error_free_result.txt
#	cp Result/final_result.txt $dir/final_result.txt
#echo "Cleaning Result ..."
#	rm -rf Result/*
#
#dir=$algo.$b.$ceres_env.GG_1.6
#mkdir -p $dir
#mkdir -p $dir/log
#mkdir -p Result
#echo "Running $algo envir = [$ceres_env], dot = [$b], sig = [$b] ..."
#	log=$dir/log/$dir.log
#	./ceres_exe $num $ceres_env_num 0.95 1 $envir_setting1 6 >& $log
#echo "Checking with python script ..."
#	log=$dir/log/$dir.stats.log
#	python Newtest.py >& $log
#echo "Copying Result ..."
#	cp Result/accu.txt $dir/accu.txt
#	cp Result/error_free_result.txt $dir/error_free_result.txt
#	cp Result/final_result.txt $dir/final_result.txt
#echo "Cleaning Result ..."
#	rm -rf Result/*
#
#dir=$algo.$b.$ceres_env.GG_2.6
#mkdir -p $dir
#mkdir -p $dir/log
#mkdir -p Result
#echo "Running $algo envir = [$ceres_env], dot = [$b], sig = [$b] ..."
#	log=$dir/log/$dir.log
#	./ceres_exe $num $ceres_env_num 0.95 2 $envir_setting1 6 >& $log
#echo "Checking with python script ..."
#	log=$dir/log/$dir.stats.log
#	python Newtest.py >& $log
#echo "Copying Result ..."
#	cp Result/accu.txt $dir/accu.txt
#	cp Result/error_free_result.txt $dir/error_free_result.txt
#	cp Result/final_result.txt $dir/final_result.txt
#echo "Cleaning Result ..."
#	rm -rf Result/*
#
###random 8
#
#dir=$algo.$b.$ceres_env.CTVA.8
#mkdir -p $dir
#mkdir -p $dir/log
#mkdir -p Result
#echo "Running $algo envir = [$ceres_env], dot = [$b], sig = [$a] ..."
#	log=$dir/log/$dir.log
#	./ceres_exe $num $ceres_env_num 0.95 0 $envir_setting1 8 >& $log
#echo "Checking with python script ..."
#	log=$dir/log/$dir.stats.log
#	python Newtest.py >& $log
#echo "Copying Result ..."
#	cp Result/accu.txt $dir/accu.txt
#	cp Result/error_free_result.txt $dir/error_free_result.txt
#	cp Result/final_result.txt $dir/final_result.txt
#echo "Cleaning Result ..."
#	rm -rf Result/*
#
#dir=$algo.$b.$ceres_env.GG_1.8
#mkdir -p $dir
#mkdir -p $dir/log
#mkdir -p Result
#echo "Running $algo envir = [$ceres_env], dot = [$b], sig = [$b] ..."
#	log=$dir/log/$dir.log
#	./ceres_exe $num $ceres_env_num 0.95 1 $envir_setting1 8 >& $log
#echo "Checking with python script ..."
#	log=$dir/log/$dir.stats.log
#	python Newtest.py >& $log
#echo "Copying Result ..."
#	cp Result/accu.txt $dir/accu.txt
#	cp Result/error_free_result.txt $dir/error_free_result.txt
#	cp Result/final_result.txt $dir/final_result.txt
#echo "Cleaning Result ..."
#	rm -rf Result/*
#
#dir=$algo.$b.$ceres_env.GG_2.8
#mkdir -p $dir
#mkdir -p $dir/log
#mkdir -p Result
#echo "Running $algo envir = [$ceres_env], dot = [$b], sig = [$b] ..."
#	log=$dir/log/$dir.log
#	./ceres_exe $num $ceres_env_num 0.95 2 $envir_setting1 8 >& $log
#echo "Checking with python script ..."
#	log=$dir/log/$dir.stats.log
#	python Newtest.py >& $log
#echo "Copying Result ..."
#	cp Result/accu.txt $dir/accu.txt
#	cp Result/error_free_result.txt $dir/error_free_result.txt
#	cp Result/final_result.txt $dir/final_result.txt
#echo "Cleaning Result ..."
#	rm -rf Result/*
#
##random 10
#
#dir=$algo.$b.$ceres_env.CTVA.10
#mkdir -p $dir
#mkdir -p $dir/log
#mkdir -p Result
#echo "Running $algo envir = [$ceres_env], dot = [$b], sig = [$a] ..."
#	log=$dir/log/$dir.log
#	./ceres_exe $num $ceres_env_num 0.95 0 $envir_setting1 10 >& $log
#echo "Checking with python script ..."
#	log=$dir/log/$dir.stats.log
#	python Newtest.py >& $log
#echo "Copying Result ..."
#	cp Result/accu.txt $dir/accu.txt
#	cp Result/error_free_result.txt $dir/error_free_result.txt
#	cp Result/final_result.txt $dir/final_result.txt
#echo "Cleaning Result ..."
#	rm -rf Result/*
#
#dir=$algo.$b.$ceres_env.GG_1.10
#mkdir -p $dir
#mkdir -p $dir/log
#mkdir -p Result
#echo "Running $algo envir = [$ceres_env], dot = [$b], sig = [$b] ..."
#	log=$dir/log/$dir.log
#	./ceres_exe $num $ceres_env_num 0.95 1 $envir_setting1 10 >& $log
#echo "Checking with python script ..."
#	log=$dir/log/$dir.stats.log
#	python Newtest.py >& $log
#echo "Copying Result ..."
#	cp Result/accu.txt $dir/accu.txt
#	cp Result/error_free_result.txt $dir/error_free_result.txt
#	cp Result/final_result.txt $dir/final_result.txt
#echo "Cleaning Result ..."
#	rm -rf Result/*
#
#dir=$algo.$b.$ceres_env.GG_2.10
#mkdir -p $dir
#mkdir -p $dir/log
#mkdir -p Result
#echo "Running $algo envir = [$ceres_env], dot = [$b], sig = [$b] ..."
#	log=$dir/log/$dir.log
#	./ceres_exe $num $ceres_env_num 0.95 2 $envir_setting1 10 >& $log
#echo "Checking with python script ..."
#	log=$dir/log/$dir.stats.log
#	python Newtest.py >& $log
#echo "Copying Result ..."
#	cp Result/accu.txt $dir/accu.txt
#	cp Result/error_free_result.txt $dir/error_free_result.txt
#	cp Result/final_result.txt $dir/final_result.txt
#echo "Cleaning Result ..."
#	rm -rf Result/*

