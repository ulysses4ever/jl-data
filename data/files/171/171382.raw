abstract QuadratureRule

immutable StroudRule{sd, deg} <: QuadratureRule end


nqp1d{sd, deg}(::Type{StroudRule{sd, deg}}) = deg
nqp{sd, deg}(::Type{StroudRule{sd, deg}}) = deg^sd

# let's take another look at the stroud evaluation.
# can we make it cleaner and closer to Ainsworth's paper?

function degminalphas(ell, deg)
    result = :($deg)
    for i=1:ell
        ai = symbol("alpha",i)
        result = :($(result) - $(ai))
    end
    return result
end

function alphaloop(alphamin, alphamax, deg, body)
    result = body
    for i=alphamax:-1:alphamin
        ai = symbol("alpha", i)
        result = Expr(:for,
                      :($(ai)=0:$(degminalphas(i-1, deg))),
                      result)
    end
    return result
end

function iloop(imin, imax, q, body)
    result = body
    for i=imax:-1:imin
        ii = symbol("i",i)
        result = Expr(:for,
                      :(($ii)=1:$(q)),
                      result)
    end
    return result
end

function index_expr(head, idx)
    ref = Expr(:ref, head)
    for i in idx
        push!(ref.args, i)
    end
    return ref
end

# I just need to write a function that will generate the body for eval_step
# and can use it for each dimension

# warning, I have reversed the order of indices over Ainsworth's
# paper to allow maximal stride-1 access!

# warning, I also seem to have the look-up into the stroud qp in the reverse
# order

function eval_step_impl(sdim, ell, deg, q)
    alpha_symbs = [symbol("alpha",i) for i=1:sdim]
    i_symbs = [symbol("i",i) for i=1:sdim]

    aip1 = [:($(a)+1) for a in alpha_symbs]

    # build innermost loop nest
    Cin_args = vcat(reverse(i_symbs[ell+1:sdim]),
                    reverse(aip1[1:ell]))
    Cout_args = vcat(reverse(i_symbs[ell:sdim]),
                     reverse(aip1[1:ell-1]))

    Cin_ref = index_expr(symbol("C",sdim-ell), Cin_args)
    Cout_ref = index_expr(symbol("C",sdim-ell+1), Cout_args)

    result = Expr(:for,
                  :($(alpha_symbs[ell])=0:$(degminalphas(ell-1, deg))),
                  Expr(:block,
                       iloop(ell+1, sdim, q,
                             :($(Cout_ref) += w * $(Cin_ref))),
                       :(w *= r * ($(degminalphas(ell, deg))) 
                         / (1.0 + $(alpha_symbs[ell])))
                       )
                  )

    # this gets rid of the artificial "begin/end" block in the ell=1 case
    if ell > 1
        result = Expr(:for,
                      :($(i_symbs[ell]) = 1:$(q)),
                      Expr(:block,
                           :(xi=qpts[$(i_symbs[ell]),$(sdim-ell+1)]),
                           :(s=1-xi),
                           :(r=xi/s),
                           alphaloop(1, ell-1, deg,
                                     Expr(:block,
                                          :(w=s^$(degminalphas(ell-1, deg))),
                                          result))))

    else
        result = Expr(:for,
                      :($(i_symbs[ell]) = 1:$(q)),
                      Expr(:block,
                           :(xi=qpts[$(i_symbs[ell]),$(sdim-ell+1)]),
                           :(s=1-xi),
                           :(r=xi/s),
                           :(w=s^$(degminalphas(ell-1, deg))),
                           result))
    end

    return result
   
end

function make_evaluator(sdim, qpts, pdeg)
    # TODO: special case for 1d...
    qdeg = size(qpts, 1)

    alpha_symbs = [symbol("alpha",i) for i=1:sdim]
    aip1 = [:($(a)+1) for a in alpha_symbs]
    i_symbs = [symbol("i",i) for i=1:sdim]
    Ci = [symbol("C", i) for i=0:sdim]

    inside_impl = Expr(:block)

    initializeCs = [:($(Ci[i+1]) *= 0.0) for i=1:sdim]

    for initC in initializeCs
        push!(inside_impl.args, initC)
    end

    C0ref = index_expr(:C0, reverse(aip1))

    setC0 = alphaloop(1, sdim, pdeg,
                      Expr(:block,
                           :($(C0ref) = coeffs[cur]),
                           :(cur += 1)))

    push!(inside_impl.args, :(cur=1))
    push!(inside_impl.args, setC0)

    for ell=sdim:-1:1
        push!(inside_impl.args, eval_step_impl(sdim, ell, pdeg, qdeg))
    end

    # write from last C to result
    push!(inside_impl.args, :(cur=1))
    result_src = index_expr(symbol("C",sdim),
                            reverse(i_symbs))
    push!(inside_impl.args,
          iloop(1,sdim, qdeg,
                Expr(:block,
                     :(result[cur] = $(result_src)),
                     :(cur += 1))))

    eval_func = Expr(:function,
                     :(evaluate(coeffs, result)),
                     inside_impl)

    # enclose this inside a function that initializes the C
    # values

    maker_body = Expr(:block)

    # initialize the C arrays
    for i=0:sdim
        Ci = symbol("C", i)
        zs = Expr(:call,
                  :zeros)
        for j=1:i
            push!(zs.args, qdeg)
        end
        for j=i+1:sdim
            push!(zs.args, pdeg+1)
        end
        push!(maker_body.args, :($(Ci) = $(zs)))
    end

    push!(maker_body.args, eval_func)
    push!(maker_body.args, :(return evaluate))

    maker = Expr(:function,
                 :(make(qpts)),
                 maker_body)

    println(maker)

    maker_f = eval(maker)
    return maker_f(qpts)
                     
end


function make_evaluator(sdim, qpts, pdeg)
    # TODO: special case for 1d...
    qdeg = size(qpts, 1)

    alpha_symbs = [symbol("alpha",i) for i=1:sdim]
    aip1 = [:($(a)+1) for a in alpha_symbs]
    i_symbs = [symbol("i",i) for i=1:sdim]
    Ci = [symbol("C", i) for i=0:sdim]

    inside_impl = Expr(:block)

    initializeCs = [:($(Ci[i+1]) *= 0.0) for i=1:sdim]

    for initC in initializeCs
        push!(inside_impl.args, initC)
    end

    C0ref = index_expr(:C0, reverse(aip1))

    setC0 = alphaloop(1, sdim, pdeg,
                      Expr(:block,
                           :($(C0ref) = coeffs[cur]),
                           :(cur += 1)))

    push!(inside_impl.args, :(cur=1))
    push!(inside_impl.args, setC0)

    for ell=sdim:-1:1
        push!(inside_impl.args, eval_step_impl(sdim, ell, pdeg, qdeg))
    end

    # write from last C to result
    push!(inside_impl.args, :(cur=1))
    result_src = index_expr(symbol("C",sdim),
                            reverse(i_symbs))
    push!(inside_impl.args,
          iloop(1,sdim, qdeg,
                Expr(:block,
                     :(result[cur] = $(result_src)),
                     :(cur += 1))))

    eval_func = Expr(:function,
                     :(evaluate(coeffs, result)),
                     inside_impl)

    # enclose this inside a function that initializes the C
    # values

    maker_body = Expr(:block)

    # initialize the C arrays
    for i=0:sdim
        Ci = symbol("C", i)
        zs = Expr(:call,
                  :zeros)
        for j=1:i
            push!(zs.args, qdeg)
        end
        for j=i+1:sdim
            push!(zs.args, pdeg+1)
        end
        push!(maker_body.args, :($(Ci) = $(zs)))
    end

    push!(maker_body.args, eval_func)
    push!(maker_body.args, :(return evaluate))

    maker = Expr(:function,
                 :(make(qpts)),
                 maker_body)

    println(maker)

    maker_f = eval(maker)
    return maker_f(qpts)
                     
end


function moment_step_impl(sdim, ell, deg, q)
    alpha_symbs = [symbol("alpha",i) for i=1:sdim]
    i_symbs = [symbol("i",i) for i=1:sdim]

    aip1 = [:($(a)+1) for a in alpha_symbs]

    # build innermost loop nest
    Fin_args = vcat(reverse(aip1[1:ell-1]),
                    reverse(i_symbs[ell:sdim]))
                    
    Fout_args = vcat(reverse(i_symbs[ell+1:sdim]),
                     reverse(aip1[1:ell]))

    Fin_ref = index_expr(symbol("F",sdim-ell), Fin_args)
    Fout_ref = index_expr(symbol("F",sdim-ell+1), Fout_args)

    result = Expr(:for,
                  :($(alpha_symbs[ell])=0:$(degminalphas(ell-1, deg))),
                  Expr(:block,
                       iloop(ell+1, sdim, q,
                             :($(Fout_ref) += w * $(Fin_ref))),
                       :(w *= r * ($(degminalphas(ell, deg))) 
                         / (1.0 + $(alpha_symbs[ell])))
                       )
                  )

    # this gets rid of the artificial "begin/end" block in the ell=1 case
    if ell > 1
        result = Expr(:for,
                      :($(i_symbs[ell]) = 1:$(q)),
                      Expr(:block,
                           :(xi=qpts[$(i_symbs[ell]),$(sdim-ell+1)]),
                           :(omega = qwts[$(i_symbs[ell]),$(sdim-ell+1)]),
                           :(s=1-xi),
                           :(r=xi/s),
                           alphaloop(1, ell-1, deg,
                                     Expr(:block,
                                          :(w=omega * s^$(degminalphas(ell-1, deg))),
                                          result))))

    else
        result = Expr(:for,
                      :($(i_symbs[ell]) = 1:$(q)),
                      Expr(:block,
                           :(xi=qpts[$(i_symbs[ell]),$(sdim-ell+1)]),
                           :(omega = qwts[$(i_symbs[ell]),$(sdim-ell+1)]),
                           :(s=1-xi),
                           :(r=xi/s),
                           :(w=omega * s^$(degminalphas(ell-1, deg))),
                           result))
    end

    return result

end

# TODO: reverse storage order for integration back to what
# Ainswort et al have so that we have stride-1 access.
# TODO: Check sizes of arrays.
function make_integrator(sdim, qpts, qwts, pdeg)
    # TODO: special case for 1d...
    qdeg = size(qpts, 1)

    alpha_symbs = [symbol("alpha",i) for i=1:sdim]
    aip1 = [:($(a)+1) for a in alpha_symbs]
    i_symbs = [symbol("i",i) for i=1:sdim]

    Fi = [symbol("F", i) for i=0:sdim]

    inside_impl = Expr(:block)

    initializeFs = [:($(Fi[i+1]) *= 0.0) for i=1:sdim]

    for initF in initializeFs
        push!(inside_impl.args, initF)
    end

    F0ref = index_expr(:F0, reverse(i_symbs))

    setF0 = iloop(1, sdim, qdeg,
                  Expr(:block,
                       :($(F0ref) = vals[cur]),
                       :(cur += 1)))
                  
    push!(inside_impl.args, :(cur=1))
    push!(inside_impl.args, setF0)

    for ell=1:sdim
        push!(inside_impl.args, moment_step_impl(sdim, ell, pdeg, qdeg))
    end

    # write from last F to result
    push!(inside_impl.args, :(cur=1))
    result_src = index_expr(symbol("F",sdim),
                            reverse(aip1))
    push!(inside_impl.args,
          alphaloop(1,sdim, pdeg,
                    Expr(:block,
                         :(result[cur] = $(result_src)),
                         :(cur += 1))))

    eval_func = Expr(:function,
                     :(integrate(vals, result)),
                     inside_impl)

    # enclose this inside a function that initializes the F
    # values

    maker_body = Expr(:block)

    # initialize the F arrays
    for i=0:sdim
        Fi = symbol("F", i)
        zs = Expr(:call,
                  :zeros)
        for j=1:i
            push!(zs.args, qdeg)
        end
        for j=i+1:sdim
            push!(zs.args, pdeg+1)
        end
        push!(maker_body.args, :($(Fi) = $(zs)))
    end

    push!(maker_body.args, eval_func)
    push!(maker_body.args, :(return integrate))

    maker = Expr(:function,
                 :(make(qpts, qwts)),
                 maker_body)

    println(maker)

    maker_f = eval(maker)
    return maker_f(qpts, qwts)
                     
end
