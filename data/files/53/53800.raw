if Pkg.installed("DataFrames") == nothing
    Pkg.add("DataFrames")
end
using DataFrames
if Pkg.installed("Winston") == nothing
    Pkg.add("Winston")
end
using Winston

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
    #"Mark 55,   0.90,   120.,   290.,   320. \n" *
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

# Hard-code combinations of small fuel tanks, sorted by dry mass
# These numbers depend on fuel tank stats
tankarray = [0 0 0;
             1 0 0;
             0 1 0;
             2 0 0;
             1 1 0;
             3 0 0;
             0 2 0;
             2 1 0;
             4 0 0;
             0 0 1] *
            array(LiquidTanks[1:3, 2:3]) * [1 1; 0 1]
dm_flt100 = LiquidTanks[:drymass][3]
pm_flt100 = LiquidTanks[:propmass][3]
# This function will be used later to determine the lowest-mass combination
# of small fuel tanks that can provide a required amount of fuel
function smalltankmass(tankarray, massratioj, rhs)
    for i=1:size(tankarray,1)
        c = massratioj * tankarray[i, 1]
        if tankarray[i, 2] - c >= rhs
            return c
        end
    end
    error("should never get here")
end

bestmass = fill(Inf, length(payload_points), length(deltav_points))
bestengine = zeros(Int, length(payload_points), length(deltav_points))
kmax = size(LiquidEngines,1)
nameslist = LiquidEngines[:name]
for k=1:kmax
    enginemassk = LiquidEngines[:mass][k]
    thrustk = LiquidEngines[:thrust][k]
    # skip this engine if it cannot meet the twr requirement
    (thrustk < enginemassk * g0_twr * mintwr) && continue
    veffk = g0_isp * (clamp(atmpressure, 0, 1) * LiquidEngines[:ispatm][k] + 
        clamp(1 - atmpressure, 0, 1) * LiquidEngines[:ispvac][k])
    for j=1:length(deltav_points)
        massratioj = exp(deltav_points[j] / veffk)
        enginedenom = (pm_flt100 + dm_flt100) * thrustk - massratioj * (
                    enginemassk*g0_twr*mintwr*pm_flt100 + dm_flt100*thrustk)
        (enginedenom <= 0.) && continue
        enginesperton = g0_twr * mintwr * pm_flt100 * massratioj / enginedenom
        tankfactor = (massratioj - 1.) / (pm_flt100 + dm_flt100 * (1. - massratioj))
        for i=1:length(payload_points)
            payloadi = payload_points[i]
            # best-case number of engines if both engines and fuel tanks were continuous
            numengines = (mintwr == 0.) ? 1. : ceil(payloadi * enginesperton)
            while numengines <= max_num_engines
                # best-case continuous number of FL-T100 tanks,
                # with number of engines rounded up to next integer
                # round number of tanks down, then look at smaller types of tanks
                numtanks_base = floor((enginemassk * numengines + payloadi) * tankfactor)
                drymass_base = enginemassk*numengines + payloadi + numtanks_base*dm_flt100
                wetmass_base = drymass_base + numtanks_base*pm_flt100
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
            boosterdenom = massratioj * (g0_twr * mintwr * (boosterpropk * dm_flt100 -
                boosterdryk * pm_flt100) - dm_flt100 * thrustk) + (dm_flt100 + pm_flt100) * thrustk
            tankdenom = pm_flt100 + dm_flt100 * (1. - massratioj)
            ((boosterdenom <= 0.) || (tankdenom <= 0.)) && continue
            boostersperton = massratioj * g0_twr * mintwr * pm_flt100 / boosterdenom
            boosterfactor = boosterdryk * (massratioj - 1.) - boosterpropk
            for i=1:length(payload_points)
                payloadi = payload_points[i]
                # best-case number of boosters if both boosters and fuel tanks were continuous
                numboosters = (mintwr == 0.) ? 1. : ceil(payloadi * boostersperton)
                while numboosters <= max_num_engines
                    # best-case continuous number of FL-T100 tanks,
                    # with number of boosters rounded up to next integer
                    # round number of tanks down, then look at smaller types of tanks
                    numtanks_base = max(0., floor((numboosters * boosterfactor +
                        (massratioj - 1.) * payloadi) / tankdenom))
                    drymass_base = boosterdryk*numboosters + payloadi + numtanks_base*dm_flt100
                    wetmass_base = drymass_base + boosterpropk*numboosters + numtanks_base*pm_flt100
                    wetmass_actual = massratioj * drymass_base + 
                        smalltankmass(tankarray, massratioj, massratioj * drymass_base - wetmass_base)
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

# Hard-code combinations of xenon tanks, sorted by dry mass
# These numbers depend on xenon tank stats
xenonarray = [0 0;
              1 0;
              0 1;
              2 0;
              1 1;
              3 0;
              0 2;
              2 1;
              4 0;
              1 2;
              3 1;
              0 3] *
             array(XenonTanks[1:2, 2:3]) * [1 1; 0 1]
# Made-up xenon tank equivalent to 3 PB-X150's, since that is the LCM of the dry masses
dm_pbx450 = 3*XenonTanks[:drymass][2]
pm_pbx450 = 3*XenonTanks[:propmass][2]
# This function will be used later to determine the lowest-mass combination
# of xenon tanks that can provide a required amount of propellant
function smallxenonmass(xenonarray, massratioj, rhs)
    for i=1:size(xenonarray,1)
        c = massratioj * xenonarray[i, 1]
        if xenonarray[i, 2] - c >= rhs
            return c
        end
    end
    error("should never get here")
end

nameslist = [nameslist, XenonEngines[:name]]
for k=kmax + (1:size(XenonEngines,1))
    enginemassk = XenonEngines[:mass][k - kmax]
    thrustk = XenonEngines[:thrust][k - kmax]
    # skip this engine if it cannot meet the twr requirement
    (thrustk < enginemassk * g0_twr * mintwr) && continue
    veffk = g0_isp * (clamp(atmpressure, 0, 1) * XenonEngines[:ispatm][k - kmax] + 
        clamp(1 - atmpressure, 0, 1) * XenonEngines[:ispvac][k - kmax])
    for j=1:length(deltav_points)
        massratioj = exp(deltav_points[j] / veffk)
        enginedenom = (pm_pbx450 + dm_pbx450) * thrustk - massratioj * (
                    enginemassk*g0_twr*mintwr*pm_pbx450 + dm_pbx450*thrustk)
        (enginedenom <= 0.) && continue
        enginesperton = g0_twr * mintwr * pm_pbx450 * massratioj / enginedenom
        tankfactor = (massratioj - 1.) / (pm_pbx450 + dm_pbx450 * (1. - massratioj))
        for i=1:length(payload_points)
            payloadi = payload_points[i]
            # best-case number of engines if both engines and fuel tanks were continuous
            numengines = (mintwr == 0.) ? 1. : ceil(payloadi * enginesperton)
            while numengines <= max_num_engines
                # best-case continuous number of "PB-X450" tanks,
                # with number of engines rounded up to next integer
                # round number of tanks down, then look at smaller types of tanks
                numtanks_base = floor((enginemassk * numengines + payloadi) * tankfactor)
                drymass_base = enginemassk*numengines + payloadi + numtanks_base*dm_pbx450
                wetmass_base = drymass_base + numtanks_base*pm_pbx450
                wetmass_actual = massratioj * drymass_base + 
                    smallxenonmass(xenonarray, massratioj, massratioj * drymass_base - wetmass_base)
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
kmax += size(XenonEngines,1)

if isdefined(Winston, :figure)
    # Need Winston from master via Pkg.checkout("Winston"),
    # otherwise default plot size is a bad aspect ratio
    figure(width=800, height=500)
end

colormap([Color.RGB(1,1,1); Color.distinguishable_colors(kmax, Color.RGB(0.25,0.25,0.25))])
t = Table(1, 2)
setattr(t, cellspacing=-65.0)
t[1,1] = imagesc(extrema(deltav_points), reverse(extrema(payload_points)),
    bestengine, (0, kmax))
setattr(t[1,1], ylog=true)
setattr(t[1,1], title="Mass optimal engine type with min Kerbin relative TWR of $mintwr")
setattr(t[1,1], title_style=[:fontsize=>2.0])
ylabel("Payload mass (t)")
if atmpressure <= 0
    xlabel("Vacuum Delta V (m/s)")
elseif atmpressure >= 1
    xlabel("Atmospheric Delta V (m/s)")
else
    xlabel("Delta V (m/s) at Pressure = $atmpressure atm")
end
setattr(t[1,1].x1, draw_grid=true)
setattr(t[1,1].x1, label_style=[:fontsize=>2.0])
setattr(t[1,1].x1, ticklabels_style=[:fontsize=>2.0])
setattr(t[1,1].y1, draw_grid=true)
setattr(t[1,1].y1, label_style=[:fontsize=>2.0])
setattr(t[1,1].y1, ticklabels_style=[:fontsize=>2.0])
t2 = Table(1,5)
t[1,2] = t2
cdata = round(linspace(0.5, kmax+0.5, (kmax+1)*20 + 1))
t2[1,5] = imagesc((1, 2), (kmax+0.5, 0.5), [cdata cdata], (0, kmax))
setattr(t2[1,5], aspect_ratio=15.0)
setattr(t2[1,5], draw_ticks=false)
setattr(t2[1,5].x1, draw_ticklabels=false)
setattr(t2[1,5].y1, draw_ticklabels=false)
setattr(t2[1,5].y2, draw_ticklabels=true)
setattr(t2[1,5].y2, ticks=1.0:kmax)
setattr(t2[1,5].y2, ticklabels=array(nameslist))
display(t)
if ! isempty(filename)
    savefig(t, filename, width=1300, height=750)
end

(bestengine, bestmass)
end
