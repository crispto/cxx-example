#!/bin/sh

echo 'start'

target='mlu-sdk3d-test'
if [ ! -e $target ];then
  echo 'not exit, will mkdir'
  mkdir $target
fi
cd $target

dest='a.txt'
if [ ! -e  $dest ];then
  echo 'create new '
  echo 'hello world' > ./$dest
else
  echo 'add content'
  echo 'add content' >> ./$dest
fi
echo '---------------------------------``'
cat ./$dest