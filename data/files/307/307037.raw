function calcJ(feval,edat,x::Vector{Float64},dif::Vector{Float64},cvodemem::Ptr{None})

	numx = length(x)
	Jac = Array(Float64,numx,1)

	for i = 1:numx

		x2 = copy(x)
		x2[i] += dif[i]
		f2::Float64 = sqrerror(edat,x2,cvodemem,edat.initp)
		Jac[i] = (f2-feval)
	end

	Jac = Jac./(dif)

	return (Jac)
end

function calcHnJ(feval,edat,x::Vector{Float64},dif::Vector{Float64},cvodemem::Ptr{None})

	numx = length(x)
	Hes = zeros(Float64,numx,numx)
	Jac = Array(Float64,numx,1)	

	for i = 1:numx

		x1 = copy(x)
		x2 = copy(x)

		x1[i] -= dif[i]
		x2[i] += dif[i]

		f1::Float64 = sqrerror(edat,x1,cvodemem,edat.initp)
		f2::Float64 = sqrerror(edat,x2,cvodemem,edat.initp)
		Jac[i] = (f2 -f1)
		Hes[i,i] = (f2+f1-2*feval)
		end

		Jac = Jac./(2.*dif)
		Hes = Hes./(dif.^2)
	return (Hes,Jac)
end
