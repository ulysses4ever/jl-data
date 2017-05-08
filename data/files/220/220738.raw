@debug function evalreg(reg, X, cut, t_exp, naughty_exp)

A=zeros(size(X,1))

for k = 1:size(X,1)	
	A[k] = multipolyval(reg[findseg(X[k,:], cut), :]', X[k,:], t_exp, naughty_exp)[1]
end
return A
end


@debug function findseg(X, cut) #Find the segment that the rows of X lie in
	
	V=zeros(size(X,1))
	A=(size(cut,1)-2)*ones(size(X,1),size(X,2)-1) #A failsafe. If the if loop isn't tripped, take the largest region
	for k =1:size(X,1)
		for i= 1:size(X,2)-1
			for j = 2:size(cut,1) #We find the first element in cut that is greater than the point, so we don't start with 
						#the minimum cut point because that doesn't correspond to a region
				if X[k,i+1] <= cut[j,i]
					A[k,i]=j-2 #subtract 1 because we want the previous segement
						   #  then subtract 1 to make 1 -> 0 for the base representation.
					break
				end
			end
		end
	V[k]=parseint(reverse(join(int(A[k,:]))), size(cut,1)-1)+1 
	#The reverse is kind of confusing. We counted backwards in our enumeration.
	end
return V
end
