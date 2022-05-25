declare -A dic
dic=()
process(){
  echo $1;
}
a="m w m a x x a w m w m m"

read -r -a array <<< $a;
for word in ${array[@]}
do
  if [ "$word" != 'm' -a "$word" != 'w' ];then
    echo "get extra word " $word
    continue;
  elif [ -n "${dic[$word]}" ];then
    dic["$word"]=`expr ${dic[$word]} + 1`
  else
    dic["$word"]=1

  fi
done

for key in ${!dic[@]}
do 
  echo $key ": " ${dic[$key]}
done