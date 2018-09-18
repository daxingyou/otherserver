#!/bin/bash
while read date time count host user world
do
	#echo $date
	#echo $time
	#echo $count
	arrIN=(${time//:/ })
	#echo ${arrIN[0]} ${arrIN[1]} ${arrIN[2]}
	timeIndex=$(expr $(expr ${arrIN[2]} + $(expr $(expr ${arrIN[0]} \* 3600) + $(expr ${arrIN[1]} \* 60))) / 3600)
	echo $date $timeIndex $count $host $user $world
done
