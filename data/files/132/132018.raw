include("sem.jl")

#msh = Nektar.nektar("meshes/ss-275D.rea")
msh = Nektar.nektar("meshes/chan2.rea")

nb, nverts, bmap = dof.basic_num_scheme(msh.elems)


tags = [b.tag for b in msh.bcs]

function get_dirichilet_nodes(bcs)

    vine = [1 2 3 4; 2 3 4 1]
    nb = length(bcs)

    dnodes = zeros(Int, 2, 3*nb)
    count = 1
    for i = 1:nb
        b = bcs[i]
        ed = b.edge
        el = b.elem
        dnodes[1,count] = el
        dnodes[2,count] = vine[1,ed]
        count += 1
        dnodes[1,count] = el
        dnodes[2,count] = ed + 4
        count += 1
        dnodes[1,count] = el
        dnodes[2,count] = vine[2,ed]
        count += 1
    end


    return dnodes
end

dnodes = get_dirichilet_nodes(msh.bcs[tags .== 'O'])

nbslv = dof.dirichilet_numbering(bmap, dnodes)

Q = 4

bmapQ, nb2, nbslv2 = dof.make_bmap(bmap, Q, nbslv)
#isvert = dof.make_bmap(bmap, Q, nbslv)

bmap2 = dof.rcm(bmap, nbslv)

bmapQ2, nbq2, nbslvq2 = dof.make_bmap(bmap2, Q, nbslv)

    
    

