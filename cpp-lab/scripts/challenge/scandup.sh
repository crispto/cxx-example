#! /usr/local/bin/bash
hash=()
while read -r line;do
  echo "line is $line"
  read sum file <<< `echo "$line"`
  if [ "${hash[x$sum]}" != '' ];then
    echo "sum is " $sum
    echo "duplicate file " $file -- ${hash[x$sum]}
  else
    hash[x$sum]="$file"
  fi
done <<< `find $1 -name "*.txt" -maxdepth 2 | xargs shasum`