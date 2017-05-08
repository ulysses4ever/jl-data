## purely functional code
## R code must declare types

## (1) integers
## (2) strings
## (3) integers and strings
## (4) support Real types, conversions
## (5) arrays, tuples


include("types.jl")

require("Iterators")

function cleanup(output)
    replace(output, "\n", "")
end

function eval_R_code(R_code::ASCIIString, convert_fun=identity)
    cmd = `Rscript cmd.R "$R_code"` |> DevNull
    run(cmd)
    f = open("out")
    output = convert_fun(cleanup(readline(f)))
    close(f)
    output
end

## R_out = eval_R_code("a<-1; a+1", int)


function bind_vars(dict, expr::String)
    for key = collect(keys(dict))
        val = dict[key]
        exp = parse(expr)
        expr = replace(expr, key, "($val)")
    end
    expr
end

dict = ["a" => 1]
bind_vars(dict, "a+1")


## compare R computation with Julia computation on every input
function test(R_code::String, Julia_code::String, input::Dict)
    num_pass = 0;
    dict = input
    Julia_code_bound = bind_vars(dict, Julia_code)
    R_code_bound = bind_vars(dict, R_code)
    julia_out = eval(parse(Julia_code_bound))
    println("julia_out = $julia_out")
    R_out = eval_R_code(R_code_bound)
    R_out = eval(parse(R_out))
    println("R_out = $R_out")
    pass = isequal(R_out, julia_out) || R_out==julia_out
    if pass
    ##if ("$R_out"=="$julia_out") ## string equality, viz NaN
        println("Passed")
    else
        println("Failed")
    end
    pass
end


## function test(R_code::String, Julia_code::String, inputs::Array{Dict})
##     num_pass = 0;
##     R_outs = Array[];
##     julia_outs = Array[];
##     for (i,dict) = enumerate(inputs)
##         println("i = $i")
##         print(dict)
##         Julia_code_bound = bind_vars(dict, Julia_code)
##         R_code_bound = bind_vars(dict, R_code)
##         julia_out = eval(parse(Julia_code_bound))
##         ##push!(julia_outs, julia_out)
##         println("julia_out = $julia_out")
##         R_out = eval_R_code(R_code_bound)
##         R_out = eval(parse(R_out))
##         ##push!(R_outs, R_out)
##         println("R_out = $R_out")
##         if (R_out==julia_out)
##             num_pass = num_pass + 1
##         end
##     end
##     println("Passed: $num_pass;  Failed: ")
##     (julia_outs, R_outs)
## end

remove_spaces(s) = replace(replace(s, " ",""), "\n", "")
is_code(s) = length(s)>2 && s[2:3]==": "
is_precondition(s) = length(s)>4 && s[1:4]=="PRE:"

## load
function read_Rjl(filename::String)
    f=open("$filename.Rjl")
    entries=T.Entry[]
    inputs=T.Input[]
    line = nothing; section=nothing;
    R=""; J=""; precond="";
    ##Entries
    while true
        line=readline(f)
        if section=="end"
            break
        end
        println(line)
        nline=remove_spaces(line)
        if(length(nline)>2 && nline[1:2]=="==")
            section=lowercase(replace(nline,"==",""))
            continue
        end
        if(section=="code")
            if (nline=="")
                push!(entries, T.Entry(R,J,"","",precond))
                R = ""; J = "";
            elseif (is_code(line))
                lang = line[1:1]
                code = nline[3:end]
                if (lang=="R")
                    R = code
                end
                if (lang=="J")
                    J = code
                end
            elseif (is_precondition(line))
                precond = replace(nline, "PRE:", "")
            end
        end
        if(section=="inputs" && nline!="")
            ss = split(line, " ")
            println("ss = $ss")
            var = ss[1]
            valString = ss[2]
            println("valString = $valString")
            vals = split(valString, ",")
            push!(inputs, T.Input(var,vals))
        end
        println("entries = $entries")
        println("inputs = $inputs")
    end
    ## Inputs
    (entries, inputs)
end


function bind_and_eval(precond, dict)
    s = ""
    for key = collect(keys(dict))
        val=dict[key]
        s = s*"$key=$val;"
    end
    bound_precond = s*precond
    eval(parse(bound_precond))
end

## bind_and_eval("a+b", dict)



function run_test(entry::T.Entry, vars, vals)
    R_code = entry.R
    Julia_code = entry.J
    dict = Dict() ## variable bindings into Dict format
    for (i, var) = enumerate(vars)
        dict[var] = vals[i]
    end
    pre_pass = bind_and_eval(entry.precond, dict)
    if !pre_pass
        println("pre-condition not met.")
        return(nothing)
    else
        test(R_code, Julia_code, dict)
    end
end


function run_tests(entries, inputs, outfile)
    ## create comprehension
    vars = map(input->input.var, inputs)
    valss = map(input->input.vals, inputs)
    f = open("$outfile.out", "w")
    for entry = entries
        for vals in apply(Iterators.product, valss)
            println(entry)
            println(vals) ##bind_vars()
            outcome = run_test(entry, vars, vals)
            ## write output file
            out_line = "$(entry.R) ;; $(entry.J) ;; $vals ;; $outcome"
            println(f, out_line)
        end
    end
    close(f)
end


##outfile = "arith"
(entries,inputs) = read_Rjl("arith")
run_tests(entries, inputs, "arith")


(entries,inputs) = read_Rjl("vectors")
run_tests(entries, inputs, "vectors")





df = DataFrame()
    df[:Julia] = julia_outs
    df[:R] = R_outs


code0_R = "a<-1; a+1";
code0_Julia = "a=1; a+1"

code1_R = "a+1";
code1_Julia = "a+1"


test(code1_R, code1_Julia, ["a" => 2])
test(code1_R, code1_Julia, ["a" => -5])


inputs = Dict[]
push!(inputs, ["a" => -5])
push!(inputs, ["a" => -1])
push!(inputs, ["a" => 0])
push!(inputs, ["a" => 1])
push!(inputs, ["a" => 1e10])

test(code1_R, code1_Julia, inputs)



