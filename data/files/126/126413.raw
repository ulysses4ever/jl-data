##########################################################################
#
#    Modélisation cours (WIP)
#
#
#    2015-07-23        : creation
#    2015-08-25 (v0.2) : nettoyage, retrait var "volume BTC", ajout test out of sample
#    2015-08-25 (v0.3) : avec scaling plus large pour accommoder evols futures
#    2015-08-26 (v0.4) : estim de la variation relative
#    2015-08-26 (v0.5) : estim de la variation absolue
#
##########################################################################

version = v"0.5"

using StatsBase
using Distances
using Distributions

using RecurrentNN
import Bokeh
using DataFrames
using DataFramesMeta

datapath = "P:/Documents/Julia/RNNpred/data"

##########################################################################
#    Chargement
##########################################################################

    function loadcsv(ddir)
        df0 = readtable(joinpath(ddir, "BAVERAGE-EUR.csv"), separator=',')
        df0 = df0[[:Date, :Ask, :Bid, :Last]]

        print(nrow(df0))
        for (fn, cn) in [("CURRFX-USDCNY.csv",  :Rate), 
                   ("CURRFX-EURUSD.csv",  :Rate),
                   ("BCHAIN-NTRAN.csv",  :Value),
                   ("BCHAIN-TVTVR.csv", :Value)]
            df = readtable(joinpath(ddir, fn), separator=',')
            nfx = symbol(fn[1:end-4])
            df[nfx] = df[cn]
            df0 = join(df0, df[[:Date, nfx]], on=:Date, kind=:inner)
            print(", ", nrow(df0))
        end
        println()
        sort!(df0, cols=:Date)
        df0
    end

    function mkdata(df, span=5, scales=nothing)  # df = df0
        ldata = Any[]
        avars = convert(Array{Float64}, df[:,2:end])'
        ares  = convert(Vector{Float64},df[:Last])
        ares  = diff(ares)
        if scales==nothing
            # vscale = 10 .^ ceil(maximum(log(10, avars),2)) # puissance de 10 supérieure
            # vscale = (2 .^ ceil(maximum(log(2, avars),2)),
            #           2 .^ floor(minimum(log(2, avars),2)) )
            vscale = (2 .^ floor(minimum(log(2, avars),2)),
                      2 .^ ceil(maximum(log(2, avars),2)) )
            rscale = 10 ^ ceil(maximum(log(10, abs(ares))))
        else
            (vscale, rscale) = scales
        end
        avars = (avars .- vscale[1]) ./ (vscale[2] - vscale[1])
        # [ minimum(avars,2) maximum(avars,2)]
        ares  = ares / rscale / 2 + 0.5
        for i in 1:nrow(df)-span  # i = 1
            vars = avars[:,i:i+span-1]
            # res  = ares[i+span] / ares[i+span-1] / 2
            # res  = convert(Float64, ares[i+span] > ares[i+span-1])
            res  = ares[i+span-1]
            push!(ldata, (vars, res))
        end

        ldata, (vscale, rscale)
    end

    #####  lecture données  ###############

        df0    = loadcsv(datapath);
        ldata0, scales = mkdata(df0, 2);
        ldata1 = shuffle(ldata0)  # pour le training

        # out of sample
        df1    = loadcsv(joinpath(datapath, "testing"));
        ldatax, _ = mkdata(df1, 2, scales);

        ress = [ x[2] for x in ldata0]
        mean( ress .< 0.5)  # à la baisse dans 53% des cas
        mean(ress)  # 0.5
        extrema(ress)  # 0.397-0.609

 
        Bokeh.hold(false)
        Bokeh.plot([1.:316;], ((avars .- Float64[ x[1] for x in vscale]) ./ Float64[ x[2]-x[1] for x in vscale])')
        Bokeh.showplot()


    # open(f -> serialize(f, (varsn, ldata)), "c:/temp/rnn-data-$version.jldata", "w")
    # varsn, ldata = open(deserialize, "c:/temp/rnn-data-$version.jldata", "r")


##########################################################################
#    Fit RNN
##########################################################################

    #### fonction de scoring des modèles
        function score(model, ldata)
            nb, success = 0, 0
            for (i, (vars, res)) in enumerate(ldata) # i, (vars, res) = 1, ldatax[8]
                pred = rnn(model, vars, res)[1] 
                vrai =                     res 

                success += ! ( (pred < 0.5) $ (vrai < 0.5) )
                nb += 1
            end

            ratio = success/nb
            pvalue = ccdf(Binomial(nb,0.5), success)
            # print("success ratio $(round(ratio*100))%, p-value $(round(pvalue,3))")
            (ratio, pvalue)
        end

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
                    println("std err = $(round(stderr, 4))")
                    err = 0.
                end
            end
        end

    #### fonction de calibrage du RNN (avec diagnostics)
        function iter2(model, ldata, ldatax; 
            nbrun=1000, nbepoch=0, freq=0, 
            learning_rate=0.01, regc=1e-5, clipval=100.0)

            solver = Solver() # RMSProp optimizer
            nfeat = size(ldata[1][1],1)
            nobs  = length(ldata)

            nbrun = nbepoch != 0 ? nbepoch*nobs : nbrun

            v = NNMatrix(nfeat, 1)
            err = 0.
            clog = Array(Float64, 0, 3)
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
                    sc1, sc2 = score(model, ldata), score(model, ldatax)                
                    err = Float64[rnn(model, dat...)[3] for dat in ldata0]
                    tmp = [sc1[1], sc2[1], std(err)]
                    println( map(x -> round(x,3), tmp))
                    clog = vcat(clog, tmp' )
                end
            end
            clog
        end

        function plotclog(clog, title="clog")
            nb = size(clog,1)
            Bokeh.plot([0.,nb], [0.5,0.5], "k--")
            Bokeh.hold(true)
            Bokeh.plot([1:nb], clog[:,1:2], title=title)
            Bokeh.showplot()
            Bokeh.hold(false)
        end

    ### RNN, layer 10
        model = RNN(7, [10], 1)
        iter(model, ldata1, nbepoch=500, freq=10000, clipval=1e1, regc=0., learning_rate=1e-3)
        iter(model, ldata1, nbepoch=5000, freq=10000, clipval=1e1, regc=0., learning_rate=1e-4)
        iter(model, ldata1, nbepoch=500, freq=10000, clipval=1e1, regc=0., learning_rate=1e-5)

        model = RNN(7, [10], 1)
        clog = iter2(model, ldata1, ldatax, nbepoch=4000, freq=10000, clipval=1e1, regc=1e-6, learning_rate=1e-4)
        plotclog(clog, "lrate 1e-4, regc 1e-6")

        model = RNN(7, [10], 1)
        clog = iter2(model, ldata1, ldatax, nbepoch=4000, freq=10000, clipval=1e1, regc=1e-6, learning_rate=1e-3)
        plotclog(clog, "lrate 1e-3, regc 1e-6")

        model = RNN(7, [10], 1)
        clog = iter2(model, ldata1, ldatax, nbepoch=4000, freq=10000, clipval=1e1, regc=1e-5, learning_rate=1e-3)
        plotclog(clog, "lrate 1e-3, regc 1e-5")

        model = RNN(7, [10], 1)
        clog = iter2(model, ldata1, ldatax, nbepoch=4000, freq=10000, clipval=1e1, regc=1e-5, learning_rate=1e-4)
        plotclog(clog, "lrate 1e-4, regc 1e-5")

        model = RNN(7, [10], 1)
        clog = iter2(model, ldata1, ldatax, nbepoch=10000, freq=10000, clipval=1e1, regc=1e-7, learning_rate=1e-5)
        plotclog(clog, "lrate 1e-5, regc 1e-7")


        model = RNN(7, [10], 1)
        clog1 = iter2(model, ldata1, ldatax, nbepoch=1000, freq=10000, clipval=1e1, regc=1e-6, learning_rate=1e-4)
        clog2 = iter2(model, ldata1, ldatax, nbepoch=3000, freq=10000, clipval=1e1, regc=1e-7, learning_rate=1e-5)
        plotclog(vcat(clog1, clog2), "combiné")

        model = RNN(7, [30], 1)
        clog1 = iter2(model, ldata1, ldatax, nbepoch=1000, freq=10000, clipval=1e1, regc=1e-6, learning_rate=1e-4)
        clog2 = iter2(model, ldata1, ldatax, nbepoch=3000, freq=10000, clipval=1e1, regc=1e-7, learning_rate=1e-5)
        plotclog(vcat(clog1, clog2), "combiné 30")


        model = RNN(7, [5,5], 1)
        clog = iter2(model, ldata1, ldatax, nbepoch=4000, freq=10000, clipval=1e4, regc=0., learning_rate=1e-4)
        plotclog(clog, "5+5 lrate 1e-4, regc 0")

        model = RNN(7, [10], 1)
        clog = iter2(model, ldata1, ldatax, nbepoch=10000, freq=10000, clipval=1e1, regc=1e-7, learning_rate=1e-5)
        plotclog(vcat(clog), "10 1e-5 / 1e-7")  # 58% / 60% err = 0.053



    #### recherche des meilleurs params de regul et learning rate
        res2 = Any[]
        for regc in 10 .^ [-10.,-8,-6,-4], lrate in 10 .^ [-3., -4, -5]
            println(regc, " / ", lrate)
            model = RNN(7, [10], 1) # success ratio 52.0%, p-value 0.182
            N = 100 ; res = Array(Float64, N, 5)
            # regc, lrate = 1e-7, 1e-3
            for i in 1:N
                iter(model, ldata1, nbepoch=100, freq=0, clipval=1e1, regc=regc, learning_rate=lrate)
                sc1, sc2 = score(model, ldata0), score(model, ldatax)                
                err = Float64[rnn(model, dat...)[3] for dat in ldata0]
                res[i,:] = [sc1..., sc2..., std(err)]
            end
            push!(res2, (regc, lrate, res))
        end

        ["reg $(x[1]) rate $(x[2])" for x in res2]

        [x[2] for x in filter(x->x[1]==1e-10, res2)]
        Bokeh.plot([1:N], res2[1:3][3][:,[1,3]], title="reg $regc rate $lrate") ; Bokeh.showplot()

        ### comparaisons à regul égale
            regc0 = 1e-4
            Bokeh.hold(true)
            pd = hcat( [x[3][:,1] for x in filter(x->x[1]==regc0, res2)]...)
            Bokeh.plot([1:N], pd, "r-|g-|b-")
            pd = hcat( [x[3][:,3] for x in filter(x->x[1]==regc0, res2)]...)
            Bokeh.plot([1:N], pd, "r--|g--|b--")
            Bokeh.showplot()
            Bokeh.hold(false)
            # reg = 1e-10 : lrate 1e-4 monte plus vite, ok jusqu'à 20 pas, 60% / 60%
            # reg = 1e-8  : lrate 1e-4 ok jusqu'à 40 pas, 60% / 60%, lrate 1e-5 plus stable à long terme  60% / 60% ?
            # reg = 1e-6  : tous rapprochés, rouge converge rapidement, aucun out of sample ne se dégrade trop
            # reg = 1e-4  : meilleur fit à 55%, reg trop forte

    ### verifs
        ress = Float64[rnn(model, dat...)[j] for dat in ldata0, j in 1:3]
        mean(ress[:,1] .>= 0.5) # 38%
        mean(ress[:,2] .>= 0.5) # 47%

        Bokeh.plot([1.:314;], ress[:,1:2]) ; Bokeh.showplot()
        Bokeh.plot(ress[:,2], ress[:,1], ".") ; Bokeh.showplot()


    ### RNN, layer 30
        model = RNN(7, [30], 1)
        iter(model, ldata1, nbepoch=500, freq=10000, clipval=1e0, regc=1e-10, learning_rate=3e-3)
        iter(model, ldata1, nbepoch=500, freq=10000, clipval=1e0, regc=1e-10, learning_rate=1e-3)
        iter(model, ldata1, nbepoch=500, freq=10000, clipval=1e2, regc=1e-10, learning_rate=2e-4)
        iter(model, ldata1, nbepoch=500, freq=10000, clipval=1e2, regc=1e-10, learning_rate=5e-5)
        # 0.0195
        score(model, ldata1) # success ratio 54.0%, p-value 0.07
        score(model, ldatax) # success ratio 59.0%, p-value 0.108
        sol1 = deepcopy(model)

    ### RNN, layer 5
        model = RNN(7, [5], 1)
        iter(model, ldata1, nbepoch=500, freq=10000, clipval=1e-2, regc=1e-3, learning_rate=1e-3)
        iter(model, ldata1, nbepoch=500, freq=10000, clipval=1e2, regc=1e-10, learning_rate=2e-4)
        iter(model, ldata1, nbepoch=500, freq=10000, clipval=1e2, regc=1e-10, learning_rate=5e-5)
        # 0.0195
        score(model, ldata1) # success ratio 52.0%, p-value 0.182
        score(model, ldatax) # success ratio 59.0%, p-value 0.108
        sol1 = deepcopy(model)

        [rnn(model, dat...) for dat in ldata0]

    ### RNN, layer 7+3
        model = RNN(7, [7,3], 1)
        iter(model, ldata1, nbepoch=500, freq=10000, clipval=1e2, regc=1e-10, learning_rate=1e-2)
        iter(model, ldata1, nbepoch=500, freq=10000, clipval=1e2, regc=1e-10, learning_rate=1e-3)
        iter(model, ldata1, nbepoch=500, freq=10000, clipval=1e2, regc=1e-10, learning_rate=5e-5)
        # 0.0196
        score(model, ldata1) # success ratio 52.0%, p-value 0.182
        score(model, ldatax) # success ratio 59.0%, p-value 0.108
        sol1 = deepcopy(model)

    ### RNN, layer 5+5
        model = RNN(7, [5,5], 1)
        ldata1 = shuffle(ldata0)
        iter(model, ldata1, nbepoch=500, freq=10000, clipval=1e2, regc=1e-10, learning_rate=1e-2)
        iter(model, ldata1, nbepoch=500, freq=10000, clipval=1e2, regc=1e-10, learning_rate=1e-3)
        iter(model, ldata1, nbepoch=500, freq=10000, clipval=1e2, regc=1e-10, learning_rate=5e-5)
        # 0.0196
        score(model, ldata1) # success ratio 52.0%, p-value 0.182
        score(model, ldatax) # success ratio 59.0%, p-value 0.108
        sol1 = deepcopy(model)


        predict = [rnn(model, dat...) for dat in ldata0]
        rnn(model, ldata0[1]...)
        rnn(model, ldata0[2]...)
        rnn(model, ldata0[3]...)
        rnn(model, ldata0[1]...)

    ### RNN, layer 20, split calib / valid set
        model = RNN(8, [20], 1)
        splitidx = round(Integer, 4/5*length(ldata))
        ldata1, ldata2 = ldata[1:splitidx], ldata[splitidx+1:end]
        iter(model, ldata1, nbepoch=100, freq=1000, clipval=1e0, regc=1e-10, learning_rate=1e-3)
        iter(model, ldata1, nbepoch=500, freq=1000, clipval=1e1, regc=1e-10, learning_rate=2e-4)
        iter(model, ldata1, nbepoch=1000, freq=10000, clipval=1e1, regc=1e-10, learning_rate=1e-5)
        # 0.02 (prof=5)
        score(model, ldata1) # [-0.0,0.014] ([0.001,0.034])
        score(model, ldata2) # [-0.0,0.012] ([0.0,0.025])
        sol = deepcopy(model)

    ### RNN, layer 10+10
        model = RNN(7, [10,10], 1)
        ldata1 = shuffle(ldata0)
        iter(model, ldata1, nbepoch=500, freq=10000, clipval=1e0, regc=1e-10, learning_rate=1e-3)
        iter(model, ldata1, nbepoch=500, freq=10000, clipval=1e2, regc=1e-10, learning_rate=5e-4)
        iter(model, ldata1, nbepoch=500, freq=10000, clipval=1e2, regc=1e-10, learning_rate=1e-4)
        iter(model, ldata1, nbepoch=1000, freq=10000, clipval=1e2, regc=1e-10, learning_rate=5e-5)
        # 0.014
        sol1 = deepcopy(model)

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

    res = simul(strat1, sol1, ldata0, costrel=0., costabs=0.) # +61% / +95% (10+10)
    Bokeh.plot(Float64[1:length(ldata0);], res[:,[1, 5, 7]])
    Bokeh.showplot()

    # cout réels coinbase
    res = simul(strat1, sol1, ldata0, costrel=0.01, costabs=0.) # +29% / 61% (10+10)
    Bokeh.plot(Float64[1:length(ldata0);], res[:,[1, 5, 7]])
    Bokeh.showplot() 


