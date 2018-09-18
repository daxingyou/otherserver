first=1
sql="replace into yxld.cost(world, date, type, reason, amount, count) values"
while read world date type reason count amount
do
        if [ -n "$amount" ]
        then
                dbWorld=$(expr $world + 1)
                if [ $first -eq 1 ]
                then
                        echo $first
                        first=0
                        sql="$sql ($dbWorld, '$date', $type, $reason, $amount, $count)"
                else
                        sql="$sql ,($dbWorld, '$date', $type, $reason, $amount, $count)"
                fi
        fi
done

echo $sql|mysql -h$1 -u$2
