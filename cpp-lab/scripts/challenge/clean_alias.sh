#! /usr/local/bin/bash

# 找到某个目录下的所有的失效链接
while read -r line;
do
  # echo "line is $line";
  # TODO 这里应该用正则表达式来获取到地址名，不然可能有文件名带空格的
  name=`ls -l $line | awk '{print $11}'`
  ab_name=`dirname $line`/$name
  # echo "name is $name"
  # echo "ab_name is $ab_name"
  if [ ! -e "$name" -a ! -e "$ab_name" ];then
    echo "无效链接: $line --> $ab_name"
  fi
done <<< `find "$1" -maxdepth 1 -type l`

