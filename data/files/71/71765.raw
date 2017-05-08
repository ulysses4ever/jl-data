## purely functional code
## R code must declare types

## (1) integers
## (2) strings
## (3) integers and strings
## (4) support Real types, conversions
## (5) arrays, tuples


## ToDo: each entry is a Dict from language id to code.


include("types.jl")
require("Iterators")
using PyCall
##using Rif
##initr()


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


## finite state machine, character by character
## words =
## reduce(append, words)

function is_alphanumeric(ch::Char)
    n = int(ch)
    (48 <= n <= 57) | (65 <= n <= 90) | (97 <= n <= 122) | (n==95) ## _ is 95
end

## STATES: 1 => alphanumeric, 2 => not
function parse_expression(expr::String)
    prev_state = 0
    state = 0
    curr = "" ## current string
    ss = [String[]]
    for i in 1:length(expr)
        ch = expr[i]
        prev_state = state
        state = is_alphanumeric(ch) ? 1 : 2
        if (state==prev_state)
            curr *= string(ch)
        else
            if curr!="" push!(ss, curr) end
            curr = string(ch)
        end
    end
    if curr!="" push!(ss, curr) end  ## push last one
    ss
end

## replace all instances
function replaceall!(arr::Array, s, r)
    for i in 1:length(arr)
        if arr[i]==s
            arr[i] = r
        end
    end
    arr
end


function bind_identifiers(expr, d::Dict)
    pexp = parse_expression(expr)
    for key in keys(d)
        replaceall!(pexp, key, "("*d[key]*")")
    end
    reduce(*, pexp)
end

expr = "a-b"
d = {"a"=>"1", "b" => "-1"}
bind_identifiers(expr, d)


## R_out = eval_R_code("a<-1; a+1", int)

## only replace full alphanumeric words
function bind_vars(dict, expr::String, translate_fn=identity)
    pexp = parse_expression(expr)
    for key in keys(dict)
        replaceall!(pexp, key, "("*translate_fn(dict[key])*")")
    end
    reduce(*, pexp)
end


dict = ["a" => "-1", "b" => "Inf"]
bind_vars(dict, "a+b")

python_literals = {"Inf" => "float('inf')"}
python_literals["Inf"]
function translate_literal_to_python(literal)
    (literal in keys(python_literals)) ? python_literals[literal] : literal
end

bind_vars(dict, "a+b", translate_literal_to_python)


remove_spaces(s) = replace(replace(s, " ",""), "\n", "")
is_code(s) = length(s)>2 && s[2:3]==": " && s[1]!="#"
is_precondition(s) = length(s)>4 && s[1:4]=="PRE:"


function read_JMPR(filename::String)
    f=open("$filename.JMPR")
    entries=T.Entry[]
    inputs=T.Input[]
    line = nothing; section=nothing;
    J=""; M=""; P=""; R=""; precond="";
    ##Entries
    for line in map(cleanup, readlines(f))
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
            if (nline=="" && J*M*P*R!="")
                push!(entries, T.Entry(J,M,P,R,precond))
                J = ""; M = ""; P = ""; R = "";
            elseif (is_code(line))
                lang = line[1:1]
                code = nline[3:end]
                if (lang=="J")
                    J = code
                end
                if (lang=="M")
                    M = code
                end
                if (lang=="P")
                    P = code
                end
                if (lang=="R")
                    R = code
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
    println("bound_precond = $bound_precond")
    eval(parse(bound_precond))
end


## run code in every language
function test(J::String, M::String, P::String, R::String, input::Dict)
    num_pass = 0;
    outs = Dict()
    outputs = Dict() ##outputs = String[]
    if J!=""
        Julia_code_bound = bind_vars(input, J)
        println("Julia_code_bound = $Julia_code_bound")
        julia_out = eval(parse(Julia_code_bound))
        println("julia_out = $julia_out")
        ##push!(outputs, "$julia_out")
        outs["J"] = julia_out
        outputs["J"] = "$julia_out"
    end
    if P!=""
        python_code_bound = bind_vars(input, P, translate_literal_to_python)
        println("python_code_bound = $python_code_bound")
        python_out = try
            pyeval(python_code_bound)
        catch
            "PythonError"
        end
        println("python_out = $python_out")
        ##push!(outputs, "$python_out")
        outs["P"] = python_out
        outputs["P"] = "$python_out"
    end
    if R!=""
        R_code_bound = bind_vars(input, R)
        R_out = eval_R_code(R_code_bound)
        R_out = eval(parse(R_out))
        println("R_out = $R_out")
        ##push!(outputs, "$R_out")
        outs["R"] = R_out
        outputs["R"] = "$R_out"
    end
    pass = length(unique(values(outputs)))==1 || length(unique(values(outs)))==1 ## i.e. all outputs are equal
    ##        (isequal(julia_out, R_out) || R_out==julia_out) && (isequal(julia_out, python_out) || R_out==python_out)     ##if ("$R_out"=="$julia_out") ## string equality, viz NaN
    if pass
        println("Passed")
    else
        println("Failed")
    end
    (outputs, pass)
end

## implement 'unique' for different notions of equality


function run_test(entry::T.Entry, vars, vals, langs::Set)
    dict = Dict() ## variable bindings into Dict format
    for (i, var) = enumerate(vars)
        dict[var] = vals[i]
    end
    println("dict = $dict")
    println("entry.precond = $(entry.precond)")
    pre_pass = entry.precond=="" ? true : bind_and_eval(entry.precond, dict)
    println("pre_pass = $pre_pass")
    if !pre_pass
        println("pre-condition not met.")
        return(nothing)
    else
        entry.J = ("J" in langs) ? entry.J : ""
        entry.M = ("M" in langs) ? entry.M : ""
        entry.P = ("P" in langs) ? entry.P : ""
        entry.R = ("R" in langs) ? entry.R : ""
        test(entry.J, entry.M, entry.P, entry.R, dict)
    end
end


function run_tests(entries, inputs, outfile, langs::Set)
    ## create comprehension
    vars = map(input->input.var, inputs)
    valss = map(input->input.vals, inputs)
    f = open("$outfile.out", "w")
    langs_str = reduce((s1,s2)->s1*" ;; "*s2,  langs)
    lang_outputs = reduce((s1,s2)->s1*" ;; "*s2, map(s->s*"_output", langs))
    header = langs_str*" ;; input ;; "*lang_outputs*" ;; passed?"
    println(f, header)
    for entry in entries
        for vals in apply(Iterators.product, valss)
            println(entry)
            println(vals) ##bind_vars()
            (outputs,outcome) = run_test(entry, vars, vals, langs)
            ## write output file
            out_line = ""
            for lang in langs
                out_line *= getfield(entry, symbol(lang))*" ;; "
            end
            out_line *= " $vals ;;"
            for output in values(outputs)
                out_line *= " $output ;; "
            end
            out_line *= "$outcome"
            println(f, out_line)
        end
    end
    close(f)
end


(entries,inputs) = read_JMPR("arith")
langs = Set({"R", "J", "P"})
run_tests(entries, inputs, "arith", langs)





code0_R = "a<-1; a+1";
code0_Julia = "a=1; a+1"

code1_R = "a+1";
code1_Julia = "a+1"

