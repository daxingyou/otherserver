{
	if($1 == "new")
	{
		count[$2] = 1;
		newCount+=1;
	}
	
	if($1 == "login")
	{
		countlogin[$2]=1;
	}
}

END{
	reloginCount = 0;
	for(b in count)
	{
		if(countlogin[b]==1)
		{
			reloginCount+=1;
		}
	}

	print reloginCount
}