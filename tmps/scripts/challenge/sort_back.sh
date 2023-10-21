 # 排序登陆者日志
 last| awk '{printf "%s%s\t\t", $1, OFS} {for(i=3;i<=6;i++) printf "%s%s", $i, (i<6 ? OFS : ORS)}'|sort -u -k1,1 |grep -v -E '(wtmp|^\s)'


count=()
while read line;do
if [ -z ${count[$line]} ];then
  count[$line]=1
else
  let count[$line]+=1
fi
done <<< `ps -ef|grep -v '^UID'|awk '{print $1}'`

for key in ${!count[@]};do
  echo $key ": " ${count[$key]}
done