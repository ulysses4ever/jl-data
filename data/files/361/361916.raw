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
burn = setv(params, "burn", int(1e2))
thin = setv(params, "thin", 100)
chains = setv(params, "chains", 10)
# stepscale = setv(params, "stepscale", 200.0)
# beta = setv(params, "beta", 0.9)
# refden_power = setv(params, "refden_power", 0.0)
D = setv(params, "D", 16)
numdata = setv(params, "numdata", 3000)
p_cpds = setv(params, "p_cpds", 0.0)
num_cpds = setv(params, "num_cpds", 0)
p_structural = setv(params, "p_structural", 0.0)

iseed = setv(params, "iseed", 1234)
# iseed = setv(params, "iseed", rand(Uint))
#seed = setv(params, "seed", rand(Uint))

#ENV["SERVER"] = "nfsc-oracle.tamu.edu"
if haskey(ENV, "SERVER")
    ctx = Context(1)
    s = Socket(ctx, ZMQ.REQ)
    ZMQ.connect(s, "tcp://$(ENV["SERVER"]):7001")
end

template = zeros(Int,D,D)
cpds = MCBN.BayesNetDAI(D)

function prior(template::Matrix{Int}, cpds::MCBN.BayesNetDAI, bns::MCBN.BayesNetSampler)

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

    if p_structural != 0.0
      adj_diff = sum(abs(bns.mat[bns.x,bns.x] - template)) 
      e_struct = p_structural * adj_diff
    else
      e_struct = 0.0
    end

    # energy contribution from cpds
    if p_cpds != 0.0 && num_cpds != 0
      cpd_diff = 0.0
      for node in 1:num_cpds
        cpd_diff += MCBN.factor_klds(bns.bnd, cpds, node)
      end
      e_cpd = p_cpds * cpd_diff
    else
      e_cpd = 0.0
    end

    return e_cpd + e_struct
end

preseed = rand(Uint)
srand(iseed)
gold = MCBN.random_net(D) 
gold_template = MCBN.net2mat(gold) |> int
data = MCBN.draw_data(gold,numdata)
srand(preseed)

## MH
bn = MCBN.BayesNetSampler(D, data, x->prior(gold_template,gold,x))
mh = [SAMC.MHRecord(deepcopy(bn), burn=burn, thin=thin) for i=1:chains]
samptime = @elapsed SAMC.sample!(mh, div(iters,chains))

edge_prob(bnd::MCBN.BayesNetDAI) = MCBN.net2mat(bnd)

kld_gold(bnd::MCBN.BayesNetDAI) = MCBN.kld(gold, bnd)

# post_edge = SAMC.posterior_e(edge_prob,mh)
post_kld = SAMC.posterior_e(kld_gold,mh)

# map_edge = edge_prob(SAMC.mapvalue(mh))
map_kld = kld_gold(SAMC.mapvalue(mh))

params["samptime"] = samptime
params["mapenergy"] = SAMC.mapenergy(mh)

# params["post_edge"] = vec(post_edge)
params["post_kld"] = post_kld
# params["map_edge"] = vec(map_edge)
params["map_kld"] = map_kld

params["gelman_kld"] = SAMC.gelman_rubin(kld_gold, mh)[1]
params["samples"] = sum(map(length,mh))

# params["cum_kld"] = SAMC.cum_posterior_e(kld_gold,mh)
# params["allpost_kld"] = convert(Vector{Float64},map(kld_gold, SAMC.samples(mh)))
params["std_kld"] = std(convert(Vector{Float64},map(kld_gold, SAMC.samples(mh))))

if "SERVER" in keys(ENV)
    data1 = Any[D, numdata, post_kld, map_kld, SAMC.mapenergy(mh)]
    schema = "dims INTEGER, numdata INTEGER, post_kld REAL, map_kld REAL, map_energy REAL, data BLOB"

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
