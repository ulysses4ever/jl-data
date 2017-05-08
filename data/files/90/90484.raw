using DtPlot

#using Winston
using Winston
using PosixCalendar
using Predictors
using DeepThought.DTPredictors
using DeepThought.DTPDFS
using Verification
using DataFrames
using Datetime
import DeepThought.DTPDFS.PDF


REPOSITORY = joinpath(Pkg.dir("DeepThoughtTestData"), "data-root")
STATION = "93439"
FVAR = "TTTTT"
CANDIDATE = "vbagging_TTTTTnz8km_TTTTT"

OBS = Observation(REPOSITORY,STATION,"TTTTT","target","observation")
F = PDFForecast(REPOSITORY,STATION,FVAR, CANDIDATE)

hourinsecs = 60*60
dayinsecs = 24*3600
basestep = 12*hourinsecs
range = (0, 48 * hourinsecs)
# Example 1 --------------------------------------------------------------------
period = Request((Time(2013,7,1,12),
                  Time(2013,7,1,12), 
                  basestep),
                 range)
#Monday 1st July 2013 12:00:00 AM

hint(OBS, period)
obs = getdata(OBS, period)

vts = None
pps = None
vals = None
bts = sort(collect(keys(obs)))

# Pdf forecast
df = prepareDataFramePdf(F, period)
fp = leaf(df, CANDIDATE)
display(fp)

# Obs
for bt = bts
    pps = sort(collect(keys(obs[bt])))
    vts = sort([bt + pp for pp = pps])
    vals = [obs[bt][pp] for pp = pps]
    pps = [pp.seconds for pp in pps]
    vts = [vt.seconds/3600 for vt in vts]
    #plot(vts, vals,"k")
end         

obsp = Curve(vts, vals, color="grey")
add(fp, obsp)
#-------------------------------------------------------------------------------

# Example 2 --------------------------------------------------------------------
period = Request((Time(2013,7,1,12),
                  Time(2013,8,5,12), 
                  basestep),
                 range)

df = prepareDataFramePdf(F, period)
figure()
fp2 = FramedPlot()
#figure()
colors = ["red", "blue", "green", "magenta", "orange"]
cnt = 0
for fc in groupby(df, :basetime)
    cnt += 1
    x = convert(Array{Float64,1}, fc[:x3])
    y = convert(Array{Float64,1}, fc[:y])

    color = colors[1+cnt%length(colors)]
    p = Points(x, y)
    style(p, kind="filled circle", size=0.3, color=color)

    c = Curve(x, y, color=color)
    add(fp2, p)
    add(fp2, c)
    #oplot(x,y)
    ## errorbar(fc[:x3], fc[:y], yerr=[fc[:q25], fc[:q75]],
    ##          fmt="o", ecolor='g', capthick=2)
end

# Obs
obs = getdata(OBS, period)
vts = None
pps = None
vals = None
bts = sort(collect(keys(obs)))
for bt = bts
    pps = sort(collect(keys(obs[bt])))
    vts = sort([bt + pp for pp = pps])
    vals = [obs[bt][pp] for pp = pps]
    pps = [pp.seconds for pp in pps]
    vts = [vt.seconds/3600 for vt in vts]
    #plot(vts, vals,"k")
end         

obsp = Points(vts, vals, color="black")
style(obsp, kind="circle", size=0.3)

obsc = Curve(vts, vals, color="grey")
#fp2 = FramedPlot()
add(fp2, obsp)
add(fp2, obsc)

display(fp2)

# adjust xbounds
setattr(fp2, "xrange",(vts[1]-20, vts[end]))
display(fp2)



# Example 3 --------------------------------------------------------------------
period = Request((Time(2013,7,1,12),
                  Time(2013,7,5,12), 
                  basestep*2),
                 range)
figure()
df = prepareDataFramePdf(F, period)
fp3 = FramedPlot()
#figure()
colors = ["red", "blue", "green", "magenta", "orange"]
cnt = 0
for fc in groupby(df, :basetime)
    cnt += 1
    x = convert(Array{Float64,1}, fc[:x2])
    y = convert(Array{Float64,1}, fc[:y])
    #println(x, "\n",y)
    println(cnt%length(colors))
    color = colors[1+cnt%length(colors)]
    p = Points(x, y)
    setattr(p, label=fc[:basetime][1])
    style(p, kind="filled circle", size=0.3, color=color)


    #l = Legend(.1, .9, {a,b,s})

    c = Curve(x, y, color=color)
    add(fp3, p)
    add(fp3, c)
    #oplot(x,y)
    ## errorbar(fc[:x3], fc[:y], yerr=[fc[:q25], fc[:q75]],
    ##          fmt="o", ecolor='g', capthick=2)
end

display(fp3)


# Example 4 --------------------------------------------------------------------
period = Request((Time(2013,7,1,12),
                  Time(2013,7,5,12), 
                  basestep),
                 (0,basestep))
figure()
df = prepareDataFramePdf(F, period)
fp4 = FramedPlot()
#figure()
colors = ["red", "blue", "green", "magenta", "orange"]
cnt = 0
for fc in groupby(df, :basetime)
    cnt += 1
    x = convert(Array{Float64,1}, fc[:x3])
    y = convert(Array{Float64,1}, fc[:y])
    #println(x, "\n",y)
    println(cnt%length(colors))
    color = colors[1+cnt%length(colors)]
    p = Points(x, y)
    setattr(p, label=fc[:basetime][1])
    style(p, kind="filled circle", size=0.3, color=color)


    #l = Legend(.1, .9, {a,b,s})

    c = Curve(x, y, color=color)
    add(fp4, p)
    add(fp4, c)
    #oplot(x,y)
    ## errorbar(fc[:x3], fc[:y], yerr=[fc[:q25], fc[:q75]],
    ##          fmt="o", ecolor='g', capthick=2)
end

display(fp4)



# Example 5 --------------------------------------------------------------------
period = Request((Time(2013,7,1,12),
                  Time(2013,7,5,12), 
                  basestep),
                 (0,basestep))
figure()
df = prepareDataFramePdf(F, period)
fp4 = FramedPlot()
#figure()
colors = ["red", "blue", "green", "magenta", "orange"]
cnt = 0
for fc in groupby(df, :basetime)
    cnt += 1
    x = convert(Array{Float64,1}, fc[:x3])
    y = convert(Array{Float64,1}, fc[:y])
    #println(x, "\n",y)
    color = colors[1+cnt%length(colors)]
    p = Points(x, y)
    setattr(p, label=fc[:basetime][1])
    style(p, kind="filled circle", size=0.3, color=color)


    #l = Legend(.1, .9, {a,b,s})

    c = Curve(x, y, color=color)
    add(fp4, p)
    add(fp4, c)
    #oplot(x,y)
    ## errorbar(fc[:x3], fc[:y], yerr=[fc[:q25], fc[:q75]],
    ##          fmt="o", ecolor='g', capthick=2)
end

display(fp4)
