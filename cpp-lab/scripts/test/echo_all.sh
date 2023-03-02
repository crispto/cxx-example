#! /usr/local/bin/bash

if [ "$1" != "-p" ];then
  echo 'invalid param'
  exit -1
else
  echo "succss: $2"
fi