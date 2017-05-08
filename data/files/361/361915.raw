reload("SAMC")
reload("MCBN")
using ZMQ
using JSON
import MsgPack

nonce = 123456

blas_set_num_threads(1)
if !("WORKHASH" in keys(ENV))
    ENV["WORKHASH"] = "aaaa0734b32730961e58eacf69b7e422fafc483f|aaaa0734b32730961e58eacf69b7e422fafc483f"
end

if "PARAM" in keys(ENV)
    params = JSON.parse(ENV["PARAM"])
    assert(isa(params, Dict))
else
    params = Dict()
end

setv(p,s,def) = convert(typeof(def), get!(p, s, def))

iters = setv(params, "iters", int(1e5))
burn = setv(params, "burn", int(1e4))
thin = setv(params, "thin", 100)
chains = setv(params, "chains", 10)
D = setv(params, "D", 4)
numdata = setv(params, "numdata", 10)
iseed = setv(params, "iseed", 123)
p_cpds = setv(params, "p_cpds", 0.2)
p_structural = setv(params, "p_structural", 0.2)
#iseed = setv(params, "iseed", rand(Uint))
#seed = setv(params, "seed", rand(Uint))

#ENV["SERVER"] = "nfsc-oracle.tamu.edu"
if haskey(ENV, "SERVER")
    ctx = Context(1)
    s = Socket(ctx, ZMQ.REQ)
    ZMQ.connect(s, "tcp://$(ENV["SERVER"]):7001")
end

template = zeros(Int,D,D)
cpds = MCBN.BayesNetDAI(D)

function factor_klds(bnd1::MCBN.BayesNetDAI, bnd2::MCBN.BayesNetDAI)
    0 #FIXME
end

function prior(bns::MCBN.BayesNetSampler)

    #p_cpds::Float64
    #cpds::BayesNetDAI
    #p_structural::Float64
    #template::Matrix{Bool}
    #limparent::Int
    #limit number of parents
    d = size(bns.mat,1)
    tot = 0
    for i=1:d
        for j=1:d
            tot += bns.mat[i,j]
        end
        if tot > bns.limparent + 1
            return 1e10
        end
        tot = 0
    end

    adj_diff = sum(abs(bns.mat[bns.x,bns.x] - template)) 
    e_struct = p_structural * adj_diff

    # energy contribution from cpds
    cpd_diff = factor_klds(bns.bnd, cpds)
    e_cpd = p_cpds * cpd_diff
    return e_cpd + e_struct
end

preseed = rand(Uint)
srand(iseed)
#data = rand(1:2, D, 60)
gold = MCBN.random_net(D) 
data = MCBN.draw_data(gold,numdata)
srand(preseed)

## PopSAMC
bngen = x->MCBN.BayesNetSampler(D, data, prior)


samc2 = SAMC.MHRecord(MCBN.BayesNetSampler(D, data, prior), burn = burn, thin=thin)
println("Before")
@show MCBN.energy(samc2.obj)
println("After")
samptime = @elapsed SAMC.sample!(samc2, iters, verbose=0)

function edge_prob(out)
    mat,x = out
    ord = sortperm(x)
    return mat[ord,ord]
end

#=kld_gold(bns::MCBN.BayesNetSampler) = MCBN.kld(gold, bns.bnd)=#

post_edge = SAMC.posterior_e(edge_prob,samc2)
#=post_kld = SAMC.posterior_e(kld_gold,samc2)=#

map_edge = edge_prob(samc2.mapvalue)
#=map_kld = kld_gold(samc2.mapvalue)=#

params["samptime"] = samptime
#params["mapenergy"] = samc2.mapenergy

params["post_edge"] = vec(post_edge)
#params["post_kld"] = post_kld
params["map_edge"] = vec(map_edge)
#params["map_kld"] = map_kld

params["cum_kld"] = SAMC.cum_posterior_e(kld_gold,samc2)

if "SERVER" in keys(ENV)
    data1 = Any[D, post_kld, map_kld, samc2.mapenergy]
    schema = "dims INTEGER, post_kld REAL, map_kld REAL, map_energy REAL, data BLOB"

    wiredata = MsgPack.pack([
        "data"=>data1,
        "schema"=>schema])

    ZMQ.send(s, ENV["WORKHASH"], SNDMORE)
    ZMQ.send(s, wiredata, SNDMORE)
    ZMQ.send(s, MsgPack.pack(params))
    ZMQ.recv(s)

    close(s)
    close(ctx)
else
    println(params)
end

