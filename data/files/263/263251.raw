## --- node update function (integrator) -----------
function upd(s,intr,slf,n)
    sss = similar(s)
    inp = intr*s
    for (i=1:n)
        sss[i] = (inp[i]>0)?1:(inp[i]<0)?0:(slf[i]==0)?0:s[i]
    end
    return sss
end

fname = "/tmp/jtb/sample_nws/randomnkp_one/11.29.15/1.dat"

edges = readdlm(fname,' ',Int64);
n = maximum(edges[:,1:2])
interc=zeros(Int64,n,n)
for i=1:length(edges[:,1])
	interc[edges[i,1],edges[i,2]]=edges[i,3]
end

selfact = diag(interc)                  # yeast specific
interc -= diagm(selfact)                # interaction matrix

fname = "/tmp/jtb/sample_nws/randomnkp_one/11.29.15/1.att"
a = readdlm(fname,' ',Any);
fps = int(a[:,1:n])
basin = a[:,n+1]
cyclen = int(a[:,n+2])
coop = a[:,n+3]
cycle = a[:,n+6]
s = fps[1,1:n]'
s = upd(s,interc,selfact,n)
println(s')
