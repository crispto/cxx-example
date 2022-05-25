#!/bin/bash
filename='dict_test.sh'
n=1
process(){
  echo "OS distribution line no. $n : $1"
  n=$((n+1))
}
while read line;
do
# for read each line
  process "$line";
done < $filename