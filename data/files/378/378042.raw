#/usr/bin/env julia

using Debug
using Winston
using ArgParse

include("functions.jl")

type sortData
    curveColor::Union(String, Integer)
    curveLabel::String
    curveY::Array
end

function parsecmd()
    settings = ArgParseSettings()
    settings.prog = "Julia Sorting Test"
    settings.description = "This is just for experimenting around with Julia features"
    
    @add_arg_table settings begin
        "--range", "-r"
        help = "The range of array size as a Range."
        nargs = 3
        arg_type = Int
        ## defaultArray = Array(Integer, 1)
        ## defaultArray = [100, 100, 1000]
        default = [100, 100, 1000]

        "--sorts", "-s"
        help = "The sorting algorithms to test. Options are 'merge', 'insert'."
        nargs = '*'
        default = {"merge"}

        "-o"
        help = "Name of the file path to export to."
        arg_type = String
        default = "o.svg"

    end
    return parse_args(settings)
end

function randomColor()
    return rand(Uint32) & 0x00ffffff
end

function test(range, f)
    times = Array(Float64, length(range))
    current = 1
    for i in range
        bla = rand(Int, i)
        tic()
        f(bla)
        times[current] = toc()
        current += 1
    end

    return times
end

function plotStuff(x, ydata...)
    result = FramedPlot(title="Sorting comparison", xlabel="Number of Elements", ylabel="Time (s)")
    curves = Array(Curve, length(ydata))
    for i in 1:length(curves)
        curves[i] = Curve(x, ydata[i].curveY, color=ydata[i].curveColor, label=ydata[i].curveLabel)
        setattr(curves[i], "label", ydata[i].curveLabel)
    end
    
    legend = Legend(.1,.9, {curves...})
    
    add(result, legend, curves...)

    return result
end

function main()
    settings = parsecmd()
    println(settings)

    rangeTuple = settings["range"]
    sortsToTry = settings["sorts"]
    
    range = rangeTuple[1]:rangeTuple[2]:rangeTuple[3]
    
    sortDict = ["merge"=>mergesort, "insert"=>insertionsort, "bubble"=>bubblesort, "quick"=>quicksort]

    x = [range]

    println(length(sortsToTry))
    
    curvesToPlot = Array(sortData, length(sortsToTry))

    for ii in 1:length(curvesToPlot)
        curvesToPlot[ii] = sortData(randomColor(), sortsToTry[ii] * "sort", test(range, get(sortDict, sortsToTry[ii], "merge")))
    end
    
    myPlot = plotStuff(x, curvesToPlot...)
    display(myPlot)
    savefig(myPlot, settings["o"])
    
end

main()
