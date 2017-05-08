M = [35 1 34 0
    1 6 0 5
    34 0 44 10
    0 5 10 15]

C = zeros(Float64,size(M))

for i in 1:size (M)[1]
    for j in 1:size(M)[2]
        C[i,j] = M[i,j]/sum(M[i,:])
    end
end

N = [29 6
    2 4
    35 9
    8 7]

O = zeros(Float64,size(N))

for i in 1:size (N)[1]
    for j in 1:size(N)[2]
        a = N[i,j]
        b = sum(M[i,:])
        O[i,j] = a/b
    end
end

println(pinv(C)*O)
