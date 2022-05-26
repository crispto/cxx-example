#! /usr/local/bin/bash
set +x
while read -r line;
do 
  tmp=`echo $line | awk '{print $1, $9}'`
  echo $tmp
  name=`echo $tmp | awk '{print $2}'`
  echo "$name" | xargs -n 1 chmod o-w
  ls -l "$name" | awk '{print $1, $9}'

done <<< `find $1 -perm -o=w -print0 | xargs -0 ls -l`