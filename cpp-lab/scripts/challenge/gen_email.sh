#! /usr/local/bin/bash
while read -r line;
do
  echo -e -n "$line@bit.edu.cn\t"
done < $1
echo