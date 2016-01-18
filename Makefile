all: test
g++ -g -o  ceres_exe CERES/execute.cpp CERES/data.cpp -pthread -std=c++0x
