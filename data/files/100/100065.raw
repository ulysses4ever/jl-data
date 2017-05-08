include("/home/jeb/Teaching/Research/Thermodynamics/eclipse-julia/HnFFTFp/src/Element.jl")
include("/home/jeb/Teaching/Research/Thermodynamics/eclipse-julia/HnFFTFp/src/Function.jl")
#Demonstrates how to put the values of a function on Hn in the order used to compute the FFT
function testFunction(M::BigInt)
  println("> Test Function")
	PA = Array(Array{Int, 1}, 16) #Create an array to hold all of the permutations of H4
	PA[1] = [0,0,0,0]
	PA[2] = [1,0,0,0]
	PA[3] = [0,1,0,0]
	PA[4] = [0,0,1,0]
	PA[5] = [0,0,0,1]
	PA[6] = [1,1,0,0]
	PA[7] = [1,0,1,0]
	PA[8] = [1,0,0,1]
	PA[9] = [0,1,1,0]
	PA[10] = [0,1,0,1]
	PA[11] = [0,0,1,1]
	PA[12] = [1,1,1,0]
	PA[13] = [1,1,0,1]
	PA[14] = [1,0,1,1]
	PA[15] = [0,1,1,1]
	PA[16] = [1,1,1,1]
  VA = Array(BigInt, 16) #Create the values of the function on Sn
    for i = 1:16
      VA[i] = big(i)
    end
	HNF = hn_f(4,M,PA,VA) #Put the values into the order used to compute the FFT
	println("> Start with any ordering: ")
	for i = 1:16
		ST = string(PA[i], "  ", VA[i])
		println(ST)
	end
	println("> Is sorted into this order for HnFFT to use: ")
	for i = 1:16
		ST = string(PA[i], "  ", HNF[i])
		println(ST)
	end
  println("> success")
end
testFunction(big(997))
