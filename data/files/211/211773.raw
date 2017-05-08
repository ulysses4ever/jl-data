function Price(x_prime,P,state)

# USAGE

# x_priume is the share
# P is the price function
# state for x_prime

#if size(state)~=size(P)
#    error("The dimensions are not matched")
#end

#if size(P,2)~=1
#    error("dimension is wrong")
#end

(value, index)=findmin ( abs (x_prime-state) );

y=P[index,1];

return y

end
