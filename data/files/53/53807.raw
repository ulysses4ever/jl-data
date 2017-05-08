if Pkg.installed("DataFrames") == nothing
    Pkg.add("DataFrames")
end
using DataFrames
if Pkg.installed("Winston") == nothing
    Pkg.add("Winston")
end
using Winston
if Pkg.installed("Images") == nothing
    Pkg.add("Images")
end
using Images
if Pkg.installed("Iterators") == nothing
    Pkg.add("Iterators")
end
using Iterators

import Base.convert

function KSP_engine_charts(mintwr=0., atmpressure=0., filename="", payload_range=[0.01 1000], deltav_range=[0 8000], max_num_engines=Inf)
# Plot mass-optimal engine type vs delta-V and payload mass,
# for a given minimum Kerbin-relative TWR (default 0) and
# atmospheric pressure (in atm, default 0). Third input is
# optional filename to save chart. Optionally, select min and
# max payloads (in t, default [0.01 1000]), min and max delta-v
# (in m/s, default [0 8000]), and max number of engines (default Inf).

# Parameters - if you change these or anything else,
# remember to re-run include("KSP_engine_charts.jl")
g0_isp = 9.82 # m/s^2
g0_twr = 9.81 # m/s^2
payload_points = logspace(log10(payload_range[1]), log10(payload_range[2]), 501) # payloads to sample (t)
deltav_points = linspace(deltav_range[1], deltav_range[2], 1001) # delta-v points to sample (m/s)

# helper function to convert comma separated string to DataFrame
str2df(s) = readtable(IOBuffer(replace(replace(s, " ", ""), "_", " ")))

LiquidEngines = str2df(
    "name,      mass, thrust, ispatm, ispvac \n" *
    "LV-1,      0.03,     4.,   220.,   290. \n" *
    "24-77,     0.09,    20.,   250.,   300. \n" *
    "48-7S,     0.10,    30.,   300.,   350. \n" *
    "LV-909,    0.50,    50.,   300.,   390. \n" *
    # uncomment the suboptimal engines if you
    # impose a max_num_engines constraint
    #"Mark_55,   0.90,   120.,   290.,   320. \n" *
    "LV-T30,    1.25,   215.,   320.,   370. \n" *
    #"LV-T45,    1.50,   200.,   320.,   370. \n" *
    "Aerospike, 1.50,   175.,   388.,   390. \n" *
    #"Rapier,    1.75,   175.,   320.,   360. \n" *
    "LV-N,      2.25,    60.,   220.,   800. \n" *
    #"Poodle,    2.50,   220.,   270.,   390. \n" *
    #"Skipper,   4.00,   650.,   300.,   350. \n" *
    #"Mainsail,  6.00,  1500.,   280.,   330. \n" *
    "KR-2L,     6.50,  2500.,   280.,   380. \n" *
    "KS-25x4,   9.75,  3200.,   320.,   360.")

LiquidTanks = str2df(
    "name,   drymass, propmass
    Oscar-B,   0.015, 0.063675
    Round-8,   0.025,    0.111
    FL-T100,  0.0625,      0.5")
    # anything bigger only matters for part count reasons
    #FL-T200,   0.125,      1.0
    #FL-T400,    0.25,      2.0
    #X200-8,      0.5,      4.0
    #X200-16,     1.0,      8.0
    #X200-32,     2.0,     16.0
    #Jumbo-64,    4.0,     32.0
    #S3-3600,     2.5,     18.0
    #S3-7200,     5.0,     36.0
    #S3-14400,   10.0,     72.0")

LiquidBoosters = str2df(
    "name,    drymass, propmass, thrust, ispatm, ispvac
    LFB_KR-1x2,  10.0,     32.0,  2000.,   320.,   360.")

SolidBoosters = str2df(
    "name,     drymass, propmass, thrust, ispatm, ispvac \n" *
    "Sepratron, 0.0125,     0.06,    18.,   100.,   100. \n" *
    # uncomment the suboptimal SRBs if you
    # impose a max_num_engines constraint
    #"LES,          1.0,   0.1125,   750.,   320.,   360. \n" *
    "RT-10,        0.5,   3.2485,   250.,   225.,   240.")
    #"BACC,         1.5,    6.375,   315.,   230.,   250. \n" *
    #"KD25k,        3.0,    18.75,   650.,   230.,   250.")

XenonEngines = str2df(
    "name,  mass, thrust, ispatm, ispvac
    PB-ION, 0.25,     2.,  4200.,  4200.")
# assume only massless OX-STAT solar panels used for electricity

XenonTanks = str2df(
    "name,   drymass, propmass
    PB-X50R,    0.03,     0.04
    PB-X150,    0.05,     0.07")

# Create an array of all combinations of tanks
function smalltankcombs(tanks::DataFrame)
    # Find the tank with the best mass ratio
    besttank = indmax(tanks[:propmass] ./ tanks[:drymass])
    # Calculate a power of 10 that will make all the dry masses integers
    power10 = 10^maximum([length(split(rstrip(@sprintf("%f", drymass), '0'), '.')[2]) for drymass in tanks[:drymass]])
    # Calculate the LCM of all the dry masses
    lcmtanks = int(lcm(int(power10*tanks[:drymass])) ./ (power10*tanks[:drymass]))
    # Create an array of all possible tank combinations
    combs = collect(Iterators.product([0:i for i in lcmtanks]...))
    tankcombs = Array(Int, size(combs,1), size(tanks,1))
    for j=1:size(combs,1)
        tankcombs[j,:] = [combs[j]...]'
    end
    # Calculate the dry and wet masses of these combinations
    tankarray = tankcombs * [tanks[:drymass] tanks[:propmass]] * [1 1; 0 1]
    # Sort by dry mass, then by wet mass
    tankarray = sortrows(tankarray)
    # Remove combinations with more dry mass than the LCM combination
    tankarray = tankarray[1:indexin([lcmtanks[1]*tanks[:drymass][1]], tankarray[:,1])[1],:]
end

# This function will be used later to determine the lowest-mass combination
# of small fuel tanks that can provide a required amount of fuel
function smalltankmass(tankarray::Matrix, massratioj, rhs)
    for i=1:size(tankarray,1)
        c = massratioj * tankarray[i, 1]
        if tankarray[i, 2] - c >= rhs
            return c
        end
    end
    error("should never get here")
end

# Find the best standard (engines and tanks are separate) engine
# Modifies bestengine and bestmass
function beststandardengine!(bestengine::Matrix, bestmass::Matrix, kmax::Int, Engines::DataFrame, Tanks::DataFrame)
    tankarray = smalltankcombs(Tanks)
    dm_optimal = tankarray[end, 1]
    pm_optimal = tankarray[end, 2] - dm_optimal

    for k=kmax + (1:size(Engines,1))
        enginemassk = Engines[:mass][k - kmax]
        thrustk = Engines[:thrust][k - kmax]
        # skip this engine if it cannot meet the twr requirement
        (thrustk < enginemassk * g0_twr * mintwr) && continue
        veffk = g0_isp * (clamp(atmpressure, 0, 1) * Engines[:ispatm][k - kmax] + 
            clamp(1 - atmpressure, 0, 1) * Engines[:ispvac][k - kmax])
        for j=1:length(deltav_points)
            massratioj = exp(deltav_points[j] / veffk)
            enginedenom = (pm_optimal + dm_optimal) * thrustk - massratioj * (
                        enginemassk*g0_twr*mintwr*pm_optimal + dm_optimal*thrustk)
            (enginedenom <= 0.) && continue
            enginesperton = g0_twr * mintwr * pm_optimal * massratioj / enginedenom
            tankfactor = (massratioj - 1.) / (pm_optimal + dm_optimal * (1. - massratioj))
            for i=1:length(payload_points)
                payloadi = payload_points[i]
                # best-case number of engines if both engines and fuel tanks were continuous
                numengines = (mintwr == 0.) ? 1. : ceil(payloadi * enginesperton)
                while numengines <= max_num_engines
                    # best-case continuous number of optimal tanks,
                    # with number of engines rounded up to next integer
                    # round number of tanks down, then look at smaller types of tanks
                    numtanks_base = floor((enginemassk * numengines + payloadi) * tankfactor)
                    drymass_base = enginemassk*numengines + payloadi + numtanks_base*dm_optimal
                    wetmass_base = drymass_base + numtanks_base*pm_optimal
                    wetmass_actual = massratioj * drymass_base + 
                        smalltankmass(tankarray, massratioj, massratioj * drymass_base - wetmass_base)
                    if wetmass_actual > bestmass[i,j]
                        # have already found a better engine at this point
                        break
                    elseif numengines * thrustk < g0_twr * mintwr * wetmass_actual
                        # twr constraint is violated due to rounding of number of fuel tanks
                        # try again with another engine added
                        numengines += 1.
                    else
                        # twr and dv constraints are satisfied, so we have found
                        # the mass-optimal number of engines and fuel tanks
                        bestmass[i,j] = wetmass_actual
                        bestengine[i,j] = k
                        break
                    end
                end
            end
        end
    end
end

bestmass = fill(Inf, length(payload_points), length(deltav_points))
bestengine = zeros(Int, length(payload_points), length(deltav_points))
kmax = 0

liquidarray = smalltankcombs(LiquidTanks)
dm_liquidopt = liquidarray[end, 1]
pm_liquidopt = liquidarray[end, 2] - dm_liquidopt

nameslist = LiquidEngines[:name]
beststandardengine!(bestengine, bestmass, kmax, LiquidEngines, LiquidTanks)
kmax += size(LiquidEngines,1)

nameslist = [nameslist, LiquidBoosters[:name]]
for k=kmax + (1:size(LiquidBoosters,1))
    boosterdryk = LiquidBoosters[:drymass][k - kmax]
    boosterpropk = LiquidBoosters[:propmass][k - kmax]
    thrustk = LiquidBoosters[:thrust][k - kmax]
    veffk = g0_isp * (clamp(atmpressure, 0, 1) * LiquidBoosters[:ispatm][k - kmax] + 
        clamp(1 - atmpressure, 0, 1) * LiquidBoosters[:ispvac][k - kmax])
    for j=1:length(deltav_points)
        massratioj = exp(deltav_points[j] / veffk)
        c = thrustk / (massratioj * g0_twr * mintwr)
        if mintwr == 0. || (massratioj - 1.) * c >= boosterpropk
            # dv constraint is more restrictive than twr constraint,
            # so use full boosters and additional fuel tanks
            boosterdenom = massratioj * (g0_twr * mintwr * (boosterpropk * dm_liquidopt -
                boosterdryk * pm_liquidopt) - dm_liquidopt * thrustk) + (dm_liquidopt + pm_liquidopt) * thrustk
            tankdenom = pm_liquidopt + dm_liquidopt * (1. - massratioj)
            ((boosterdenom <= 0.) || (tankdenom <= 0.)) && continue
            boostersperton = massratioj * g0_twr * mintwr * pm_liquidopt / boosterdenom
            boosterfactor = boosterdryk * (massratioj - 1.) - boosterpropk
            for i=1:length(payload_points)
                payloadi = payload_points[i]
                # best-case number of boosters if both boosters and fuel tanks were continuous
                numboosters = (mintwr == 0.) ? 1. : ceil(payloadi * boostersperton)
                while numboosters <= max_num_engines
                    # best-case continuous number of optimal liquid tanks,
                    # with number of boosters rounded up to next integer
                    # round number of tanks down, then look at smaller types of tanks
                    numtanks_base = max(0., floor((numboosters * boosterfactor +
                        (massratioj - 1.) * payloadi) / tankdenom))
                    drymass_base = boosterdryk*numboosters + payloadi + numtanks_base*dm_liquidopt
                    wetmass_base = drymass_base + boosterpropk*numboosters + numtanks_base*pm_liquidopt
                    wetmass_actual = massratioj * drymass_base + 
                        smalltankmass(liquidarray, massratioj, massratioj * drymass_base - wetmass_base)
                    if wetmass_actual > bestmass[i,j]
                        # have already found a better engine at this point
                        break
                    elseif numboosters * thrustk < g0_twr * mintwr * wetmass_actual
                        # twr constraint is violated due to rounding of number of fuel tanks
                        # try again with another engine added
                        numboosters += 1.
                    else
                        # twr and dv constraints are satisfied, so we have found
                        # the mass-optimal number of engines and fuel tanks
                        bestmass[i,j] = wetmass_actual
                        bestengine[i,j] = k
                        break
                    end
                end
            end
        elseif c > boosterdryk
            # twr constraint is high enough that a full booster cannot satisfy it
            boostersperton = 1. / (c - boosterdryk)
            for i=1:length(payload_points)
                payloadi = payload_points[i]
                numboosters = max(1., ceil(payloadi * boostersperton))
                (numboosters > max_num_engines) && continue
                drymass_base = boosterdryk*numboosters + payloadi
                wetmass_actual = massratioj * drymass_base
                if wetmass_actual <= bestmass[i,j]
                    bestmass[i,j] = wetmass_actual
                    bestengine[i,j] = k
                end
            end
        end
        # otherwise, twr constraint is so high that even an empty booster cannot satisfy it
    end
end
kmax += size(LiquidBoosters,1)

nameslist = [nameslist, SolidBoosters[:name]]
for k=kmax + (1:size(SolidBoosters,1))
    boosterdryk = SolidBoosters[:drymass][k - kmax]
    boosterpropk = SolidBoosters[:propmass][k - kmax]
    thrustk = SolidBoosters[:thrust][k - kmax]
    veffk = g0_isp * (clamp(atmpressure, 0, 1) * SolidBoosters[:ispatm][k - kmax] + 
        clamp(1 - atmpressure, 0, 1) * SolidBoosters[:ispvac][k - kmax])
    for j=1:length(deltav_points)
        massratioj = exp(deltav_points[j] / veffk)
        boosterdenom = boosterpropk - (massratioj - 1.) * boosterdryk
        # skip this SRB if it cannot meet the dv constraint
        (boosterdenom <= 0) && continue
        c = thrustk / (massratioj * g0_twr * mintwr)
        if mintwr == 0. || (massratioj - 1.) * c >= boosterpropk
            # dv constraint is more restrictive than twr constraint,
            # so calculate best-case continuous number of full boosters
            boostersperton = (massratioj - 1.) / boosterdenom
        elseif c > boosterdryk
            # twr constraint is high enough that a full booster cannot satisfy it
            boostersperton = 1. / (c - boosterdryk)
        else # twr constraint is so high that even an empty booster cannot satisfy it
            continue
        end
        for i=1:length(payload_points)
            payloadi = payload_points[i]
            numboosters = max(1., ceil(payloadi * boostersperton))
            (numboosters > max_num_engines) && continue
            drymass_base = boosterdryk*numboosters + payloadi
            wetmass_actual = massratioj * drymass_base
            if wetmass_actual <= bestmass[i,j]
                bestmass[i,j] = wetmass_actual
                bestengine[i,j] = k
            end
        end
    end
end
kmax += size(SolidBoosters,1)

nameslist = [nameslist, XenonEngines[:name]]
beststandardengine!(bestengine, bestmass, kmax, XenonEngines, XenonTanks)
kmax += size(XenonEngines,1)

colormap([Color.RGB(1,1,1); Color.distinguishable_colors(kmax, Color.RGB(0.25,0.25,0.25))])
chart = imagesc(extrema(deltav_points), reverse(extrema(payload_points)),
    bestengine, (0, kmax))
setattr(chart, ylog=true)
setattr(chart, title="Mass optimal engine type with min Kerbin relative TWR of $mintwr")
setattr(chart, title_style=[:fontsize=>2.0])
setattr(chart.y1, label="Payload mass (t)")
if atmpressure <= 0
    setattr(chart.x1, label="Vacuum Delta V (m/s)")
elseif atmpressure >= 1
    setattr(chart.x1, label="Atmospheric Delta V (m/s)")
else
    setattr(chart.x1, label="Delta V (m/s) at Pressure = $atmpressure atm")
end
setattr(chart.x1, draw_grid=true)
setattr(chart.x1, label_style=[:fontsize=>2.0])
setattr(chart.x1, ticklabels_style=[:fontsize=>2.0])
setattr(chart.y1, draw_grid=true)
setattr(chart.y1, label_style=[:fontsize=>2.0])
setattr(chart.y1, ticklabels_style=[:fontsize=>2.0])

imagelegend = Table(kmax,1)
for i=1:kmax
    imagelegend[i,1] = plotimage(padimage(convert(Winston.Image, imread("img/" * nameslist[kmax+1-i] * ".png")), 60, 60))
    setattr(imagelegend[i,1], draw_ticks=false)
    setattr(imagelegend[i,1].x, draw_axis=false)
    setattr(imagelegend[i,1].y, draw_axis=false)
    setattr(imagelegend[i,1].x, draw_ticklabels=false)
    setattr(imagelegend[i,1].y, draw_ticklabels=false)
end
setattr(imagelegend, cellspacing=0.0)

colorlegend = imagesc((1, 2), (kmax+0.5, 0.5), [1:kmax 1:kmax], (0, kmax))
setattr(colorlegend, draw_ticks=false)
setattr(colorlegend.x1, draw_ticklabels=false)
setattr(colorlegend.y1, draw_ticklabels=false)
setattr(colorlegend.y2, draw_ticklabels=true)
setattr(colorlegend.y2, ticks=1.0:kmax)
setattr(colorlegend.y2, ticklabels=array(nameslist))

legend = Table(1,2)
setattr(legend, cellspacing=0.0)
setattr(legend, align_interiors=true)
setattr(legend, aspect_ratio=kmax/2)
legend[1,1] = imagelegend
legend[1,2] = colorlegend

t = Table(1,2)
setattr(t, cellspacing=-55.0)
t[1,1] = chart
t[1,2] = Table(1,4)
t[1,2][1,4] = legend

figure(width=800, height=500)
display(t)
if ! isempty(filename)
    savefig(t, filename, width=1300, height=750)
end

(bestengine, bestmass)
end

# Image manipulation helper functions

# Convert ARGB Images.Image to Winston.Image
function convert(::Type{Winston.Image}, img::Images.Image)
    if colorspace(img) == "ARGB"
        img_array = convert(Array, img)
        a = img_array[:,:,1] / 0xff
        r,g,b = [uint32((1-a)*0xff + a.*img_array[:,:,i]) for i=2:4]
        img_out = map(v->(v<<16), r) + map(v->(v<<8), g) + b
        width = size(img_out,2)
        height = size(img_out,1)
        Winston.Image((0,width), (height,0), flipud(img_out))
    end
end

# Resize an image by padding it with whitespace
function padimage(img::Winston.Image, width, height)
    if width >= img.w && height >= img.h
        x = int((width-img.w)/2)
        y = int((height-img.h)/2)
        img_out = fill(uint32(0x00ffffff), height, width)
        img_out[1+y:img.h+y, 1+x:img.w+x] = img.img
        Winston.Image((0,width), (height,0), img_out)
    end
end

# Add an image to a plot
function plotimage(img::Winston.Image)
    p = Winston.ghf()
    Winston.add(p, img)
    Winston.ghf(p)
end
