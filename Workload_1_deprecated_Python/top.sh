#!/bin/bash
PID=$(cat process.pid)
touch finaltopnode.csv
#for i in {1..15}
#do
    #top -b -p $PID -n 1 d 1| sed -n '8, 12{s/^ *//;s/ *$//;s/  */,/gp;};12q' >> finaltopnode.csv
    
#done
top -b -p $PID -n 15 d 1 >> finaltopnode.csv
