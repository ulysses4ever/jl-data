using Codecs

include("warm_up_excercise.jl")

function submit(partId)
    partId = 1

    (login,password) = ("thomas.mccolgan@gmail.com","J92J54ztjs")
    

    thisPartId = partId # submitParts(s)
    (result,restype) = submitSolutionWeb(login, thisPartId, output(thisPartId, ""), source(thisPartId))
    result = take76(base64encode(result))

    saveAsFile = "text.txt"

    fid = open(saveAsFile, "w")
    write(fid, result)
    close(fid)
end

function homework_id()
    id = "1"
end

function take76(str)
    # Breaks an encoding string into a mime proper format
    segments = convert(Int64, ceil(length(str)/76))
    println
    tmp = ASCIIString[]
    index = 0
    index_end = index + 76
    for i in [1:segments]
        if index_end > length(str)
            push!(tmp, str[index+1:])
        else
            if index == 1
                push!(tmp, str[index:index_end])
            else
                push!(tmp, str[index+1:index_end])
            end
            index = index_end
            index_end = index + 76
        end
    end
    join(tmp, '\n') * "\n"
end

function sources()
    # Separated by part
    [
     "warm_up_excercise.jl",
     "computeCost.jl",
     "gradientDescent.jl",
     "featureNormalize.jl",
     "computeCostMulti.jl",
     "gradientDescentMulti.jl",
     "normalEqn.jl"
     ]
end

function source(id)
    srcs = sources()
    fid = open(srcs[id])
    ret = string(readall(fid),"||||||||")
    return ret
end

function base64encode(str)
    return bytestring(encode(Base64,convert(ASCIIString,str)))
end


#function validParts()
#    partNames = { "Warm up exercise ", ...
#    "Computing Cost (for one variable)", ...
#    "Gradient Descent (for one variable)", ...
#    "Feature Normalization", ...
#    "Computing Cost (for multiple variables)", ...
#    "Gradient Descent (for multiple variables)", ...
#    "Normal Equations"}
#end
#
#function sources()
#    # Separated by part
#    srcs = { { "warmUpExercise.jl" }, ...
#    { "computeCost.jl" }, ...
#    { "gradientDescent.jl" }, ...
#    { "featureNormalize.jl" }, ...
#    { "computeCostMulti.jl" }, ...
#    { "gradientDescentMulti.jl" }, ...
#    { "normalEqn.jl" }, ...
#    }
#end

function output(partId, auxstring)
    # Random Test Cases
    #X1 = [ones(20,1) (exp(1) + exp(2) * (0.1:0.1:2))']
    #Y1 = X1(:,2) + sin(X1(:,1)) + cos(X1(:,2))
    #X2 = [X1 X1(:,2).^0.5 X1(:,2).^0.25]
    #Y2 = Y1.^0.5 + Y1
    if partId == 1
        tmp = reshape(warmUpExercise(), length(warmUpExercise()), 1)'
        join(map(x -> @sprintf("%0.5f ", x), tmp));
    #elseif partId == 2
    #    out = sprintf("%0.5f ", computeCost(X1, Y1, [0.5 -0.5]'))
    #elseif partId == 3
    #    out = sprintf("%0.5f ", gradientDescent(X1, Y1, [0.5 -0.5]', 0.01, 10))
    #elseif partId == 4
    #    out = sprintf("%0.5f ", featureNormalize(X2(:,2:4)))
    #elseif partId == 5
    #    out = sprintf("%0.5f ", computeCostMulti(X2, Y2, [0.1 0.2 0.3 0.4]'))
    #elseif partId == 6
    #    out = sprintf("%0.5f ", gradientDescentMulti(X2, Y2, [-0.1 -0.2 -0.3 -0.4]', 0.01, 10))
    #elseif partId == 7
    #    out = sprintf("%0.5f ", normalEqn(X2, Y2))
    end 
end

# ========================= CHALLENGE HELPERS =========================

function submitSolutionWeb(email, part, output, source)
    println(output)
    println("$(homework_id())-$(part)")
    result = string("{\"assignment_part_sid\":\"",base64encode("$(homework_id())-$(part)"),"\",\"email_address\":\"",base64encode(email),"\",\"submission\":\"",base64encode(output),"\",\"submission_aux\":\"",base64encode(source),"\"}")
    println(result)
    str = "Web-submission"
    return (result, str)
end
