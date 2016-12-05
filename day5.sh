str="cxdnnyjw"
digits=0
num=$1
end=$2
code=""
while [ $num -lt $end ]
do
  str2="$str""$num"
  mdhash=`echo -n "$str2" | md5sum`
  if [ "${mdhash:0:5}" = "00000" ]; then
    echo "$num " "$str2 " "$mdhash " "${mdhash:0:5}"
    code="$code""${mdhash:5:1}"
    echo "$code"
    (( digits = digits + 1 ))
  fi
#  if [ $(( num % 10000 )) -eq 0 ]; then
#    echo "$num " "$str2 " "$mdhash " "${mdhash:0:5}"
#  fi
  (( num = num + 1 ))
done
#echo "$code"
