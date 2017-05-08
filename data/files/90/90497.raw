module DtPlot

#using Winston
using PyPlot
using Winston
using PosixCalendar
using Predictors
using DeepThought.DTPredictors
using DeepThought.DTPDFS
using Verification
using DataFrames
using Datetime
import DeepThought.DTPDFS.PDF

export prepareDataFramePdf, prepareDataFrameObs, leaf

function prepareDataFramePdf(F, period)
    fx = asdataframe(F, period)
    fx[:x1] = [x.seconds/3600 for x = fx[:basetime]]
    fx[:x2] = [x.seconds/3600 for x = fx[:prognosis]]
    fx[:x3] = [x.seconds/3600 for x = fx[:basetime] + fx[:prognosis]]
    fx[:x4] = [datetime(PosixCalendar.ymdhms(x)...) for x = fx[:basetime] + fx[:prognosis]]
    fx[:x5] = [string(datetime(PosixCalendar.ymdhms(x)...)) for x = fx[:basetime] + fx[:prognosis]]
    
    fx[:y] = [median(x) for x = fx[:value]]
    fx[:q75] = [quantile(x, 0.75) for x = fx[:value]]
    fx[:q25] = [quantile(x, 0.25) for x = fx[:value]]
    #fx[:y] = dropna(fx[:y])
    sort!(fx,cols=:x2)
end

function prepareDataFrameObs(F, period)
    fx = asdataframe(F, period)
    fx[:x1] = [x.seconds/3600 for x = fx[:basetime]]
    fx[:x2] = [x.seconds/3600 for x = fx[:prognosis]]
    fx[:x3] = [x.seconds/3600 for x = fx[:basetime] + fx[:prognosis]]
    fx[:x4] = [datetime(PosixCalendar.ymdhms(x)...) for x = fx[:basetime] + fx[:prognosis]]
    fx[:x5] = [string(datetime(PosixCalendar.ymdhms(x)...)) for x = fx[:basetime] + fx[:prognosis]]
    
    fx[:y] = fx[:value]
    sort!(fx,cols=:x2)
end


function leaf(fx, title)
    
    progstep = 1
    bulge = progstep * 0.3

    #fp = FramedPlot(title = "candidate")
    fp = FramedPlot(title = title)
    for fc in groupby(fx, :basetime)
    
        #add(fp, Points(fc[:x3], fc[:y]))
        #add(fp, Curve(fc[:x3], fc[:y]))
        for fpp in groupby(fc, :prognosis)
            bt = fpp[:x1][1]
            vt = fpp[:x3][1]
            pdfi = fpp[:value][1]
            p = [[0.01:0.1:0.26]]
            y1 = [quantile(pdfi, p) for p = [.005:.005:.995]]
            y2 = [quantile(pdfi, p) for p = [.25:.005:.75]]
            x1 = [pdf(pdfi,yi)  for yi = y1] /pdf(pdfi, quantile(pdfi, 0.50)) * bulge
            x2 = [pdf(pdfi,yi)  for yi = y2] /pdf(pdfi, quantile(pdfi, 0.50)) * bulge
            #add(fp, Curve(vt + x, y, color="red"))
            #add(fp, Curve(vt - x, y))
            
            add(fp, FillBetween(vt .- x1, y1,
                                vt .+ x1, y1; color="orange", alpha=0.1))
            add(fp, FillBetween(vt .- x2, y2,
                                vt .+ x2, y2; color="blue", alpha=0.1))
            # add(fp, FillBetween(vt - x1, y1,
            #                     vt + x1, y1; color="#E0E20C", alpha=0.1))
            # add(fp, FillBetween(vt - x2, y2,
            #                     vt + x2, y2; color="#00274C", alpha=0.1))
            ## add(fp, FillBetween(vt - x1, y1,
            ##                     vt + x1, y1; color="#00274C", alpha=0.1))
            ## add(fp, FillBetween(vt - x2, y2,
            ##                     vt + x2, y2; color="#E0E20C", alpha=0.1))
            
            #plot(vt+x,y,"r-", color = gca().lines[-1].get_color())
            #plot(vt-x,y,"r-", color = gca().lines[-1].get_color())
        end
        b = Points(fc[:x3], fc[:y])
        #setattr(b, label="b points")
        style(b, kind="filled circle", size=0.5, color="white")
        #style(b, size=0.5)
        add(fp, b)
        add(fp, Curve(fc[:x3], fc[:y]))
        
        epoch_ticklabels = getattr(fp.x1, "ticklabels")
        epoch_ticks = getattr(fp.x1, "ticks")
        println("xxx ", epoch_ticks)
        println("xxx ", epoch_ticklabels)
        
        
        nticks = 4
        date_ticklabels = String[]
        [push!(date_ticklabels, PosixCalendar.iso(i)) for i in fc[:basetime] + fc[:prognosis] ]
        date_idxs = map(int, linspace(1, length(date_ticklabels), nticks))
        date_ticklabels2 = String[]
        println([date_ticklabels[i] for i in date_idxs ]  )
        [push!(date_ticklabels2, replace(date_ticklabels[i], "T", "\n  "))
         for i in date_idxs ]                      
        #date_ticklabels2 = ["aaaa\nbbb","aaaa\nbbb","aaaa\nbbb","aaaa\nbbb"]

        ## println("yyy ", epoch_ticklabels)
        ## println("yyy ", date_ticklabels)
        ## ticklabels = String[]
        
        ## [push!(ticklabels, i) for i = ["a","b"]]
        setattr(fp.x1, "ticks", length(date_ticklabels2))
        setattr(fp.x1, "ticklabels", date_ticklabels2)
        # setattr(fp.x1, "ticks_style", angle=90)
        #style(fp, angle=90)
    end
    return fp
end





## function plot{T}(p::Predictor{T},period::Request)
##     BT = Time[]
##     PP = Duration[]
##     value = T[]  
##     hint(p, period)
##     d = getdata(p, period)
##     for bt in keys(d)
##         for pp in keys(d[bt])
##             push!(BT,bt)
##             push!(PP,pp)
##             push!(value,d[bt][pp])
##         end
##     end
    
    
## ## end
## figure()

## #-------------------------------------------------------------------------------
## figure()
## plot(vts, vals, "k-")
## F = PDFForecast(REPOSITORY,STATION,"TTTTT","polishing_TTTTTNZBlend_TTTTT")
## hint(F, period)
## fx  = getdata(F, period)
## vts = None
## pps = None
## vals = None
## bts = sort(collect(keys(fx)))
## for bt = bts
##     pps = sort(collect(keys(fx[bt])))
##     vts = sort([bt + pp for pp = pps])
##     vals = [mean(fx[bt][pp]) for pp = pps]
##     pps = [pp.seconds for pp in pps]
##     vts = [vt.seconds for vt in vts]
##     #plot(vts, vals)
## end         




# Need to add obs to dataframe


# figure()
# for fc in groupby(fx, :basetime)
#     plot(fc[:x1], fc[:y],"o")
# end

# figure()
# for fc in groupby(fx, :basetime)
#     plot(fc[:x2], fc[:y],"o")
# end

## #figure()
## title(candidate)
## for fc in groupby(fx, :basetime)
##     plot(fc[:x3], fc[:y],"o-")
##     for fpp in groupby(fc, :prognosis)
##         bt = fpp[:x1][1]
##         vt = fpp[:x3][1]
##         pdfi = fpp[:value][1]
##         p = [[0.01:0.1:0.26]]
##         y = [quantile(pdfi, p) for p = [.005:.005:.995]]
##         x = [pdf(pdfi,yi)  for yi = y] /pdf(pdfi, quantile(pdfi, 0.50)) * 0.5 * 1 #12
##         plot(vt+x,y,"r-")
##         plot(vt-x,y,"r-")
##         #plot(vt+x,y,"r-", color = gca().lines[-1].get_color())
##         #plot(vt-x,y,"r-", color = gca().lines[-1].get_color())
##     end
## end





## title(candidate)
## for fc in groupby(fx, :basetime)
##     #plot(fc[:x3], fc[:y],"o-")
##     #plot(fc[:x3], fc[:q25],"r-")
##     #plot(fc[:x3], fc[:q75],"ro")
##     yerr = zeros((2,length(fc[:q25])))
##     yerr[1,:] = fc[:y] - fc[:q25]
##     yerr[2,:] = fc[:q75] - fc[:y]
##     errorbar(fc[:x3], fc[:y], yerr=yerr,
##              fmt="o", ecolor='g', capthick=2)
## end

## figure()
## for fc in groupby(fx, :basetime)
##     plot(fc[:x3], fc[:y],"o-")
##     ## errorbar(fc[:x3], fc[:y], yerr=[fc[:q25], fc[:q75]],
##     ##          fmt="o", ecolor='g', capthick=2)
## end

# figure()
# for fc in groupby(fx, :basetime)
#     #plot(fc[:x3], fc[:y],"o-")
#     errorbar(fc[:x3], fc[:y], yerr=[fc[:q25], fc[:q75]],
#              fmt="o", ecolor='g', capthick=2)
# end

# p = FramedPlot(
#          title="title!",
#          xlabel="\\Sigma x^2_i",
#          ylabel="\\Theta_i")

# for fc in groupby(fx, :basetime)
#     x = Float64[]
#     y = Float64[]
#     yp = Float64[]
#     ym = Float64[]
#     [push!(x, i)  for i = fc[:x3]]
#     [push!(y, i)  for i = fc[:y]]
#     [push!(yp, i) for i = fc[:q25]]
#     [push!(ym, i) for i = fc[:q75]]
#     # add(p, FillBetween(x, ym, x, yp))
#     # add(p, Curve(x, y))
#     # add(p, Points(x, y))
#     # savefig("fig.png")
#     add(p,Winston.ErrorBarsY(x,ym,yp,color="green"))
# end
# savefig("fig.png")
# # function basicplot(df) # This should be *much* more sophisticated!
# #     p=Winston.FramedPlot(xlabel="$(names(df)[1]) (hours)")
# #     t=map((x)->x.seconds/3600,df[1])
# #     add(p,Winston.ErrorBarsY(t,df[:q05],df[:q95],color="green"))
# #     add(p,Winston.ErrorBarsY(t,df[:q25],df[:q75],color="blue"))
# #     add(p,Winston.ErrorBarsY(t,df[:q50],df[:q50],color="red"))
# #     return p
# # end


# figure()
# for fc in groupby(fx, :basetime)
#     x = Float64[]
#     y = Float64[]
#     [push!(x, xi) for xi = fc[:x3]]
#     [push!(y, yi) for yi = fc[:y]]
#     oplot(x, y,"o-")
# end
# savefig("figure.png") 

# figure()
# for fc in groupby(fx, :basetime)
#    plot_date(fc[:x4], fc[:y],"o")
# end

# for fc in groupby(fx, :basetime)
#     p = Gadfly.plot(fc ,x="x5",y="y",Geom.line)
#     #draw(D3("mammals.js", 6inch, 6inch), p)
#     draw(SVG("myplot.svg", 12inch, 6inch), p)
# end

# p = plot(fx, x="x2", y="y",color="basetime", Geom.line)
# draw(SVG("myplot2.svg", 12inch, 6inch), p)
 

## #-------------------------------------------------------------------------------
## G = PDFForecast(REPOSITORY,STATION,"TTTTT","revising_TTTTTNZBlend_TTTTT")
## hint(G, period)
## gx  = getdata(G, period)
## vts = None
## pps = None
## vals = None
## bts = sort(collect(keys(obs)))
## for bt = bts
##     pps = sort(collect(keys(gx[bt])))
##     vts = sort([bt + pp for pp = pps])
##     vals = [gx[bt][pp] for pp = pps]
##     pps = [pp.seconds for pp in pps]
##     vts = [vt.seconds for vt in vts]
##     plot(vts, vals)
## end         

## function fromTimetoSeconds(t::Time)
##     t.seconds
## end

## function fromTimetoSeconds(t::Time[])
##     return [ti.seconds for ti = t]
## end

## function toString(t::Time)
## end


#req = Request((Time(2014,5,1), Time(2014,6,1),), (0,dayinsecs*15))
#hint(OBS,req)
#data=Predictors.Unary{pointtype}(data,pointfunc)
#data=getdata(OBS,req)
end # module
