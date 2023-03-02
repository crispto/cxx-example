base=$1
if [ ! -e $base -o ! -d $base ];then
  echo "not exists or not directory"
  exit -1
fi

# pwd_path=`pwd`
# full_path=''
# if [ `basename $base` == "$base" ];then
#   full_path=$pwd_path/$base
# else
#   full_path=$base
# fi
# full_path=`dirname $full_path`
full_path=$base
count=0

get_line_number(){
  read line name <<< "$1";
  echo $line;
}

while read -r line; 
do 
txt=`wc -l $line`
n=`get_line_number "$txt"`

if [ $count -ge 3 ];then
  break

elif [ "$n" -ge 20 ];then
  echo "find valid: $line"
  let count+=1
fi
done <<< `find $full_path -name "*.sh"`

