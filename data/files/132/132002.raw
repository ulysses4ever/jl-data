# Only works for Quad elements.

function basic_num_scheme(elems)
    N = length(elems)

    emap = zeros(Int, 4, N)
    vmap = zeros(Int, 4, N)
    
    count = build_vertex_map(vmap, elems, 1)
    local e0, eid0, ed, e, neigh, e1, ed1, eid1
    nverts = count
    for e = 1:N
        e0 = e
        eid0 = e
        for ed = 1:4
            if emap[ed,e] > 0
                continue
            end
            emap[ed,e] = count
            neigh = elems[e0].neigh[ed,1]
            if neigh <= 0
                count += 1
                continue
            end

            e1 = neigh
            ed1 = elems[e0].neigh[ed,2]
            eid1 = e1
            if eid1 < eid0
                continue
            end

            emap[ed1,eid1] = count
            count += 1
        end
    end

    return count, nverts, vcat(vmap, emap)
    
end

function build_vertex_map(vmap, elems, count=1)

    local vine = [1 2 3 4; 2 3 4 1]
    local einv = [4 1 2 3; 1 2 3 4]

    local N = length(elems)
    local ed1, eid0, eid1

    local neigh
    local e_actual, e0
    local vert
    local full_cycle = false
    for e = 1:N

        e0 = e
        eid0 = e
        for v = 1:4
            if vmap[v,e] != 0
                continue
            end
            vmap[v,eid0] = count
            e_actual = e0
            vert = v
            full_cycle = false
            while true
                neigh = elems[e_actual].neigh[einv[1,vert],1]
                ed1 = elems[e_actual].neigh[einv[1,vert],2]
                if neigh<=0
                    break
                end
                e_actual = neigh
                if e_actual == e0
                    full_cycle = true
                    break
                end
                eid1 = e_actual
                vert = vine[1,ed1]
                vmap[vert,eid1] = count
            end

            if !full_cycle
                e_actual = e0
                vert = v
                while true
                    neigh = elems[e_actual].neigh[einv[2,vert],1]
                    ed1 = elems[e_actual].neigh[einv[2,vert],2]
                    if neigh <= 0
                        break
                    end
                    e_actual = neigh
                    if e_actual == e0
                        full_cycle = true
                        break
                    end

                    eid1 = e_actual
                    vert = vine[2,ed1]
                    vmap[vert,eid1] = count
                end
            end
            count += 1
        end
    end

    return count
end


function bandwidth(bmap, nbslv)
    
    local m = 0
    local min_idx = 0
    local max_idx = 0
    Nel = size(bmap,2)
    for e = 1:Nel
        bm = bmap[:,e]
        for i in bm
            if i <= nbslv
                min_idx = i
                max_idx = i
                break
            end
        end

        for i in bm
            if i <= nbslv 
                min_idx = (i < min_idx)? i : min_idx
                max_idx = (i > max_idx)? i : max_idx
            end
        end
        m = max(m, (max_idx - min_idx))
    end

    return m
end


function dirichilet_numbering(bmap, dnodes::Array{Int,2})

    ndn = size(dnodes, 2)
    
    mask = similar(bmap, Int)
    fill!(mask, 1)

    for i = 1:ndn
        el = dnodes[1,i]
        ed = dnodes[2,i]
        mask[ed,el] = 0
    end

    nb = max(bmap)

    gmask = ones(Int, nb)

    Nel = size(bmap,2)
    nbe = size(bmap,1)

    for e = 1:Nel
        for i = 1:nbe
            gmask[bmap[i,e]] *= mask[i,e]
        end
    end

    for e = 1:Nel
        for i = 1:nbe
            mask[i,e] = gmask[bmap[i,e]]
        end
    end

    nbslv = 0
    for i = 1:nb
        nbslv = (gmask[i]>0)?nbslv+1:nbslv
    end
    gbmap = gmask
    fill!(gbmap, -1)

    n1 = 1
    n2 = nbslv+1
    for e = 1:Nel
        for i = 1:nbe
            bm = bmap[i,e]
            if (gbmap[bm] == -1)
                if mask[i,e] == 1
                    gbmap[bm] = n1
                    n1 += 1
                else
                    gbmap[bm] = n2
                    n2 += 1
                end
            end
        end
    end

    for e = 1:Nel
        for i = 1:nbe
            bmap[i,e] = gbmap[bmap[i,e]]
        end
    end

    return nbslv
end

function make_bmap(bmap, Q, nbslv)

    nb = max(bmap)
    Nel = size(bmap,2)
    nbe = size(bmap,1)
    isvert = zeros(Int, nb)
    isvert[bmap[1:4,:]] = 1

    Qm2 = Q-2
    nb2 = 1
    for i = 1:nbslv
        if isvert[i] > 0
            isvert[i] = nb2
            nb2 += 1
        else
            isvert[i] = nb2
            nb2 += Qm2
        end
    end
    nbslv2 = nb2-1
    for i = (nbslv+1):nb
        if isvert[i] > 0
            isvert[i] = nb2
            nb2 += 1
        else
            isvert[i] = nb2
            nb2 += Qm2
        end
    end

    nb2 -= 1
    bmap2 = zeros(Int, 4+4*Qm2, Nel)
    edge_considered = falses(nb)
    eidx = reshape(4 + [1:(4*Qm2)], Qm2, 4)
    
    r = [0:(Qm2-1)]
    for e = 1:Nel
        for i=1:4
            bmap2[i,e] = isvert[bmap[i,e]]
        end

        for i = 1:4
            bm = bmap[i+4,e]
            en = isvert[bm]
            ei = eidx[:,i]
            if !edge_considered[bm]
                bmap2[ei,e] = en + r
                edge_considered[bm] = true
            else
                bmap2[reverse(ei),e] = en + r
            end
        end
    end

    return bmap2, nb2, nbslv2
end

function push_unique!(x, v)
    n = length(x)
    found = false
    for y in x
        if y==v
            found = true
            break
        end
    end

    if !found
        push!(x, v)
    end
end

function node_neighbors(bmap, nbslv=0)

    if nbslv==0
        nbslv = max(bmap)
    end
    
    Nel = size(bmap, 2)
    nbe = size(bmap, 1)

    neigh = Array(Array{Int,1}, nbslv)
    for i = 1:nbslv
        neigh[i] = zeros(Int,0)
    end
    for e = 1:Nel
        bm = bmap[:,e]
        for i = 1:nbe
            ni = bm[i]
            if ni <= nbslv
                for k = (i+1):nbe
                    nk = bm[k]
                    if nk <= nbslv
                        push_unique!(neigh[nk], ni)
                        push_unique!(neigh[ni], nk)
                    end
                end
            end
        end
    end


    return neigh
end


function rcm(bmap, nbslv=0, rev=true)

    if nbslv == 0
        nbslv = max(bmap)
    end

    Nel = size(bmap,2)
    nbe = size(bmap,1)
    
    
    G = node_neighbors(bmap, nbslv)
    Q = zeros(Int, 0)
    R = zeros(Int, 0)
    inserted = falses(nbslv)
    idx = [1:nbslv]
    count = 0
    glen = [length(x) for x in G]
    inR = 0
    while true
        if inR == nbslv
            break
        else
            P = idx[indmin(glen[!inserted])]
        end
        push!(R, P)
        inserted[P] = true
        inR += 1
        idx = sortperm([glen[k] for k in G[P]])
        adj = G[P][idx]
        append!(Q, adj)
        
        while true
            if length(Q) == 0
                break
            end
            C = shift!(Q)
            if !inserted[C]
                push!(R, C)
                inserted[C] = true
                inR += 1
                idx = sortperm([glen[k] for k in G[C]])
                for i in idx
                    a = G[C][i]
                    if !inserted[a]
                        push!(Q, a)
                    end
                end
            end
        end
    end

    if rev
        reverse!(R)
    end

    # Create new map:
    L = similar(R)
    for i = 1:nbslv
        r = R[i]
        L[r] = i
    end

    
    bmap2 = similar(bmap)

    for e = 1:Nel
        for i = 1:nbe
            bm = bmap[i,e]
            if bm <= nbslv
                bmap2[i,e] = L[bm]
            else
                bmap2[i,e] = bm
            end
        end
    end
    
    
    return bmap2
    
end    

    
        