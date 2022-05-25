declare -a dic
dic=()




process(){
  echo $1;
}
a="m w m"

read -r -a array <<< $a;
for word in ${array[@]}
do
  if [ -n "${dic[$word]}" ];then
    dic["$word"]=`expr ${dic[$word]} + 1`
  else
    dic["$word"]=1
  fi
done

for key in ${!dic[@]}
do 
  echo $key ": " ${dic[$key]}
done