function makeM(m,n,r,c)

m = 6
n = 10
r = 3
c = 5

# find all rows that sum to 5
v = [0;1]

tmpM = zeros(Int,2^m, m)
for i1 in v , i2 in v , i3 in v , i4 in v , i5 in v , i6 in v
    tmpM[i6*2^5+i5*2^4+i4*2^3+i3*2^2+i2*2^1+i1+1,:] = [i6 i5 i4 i3 i2 i1]
end
k = sum(tmpM, 2)
M=tmpM[find(k.==3),:]

tmp = int(size(M,1)/2)
# generate
while true
    c1_0 = randperm(tmp)
    c1_1 = tmp+randperm(tmp)
    c1= [c1_1[1:c];c1_0[1:n-c]]
    p = randperm(n)
    H = M[c1[p],:]
    if all(sum(H,1).==c)
        return H'
    end
end
end