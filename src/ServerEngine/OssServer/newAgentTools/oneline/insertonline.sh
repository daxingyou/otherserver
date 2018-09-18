first=1
sql="replace into yxld.online(world, date, timeindex, maxonline, avgonline) values"

while read date timeindex max avg world
do
	#echo "replace into yxld.online(world, date, timeindex, maxonline, avgonline) values($dbWorld, '$date', $timeindex, $max, $avg)"|mysql -h$host -u$user
	if [ -n "$world" ]
	then
		dbWorld=$(expr $world + 1)
		if [ $first -eq 1 ]
		then
			echo $first
			first=0
			sql="$sql ($dbWorld, '$date', $timeindex, $max, $avg)"
		else
			sql="$sql ,($dbWorld, '$date', $timeindex, $max, $avg)"
		fi
		#echo "replace into yxld.levellost(world, date, account, level) values($dbWorld, '$date', '$account', $level)"
        	#echo "replace into yxld.levellost(world, date, account, level) values($dbWorld, '$date', '$account', $level)"|mysql -h$host -u$user
	fi
	
done


#echo $sql
echo $sql|mysql -h$1 -u$2
