function lua_is_prime(n)
	if n<=3 then
		return n>1
	end
	if (n%2 == 0 or n%3 == 0) then
		return false
	end
	for i=5, n/2, 6 do
		if (n%i==0 or n%(i+2)==0) then
			return false
		end
	end
	return true
end