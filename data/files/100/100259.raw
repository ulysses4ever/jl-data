using DirectionalRegression
const DR = DirectionalRegression
import Base.Test


function test_get_κ()
	κ = DR.get_κ(DR.I1(1.5)/DR.I0(1.5))
	Base.Test.@test_approx_eq κ 1.5	
end

function test_func3_vs_func4()
	_β = rand(20) - 0.5
	_μ = 0.0
	_Aκ = 0.9
	_X = rand(1000,20)
	_Xt = _X'
	_θ = 2*pi*rand(1000) - pi;
	dβ1 = DR.func4(_β, _X, _θ, _μ, _Aκ)
	dβ2 = DR.func3(_β, _Xt, _θ, _μ, _Aκ) 
	Base.Test.@test_approx_eq dβ1 dβ2
end

"""
Check that the IRWLS algorithm converges to the correct β if we supply the correct μ and κ
	"""
function test_func2()
	X = 2*rand(1000,3)-1;
	β = [0.181689,0.533594,0.132475]
	μ0 = 2*atan(X*β);
	θ = zeros(size(X,1))
	κ = 2.0
	Aκ  = DR.I1(κ)/DR.I0(κ)
	θ
	for i in 1:length(θ)
		 θ[i] = rand(DR.sampler(DR.VonMises(μ0[i], κ)))
	 end
	 βn = 2*rand(size(X,2))-1
	 for i in 1:10
		 δβ = DR.func2(βn, X', θ, 0.0, Aκ)
		 for j in 1:length(β)
			 βn[j] += δβ[j]
		 end
	 end
	 print(βn)
	 Base.Test.@test sumabs2(β - βn) < 1e-2
end

test_get_κ()
test_func3_vs_func4()
test_func2()
