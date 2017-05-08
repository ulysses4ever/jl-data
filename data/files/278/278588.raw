using NLopt
using Debug
using Base.LinAlg.BLAS

function randiv(n::Int64        = 100;
                m::Int64        = 5,
                k::Int64        = 1,
                theta0::Float64 = 0.0,
                rho::Float64    = 0.9,
                CP::Int64       = 10)

    tau     = fill(sqrt(CP/(m*n)), m)
    z       = randn(n, m)
    vi      = randn(n, 1)
    eta     = randn(n, 1)
    epsilon = rho*eta+sqrt(1-rho^2)*vi
    x       = z*tau + eta
    if k>1
        x = [x  randn(n, k-1)]
    end
    y       = x[:,1]*theta0 + epsilon
    return y, x, z
end



type Gel
    innerobj::Function
    outerobj::Function
    innergrd::Function
    outergrd::Function
    gelweights::Function
    divergence::Function
    loglik::Function    
end


function et()
    function innerobj(z, lambda0, w = [])
        if length(w)==0
             2.0*sum(expm1(z) - lambda0)
        else
            2.0*sum(w.*expm1(z)-lambda0)
        end
    end

    function outerobj(z, lambda0, w = [])
        if length(w)==0
             2.0*sum(expm1(z) - lambda0)
        else
            2.0*sum(w.*expm1(z)-lambda0)
        end
    end

    function gelweights(z)
        exp(z)
    end

    function innergrd(g, z) 
        p = exp(z)
        grd_1 = 2.0*(sum(p)-1)
        grd_2 = 2.0*sum(p.*g, 1)
        grd = [grd_1 grd_2]
    end
    
    function outergrd(lambda, Dg::Array{Float64,2})
        2.0*lambda[2:end]'*Dg
    end

    function divergence(p, w = [])
        if length(w)==0
            u = p
        else
            u = p/w
            u.*log-u+1
        end
    end

    function loglik(z)
        sum(exp(z))
    end

    Gel(innerobj,
        outerobj,
        innergrd,
        outergrd,
        gelweights,
        divergence,
        loglik)

end


function estgel(theta::Vector, momfun::Function, dmomfun::Function,
                inneropt::NLopt.Opt, outeropt::NLopt.Opt, gel::Gel=et())
    g =
        try
            momfun(theta)
        catch
            error("momfun is not evaluable")
        end

    k = size(theta,1)
    m = size(g, 2)
    n = size(g, 1)

    Dg =
        try
            dmomfun(theta, fill(1/n, n))
        catch
            error("dmomfun is not evaluable")
        end

    if (m, k) != size(Dg)
        error("dmomfun is not (m,k)")
    end

    gel_sol = outer(theta, momfun, dmomfun, inneropt, outeropt, gel)
    
            
end



function outer(theta::Vector, momfun::Function, dmomfun::Function,
               inneropt::NLopt.Opt, outeropt::NLopt.Opt, gel::Gel)
    outerobj = gel.outerobj
    outergrd = gel.outergrd
    gelweights = gel.gelweights
    function obj(theta::Vector, grad::Vector = [])
        #print("I am inside outer. theta: $theta\n")
        g = momfun(theta)
        sol = inner(g, inneropt, gel)        
        if (sol[3]==1)
            lambda = sol[1]
            z_ = lambda[1] + g*lambda[2:end]
            if length(grad)>0
                Dg = dmomfun(theta, gelweights(z_))
                grad[:] = outergrd(lambda, Dg)
            end
            return outerobj(z_, lambda[1])
        else
            if length(grad)>0
                grad[:] = fill(1e+08, size(theta,1))
            end
        end
        return -1.340781e+154
    end
    ##print("I am here\n")

    opt = outeropt
    NLopt.max_objective!(opt, obj)
    
    sol_outer =
        try
            NLopt.optimize(opt, theta)
        catch
            ([], [], 0)
        end
    ##print("And now I am here\n")
    if sol_outer[3]==0
        return(sol_outer)
    else
        theta = sol_outer[2]
        sol_inner = inner(momfun(theta), inneropt, gel)
        test = sol_inner[3]==1
        test ? (convergence = 1) : (convergence=0)
        return (theta, sol_inner[1], -sol_inner[2], convergence)
    end
end

function inner(g, inneropt::NLopt.Opt, gel::Gel)
    innerobj = gel.innerobj
    function obj(lambda::Vector, grad::Vector)
        ##print("I am inside obj. lambda: $lambda\n")
        z_ = lambda[1]+g*lambda[2:end]
        if length(grad)>0
            p = exp(z_)    
            grad[1] = 2.0*(sum(p)-length(z_))
            grad[2:end] = 2.0*sum(p.*g, 1)
        end
        innerobj(z_, lambda[1])
        #print("\n The objective was: $out\n")
        #return(out)
    end
    n = size(g, 1)
    m = size(g, 2)
    lambda0 = fill(0.0, m+1)
    lambda0[2:end] = gemm('T', 'N', 1.0, g, g)\(-sum(g, 1)')[:,1]
    lambda0[1] = log(n/sum(exp(g*lambda0[2:end])))

    opt = inneropt
    NLopt.min_objective!(opt, obj)
    NLopt.lower_bounds!(opt, fill(-Inf, m+1))
    NLopt.upper_bounds!(opt, fill(+Inf, m+1))
    
    sol = try
        NLopt.optimize(opt, lambda0)
    catch
        ([], fill(0, m+1), 0)
    end

    lambda = sol[2]
    
    if typeof(sol[3])==Symbol
        z_ = lambda[1]+g*lambda[2:end]
        w = exp(z_)
        divergence = -2.0*sum(w.*log(w)-w+1)
        test =  (sol[1]-divergence<eps()^.5) 
        test ? (convergence = 1) : (convergence = 0)
    else
        convergence = 0
    end
    
    return(lambda, sol[1], convergence)    
end


y,x,z = randiv(200);
inneropt_ = NLopt.Opt(:LD_TNEWTON_PRECOND_RESTART, 5+1);
outeropt_ = NLopt.Opt(:LD_TNEWTON_PRECOND_RESTART, 1);

function momfun_(theta::Vector)
    z.*(y-x*theta)
end

function dmomfun_(theta::Vector, w::Vector)
    gemm('T', 'N', 1.0, w.*z, -x)
end

function dmomfun_(theta::Vector)
    gemm('T', 'N', 1.0, z, -x)
end

theta_init = [.02];

et_est = estgel(theta_init, momfun_, dmomfun_, inneropt_, outeropt_)
