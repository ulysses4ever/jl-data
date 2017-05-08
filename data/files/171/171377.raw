# let's take another look at the stroud evaluation.
# can we make it cleaner and closer to Ainsworth's paper?

function degminalphas(ell)
    result = :deg
    for i=1:ell
        ai = symbol("alpha",i)
        result = :($(result) - $(ai))
    end
    return result
end

function alphaloop(alphamin, alphamax, body)
    result = body
    for i=alphamax:-1:alphamin
        ai = symbol("alpha", i)
        result = Expr(:for,
                      :($(ai)=0:$(degminalphas(i-1))),
                      result)
    end
    return result
end

function iloop(imin, imax, body)
    result = body
    for i=imax:-1:imin
        ii = symbol("i",i)
        result = Expr(:for,
                      :(($ii)=1:q),
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

function eval_step_impl(sdim, ell)
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
                  :($(alpha_symbs[ell])=0:$(degminalphas(ell-1))),
                  Expr(:block,
                       iloop(ell+1, sdim,
                             :($(Cout_ref) += w * $(Cin_ref))),
                       :(w *= r * ($(degminalphas(ell))) 
                         / (1.0 + $(alpha_symbs[ell])))
                       )
                  )

    # this gets rid of the artificial "begin/end" block in the ell=1 case
    if ell > 1
        result = Expr(:for,
                      :($(i_symbs[ell]) = 1:q),
                      Expr(:block,
                           :(xi=qpts[$(i_symbs[ell]),$(sdim-ell+1)]),
                           :(s=1-xi),
                           :(r=xi/s),
                           alphaloop(1, ell-1,
                                     Expr(:block,
                                          :(w=s^$(degminalphas(ell-1))),
                                          result))))

    else
        result = Expr(:for,
                      :($(i_symbs[ell]) = 1:q),
                      Expr(:block,
                           :(xi=qpts[$(i_symbs[ell]),$(sdim-ell+1)]),
                           :(s=1-xi),
                           :(r=xi/s),
                           :(w=s^$(degminalphas(ell-1))),
                           result))
    end

    return result
   
end

function make_evaluation_constructor(sdim)
    # TODO: special case for 1d

    alpha_symbs = [symbol("alpha",i) for i=1:sdim]
    aip1 = [:($(a)+1) for a in alpha_symbs]

    i_symbs = [symbol("i",i) for i=1:sdim]

    C0ref = index_expr(:C0, reverse(aip1))

    setC0 = alphaloop(1, sdim,
                      Expr(:block,
                           :($(C0ref) = coeffs[cur]),
                           :(cur += 1)))
    inside_impl = Expr(:block,
                       :(cur=1),
                       setC0)

    initializeCs = [:($(symbol("C",i)) *= 0.0) for i=1:sdim]

    for initC in initializeCs
        push!(inside_impl.args, initC)
    end

    for ell=sdim:-1:1
        push!(inside_impl.args, eval_step_impl(sdim, ell))
    end

    # write from last C to result
    push!(inside_impl.args, :(cur=1))
    result_src = index_expr(symbol("C",sdim),
                            reverse(i_symbs))
    push!(inside_impl.args,
          iloop(1,sdim,
                Expr(:block,
                     :(result[cur] = $(result_src)),
                     :(cur += 1))))

    eval_func = Expr(:function,
                     :(evaluate(coeffs, result)),
                     inside_impl)
    

    make_eval_body = Expr(:block)

    push!(make_eval_body.args, :(q=size(qpts,1)))

    for i=0:sdim
        Ci = symbol("C",i)
        Ciinit = Expr(:call,
                      :zeros)
        for j=1:i
            push!(Ciinit.args, :q)
        end
        for j=i+1:sdim
            push!(Ciinit.args, :(deg+1))
        end
        push!(make_eval_body.args, :($(Ci) = $(Ciinit)))
    end

    push!(make_eval_body.args, eval_func)
    push!(make_eval_body.args, :(return evaluate))

    println(make_eval_body)

    return eval(:( (deg, qpts) -> $(make_eval_body)))

    
    return result
                     

end

