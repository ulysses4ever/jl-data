type SynergeticComputer
	proto::Matrix
	proto_adj::Matrix

	function SynergeticComputer(proto::Matrix)
		proto_adj = pinv(proto*proto')*proto
		new(proto, proto_adj)
	end
end

function recognition(
 	sc::SynergeticComputer,
 	pattern::Vector,
 	N::Integer, 
	Tau::Real,
 	lambda::Real=1.0,
 	B::Real=1.0,
 	C::Real=1.0,
	tol::Real=1e-5)

	xi = sc.proto_adj' * pattern
	
	for j=1:N
		D = (B+C)*sum(xi.*xi)
		xi += map(x->Tau*(lambda-D+B*x*x)*x,xi)
		if convergence(xi, tol)
			break
		end
	end

	return xi
end

function convergence(xi::Vector, tol::Real)
	if (one(xi[1]) - maximum(xi)) < tol
		return true
	else
		return false
	end
end

function getpattern(sc::SynergeticComputer, xi::Vector)
	# sc.proto[findmax(xi)[2]]
	sc.proto * xi
end
