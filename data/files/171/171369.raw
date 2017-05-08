# Let's make the stroud stuff @generated.

function stroud_eval1d(deg, coeffs, result, qpts)
    nqp1d = size(qpts, 1)
    for i=1:nqp1d
        result[i] = 0.0
        xi = qpts[i, 1]
        s = 1-xi
        r = xi / s
        w = s^deg
        for alpha=0:deg
            result[i] += w * coeffs[alpha+1]
            w *= r * (deg-alpha) / (alpha+1.0)
        end
    end
    return
end


function stroud_eval2d(deg, coeffs, result, qpts)
    nqp1d = size(qpts, 1)
    result[:] = 0.0
    tmp = zeros(nqp1d, deg+1)
    for i2=1:nqp1d
        xi = qpts[i2, 2]
        s = 1 - xi
        r = xi / s
        for alpha1=0:deg
            w = s^(deg-alpha1)
            aind = polydim(2,deg) - polydim(2, deg-alpha1) + 1
            for alpha2=0:deg-alpha1
                tmp[i2, alpha1+1] += w * coeffs[aind+alpha2]
                w = w * r * (deg-alpha1-alpha2) / (1.0 + alpha2)
            end
        end
    end
    for i1=1:nqp1d
        xi = qpts[i1, 1]
        s = 1-xi
        r = xi / s
        w = s^deg
        for alpha1=0:deg
            for i2=1:nqp1d
                result[(i1-1)*nqp1d + i2] += w*tmp[i2, alpha1+1]
            end
            w = w * r * (deg-alpha1) / (1. + alpha1)
        end
    end
    
    return
end

val2val{d}(::Type{Val{d}}) = d

@generated function stroud_eval{sdim}(::Type{Val{sdim}}, deg, coeffs, result, qpts)
    return stroud_eval_impl(Val{sdim}, deg, coeffs, result, qpts)
end

function make_stroud_eval_constructor(sd)
    # return sdim = 1 code as a special case
    if sd == 1
        function makeit(deg, qpts)
            function doit(coeffs, result)
                nqp1d = size(qpts, 1)
                for i=1:nqp1d
                    result[i] = 0.0
                    xi = qpts[i, 1]
                    s = 1-xi
                    r = xi / s
                    w = s^deg
                    for alpha=0:deg
                        result[i] += w * coeffs[alpha+1]
                        w *= r * (deg-alpha) / (alpha+1.0)
                    end
                end
                return
            end
            return doit
        end
        return makeit
    else # sd >= 2
        # first we have to generate the function body.
        ai = [symbol("alpha",i) for i=1:sd]
        ii = [symbol("i",i) for i=1:sd]

        degminalphas = Dict()
        degminalphas[0] = :deg
        for i=1:sd
            degminalphas[i] = :($(degminalphas[i-1]) - $(ai[i]))
        end

        # work on the first stage, which is different since it
        # reads from the input

        tmp_inds = vcat([:($(ii[sd]))],
                        [:($(ai[i])+1) for i=(sd-1):-1:1],
                        [:1])
        tmp_ref = Expr(:ref,
                       :tmp)

        for ti in tmp_inds 
            push!(tmp_ref.args, ti)
        end

        first_stage = Expr(:for,
                           :($(ai[sd])=0:$(degminalphas[sd-1])),
                           Expr(:block,
                                :($(tmp_ref) += w*coeffs[aind+$(ai[sd])]),
                                :(w = w * r * $(degminalphas[sd]) / (1.0 + $(ai[sd])))))

        aind = :(binomial($(sd)+deg, $(sd)) - binomial($(sd)+deg-alpha1, $(sd)))
        for i=(sd-1):-1:2
            aind = :($(aind) + binomial($(i)+ $(degminalphas[sd-i]),$(i)) 
                     - binomial($(i)+ $(degminalphas[sd-i+1]), $(i)))
        end
        aind = :($(aind)+1)
        first_stage = Expr(:block,
                           :(aind = $(aind)),
                           :(w=s^($(degminalphas[sd-1]))),
                           first_stage)



        for i=(sd-1):-1:1
            first_stage = Expr(:for,
                               :($(ai[i])=0:$(degminalphas[i-1])),
                               first_stage)
        end

        first_stage = Expr(:for,
                           :($(ii[sd])=1:nqp1d),
                           Expr(:block,
                                :(xi=qpts[$(ii[sd]), $(sd)]),
                                :(s=1-xi),
                                :(r=xi/s),
                                first_stage))


        # middle stages:
        # on stage k, we have k-1 innermost i loops over last i variables
        # tucked inside of (sd-k+1) alpha loops
        # tucked inside of a loop over ik

        middle_stages = []
        
        for k=2:(sd-1)
            # start wth write location for tmp
            iinds = [:($(ii[sd-i+1])) for i=1:k]
            ainds = [:($(ai[i])+1) for i=(sd-k):-1:1]
            tmp_inds = vcat(iinds, ainds, [:($k)])
            tmp_write_ref = Expr(:ref,
                                 :tmp)
            
            for ti in tmp_inds 
                push!(tmp_write_ref.args, ti)
            end
            
            # read location for tmp
            iinds = [:($(ii[sd-i+1])) for i=1:(k-1)]
            ainds = [:($(ai[i])+1) for i=(sd-k+1):-1:1]
            tmp_inds = vcat(iinds, ainds, [:($(k-1))])
            tmp_read_ref = Expr(:ref,
                                :tmp)
            
            for ti in tmp_inds 
                push!(tmp_read_ref.args, ti)
            end
            
            ms = :($(tmp_write_ref) += w * $(tmp_read_ref))

            # wrap ms into the i loops
            for i=1:(k-1)
                ms = Expr(:for,
                          :($(ii[sd-i+1])=1:nqp1d),
                          ms)
            end

            # the innermost alpha is sd - k + 1
            j = sd - k 
            ms = Expr(:for,
                      :($(ai[j+1])=0:$(degminalphas[j])),
                      Expr(:block,
                           ms,
                           :(w=w*r*($(degminalphas[j+1])) / (1.0+$(ai[j+1])))))

            ms = Expr(:block,
                      :(w=s^($(degminalphas[j]))),
                      ms)
            
            for i=k-1:-1:1
                ms = Expr(:for,
                          :($(ai[i])=0: $(degminalphas[i-1])),
                          ms)
            end
            
            ms = Expr(:for,
                      :($(ii[sd-k+1])=1:nqp1d),
                      Expr(:block,
                           :(xi=qpts[$(ii[sd-k+1]), $(sd-k+1)]),
                           :(s=1-xi),
                           :(r=xi/s),
                           ms)
                      )

            push!(middle_stages, ms)
            
        end

        # last stage is different because we're writing into the result
        # we have an outer loop over i1
        write_idx = :($(ii[sd]))
        for i=(sd-1):-1:1
            write_idx = :(($(ii[i])-1)*nqp1d^($(sd-i)) + $(write_idx))
        end
        
        tmp_idx = Expr(:ref, 
                       :tmp)
        for i=sd:(-1):2
            push!(tmp_idx.args, :($(ii[i])))
        end
        push!(tmp_idx.args, :(alpha1+1))
        push!(tmp_idx.args, :($(sd-1)))
                       
        last_stage = Expr(:+=,
                          Expr(:ref,
                               :result,
                               write_idx),
                          :(w * $(tmp_idx)))

        for i=sd:-1:2
            last_stage = Expr(:for,
                              :($(ii[i])=1:nqp1d),
                              last_stage)
        end

        last_stage = Expr(:for,
                          :(i1=1:nqp1d),
                          Expr(:block,
                               :(xi=qpts[i1,1]),
                               :(s=1-xi),
                               :(r=xi/s),
                               :(w=s^deg),
                               Expr(:for,
                                    :(alpha1=0:deg),
                                    Expr(:block,
                                         last_stage,
                                         :(w=w*r*(deg-alpha1)/(1.+alpha1))))))

        make_tmp = Expr(:call, :zeros)
        push!(make_tmp.args, :nqp1d)
        for i=1:sd-1
           push!(make_tmp.args, :(deg+1))
        end
        push!(make_tmp.args, sd-1)

        doit_func = Expr(:function,
                         :(doit(coeffs, result)))

        doit_func_body = Expr(:block)

        push!(doit_func_body.args,
              :(for i=1:length(result) result[i] = 0.0 end))
        push!(doit_func_body.args,
              first_stage)
        for ms in middle_stages
            push!(doit_func_body.args, ms)
        end
        push!(doit_func_body.args, last_stage)

        push!(doit_func.args, doit_func_body)


        func_impl = quote
            function makeit(deg, qpts)
                nqp1d = size(qpts, 1)
                tmp = $(make_tmp)
                $(doit_func)
                return doit
            end
        end

        println(func_impl)

        return eval(func_impl)
end

end

