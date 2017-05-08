#! /usr/bin/julia

# Rosetta Code, Monty Hall problem

function play_mh_literal{T<:Integer}(ncur::T=3, ncar::T=1)
    ncar < ncur || throw(DomainError())
    curtains = shuffle(collect(1:ncur))
    cars = curtains[1:ncar]
    goats = curtains[(ncar+1):end]
    pick = rand(1:ncur)
    isstickwin = pick in cars
    deleteat!(curtains, findin(curtains, pick))
    if !isstickwin
        deleteat!(goats, findin(goats, pick))
    end
    if length(goats) > 0 # reveal goat
        deleteat!(curtains, findin(curtains, shuffle(goats)[1]))
    else # no goats, so reveal car 
        deleteat!(curtains, rand(1:(ncur-1)))
    end
    pick = shuffle(curtains)[1]
    isswitchwin = pick in cars
    return (isstickwin, isswitchwin)
end

function play_mh_clean{T<:Integer}(ncur::T=3, ncar::T=1)
    ncar < ncur || throw(DomainError())
    pick = rand(1:ncur)
    isstickwin = pick <= ncar
    pick = rand(1:(ncur-2))
    if isstickwin # remove initially picked car from consideration
        pick += 1
    end
    isswitchwin = pick <= ncar
    return (isstickwin, isswitchwin)
end

function mh_results{T<:Integer}(ncur::T, ncar::T,
                                nruns::T, play_mh::Function)
    stickwins = 0
    switchwins = 0
    for i in 1:nruns
        (isstickwin, isswitchwin) = play_mh(ncur, ncar)
        if isstickwin
            stickwins += 1
        end
        if isswitchwin
            switchwins += 1
        end
    end
    return (stickwins/nruns, switchwins/nruns)
end

function mh_analytic{T<:Integer}(ncur::T, ncar::T)
    stickodds = ncar/ncur
    switchodds = (ncar - stickodds)/(ncur-2)
    return (stickodds, switchodds)
end

function show_odds{T<:Real}(a::T, b::T)
    @sprintf "   %.1f   %.1f     %.2f" 100.0*a 100*b 1.0*b/a
end

function show_simulation{T<:Integer}(ncur::T, ncar::T, nruns::T)
    println()
    print("Simulating a ", ncur, " door, ", ncar, " car ")
    println("Monty Hall problem with ", nruns, " runs.\n")

    println("   Solution   Stick  Switch  Improvement")

    (a, b) = mh_results(ncur, ncar, nruns, play_mh_literal)
    println(@sprintf("%10s: ", "Literal"), show_odds(a, b))

    (a, b) = mh_results(ncur, ncar, nruns, play_mh_clean)
    println(@sprintf("%10s: ", "Clean"), show_odds(a, b))

    (a, b) = mh_analytic(ncur, ncar)
    println(@sprintf("%10s: ", "Analytic"), show_odds(a, b))
    println()
    return nothing
end


for i in 3:5, j in 1:(i-2)
    show_simulation(i, j, 10^5)
end


        
