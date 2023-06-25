#!/bin/bash

#Executing CBC Mode

# 115 MB

cd CBC_tests/115MB_CBC/ ; ./script_CBC_Optimization_Openmp.sh;

# 676 MB

cd ../676MB_CBC/ ; ./script_CBC_Optimization_Openmp.sh;

# 1351 MB

cd ../1351MB_CBC ; ./script_CBC_Optimization_Openmp.sh;


#Executing CFB Mode

# 115 MB

cd ../../CFB_tests/115MB_CFB ; ./script_CFB_Optimization_Openmp.sh;

# 676 MB

cd ../676MB_CFB ; ./script_CFB_Optimization_Openmp.sh;

# 1351 MB

cd ../1351MB_CFB ; ./script_CFB_Optimization_Openmp.sh;
