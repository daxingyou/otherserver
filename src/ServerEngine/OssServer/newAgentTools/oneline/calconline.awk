{
	if($3 > countmax[$2])
	{
		countmax[$2] = $3
	}
	
	countavg[$2] += $3;
	valueCount[$2]++;
	
	dt = $1
	host=$4
	user=$5
	world=$6
}


END{
	for(b in countmax)
	{
		print dt, b, countmax[b], countavg[b]/valueCount[b], host,user,world
	}
}
