#! /bin/bash
if [ $UID -ne 0 ]; then
  echo 'you are not super use'
else
  echo 'you are super user'
fi