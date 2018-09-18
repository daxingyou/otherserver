first=1
sql="replace into yxld.levellost(world, date, account, level) values"
while read date world account level
do
	if [ -n "$level" ]
	then
		dbWorld=$(expr $world + 1)
		if [ $first -eq 1 ]
		then
			echo $first
			first=0
			sql="$sql ($dbWorld, '$date', '$account', $level)"
		else
			sql="$sql ,($dbWorld, '$date', '$account', $level)"
		fi
		#echo "replace into yxld.levellost(world, date, account, level) values($dbWorld, '$date', '$account', $level)"
        	#echo "replace into yxld.levellost(world, date, account, level) values($dbWorld, '$date', '$account', $level)"|mysql -h$host -u$user
	fi
done

echo $sql|mysql -h$1 -u$2
