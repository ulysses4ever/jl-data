#=
Bartłomiej Sadowski
=#
function del()
	d=2^52
	d=1/d
	return d
end

function showNextPrev(xorg,xnext,xprev)
	println(bits(xprev))
	println(bits(xorg))
	println(bits(xnext))
	println(abs(xorg-xprev))
	end
	
dd=del()

k=51
xprev=1/2+2^(k-1)*dd
xorg=1/2+2^k*dd
xnext=1/2+(2^(k+1)-1)*dd

println(xprev,"\n",xorg,"\n",xnext)


showNextPrev(xorg,xnext,xprev)

z=1+2^k*dd
println(bits(z))



