module DerivativesTest

using Derivatives, FactCheck

facts("Prueba básicas de derivación:") do
    
    A = makex(3)
    B = Derive(3)
    
    @fact A => Derive(3,1)
    @fact B => Derive(3,0)
    @fact A+B => A+3
    @fact A-2 => Derive(1,1)
    @fact 6*A.d => 6
    @fact ((A)^2+5).d => (A^2).d 
    @fact (exp(A)).d => (exp(A)).f
    @fact cos(2A).d => 2*sin(6)
    @fact sin(A).d => -cos(A).f
    @fact log(A).d => (1.0/3.0)
    
    
end

end

	

