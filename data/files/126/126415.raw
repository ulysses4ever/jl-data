##########################################################################
#
#    Modélisation cours (WIP)
#
#
#    2015-07-23        : creation
#
##########################################################################

version = v"0.1"

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
        P:\Documents\Julia\prediction\data

        df0 = readtable(joinpath(datapath, "BAVERAGE-BITCOIN_CENTRALEUR.csv"), separator=',')
        # df0 = @transform(df0, Date = Date(:Date)) ; nothing
        df0 = df0[[:Date, :Ask, :Bid, :Last, :Volume_BTC_]]

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

    ##### Création des variables -----------------------------------------------------
        # df = @select(df0, 
        #     age              = :age,
        #     lcommit          = (log( :commit ) - 13.) / 20,
        #     on0              = :on ./ :commit,
        #     isLNI            = :SBU .== "LNI" ,
        #     isNAT            = :SBU .== "NAT" ,
        #     isSAFT           = :SBU .== "SAFT" ,
        #     isUSD            = :currency .== "USD" ,
        #     isEUR            = :currency .== "EUR" ,
        #     dur              = :dur ,
        #     durt             = :durt ,
        #     age_expiry       = :durt ./ :dur,
        #     rating           = convert(Array, :rating, 5),    # NA remplacés par 5
        #     iscorpo          = !isna(:ctr) & (indexin(:ctr,[15:22;]) .!= 0),  
        #     isspv            = !isna(:ctr) & (:ctr .== 23   ),     
        #     isFrance         = !isna(:country) & (:country .== "FRANCE") ,
        #     isUSA            = !isna(:country) & (:country .== "UNITED STATES OF AMERICA") ,
        #     isPIIGS          = !isna(:country) & 
        #                         (indexin(:country, ["PORTUGAL", "GREECE", "IRELAND", "SPAIN", "ITALY"]) .!= 0),
        #     :DiffRel_Itraxx_5Y
        #     ) ; nothing

        # varsn = names(df)
        # describe(df)


    #### Génération des séries historiques de longueur 'Span'
        Span = 20

        ldata = Any[]
        avars = convert(Array{Float64}, df0[:,2:end])'
        ares  = convert(Vector{Float64},df0[:Last])
        vscale = mapslices(v -> (minimum(v), maximum(v)), avars, 2)
        rscale = (minimum(ares), maximum(ares))
        for i in 1:nrow(df0)-Span  # i = 1
            vars = (avars[:,i:i+Span-1] .- [ x[1] for x in vscale]) ./ [ x[2]-x[1] for x in vscale]
            res  = (ares[i+Span] - rscale[1]) ./ (rscale[2]-rscale[1])
            push!(ldata, (vars, res))
        end

        srand(1)
        shuffle!(ldata)





    #### Génération des séries historiques de longueur 'Span'
        Span = 5

        ldata0 = Any[]
        avars = convert(Array{Float64}, df0[:,2:end])'
        ares  = convert(Vector{Float64},df0[:Last])
        vscale = mapslices(v -> (minimum(v), maximum(v)), avars, 2)
        rscale = (minimum(ares), maximum(ares))
        for i in 1:nrow(df0)-Span  # i = 1
            vars = (avars[:,i:i+Span-1] .- [ x[1] for x in vscale]) ./ [ x[2]-x[1] for x in vscale]
            res  = (ares[i+Span] - rscale[1]) ./ (rscale[2]-rscale[1])
            push!(ldata0, (vars, res))
        end

        srand(1)
        ldata = shuffle(ldata0)



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
        model = RNN(8, [20], 1)
        ldata1 = shuffle(ldata0)
        iter(model, ldata1, nbepoch=100, freq=1000, clipval=1e0, regc=1e-10, learning_rate=1e-3)
        iter(model, ldata1, nbepoch=500, freq=1000, clipval=1e2, regc=1e-10, learning_rate=2e-4)
        iter(model, ldata1, nbepoch=1000, freq=1000, clipval=1e2, regc=1e-10, learning_rate=5e-5)
        # 0.037 - 0.015 (prof=5)
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
            pred = rnn(model, vars, res)[1] * (rscale[2]-rscale[1]) + rscale[1]
            vrai =                    res * (rscale[2]-rscale[1]) + rscale[1]
            current = vars[3,end] * (rscale[2]-rscale[1]) + rscale[1]
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

    res = simul(strat1, sol1, ldata0) # +41%
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
#    Comparaison autres modèles
##########################################################################

    function score(model, ldata)
        scores = Array(Float64, length(ldata), 2)
        for (i, (vars, res)) in enumerate(ldata) # i, vars, res = 1, ldata[10]...
            estim1, _, _ = rnn(sol, vars, res)
            estim2 = vars[3,end]
            scores[i,:] = [estim1-res, estim2-res]
        end
        print(map(x -> round(x,3), map(f -> f(scores[:,1]), [mean, std])))
        println(" (", map(x -> round(x,3), map(f -> f(scores[:,2]), [mean, std])), ")")
    end
        vcat([:model :last], mean(scores,1), std(scores,1))

        # RNN 10, profondeur 20
         #   :model       :last     
         # -0.00505388  -0.000918741
         #  0.104587     0.0288861   

        # RNN 10, profondeur 20, avec plus de données
         #  :model      :last     
         # 0.00437043  0.000710993
         # 0.0408073   0.032032 

        # RNN 20, profondeur 20, avec plus de données
         #  :model      :last     
         # 0.00369993  0.000710993
         # 0.0382283   0.032032   

        # RNN 20, profondeur 5, avec plus de données
         #  :model      :last     
         # -0.000722144  0.000950978
         #  0.0154367    0.0319049    # YES ! err=5.1€ d'écart-type vs 11€ vol quotidienne

        # RNN 10, profondeur 5
         #  :model      :last     
         # 0.0162666  -0.000719591
         # 0.0736809   0.0286744   

        # RNN 10
         #  :model       :last     
         # 0.00273951  -0.000918741
         # 0.104959     0.0288861  

        # GRU 10
         #  :model       :last     
         # 0.00475316  -0.000918741
         # 0.104127     0.0288861   






##########################################################################
#    Graphes
##########################################################################

    function plotmodel(sol, v0;pars...) # pars = [(:on0, [0., 0.5])]
        # other params set feature vector
        v = copy(v0)
        for (vs, vn) in pars[2:end]
            v[indexin([vs], varsn)] = vn
        end

        # iterate on first param
        vals = pars[1][2]
        pos = indexin([pars[1][1]], varsn)

        Bokeh.hold(true)
        Bokeh.plot( [0., 1., 1.], [1., 1., 0.], "k--")
        colors = ["r", "g", "b", "k"]
        for (i,va) in enumerate(vals) #  on0 = 0.2
            v[pos] = va
            _ , ages, tirs = rnn(sol, v)
            Bokeh.plot( ages, tirs, colors[1 + (i - 1) % length(colors)])
        end
        Bokeh.showplot()
        Bokeh.hold(false)
    end

    v0 = [   0.0,        # :age
                 0.339086,   # :lcommit
                 0.0,        # :on0
                 0.0,        # :isLNI
                 1.0,        # :isNAT
                 0.0,        # :isSAFT
                 1.0,        # :isUSD
                 0.0,        # :isEUR
                 1.5,        # :dur
                 0.35,       # :durt
                 0.233,      # :age_expiry
                 3.0,        # :rating
                 1.0,        # :iscorpo
                 0.0,        # :isspv
                 0.0,        # :isFrance
                 0.0,        # :isUSA
                 0.0,        # :isPIIGS
                 1.0,        # :DiffRel_Itraxx_5Y
                 1.3  ]      # :horizon 

    plotmodel(sol, v0, on0 = [0:0.2:1.;])
    plotmodel(sol, v0, DiffRel_Itraxx_5Y= [0.5:0.5:2.0;], isNAT=0., isSAFT=1.) # SAFT sensible à l'ITRAXX
    plotmodel(sol, v0, DiffRel_Itraxx_5Y= [0.5:0.5:2.0;], isNAT=1., isSAFT=0.) # NAT peu sensible
    plotmodel(sol, v0, isNAT = [1., 0.], isLNI=0., isSAFT=0.)
    plotmodel(sol, v0, isLNI = [1., 0.], isNAT=0., isSAFT=0.)
    plotmodel(sol, v0, isspv = [1., 0.], iscorpo=0.)
    plotmodel(sol, v0, iscorpo = [1., 0.], isspv=0.)
    plotmodel(sol, v0, age_expiry = [0:0.2:1.;])



##########################################################################
#      Sélection de variables influentes
##########################################################################
    function sensi2(model, fitdata)
        vars, pond, res, _, idx = fitdata

        nfeat = size(vars,2)
        nobs  = length(res)
        v = NNMatrix(nfeat, 1)
        δ = zeros(nfeat)
        for ik in 1:nobs  # ik = 10000
            hsem = round(Integer, vars[ik,19] * vars[ik,9] * 365 / 7) # horizon en semaines
            (hsem==0) && continue  # si horizon 0, pas de fit
            δage = 7 / 365 / vars[ik,9]

            prev = (Array(NNMatrix,0), Array(NNMatrix,0), NNMatrix(1,1))
            copy!(v.w, vars[ik,:])

            g = Graph() 
            for i in 1:hsem # i = 1
                v.w[end] = v.w[1] > 1. # horizon à remplacer par flag age > mat
                prev = forwardprop(g, model, v, prev)
                new_on = 1 / (1 + exp(- prev[end].w[1]))
                v.w[1] += δage
                v.w[3] = new_on
            end
            δtx = v.w[3] - res[ik]
            out = prev[end]
            out.dw = ones(out.dw) * pond[ik] * v.w[3] * (1 - v.w[3]) 
            backprop(g)

            δ += model.hdlayers[1].wxh.w' * model.hdlayers[1].bhh.dw 
        end
        δ
    end

