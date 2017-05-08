##########################################################################
#
#    Modélisation cours (WIP)
#
#
#    2015-07-23        : creation
#    2015-08-25 (v0.2) : nettoyage, retrait var "volume BTC", ajout test out of sample
#    2015-08-25 (v0.3) : avec scaling plus large pour accommoder evols futures
#
##########################################################################

version = v"0.3"

using StatsBase
using Distances

using RecurrentNN
import Bokeh

##########################################################################
#    Chargement
##########################################################################
    using DataFrames
    using DataFramesMeta

    datapath = "P:/Documents/Julia/prediction/data"

    #####  lecture données  ###############

        df0 = readtable(joinpath(datapath, "BAVERAGE-BITCOIN_CENTRALEUR.csv"), separator=',')
        # df0 = @transform(df0, Date = Date(:Date)) ; nothing
        # df0 = df0[[:Date, :Ask, :Bid, :Last, :Volume_BTC_]]
        df0 = df0[[:Date, :Ask, :Bid, :Last]]
        # lasts = array(df0[:Last])
        # μs = lasts[2:end] ./ lasts[1:end-1]
        # fit_mle(LogNormal, μs)
        # fit_mle(Normal, μs - 1.)
        # fit_mle(Normal, μs )

        println(nrow(df0))
        for (fn, cn) in [("CURRFX-USDCNY.csv",  :Rate), 
                   ("CURRFX-EURUSD.csv",  :Rate),
                   ("BCHAIN-NTRAN.csv",  :Value),
                   ("BCHAIN-TVTVR.csv", :Value)]
            # fn = "BCHAIN-NTRAN.csv"
            df = readtable(joinpath(datapath, fn), separator=',')
            nfx = symbol(fn[1:end-4])
            # df = @transform(df, Date = Date(:Date))
            df[nfx] = df[cn]
            df0 = join(df0, df[[:Date, nfx]], on=:Date, kind=:inner)
            println(nrow(df0))
        end

        sort!(df0, cols=:Date)
        head(df0)


    #### Génération des séries historiques de longueur 'Span'
        Span = 5

        ldata0 = Any[]
        avars = convert(Array{Float64}, df0[:,2:end])'
        vscale = 10 .^ ceil(maximum(log(10, avars),2)) # puissance de 10 supérieure
        avars = avars ./ vscale
        ares  = convert(Vector{Float64},df0[:Last])
        rscale = 10 ^ ceil(maximum(log(10, ares)))
        ares  = ares ./ rscale
        for i in 1:nrow(df0)-Span  # i = 1
            vars = avars[:,i:i+Span-1]
            res  = ares[i+Span]
            push!(ldata0, (vars, res))
        end

        std(diff(ares)) # baseline variations = 0.0108

        Bokeh.hold(false)
        Bokeh.plot([1.:316;], ((avars .- Float64[ x[1] for x in vscale]) ./ Float64[ x[2]-x[1] for x in vscale])')
        Bokeh.showplot()


    # open(f -> serialize(f, (varsn, ldata)), "c:/temp/rnn-data-$version.jldata", "w")
    # varsn, ldata = open(deserialize, "c:/temp/rnn-data-$version.jldata", "r")


##########################################################################
#    Fit RNN
##########################################################################

    #### fonction d'application du RNN
        function rnn(model, vars, res) # vars, res = ldata[10]
            g = Graph(false) # backprop not needed
            prev = (Array(NNMatrix,0), Array(NNMatrix,0), NNMatrix(1,1))
            v = NNMatrix(size(vars,1), 1)
            copy!(v.w, vars[:,1])

            g = Graph(false)
            for i in 1:size(vars,2) # i = 1
                prev = forwardprop(g, model, v, prev)
            end
            tmp = exp(-prev[end].w[1]) # tmp = exp(0)
            estim = 1 / (1 + tmp)
            (estim, res, estim - res)
        end
        # rnn( GRU(19, [10], 1), vec(vars2[11210,:]))

    #### fonction de calibrage du RNN
        function iter(model, ldata; 
            nbrun=1000, nbepoch=0, freq=0, 
            learning_rate=0.01, regc=1e-5, clipval=100.0)

            solver = Solver() # RMSProp optimizer
            nfeat = size(ldata[1][1],1)
            nobs  = length(ldata)

            nbrun = nbepoch != 0 ? nbepoch*nobs : nbrun

            v = NNMatrix(nfeat, 1)
            err = 0.
            for k in 1:nbrun  # k = 1000
                ik   = 1 + (k-1) % nobs
                vars, res = ldata[ik]

                prev = (Array(NNMatrix,0), Array(NNMatrix,0), NNMatrix(1,1))
                copy!(v.w, vars[:,1])

                g = Graph() 
                for i in 1:size(vars,2) # i = 1
                    prev = forwardprop(g, model, v, prev)
                end
                tmp = exp(-prev[end].w[1]) # tmp = exp(0)
                estim = 1 / (1 + tmp)
                δ = estim - res
                err += δ*δ
                prev[end].dw[1] = 2 * δ * estim * (1 - estim)
                backprop(g)
                solverstats = RecurrentNN.step(solver, model, learning_rate, regc, clipval)

                if (freq > 0) && (k % freq == 0)
                    stderr = sqrt(err / freq)
                    println("std err = $(round(stderr, 3))")
                    err = 0.
                end
            end
        end

    ### RNN, layer 10
        model = RNN(8, [10], 1)
        iter(model, ldata, nbepoch=100, freq=1000, clipval=1e1, regc=1e-10, learning_rate=1e-3)
        iter(model, ldata, nbepoch=500, freq=1000, clipval=1e1, regc=1e-10, learning_rate=1e-4)
        # 0.038
        sol = deepcopy(model)

    ### RNN, layer 20
        model = RNN(7, [20], 1)
        ldata1 = shuffle(ldata0)
        iter(model, ldata1, nbepoch=500, freq=10000, clipval=1e0, regc=1e-10, learning_rate=1e-3)
        iter(model, ldata1, nbepoch=500, freq=10000, clipval=1e2, regc=1e-10, learning_rate=2e-4)
        iter(model, ldata1, nbepoch=1000, freq=10000, clipval=1e2, regc=1e-10, learning_rate=5e-5)
        # 0.037 - 0.015 (prof=5)
        # 0.012, pas terrible
        sol1 = deepcopy(model)

    ### RNN, layer 20, split calib / valid set
        model = RNN(8, [20], 1)
        splitidx = round(Integer, 4/5*length(ldata))
        ldata1, ldata2 = ldata[1:splitidx], ldata[splitidx+1:end]
        iter(model, ldata1, nbepoch=100, freq=1000, clipval=1e0, regc=1e-10, learning_rate=1e-3)
        iter(model, ldata1, nbepoch=500, freq=1000, clipval=1e1, regc=1e-10, learning_rate=2e-4)
        iter(model, ldata1, nbepoch=1000, freq=1000, clipval=1e2, regc=1e-10, learning_rate=3e-5)
        # 0.02 (prof=5)
        score(model, ldata1) # [-0.0,0.014] ([0.001,0.034])
        score(model, ldata2) # [-0.0,0.012] ([0.0,0.025])
        sol = deepcopy(model)

    ### RNN, layer 10+10
        model = RNN(8, [10,10], 1)
        iter(model, ldata, nbepoch=500, freq=1000, clipval=1e1, regc=1e-5, learning_rate=1e-3)
        # 0.065
        sol = deepcopy(model)

    ### GRU, layer 10
        model = GRU(5, [10], 1)
        iter(model, ldata, nbepoch=100, freq=1000, clipval=1e4, regc=1e-5, learning_rate=1e-5)
        iter(model, ldata, nbepoch=50, freq=1000, clipval=1e1, regc=1e-5, learning_rate=1e-2)
        # 0.113
        sol = deepcopy(model)



##########################################################################
#    Simulation
##########################################################################
 
    function strat1(spot, pred, cash, pose, costrel, costabs)
        amountstep = 10.
        cost = amountstep * costrel + costabs
        seuilvente = pose * (pred - spot)
        seuilachat = (pose + amountstep / spot * (1 - costrel)) * (pred - spot)
        seuilachat >  cost && return amountstep / spot
        seuilvente < -cost && return -amountstep / spot
        return 0.
    end
    strat1(300, 290, 100, 0.5, 0., 0.)

    function simul(strat::Function, model, ldata0;
        costabs = 0., costrel = 0.01)
        amount  = 100.
        pos     = 0. 
        dat = Array(Float64, length(ldata0),7)
        for (i, (vars, res)) in enumerate(ldata0) # i, vars, res = 1, ldata0[8]...
            pred = rnn(model, vars, res)[1] * rscale
            vrai =                      res * rscale
            current = vars[3,end] * vscale[3]
            # print("$(lpad(i,4)) : ")
            # print("spot $(round(current,2)) prévu $(round(pred,2))")
            mvta = strat(current, pred, amount, pos, costrel, costabs)
            if mvta > 0. # achat   
                # mvta, costrel, costabs, amount = 0.2, 0.01, 0.2, 100.
                mvtc = -min(current*mvta/(1-costrel)+costabs, amount) # plafond au cash restant 
                mvta = (-mvtc-costabs)*(1-costrel)/current # correction le cas échéant
            elseif mvta < 0. # vente
                # mvta, costrel, costabs, amount, pos = -0.2, 0.01, 0.2, 100., 0.3
                mvta = max(mvta, -pos) # seuillage à la pose vendable
                mvtc = -current*mvta*(1-costrel)-costabs
            else
                mvtc = 0.
            end
            amount += mvtc
            pos    += mvta
            dat[i,:] = [current, pred, mvta, mvtc, amount, pos, amount+pos*current]
            # println("  cash $(round(amount,2)) pose $(round(pos,3)) = $(round(amount+pos*current,2))")
        end
        dat
    end

    res = simul(strat1, sol1, ldata0) # +80%
    Bokeh.plot(Float64[1:length(ldata0);], res[:,[1, 5, 7]])
    Bokeh.showplot()

    # cout réels coinbase
    res = simul(strat1, sol1, ldata0, costrel=0.01, costabs=0.) # +69%
    Bokeh.plot(Float64[1:length(ldata0);], res[:,[1, 5, 7]])
    Bokeh.showplot() 

##########################################################################
#    Fit <> backtest
##########################################################################

    ### RNN, layer 20, split calib / valid set
        model = RNN(8, [20], 1)
        splitidx = 200
        ldata1 = shuffle(ldata0[1:splitidx])
        iter(model, ldata1, nbepoch=100, freq=1000, clipval=1e0, regc=1e-10, learning_rate=1e-3)
        iter(model, ldata1, nbepoch=500, freq=1000, clipval=1e1, regc=1e-10, learning_rate=2e-4)
        iter(model, ldata1, nbepoch=1000, freq=1000, clipval=1e3, regc=1e-10, learning_rate=3e-5)
        iter(model, ldata1, nbepoch=1000, freq=1000, clipval=1e3, regc=1e-10, learning_rate=1e-5)
        # 0.019 (prof=5)
        score(model, ldata1) # [-0.0,0.031] ([0.002,0.037])
        score(model, ldata0) # [-0.002,0.031] ([0.001,0.032])
        sol2 = deepcopy(model)

    res = simul(strat1, sol2, ldata0, costrel=0.01, costabs=0.) #+49%
    Bokeh.plot(Float64[1:length(ldata0);], res[:,[1, 5, 7]])
    Bokeh.showplot() # +21%

    # perf future, après splitidx
        ldata2 = ldata0[splitidx+1:end]

        res = simul(strat1, sol2, ldata2, costrel=0.01, costabs=0.) #+11%
        Bokeh.plot(Float64[1:size(res,1);], res[:,[1, 5, 7]])
        Bokeh.showplot() # +21%


##### contrôles par rapport aux couts Coinbase
    ### ventes
    mc, mb, fx = 77.35, 0.3, 260.44
    mc, mb, fx = 257.24, 1., 259.84

    costrel, costabs = 0.01, 0.
    mvta, current = -mb, fx
    mvtc = -current*mvta*(1-costrel)-costabs

    ### achats
    mc, mb, fx = 10., 0.03805289, 260.17
    mvtc, current = -mc, fx
    (-mvtc-costabs)*(1-costrel)/current



    ### random predictions
        rnn(model::Float64, vars, res) = [ vars[3,end] + randn()*0.03, 0., 0.]
        res = simul(strat1, 0., ldata0)
        Bokeh.plot(Float64[1:length(ldata0);], res[:,[1, 5, 7]])
        Bokeh.showplot()

##########################################################################
#   Out of sample
##########################################################################
    datapath = "P:/Documents/Julia/prediction/data/testing"

    #####  lecture données  ###############
        df0 = readtable(joinpath(datapath, "BAVERAGE-EUR.csv"), separator=',')
        # df0 = @transform(df0, Date = Date(:Date)) ; nothing
        df0 = df0[[:Date, :Ask, :Bid, :Last]]
        # lasts = array(df0[:Last])
        # μs = lasts[2:end] ./ lasts[1:end-1]
        # fit_mle(LogNormal, μs)
        # fit_mle(Normal, μs - 1.)
        # fit_mle(Normal, μs )

        println(nrow(df0))
        for (fn, cn) in [("CURRFX-USDCNY.csv",  :Rate), 
                   ("CURRFX-EURUSD.csv",  :Rate),
                   ("BCHAIN-NTRAN.csv",  :Value),
                   ("BCHAIN-TVTVR.csv", :Value)]
            # fn = "BCHAIN-NTRAN.csv"
            df = readtable(joinpath(datapath, fn), separator=',')
            nfx = symbol(fn[1:end-4])
            # df = @transform(df, Date = Date(:Date))
            df[nfx] = df[cn]
            df0 = join(df0, df[[:Date, nfx]], on=:Date, kind=:inner)
            println(nrow(df0))
        end

        sort!(df0, cols=:Date)
        head(df0)

    #### Génération des séries historiques de longueur 'Span'
        ldatax = Any[]

        avars = convert(Array{Float64}, df0[:,2:end])' ./ vscale # scaling identique !
        ares  = convert(Vector{Float64},df0[:Last]) / rscale     # scaling identique !
        for i in 1:nrow(df0)-Span  # i = 21
            vars = avars[:,i:i+Span-1]
            res  = ares[i+Span]
            push!(ldatax, (vars, res))
        end

        length(ldatax)
        ldatax[1]
        ldatax[21]
        ldatax[22]
        avars[:,20:end]
    #### contrôle

        for (i, (vars, res)) in enumerate(ldatax) # i, vars, res = 1, ldata0[8]...
            pred = rnn(sol1, vars, res)[1] * rscale
            vrai =                     res * rscale
            current =          vars[3,end] * vscale[3]
            print("$(lpad(i,4)) : ")
            print("spot $(round(current,2)) prévu $(round(pred,2))")
            print("  vrai $vrai   ")
            println( sign(pred-current)==sign(vrai-current) ? "ok" : "erreur")
        end

    df0[20:end,:]