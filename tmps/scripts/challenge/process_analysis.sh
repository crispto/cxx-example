#! /usr/local/bin/bash
declare -A tty_map
tty_map=()
process(){
  tty=$1;
  process=$2;
  if [ -n "${tty_map[$1]}" ];then
    tmp=`expr ${tty_map[$tty]} + 1`
    tty_map[$tty]=$tmp
  else 
    tty_map[$tty]=1
  fi
}

ps -Af | awk '{printf "%-8s %-8s\n", $6, $8}' > tmp.txt

while read -r line ; 
  do process $line;
    done < tmp.txt

echo 'start report'
for x in ${!tty_map[@]}
do
  printf "%-8s %-8s\n" $x ${tty_map[$x]}
done