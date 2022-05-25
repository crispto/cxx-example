#! /usr/local/bin/bash
#一个无限循环，让黑名单中的进程一启动就被杀死
# 注意 用 wc -l 来判断输出是否存在不准确，空的和一条都是1
danger_list=("danger.sh")

while true;
do
  echo 'scanning...'
  for app in ${danger_list[@]};do
      ps=`ps | grep $app |grep -v "grep"`
      n1=`echo $ps | wc -l`
      if [ -n "$ps" -a $n1 -gt 0 ];then
        echo "发现危险 app $ps, n1: $n1"
        pid=`echo -e $ps| awk '{print $1}'`
        kill -9 $pid
      fi
  done
  sleep 3
done