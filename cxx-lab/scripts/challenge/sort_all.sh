while read -r line;
do 
  sort -o $line $line;
done <<< `find $1 -name "*.c" -print`