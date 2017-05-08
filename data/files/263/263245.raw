include("/home/alkan/c/nese/jtb/yeast_dyn.jl")

# --- switch edges, keeping incoming and outgoing degrees ---
function switchnet (intr)
    n = length(intr[:,1])
    el = (Int64,Int64,Int64)[] # empty edge list
    for i=1:n for j=1:n
        if intr[i,j] != 0
            el = [el,(i,j,intr[i,j])]
        end
    end end

    ## shuffle edgelist
    ne = length(el)
    for rep=1:ne
        switching = true
        while switching
            r = rand(1:ne)              # pick a random edge
            rr = rand(1:ne)
            while r==rr rr=rand(1:ne) end # make sure edges are different
            if r<rr
                (r,rr) = (rr,r) # critical (otherwise idxs shift during splice)
            end
            if el[r][3]==el[rr][3]    # forget unless both + or both -
                if el[r][1]!=el[rr][2] && el[r][2]!=el[rr][1] && 
                    el[r][1]!=el[rr][1] && el[r][2]!=el[rr][2] # 4 different nodes
                    e1=(el[r][1],el[rr][2],el[r][3]) # new edges
                    e2=(el[rr][1],el[r][2],el[r][3])
                    e3=(e1[1],e1[2],-e1[3]) # new edges
                    e4=(e2[1],e2[2],-e2[3]) # new edges
                    if !in(e1,el) && !in(e2,el) && !in(e3,el) && !in(e4,el)
                        splice!(el,r)
                        splice!(el,rr)
                        append!(el,[e1,e2])
                        switching = false
                    end end end         # ifs
        end                             # while
    end                                 # for
    nw = zeros(Int64,n,n)
    for i=1:ne                          # construct new nw
        nw[el[i][1],el[i][2]] = el[i][3]
    end
return nw
end


# --- return a (n,ne,np) preserved shuffled version of a network
function shufflenet (intr,slf)
    n = length(slf)
    nw = similar(intr)                  # this will be the randomized version
    shf = shuffle(slf)                  # keep number of self degredating genes
    tl = tril(intr)                     # remove diag and join upper/lower triang
    tu = triu(intr)
    rect = tu[:,2:end]+tl[:,1:end-1]    # shuffle this
    rect = reshape(shuffle(reshape(rect,length(rect),1)[:,1]),n,n-1)
    rrect = [rect zeros(Int64,n)]       # now insert back the shuffled diagonal
    lrect = [zeros(Int64,n) rect]
    nw = tril(rrect - diagm(diag(rrect))) + triu(lrect-diagm(diag(lrect)))
    return (nw,shf)
end


# --- generate a random (n,ne,np) network.
# --- d = matrix diagonal
# --- ne = number of edges
# --- np = number of positive edges
function randomnkp (d,ne,np)
    n = length(d)                       # int matrix diagonal - never change
    nn = ne-np                          # negative edges
    nz = n*(n-1)-ne                     # number of zero-edges
#    print("in randomnkp() with $ne, $np")
    intlist = [ones(Int64,np);-ones(Int64,nn);zeros(Int64,nz)]
    rect = reshape(shuffle(intlist),n,n-1)
    rrect = [rect zeros(Int64,n)]
    lrect = [zeros(Int64,n) rect]
    interrand = tril(rrect - diagm(diag(rrect))) + triu(lrect-diagm(diag(lrect)))
#    println("done reshaping.")
    return interrand
end

