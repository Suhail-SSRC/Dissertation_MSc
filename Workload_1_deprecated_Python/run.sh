#!/bin/bash

echo $$ > /tmp/myprocess.pid

for i in {1..15}
do
echo "$i"
sleep 2
printf "\n"

done

#In another file you may need the PID, just an enviornmental variable and call it by cat the/file/location
# pid = $(cat /tmp/myprocess.pid)      to call it use $pid