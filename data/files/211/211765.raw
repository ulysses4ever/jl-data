a = zeros(5,1)
b = zeros(5,1)
test=zeros(5,5)
for j=1:5

b=zeros(5,1)
for i=1:5
b[i,1] = i+j
end
test[:,j]=b
#print([a b])
diff = max(abs(b-a))
println(diff)
a[:,1] = b[:,1]
#print(a)
end

println(test)
