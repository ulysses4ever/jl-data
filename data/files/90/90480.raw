module DtPlot

#using Winston
using PyPlot
#using Winston
using PosixCalendar
using Predictors
using DeepThought.DTPredictors
using DeepThought.DTPDFS
using Verification
using DataFrames
using Datetime
#import Gadfly.plot
#using Gadfly
#include(joinpath(Pkg.dir("Gadfly"), "src", "gadfly.js"))


REPOSITORY = "/home/jade/metservice/code/deepthought/revising/branch-revisingjob/install/data-root_static"
STATION = "93110"

OBS = Observation(REPOSITORY,STATION,"TTTTT","target","observation")
#G = PDFForecast(REPOSITORY,STATION,"TTTTT","revising_TTTTTNZBlend_TTTTT")
F = PDFForecast(REPOSITORY,STATION,"TTTTT","polishing_TTTTTNZBlend_TTTTT")

hourinsecs = 60*60
dayinsecs = 24*3600

#period = Request((Time(2013,7,1),Time(2013,10,1),86400),(0,48*3600))
period = Request((Time(2014,5,1),Time(2014,5,30), 12*hourinsecs),(0,48*3600))


## hint(OBS, period)
## obs = getdata(OBS, period)

## vts = None
## pps = None
## vals = None
## bts = sort(collect(keys(obs)))

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
    
    
## end

## for bt = bts
##     pps = sort(collect(keys(obs[bt])))
##     vts = sort([bt + pp for pp = pps])
##     vals = [obs[bt][pp] for pp = pps]
##     pps = [pp.seconds for pp in pps]
##     vts = [vt.seconds for vt in vts]
##     plot(vts, vals)
## end         

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


fx = asdataframe(F, period)
fx[:x1] = [x.seconds/3600 for x = fx[:basetime]]
fx[:x2] = [x.seconds/3600 for x = fx[:prognosis]]
fx[:x3] = [x.seconds/3600 for x = fx[:basetime] + fx[:prognosis]]
fx[:x4] = [datetime(PosixCalendar.ymdhms(x)...) for x = fx[:basetime] + fx[:prognosis]]
fx[:x5] = [string(datetime(PosixCalendar.ymdhms(x)...)) for x = fx[:basetime] + fx[:prognosis]]

fx[:y] = [median(x) for x = fx[:value]]
fx[:q75] = [quantile(x, 0.75) for x = fx[:value]]
fx[:q25] = [quantile(x, 0.75) for x = fx[:value]]

sort!(fx,cols=:x2)


# Need to add obs to dataframe


# figure()
# for fc in groupby(fx, :basetime)
#     plot(fc[:x1], fc[:y],"o")
# end

# figure()
# for fc in groupby(fx, :basetime)
#     plot(fc[:x2], fc[:y],"o")
# end

figure()
for fc in groupby(fx, :basetime)
    plot(fc[:x3], fc[:y],"o-")
end
plot(vts, )

figure()
for fc in groupby(fx, :basetime)
    #plot(fc[:x3], fc[:y],"o-")
    errorbar(fc[:x3], fc[:y], yerr=[fc[:q25], fc[:q75]],
             fmt="o", ecolor='g', capthick=2)
end

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
