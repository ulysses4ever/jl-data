using RandomTestMatrices
using Base.Test

d = rand(1:100)

let A = randsym(d)
    @Test.test isreal(A)
    @Test.test size(A) == (d,d)
    @Test.test issym(A)
end


let A = randantisym(d)
    i = rand(1:d)
    j = rand(1:d)
    @Test.test isreal(A)
    @Test.test size(A) == (d,d)
    @Test.test A[i,j] == -A[j,i]
end


let A = randposdef(d)
    @Test.test isreal(A)
    @Test.test size(A) == (d,d)
    @Test.test isposdef(A)
    @Test.test issym(A)
end


let A = randstable(d)
    @Test.test size(A) == (d,d)
    @Test.test isreal(A)
    @Test.test all(real(eig(A)[1]) .< 0.0)
end


let A = randunitary(d)
    @Test.test size(A) == (d,d)
    @Test.test !isreal(A)
    @Test.test norm(A*A' - eye(d)) < d*eps()
end


let A = randorth(d)
    @Test.test size(A) == (d,d)
    @Test.test isreal(A)
    @Test.test norm(A*A' - eye(d)) < d*eps()
end 


let A = randnormal(d)
    @Test.test size(A) == (d,d)
    @Test.test isreal(A)
    @Test.test norm(A*A' - A'*A) < d*eps(100.)
end 
