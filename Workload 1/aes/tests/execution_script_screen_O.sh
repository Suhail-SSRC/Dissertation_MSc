#!/bin/bash

#Executing CBC Mode

# 115 MB

#cd CBC_tests/115MB_CBC_V2_THP/ ; ./script_optimization_O.sh ; ./script_CBC_Optimization_Openmp_O.sh;

# 676 MB

#cd ../676MB_CBC_V2_THP/ ; ./script_optimization_O.sh ; ./script_CBC_Optimization_Openmp_O.sh;

# 1351 MB

#cd ../1351MB_CBC_V2_THP/ ; ./script_optimization_O.sh ; script_CBC_Optimization_Openmp_O.sh;


#Executing CFB Mode

# 115 MB

cd CFB_tests/115MB_CFB_V2_THP/ ; ./script_optimization_O.sh ; ./script_CFB_Optimization_Openmp_O.sh;

# 676 MB

cd ../676MB_CFB_THP/ ; ./script_optimization_O.sh ; ./script_CFB_Optimization_Openmp_O.sh;

# 1351 MB

cd ../1351MB_CFB_V2_THP/ ; ./script_optimization_O.sh ; ./script_CFB_Optimization_Openmp_O.sh;


#Executing ECB Mode

# 115 MB

cd ../../ECB_tests/115MB_ECB_V2_THP/ ; ./script_optimization_O.sh ; ./script_ECB_Optimization_OpenMP_O.sh ; ./script_ECB_Optimization_threads_O.sh;

# 676 MB

cd ../676MB_ECB_V2_THP/ ;./script_optimization_O.sh ; ./script_ECB_Optimization_OpenMP_O.sh ; ./script_ECB_Optimization_threads_O.sh;

# 1351 MB

cd ../1351MB_ECB_V2_THP/ ; ./script_optimization_O.sh ; ./script_ECB_Optimization_OpenMP_O.sh ; ./script_ECB_Optimization_threads_O.sh;

