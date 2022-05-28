#! /usr/local/bin/bash

function DEBUG(){
  [ "$_DEBUG" == "on" ] && echo $@ || :
  for i in {1..10}
  do
    DEBUG echo $i
  done
}

DEBUG
